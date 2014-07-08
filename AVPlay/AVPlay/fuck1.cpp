#include <opencv2/opencv.hpp>
#include <cv_link_all.h>

using namespace cv;
extern "C"{
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavformat/avio.h>
#include <libswscale/swscale.h>
#include <libavutil/file.h>
}
struct buffer_data {
	uint8_t *ptr;
	size_t size; ///< size left in the buffer
};

static int read_packet(void *opaque, uint8_t *buf, int buf_size)
{
	struct buffer_data *bd = (struct buffer_data *)opaque;
	buf_size = FFMIN(buf_size, bd->size);

	//printf("ptr:%p size:%zu\n", bd->ptr, bd->size);

	/* copy internal buffer data to buf */
	memcpy(buf, bd->ptr, buf_size);
	bd->ptr += buf_size;
	bd->size -= buf_size;

	return buf_size;
}

int main(int argc, char *argv[])
{
	AVFormatContext *fmt_ctx = NULL;
	AVIOContext *avio_ctx = NULL;
	uint8_t *buffer = NULL, *avio_ctx_buffer = NULL;
	size_t buffer_size, avio_ctx_buffer_size = 4096;
	char *input_filename = NULL;
	int ret = 0;
	struct buffer_data bd = { 0 };

	
	input_filename = "test.h264";

	/* register codecs and formats and other lavf/lavc components*/
	av_register_all();

	/* slurp file content into buffer */
	//ret = av_file_map(input_filename, &buffer, &buffer_size, 0, NULL);
	FILE* f = fopen(input_filename, "rb");
	buffer = new uint8_t[272700];
	buffer_size = fread(buffer, 1, 272700, f);
	ret = 1;
	if (ret < 0)
		//goto end;
		return 0;

	/* fill opaque structure used by the AVIOContext read callback */
	bd.ptr = buffer;
	bd.size = buffer_size;

	if (!(fmt_ctx = avformat_alloc_context())) {
		ret = AVERROR(ENOMEM);
		//goto end;
		return 0;
	}

	avio_ctx_buffer = (uint8_t*)av_malloc(avio_ctx_buffer_size);
	if (!avio_ctx_buffer) {
		ret = AVERROR(ENOMEM);
		//goto end;
		return 0;
	}
	avio_ctx = avio_alloc_context(avio_ctx_buffer, avio_ctx_buffer_size,
		0, &bd, &read_packet, NULL, NULL);
	if (!avio_ctx) {
		ret = AVERROR(ENOMEM);
		//goto end;
		return 0;
	}
	fmt_ctx->pb = avio_ctx;

	ret = avformat_open_input(&fmt_ctx, NULL, NULL, NULL);
	if (ret < 0) {
		fprintf(stderr, "Could not open input\n");
		//goto end;
		return 0;
	}

	ret = avformat_find_stream_info(fmt_ctx, NULL);
	if (ret < 0) {
		fprintf(stderr, "Could not find stream information\n");
		//goto end;
		return 0;
	}

	av_dump_format(fmt_ctx, 0, input_filename, 0);
	AVCodecContext* pCodecCtx;
	AVCodec* pCodec;
	AVFrame* pFrame;
	AVFrame* pFrameYUV;
	pCodec = avcodec_find_decoder(AV_CODEC_ID_H264);
	//pCodecCtx = avcodec_alloc_context3(pCodec);
	pFrame = av_frame_alloc();
	pFrameYUV = av_frame_alloc();

	pCodecCtx = fmt_ctx->streams[0]->codec;

	uint8_t* out_buffer = new uint8_t[avpicture_get_size(PIX_FMT_RGB24, pCodecCtx->width, pCodecCtx->height)];
	AVPacket* packet = (AVPacket*)malloc(sizeof(AVPacket));
	av_new_packet(packet, pCodecCtx->width*pCodecCtx->height);
	avpicture_fill((AVPicture *)pFrameYUV, out_buffer, PIX_FMT_RGB24, pCodecCtx->width, pCodecCtx->height);

	if (avcodec_open2(pCodecCtx, pCodec, NULL) < 0) {
		printf("could not open codec\n");
	}
	if (pCodec->capabilities&CODEC_CAP_TRUNCATED) {
		pCodecCtx->flags |= CODEC_FLAG_TRUNCATED;
	}
	namedWindow("img");
	int got_picture;
	static struct SwsContext *img_convert_ctx;
	Mat img(pCodecCtx->height, pCodecCtx->width, CV_8UC3);
	while (av_read_frame(fmt_ctx, packet)>=0)
	{
		int len = avcodec_decode_video2(pCodecCtx, pFrame, &got_picture, packet);
		if (len < 0) {
			goto end;
		}
		if (got_picture) {
			printf("size:%d,%d\n", pCodecCtx->width, pCodecCtx->height);
			img_convert_ctx = sws_getContext(pCodecCtx->width, pCodecCtx->height, pCodecCtx->pix_fmt, pCodecCtx->width, pCodecCtx->height, PIX_FMT_RGB24, SWS_BICUBIC, NULL, NULL, NULL);
			sws_scale(img_convert_ctx, (const uint8_t* const*)pFrame->data, pFrame->linesize, 0, pCodecCtx->height, pFrameYUV->data, pFrameYUV->linesize);
			sws_freeContext(img_convert_ctx);
			img.data = (uchar*)(pFrameYUV->data[0]);
			imshow("img", img);
			waitKey(33);
		}
	}
end:
	avformat_close_input(&fmt_ctx);
	/* note: the internal buffer could have changed, and be != avio_ctx_buffer */
	if (avio_ctx) {
		av_freep(&avio_ctx->buffer);
		av_freep(&avio_ctx);
	}
	av_file_unmap(buffer, buffer_size);

	if (ret < 0) {
		return 1;
	}

	return 0;

}