// RobotControlView.cpp : implementation of the CRobotControlView class
//

#include "stdafx.h"
#include "RobotControl.h"

#include "RobotControlMultiDoc.h"
#include "MainFrm.h"
#include "PathPlanDlg.h"
#include "RobotControlView.h"             //---��---���ϼ�����
#include "conio.h"

#ifdef _DEBUG                            //----��---����������򣬱��뿪ʼ��־
#define new DEBUG_NEW
#undef THIS_FILE                        //--��---ȡ���궨���־����
static char THIS_FILE[] = __FILE__;
#endif

#define COMPILE false

/////////////////////////////////////////////////////////////////////////////
// CRobotControlView

IMPLEMENT_DYNCREATE(CRobotControlView, CView)   //---ʵ�֡�����ʱ����ʶ�𡱺�--????

BEGIN_MESSAGE_MAP(CRobotControlView, CView)  //---�궨����Ϣ������
	//{{AFX_MSG_MAP(CRobotControlView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_DESTROY()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	//}}AFX_MSG_MAP
	// Standard printing commands
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRobotControlView construction/destruction

CRobotControlView::CRobotControlView()
{
	// TODO: add construction code here
	m_hGLContext = NULL;    //---��---����
	m_GLPixelIndex = 0;     //---����---ָ��
	m_LButtonDown = FALSE;  //---������
	m_RButtonDown=FALSE;    //---������
	display_revert = false;

	if (COMPILE) {
		AllocConsole();
	}
}

CRobotControlView::~CRobotControlView()//---�����������������ϵͳ�����ͷ���Դ
{
	if (COMPILE) {
		FreeConsole();
	}
}

BOOL CRobotControlView::PreCreateWindow(CREATESTRUCT& cs)    //--��--�������Ժ���
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	cs.style |= (WS_CLIPCHILDREN | WS_CLIPSIBLINGS);     //----��--��������������ڱ仯
	return CView::PreCreateWindow(cs);

}

/////////////////////////////////////////////////////////////////////////////
// CRobotControlView drawing

