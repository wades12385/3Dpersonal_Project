#pragma once

#ifndef __ENGINE_DEFINE_H__



#ifdef ENGINE_EXPORT
#define ENGINE_DLL _declspec(dllexport)
#else
#define ENGINE_DLL _declspec(dllimport)
#endif


#ifdef _AFX
#define  MSG_BOX(MSG) AfxMessageBox(MSG)
#else
#define	MSG_BOX(_message)			MessageBox(NULL, _message, L"System Message", MB_OK)
#endif // _AFX


#define BEGIN(Name) namespace Name {
#define END }
#define USING(Name) using namespace Name;



// [2/5/2021 wades]
#define ENUMSPACES(MyEnum) namespace MyEnum { \
 enum MyEnum  



#define NO_EVENT		0
#define CHANGE_SCNENE	1



//  [1/18/2021 Administrator]

#ifndef _AFX

#define NULL_CHECK( _ptr)	\
{if( _ptr == 0){__asm { int 3 };return;}}

#define NULL_CHECK_RETURN( _ptr, _return)	\
{if( _ptr == 0){__asm { int 3 };return _return;}}

#define NULL_CHECK_MSG( _ptr, _message )		\
{if( _ptr == 0){MessageBox(NULL, _message, L"System Message",MB_OK);__asm { int 3 };}}

#define NULL_CHECK_RETURN_MSG( _ptr, _return, _message )	\
{if( _ptr == 0){MessageBox(NULL, _message, L"System Message",MB_OK);__asm { int 3 };return _return;}}

#else


#define NULL_CHECK( _ptr)	\
{if( _ptr == 0){__asm { int 3 };return;}}

#define NULL_CHECK_RETURN( _ptr, _return)	\
{if( _ptr == 0){__asm { int 3 };return _return;}}

#define NULL_CHECK_MSG( _ptr, _message )		\
{if( _ptr == 0){AfxMessageBox(L"System Message");__asm { int 3 };}}

#define NULL_CHECK_RETURN_MSG( _ptr, _return, _message )	\
{if( _ptr == 0){AfxMessageBox(L"System Message");__asm { int 3 };return _return;}}

#endif // !_AFX

#define FAILED_CHECK(_hr)	if( ((HRESULT)(_hr)) < 0 )	\
{ MessageBoxW(NULL, L"Failed", L"System Error",MB_OK); __asm { int 3 }; return E_FAIL;}

//º¹±¸ [2/2/2021 Administrator]
#define NO_COPY(ClassName)							\
	private:										\
	ClassName(const ClassName&) ;					\
	ClassName& operator = (const ClassName&);		

#define DECLARE_SINGLETON(ClassName)				\
	NO_COPY(ClassName)								\
private:											\
	static ClassName*	m_pInstance;				\
public:												\
	static ClassName*	Get_Instance();				\
	static _ulong	Release_Instance();			

#define IMPLEMENT_SINGLETON(ClassName)				\
	ClassName*	ClassName::m_pInstance = nullptr;	\
	ClassName*	ClassName::Get_Instance()			\
    {												\
		if(nullptr == m_pInstance) 					\
			m_pInstance = new ClassName();			\
		return m_pInstance;							\
	}												\
	_ulong ClassName::Release_Instance()			\
    {												\
		_ulong iRefCnt =0;							\
		if(nullptr != m_pInstance)					\
			 iRefCnt = m_pInstance->Release();		\
		return iRefCnt;								\
	}


#define vZeroMemory(vec) ZeroMemory(&vec, sizeof(D3DXVECTOR3))
#define vZero _vec3(0,0,0)

#define OBJ_DEAD 1
#define OBJ_NOEVENT 0

#define RETURN_FAILED -1
#define NONE_SCENE -1
#define NOT_FOUND -1
 

#define COLOR_GRAY				D3DCOLOR_XRGB(125,125,125)
#define COLOR_RED				D3DCOLOR_XRGB(255,0,0)
#define COLOR_BLUE				D3DCOLOR_XRGB(0,0,255)
#define COLOR_SKYBLUE			D3DCOLOR_XRGB(0,255,255)
#define COLOR_GREEN				D3DCOLOR_XRGB(0,255,0)
#define COLOR_PINK				D3DCOLOR_XRGB(255,0,255)
#define COLOR_YELLOW			D3DCOLOR_XRGB(255,255,0)
#define COLOR_ORANGE			D3DCOLOR_XRGB(255,128,0)
#define COLOR_LIGHTGRAY			D3DCOLOR_XRGB(192,192,192)
#define COLOR_PURPLE			D3DCOLOR_XRGB(128,0,128)

#define VCOLOR_GRAY				D3DXVECTOR3(125,125,125)
#define VCOLOR_RED				D3DXVECTOR3(255,0,0)
#define VCOLOR_BLUE				D3DXVECTOR3(0,0,255)
#define VCOLOR_SKYBLUE			D3DXVECTOR3(0,255,255)
#define VCOLOR_GREEN			D3DXVECTOR3(0,255,0)
#define VCOLOR_PINK				D3DXVECTOR3(255,0,255)
#define VCOLOR_YELLOW			D3DXVECTOR3(255,255,0)
#define VCOLOR_ORANGE			D3DXVECTOR3(255,128,0)
#define VCOLOR_LIGHTGRAY		D3DXVECTOR3(192,192,192)
#define VCOLOR_PURPLE			D3DXVECTOR3(128,0,128)
	
#define VecToColor_XRGB(vec3)  D3DCOLOR_XRGB((int)vec3.x , (int)vec3.y, (int)vec3.z)

#define __ENGINE_DEFINE_H__ 
#endif