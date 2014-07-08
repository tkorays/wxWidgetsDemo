#ifndef __IH264DECODER_H
#define __IH264DECODER_H

#ifdef  _H264DECODER_EXPORTS
#define H264DECODER_API __declspec(dllexport)
#else
#define H264DECODER_API __declspec(dllimport)
#endif
#define PLAYHANDLE void *
#ifdef __cplusplus
extern "C" {  
#endif

	typedef int (CALLBACK *LPCALLYUVData)(int decHandle, unsigned char* pYUVData, unsigned long lSize, unsigned long dwWidth,unsigned long dwHeight, void* lpUser);

	H264DECODER_API int FAR PASCAL H264Decoder_Init();
	H264DECODER_API int FAR PASCAL H264Decoder_Open();
	H264DECODER_API int FAR PASCAL H264Decoder_Close(int nDecHandle);
	H264DECODER_API int FAR PASCAL H264Decoder_SetYuvCallback(int nDecHandle,LPCALLYUVData pCallBack,DWORD dwContext);
	H264DECODER_API int FAR PASCAL H264Decoder_InputData(int nDecHandle,void* pBuf,DWORD dwDataLen);
	H264DECODER_API int FAR PASCAL H264Decoder_Fini();

#ifdef __cplusplus
} 

#endif

#endif  // __IH264DECODER_H