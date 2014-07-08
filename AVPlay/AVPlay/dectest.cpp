


#include <opencv2/opencv.hpp>
#include <cv_link_all.h>
using namespace cv;

#include "H264Decoder.h"
using namespace whu;


Mat img(360, 640, CV_8UC3);

void showImg(void* p) {
	
	img.data = (uchar*)p;
	imshow("img", img);
}

int main() {
	H264Decoder h264dc;
	uint8_t inbuf[32768];
	//uint8_t* inbuf[40960];
	//memset(inbuf, 0, 40960);
	FILE* file = NULL;
	file = fopen("test.h264", "rb");
	if (!file) {
		printf("open video error!\n");
		return 0;
	}
	int size;
	namedWindow("img");

	size = fread(inbuf, 1, 32768, file);
		
	h264dc.process(inbuf, size, showImg);
	fclose(file);
	return 0;
}