void CRobotControlView::OnDraw(CDC* pDC)  //----��---��ͼ����
{
	CRobotControlMultiDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// ��ô��ڿͻ�����С
	int x_client, y_client;
	CRect client_rect = CRect(0, 0, 100, 100);
	GetClientRect(&client_rect);
	x_client = client_rect.Width(), y_client = client_rect.Height();


	// �ֱ�������������ӿͻ���
	glClearColor(1.0,1.0,1.0,1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
    glLoadIdentity();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45,pDoc->doc_delay->aspect,0.1,200.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glViewport(0,0,x_client/2,y_client);
	//pDoc->doc_delay->m_zRotation += 180; 
	//pDoc->doc_real->m_xRotation = pDoc->doc_delay->m_xRotation += 180; 
	if (!display_revert) {
		pDoc->doc_delay->m_zRotation += 180;
		pDoc->doc_real->m_zRotation += 180;
		display_revert = true;;
	}

	pDoc->doc_delay->RenderScene();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45,pDoc->doc_real->aspect,0.1,200.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glViewport(x_client/2,0,x_client/2,y_client);
	// 
	//pDoc->doc_real = pDoc->doc_delay;
	//pDoc->doc_real->m_zRotation += 180;
	pDoc->doc_real->RenderScene();
	
	SwapBuffers(pDC->m_hDC);
	// TODO: add draw code for native data here
}



/////////////////////////////////////////////////////////////////////////////
// CRobotControlView diagnostics

#ifdef _DEBUG
void CRobotControlView::AssertValid() const
{
	CView::AssertValid();
}

void CRobotControlView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CRobotControlMultiDoc* CRobotControlView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CRobotControlMultiDoc)));
	return (CRobotControlMultiDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CRobotControlView message handlers

BOOL CRobotControlView::SetWindowPixelFormat(HDC hDC)
{
	static PIXELFORMATDESCRIPTOR pixelDesc= 
	{
        sizeof(PIXELFORMATDESCRIPTOR),  // size of this pfd
			1,                              	 // version number
			PFD_DRAW_TO_WINDOW |          // support window
			PFD_SUPPORT_OPENGL|          // support OpenGL
			PFD_DOUBLEBUFFER,          //support doublebuffer
			PFD_TYPE_RGBA,                  // RGBA type
			24,                         // 24-bit color depth
			0, 0, 0, 0, 0, 0,                // color bits ignored
			0,                          // no alpha buffer
			0,                          // shift bit ignored
			0,                          // no accumulation buffer
			0, 0, 0, 0,                    // accum bits ignored
			32,                         // 32-bit z-buffer
			0,                          // no stencil buffer
			0,                          // no auxiliary buffer
			PFD_MAIN_PLANE,          // main layer
			0,                          // reserved
			0, 0, 0                       // layer masks ignored
    };  
    m_GLPixelIndex = ChoosePixelFormat(hDC,&pixelDesc);
	if (m_GLPixelIndex==0) // Let's choose a default index.
	{
		m_GLPixelIndex = 1;	
		if (DescribePixelFormat(hDC, m_GLPixelIndex, 
			sizeof(PIXELFORMATDESCRIPTOR), 
			&pixelDesc)==0)
		{
			return FALSE;
		}
	}
	if (SetPixelFormat( hDC, m_GLPixelIndex, &pixelDesc)==FALSE)
	{
		return FALSE;
	}
	return TRUE;
}

BOOL CRobotControlView::CreateViewGLContext(HDC hDC)
{
    m_hGLContext = wglCreateContext(hDC);    
	if (m_hGLContext == NULL)    
	{
        return FALSE;    
	}    
	if (wglMakeCurrent(hDC, m_hGLContext)==FALSE)    
	{
        return FALSE;    
	}    
	return TRUE;
}



int CRobotControlView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	HWND hWnd = GetSafeHwnd();
	HDC hDC = ::GetDC(hWnd);

	if(SetWindowPixelFormat(hDC)==FALSE)
		return 0;
	if(CreateViewGLContext(hDC)==FALSE)
		return 0;

	////////////////////////////////
    GLfloat light_position1[]={0.0,-1.0,6.0,0.0}; 
     glLightfv(GL_LIGHT0,GL_POSITION,light_position1); 

     glEnable(GL_LIGHTING); 
     glEnable(GL_LIGHT0);

	glDrawBuffer(GL_BACK);	
    glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_FLAT);
	//draw front face
	glFrontFace(GL_CW);
	glCullFace(GL_FRONT);
	glEnable(GL_CULL_FACE);

    glColorMaterial(GL_FRONT,GL_DIFFUSE); 
    glEnable(GL_COLOR_MATERIAL); 
	
	
    GLfloat ambientLight[] = {0.3f, 0.3f, 0.3f, 1.0f };
	GLfloat diffuseLight[] = {0.7f, 0.7f, 0.3f, 1.0f };
	GLfloat specular[] = {1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat specref[] = {1.0f, 1.0f, 1.0f, 1.0f };
	
	glEnable(GL_LIGHTING); 
	glLightfv(GL_LIGHT0,GL_AMBIENT,ambientLight);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,diffuseLight);
	glLightfv(GL_LIGHT0,GL_SPECULAR,specular);
	glEnable(GL_LIGHT0);
	
	glEnable(GL_COLOR_MATERIAL); 
	glColorMaterial(GL_FRONT,GL_AMBIENT_AND_DIFFUSE); 
	glMaterialfv(GL_FRONT, GL_SPECULAR, specref);
	glMateriali(GL_FRONT, GL_SHININESS,128);
	
	
	//Transparent capacity
	glEnable(GL_BLEND); 
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA); 
	glHint(GL_LINE_SMOOTH_HINT,GL_DONT_CARE); 	
	
	return 0;
}

void CRobotControlView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	CSize size(cx,cy);

	glViewport(0,0,size.cx,size.cy);
	CRobotControlMultiDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->doc_delay->aspect= (cy == 0) ? (double)size.cx : (double)size.cx/(double)size.cy;
	pDoc->doc_real->aspect= (cy == 0) ? (double)size.cx : (double)size.cx/(double)size.cy;
}



