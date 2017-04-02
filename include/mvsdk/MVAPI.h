#ifndef  __MVAPI__
#define  __MVAPI__

#include "Common.h"

#ifdef __cplusplus
#define MVAPI extern "C" __declspec (dllexport)
#else
#define MVAPI __declspec (dllexport)
#endif

class CLabView
{
private:
	HANDLE  m_fHandle;
	ULONG   m_DataPoint;

	HANDLE  m_BmpThread;
	BOOL    m_Exit;
	BOOL    m_bBusy;
	static DWORD WINAPI Bmp_Thread( CLabView* lp );

public:
	ULONG   m_Width;
	ULONG   m_Height;
	ULONG   m_nColor;
	ULONG   m_SkipPixel;
	PUCHAR  m_pMiddle;

	ULONG   m_BmpLength;
	ULONG   m_BmpLineByte;
	ULONG   m_RawLineByte;
	ULONG   m_RawSkipByte;

	CLabView( ULONG Width, ULONG Heigth, ULONG nColor, ULONG SkipPixel );
	~CLabView();
	static BOOL  WINAPI LabViewCallBack( PVOID pData, PMV_IMAGEINFO pImageInfo, CLabView* lp, ULONG Index );
};

// ������ʾ
MVAPI DWORD WINAPI MV_GetLastError( BOOL bDisplayErrorStyring );

// ����pImageData��ͼ��MV_FILETYPEָ�����͵��ļ�
MVAPI BOOL WINAPI MV_SaveFile( PUCHAR FileName, MV_FILETYPE FileType, PVOID pImageData, PMV_IMAGEINFO pImage,
							   ULONG ImageTotal, BOOL IsUpDown, BOOL ColororNot, ULONG Quality, BOOL m_bRGB15=TRUE);
MVAPI BOOL WINAPI MV_SaveFilePro( PUCHAR FileName, MV_FILETYPE FileType, PVOID pImageData, PMV_IMAGEINFO pImage,
							   ULONG ImageTotal, BOOL IsUpDown, BOOL ColororNot, ULONG Quality,BOOL m_bRGB15=TRUE);

// �õ������в��΢�ӵĿ���
MVAPI DWORD   WINAPI MV_GetDeviceNumber();

// �����豸
MVAPI HANDLE  WINAPI MV_OpenDevice( DWORD Index, BOOL bRelese );

// ɾ���豸
MVAPI VOID    WINAPI MV_CloseDevice( HANDLE hDevice );

// �����豸
MVAPI RUNOPER WINAPI MV_OperateDevice( HANDLE hDevice, RUNOPER Oper );

// �����豸�Ĳ���
MVAPI BOOL    WINAPI MV_SetDeviceParameter( HANDLE hDevice, MV_PARAMTER Oper, DWORD Val );

// �õ��豸�Ĳ���
MVAPI LONG    WINAPI MV_GetDeviceParameter( HANDLE hDevice, MV_PARAMTER Oper );

MVAPI BOOL    WINAPI MV_SaveDeviceParam( HANDLE hDevice );
MVAPI BOOL    WINAPI MV_ResetDeviceParam( HANDLE hDevice );

// ����һ֡
MVAPI PVOID WINAPI MV_CaptureSingle( HANDLE hDevice, BOOL IsProcess, PVOID pInBuff, ULONG BuffLen, PMV_IMAGEINFO pInfo );

// �����豸�Ļص�
MVAPI BOOL    WINAPI MV_SetCallBack( HANDLE hDevice, CALLBACKFUNC pCallBack, PVOID pUserData, CALLBACKTYPE CallType );

// �������
MVAPI BOOL    WINAPI MV_SetOutputState( HANDLE hDevice, ULONG Index, ULONG HorL );

//����״̬��ȡ
MVAPI ULONG WINAPI MV_GetInputState( HANDLE hDevice, ULONG Index );

// ���봥������
MVAPI BOOL  WINAPI MV_SetInputCallBack( HANDLE hDevice, ULONG Index, ULONG UniquelyID, PTRIGGEROUTINE pTirggerCall, PVOID pContext );

// �����Զ�֡��
MVAPI BOOL    WINAPI MV_TestSignal( HANDLE hDevice, DWORD XSize, DWORD YSize );

// �õ��źŵ�ĳһ������
MVAPI DWORD   WINAPI MV_GetSignalParam( HANDLE hDevice, VIDEOSIGNAL Signal, float *FloatVal, DWORD *IntVal );

// �����Զ�֡��Ĳ�����Ini
MVAPI BOOL    WINAPI MV_SaveSignalParamToIni( HANDLE hDevice );

