#include <vfw.h>

__declspec(dllexport)   void __stdcall  MV_AVIFileInit(DWORD filetype,short framerate);
__declspec(dllexport)   void __stdcall  MV_AVIFileFini();
__declspec(dllexport)   BOOL __stdcall  MV_AVIFileOpen(int index,LPCTSTR lpszFileName, LPBITMAPINFO alpb, WORD wSkipRate);
__declspec(dllexport)   BOOL __stdcall  MV_AVIFileAddFrame(int index, LPBITMAPINFO alpb, LPBYTE alpImageBits );
__declspec(dllexport)   BOOL __stdcall  MV_AVIFileVertFlipBuf(BYTE  * inbuf,  UINT widthBytes, UINT height);