void CRobotControlView::OnDestroy() 
{
	CView::OnDestroy();
	
	if(wglGetCurrentContext()!=NULL)     
	{   // make the rendering context not current
        wglMakeCurrent(NULL, NULL) ;    
	}        
	if (m_hGLContext!=NULL)    
	{
		wglDeleteContext(m_hGLContext);        
		m_hGLContext = NULL;    
	}

	// TODO: Add your message handler code here
	
}

void CRobotControlView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CRobotControlMultiDoc* pDoc = GetDocument();
	if (m_LButtonDown)
	{
		CSize rotation = point- m_LDownPos ;
		m_LDownPos = point;
		pDoc->doc_delay->m_zRotation += rotation.cx/3; //x��������,��z����ʱ��ת��
		pDoc->doc_real->m_zRotation = pDoc->doc_delay->m_zRotation;
		pDoc->doc_delay->m_xRotation += rotation.cy/3; //y��������,��x����ʱ��ת��
		pDoc->doc_real->m_xRotation = pDoc->doc_delay->m_xRotation;
		InvalidateRect(NULL, FALSE);
	}       
	if (m_RButtonDown)   //---��---ͼ�ε����ź���
	{
		CSize zoom = point-m_RDownPos ;
		m_RDownPos = point;

		pDoc->doc_delay->m_zoom -=(GLfloat)zoom.cx/50;  //x��������,zoomԽС,-zoom(���Ǿ���ֵ)Խ��,�Ŵ�
		pDoc->doc_real->m_zoom = pDoc->doc_delay->m_zoom;
		pDoc->doc_delay->m_zoom +=(GLfloat)zoom.cy/50;  //y����Խ��,zoomԽ��,-zoomԽС,��С
		pDoc->doc_real->m_zoom = pDoc->doc_delay->m_zoom;
		if (pDoc->doc_delay->m_zoom>100) {
			pDoc->doc_delay->m_zoom=100;
			pDoc->doc_real->m_zoom = 100;
		}
		if (pDoc->doc_delay->m_zoom<0.1) {
			pDoc->doc_delay->m_zoom=0.1;
			pDoc->doc_real->m_zoom=0.1;
		}
		InvalidateRect(NULL, FALSE);
	}

	CView::OnMouseMove(nFlags, point);
}



void CRobotControlView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

	m_LButtonDown = true;
	m_LDownPos = point;
	SetCapture();  /*������ꡣһ������£�����������Ƴ���ĳ���������ڵķ�Χ��
	                ��ô�˴��ڽ����ټ����յ������Ϣ���������SetCapture��������겶��
		            ��ô����ʹ�������Ƴ��˴��ڣ���Ȼ�����յ������Ϣ��
		            ֱ����ReleaseCapture����ĳ�������Ͻ��е��Ϊֹ��*/

	CView::OnLButtonDown(nFlags, point);
}


void CRobotControlView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	m_LButtonDown = false;	
	ReleaseCapture();	
	
	CView::OnLButtonUp(nFlags, point);
}


void CRobotControlView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	m_RButtonDown = true;
	m_RDownPos = point;
	SetCapture();

	CView::OnRButtonDown(nFlags, point);
}


void CRobotControlView::OnRButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	m_RButtonDown = false;	
	ReleaseCapture();

	CView::OnRButtonUp(nFlags, point);
}

void CRobotControlView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	GetPathPlanDlg()->OnKeyDown(nChar, nRepCnt, nFlags);
	/*
	switch (nChar) {
		case 'A':
			if (COMPILE) {
				_cprintf("call the a key down.\n");
				system("pause");
			}
			break;
		case 'S':
			break;
		case 'W':
			break;
		case 'D':
			break;
		case 'R':
			break;
		default:
			break;
	}
	*/
}

void  CRobotControlView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) {
	GetPathPlanDlg()->OnKeyUp(nChar, nRepCnt, nFlags);
}

CPathPlanDlg* CRobotControlView::GetPathPlanDlg() {
	// get main frame handle here
	CMainFrame* frame=(CMainFrame*)AfxGetApp()->GetMainWnd();
	
	return frame->pSiderBar->pCtrlTab->pPathPlanDlg;
}

LRESULT CRobotControlView::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	//GetPathPlanDlg()->viewProc(message, wParam, lParam);
	return CView::WindowProc(message, wParam, lParam);
}	