MVAPI BOOL    WINAPI MV_SplitRGB( HANDLE hDevice, PMV_RGB pRGB, ULONG DispType, ULONG DispPolicy, ULONG CallBackPolicy );

// ��OsdModeģʽʹ��OSD(����)����:
MVAPI BOOL   WINAPI MV_SetMaskFunction( HANDLE hDevice, ULONG OsdMode );
// ��OSDͼ�����͵��豸
MVAPI BOOL   WINAPI MV_SetMaskBit( HANDLE hDevice, RECT MaskArea, LPBYTE pBitPattern );
MVAPI LPBYTE WINAPI MV_MakeMaskBit( HANDLE hDevice, HWND hWnd, RECT Area, COLORREF Color );

// ���豸�����֡��
MVAPI BOOL   WINAPI MV_AllocSequenceFrameMemory( HANDLE hDevice, ULONG Action, DWORD Number, CALLBACKTYPE MemoryType );
// ���豸�ͷŴ�֡��
MVAPI BOOL   WINAPI MV_FreeSequenceFrameMemory( HANDLE hDevice );
// �Դ�֡�濪ʼ��������
MVAPI BOOL WINAPI MV_StartSequenceCapture( HANDLE hDevice, CONTINUEGARBMECHANISM pContinueCall, PVOID pContext );
// �Դ�֡��ֹͣ��������
MVAPI LONG   WINAPI MV_StopSequenceCapture( HANDLE hDevice );
// ����FrameNo����֡�ŵ�ַ��֡����
MVAPI PVOID WINAPI MV_GetSequenceFrameAddress( HANDLE hDevice, ULONG FrameNo, PMV_IMAGEINFO pProperty );

MVAPI ULONG WINAPI MV_ReadPixel( PMV_IMAGEINFO pProperty, PVOID pImageData, PPOINT Point, PBYTE pVal );
MVAPI VOID  WINAPI MV_WritePixel( PMV_IMAGEINFO pProperty, PVOID pImageData, PPOINT Point, PBYTE pVal );
MVAPI ULONG WINAPI MV_ReadLine( PMV_IMAGEINFO pProperty, PVOID pImageData, ULONG  nLine, PBYTE pVal );
MVAPI VOID  WINAPI MV_WriteLine( PMV_IMAGEINFO pProperty, PVOID pImageData, ULONG  nLine, PBYTE pVal );
MVAPI ULONG WINAPI MV_ReadArea( PMV_IMAGEINFO pProperty, PVOID pImageData, PRECT  pRect, PBYTE pVal );
MVAPI VOID  WINAPI MV_WriteArea( PMV_IMAGEINFO pProperty, PVOID pImageData, PRECT  pRect, PBYTE pVal );

MVAPI BOOL WINAPI I2CWrite( HANDLE hDevice, ULONG SubAdd, UCHAR buff, BOOL bPort );
MVAPI BOOL WINAPI I2CRead( HANDLE hDevice, ULONG SubAdd, PUCHAR pBuff, BOOL bPort );

MVAPI RUNOPER WINAPI MV_LabView_OperateDevice( HANDLE hDevice, RUNOPER Oper );
MVAPI PVOID WINAPI MV_LabView_GetBuffer( HANDLE hDevice );
MVAPI ULONG WINAPI MV_LabView_GetLength( HANDLE hDevice );
MVAPI ULONG WINAPI MV_LabView_GetnColor( HANDLE hDevice );
MVAPI ULONG WINAPI MV_LabView_GetHeigth( HANDLE hDevice );
MVAPI ULONG WINAPI MV_LabView_GetWidth( HANDLE hDevice );
MVAPI ULONG WINAPI MV_LabView_GetLineSkipPixel( HANDLE hDevice );

MVAPI HANDLE WINAPI MV_CreateAvi( char* FileName, PMV_IMAGEINFO pInfo, ULONG dwRate );
MVAPI VOID   WINAPI MV_WriteAvi( HANDLE hAvi, PUCHAR pBuffer, PMV_IMAGEINFO pInfo, LONG Index );
MVAPI VOID   WINAPI MV_CloseAvi( HANDLE hAvi );

MVAPI BOOL WINAPI MV_AmplifyImage(BYTE* pInputImage, long lWidth, long lHeight, BYTE* pOutputImage,int Bits);
MVAPI BOOL WINAPI MV_RGB16TORGB24(BYTE* pRGB16Buf, long lWidth, long lHeight, BYTE* pRGB24Buf,BOOL RGB1516);

#endif