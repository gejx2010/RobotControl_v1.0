// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__DADE7B45_7426_4496_8607_D7D723B4CE32__INCLUDED_)
#define AFX_STDAFX_H__DADE7B45_7426_4496_8607_D7D723B4CE32__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#define NO_WARN_MBCS_MFC_DEPRECATION   //---乐----添加消除警报信息
#define _CRT_SECURE_NO_WARNINGS // to disable deprecation with fopen, freopen and so on, added by gjx
#endif // _MSC_VER > 1000
#pragma warning(disable: 4244) // outlet the truncation error
#pragma warning(disable: 4305) // outlet the truncation error
#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <gl\gl.h>
#include <gl\glu.h>
#include <gl\glaux.h>
#include <afxcontrolbars.h>
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__DADE7B45_7426_4496_8607_D7D723B4CE32__INCLUDED_)
