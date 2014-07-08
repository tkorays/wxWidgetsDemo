#pragma   warning(disable:4996) 
#include <opencv2/opencv.hpp>
#include <cv_link_all.h>
using namespace cv;

extern "C"{
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
}


int main() {
	av_register_all();
	avformat_network_init();

	AVFormatContext* pFormatCtx = avformat_alloc_context();
	const char* fn = "192.168.1.1";
	
	if (avformat_open_input(&pFormatCtx,fn,NULL,NULL) != 0) {
		printf("format contex error!\n");
		return -1;
	}
	if (avformat_find_stream_info(pFormatCtx,NULL) < 0) {
		printf("no info!\n");
		return -1;
	}

	int i, videoIndex = -1;
	AVCodecContext* pCodecCtx;
	for ( i = 0; i < pFormatCtx->nb_streams; i++) {
		if (pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO) {
			videoIndex = i;
			break;
		}
	}
	if (videoIndex==-1) {
		printf("no video stream!\n");
		return -1;
	}

	pCodecCtx = pFormatCtx->streams[videoIndex]->codec;

	AVCodec* pCodec = NULL;
	pCodec = avcodec_find_decoder(AV_CODEC_ID_H264/*pCodecCtx->codec_id*/);
	if (pCodec == NULL) {
		printf("codec not found!\n");
		return -1;
	}

	if (avcodec_open2(pCodecCtx,pCodec,NULL)<0) {
		printf("could not open codec\n");
		return -1;
	}
	AVFrame* pFrame, *pFrameYUV;
	pFrame = av_frame_alloc();
	pFrameYUV = av_frame_alloc();

	uint8_t* out_buffer = new uint8_t[avpicture_get_size(PIX_FMT_RGB24, pCodecCtx->width, pCodecCtx->height)];
	AVPacket* packet = (AVPacket*)malloc(sizeof(AVPacket));
	av_new_packet(packet, pCodecCtx->width*pCodecCtx->height);
	avpicture_fill((AVPicture *)pFrameYUV, out_buffer, PIX_FMT_RGB24, pCodecCtx->width, pCodecCtx->height);
	


	static struct SwsContext *img_convert_ctx;
	int ret,got_picture;

	namedWindow("img");
	Mat img(pCodecCtx->height, pCodecCtx->width, CV_8UC3);

	
	
	while (av_read_frame(pFormatCtx,packet)>=0) {
		if (packet->stream_index == videoIndex) {
			ret = avcodec_decode_video2(pCodecCtx, pFrame, &got_picture,packet);
			if (ret<0) {
				printf("error!\n");
				return -1;
			}
			
			
			
			if (got_picture) {
				img_convert_ctx = sws_getContext(pCodecCtx->width, pCodecCtx->height, pCodecCtx->pix_fmt, pCodecCtx->width, pCodecCtx->height, PIX_FMT_RGB24, SWS_BICUBIC, NULL, NULL, NULL);
				sws_scale(img_convert_ctx, (const uint8_t* const*)pFrame->data, pFrame->linesize, 0, pCodecCtx->height, pFrameYUV->data, pFrameYUV->linesize);
				sws_freeContext(img_convert_ctx);
				uchar* dt = (uchar*)(pFrameYUV->data[0]);
				img.data = dt;
				imshow("img", img);
				waitKey(33);
			}
		}
		av_free_packet(packet);
	}
	return 0;
}