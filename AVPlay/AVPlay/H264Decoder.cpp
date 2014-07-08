#include "H264Decoder.h"
using namespace whu;
#pragma   warning(disable:4996) 
#include <libavutil/file.h>

#include <Windows.h>


struct buffer_data {
	uint8_t *ptr;
	size_t size; ///< size left in the buffer
};

int fill_iobuffer(void * opaque, uint8_t *buf, int buf_size){
	struct buffer_data *bd = (struct buffer_data *)opaque;
	buf_size = FFMIN(buf_size, bd->size);

	printf("ptr:%p size:%zu\n", bd->ptr, bd->size);

	/* copy internal buffer data to buf */
	memcpy(buf, bd->ptr, buf_size);
	bd->ptr += buf_size;
	bd->size -= buf_size;
	return buf_size;
}
H264Decoder::H264Decoder() {
	
	//width = 640;
	//height = 360;
	buffer = new uint8_t[INBUF_SIZE];
	io_buffer = new uint8_t[INBUF_SIZE];
	struct buffer_data bd = { 0 };
	bd.ptr = buffer;
	bd.size = 32768;
	av_register_all();
	av_init_packet(&packet);
	pIOCtx = avio_alloc_context(io_buffer, INBUF_SIZE, 0, buffer, fill_iobuffer, NULL, NULL);
	
	//av_probe_input_buffer(pIOCtx, &pInputFmt, "", NULL, 0, 0);

	pCodec = avcodec_find_decoder(AV_CODEC_ID_H264);
	pFormatCtx = avformat_alloc_context();
	pFormatCtx->pb = pIOCtx;


	pCodecCtx = avcodec_alloc_context3(pCodec);
	pFrame = av_frame_alloc();
	pFrameYUV = av_frame_alloc();
	
	
	

	if (avcodec_open2(pCodecCtx, pCodec, NULL) < 0) {
		printf("could not open codec\n");
	}
	if (pCodec->capabilities&CODEC_CAP_TRUNCATED) {
		pCodecCtx->flags |= CODEC_FLAG_TRUNCATED;
	}
	videoIndex = -1;
	//io_buffer = (uint8_t*)av_malloc(IO_BUF_SIZE);
	//videoIndex = -1;
	/*pCodecCtx = avcodec_alloc_context3(pCodec);
	pCodecCtx->width = 640;
	pCodecCtx->height = 360;
	pCodecCtx->time_base.num = 30;
	pCodecCtx->codec_type = AVMEDIA_TYPE_VIDEO;*/
	
	
}
void H264Decoder::process(void* data, int size, void(*callback)(void*p)) {
	//packet.size = size;
	//packet.data = (uint8_t*)data
	
	//buffer = (uint8_t*)data;
	memcpy(buffer, data, size);
	//av_probe_input_buffer(pIOCtx, &pInputFmt, "", NULL, 0, 2048);
	
	if (avformat_open_input(&pFormatCtx, "", NULL/*pInputFmt*/, NULL) < 0){
		printf("hello...........\n");
	}
	avformat_find_stream_info(pFormatCtx, NULL);
	printf("%d\n",av_read_frame(pFormatCtx, &packet));
	//if (av_find_stream_info(pFormatCtx) < 0){
	//	printf("could no found stream\n");
	//	return;
	//}
	
	
	//av_dump_format(pFormatCtx, 0, "", 0);
	/*
	while (av_read_frame(pFormatCtx, &packet) >= 0)
	{
		while (packet.size > 0){
			int len = avcodec_decode_video2(pCodecCtx, pFrame, &got_picture, &packet);
			if (len < 0) {
				return;
			}
			printf("len:%d\n", len);
			if (got_picture) {
				printf("size:%d,%d\n", pCodecCtx->width, pCodecCtx->height);
				img_convert_ctx = sws_getContext(pCodecCtx->width, pCodecCtx->height, pCodecCtx->pix_fmt, pCodecCtx->width, pCodecCtx->height, PIX_FMT_RGB24, SWS_BICUBIC, NULL, NULL, NULL);
				sws_scale(img_convert_ctx, (const uint8_t* const*)pFrame->data, pFrame->linesize, 0, pCodecCtx->height, pFrameYUV->data, pFrameYUV->linesize);
				sws_freeContext(img_convert_ctx);
				data = (uchar*)(pFrameYUV->data[0]);
				if (callback) {
					callback(data);
				}

			}

			packet.size -= len;
			packet.data += len;

		}
	}
	packet.data = NULL;
	packet.size = 0;
	*/

}