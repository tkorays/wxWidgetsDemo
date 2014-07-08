#ifndef _TK_H264DECODER_H_
#define _TK_H264DECODER_H_
extern "C"{
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
}

#define INBUF_SIZE 4096*500
#define AUDIO_INBUF_SIZE 20480
#define AUDIO_REFILL_THRESH 4096
#define IO_BUF_SIZE 32378
#define FRAME_BUF_SIZE 691200+100


typedef unsigned char uchar;
//typedef unsigned char uint8_t;
//
//struct AVFormatContext;
//struct AVCodecContext;
//struct AVIOContext;
//struct AVCodec;
//struct AVFrame;
//struct AVPacket;

static struct SwsContext *img_convert_ctx;

namespace whu {
	class H264Decoder {
	private:
		AVFormatContext* pFormatCtx;
		AVCodecContext* pCodecCtx;
		AVIOContext* pIOCtx;
		AVInputFormat* pInputFmt;
		AVCodec* pCodec;
		AVFrame* pFrame;
		AVFrame* pFrameYUV;
		AVPacket packet;
		

		uint8_t* buffer;
		uint8_t* io_buffer;

		int videoIndex;
		int got_picture;
	public:
		H264Decoder();
		void process(void* data,int size,void(*callback)(void*p));
	};
}

#endif // _TK_H264DECODER_H_