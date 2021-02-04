#pragma once

#ifndef __ENGINE_DEFINE_H__



#ifdef ENGINE_EXPORT
#define ENGINE_DLL _declspec(dllexport)
#else
#define ENGINE_DLL _declspec(dllimport)
#endif

#ifndef MSG_BOX
#define	MSG_BOX(_message)			MessageBox(NULL, _message, L"System Message", MB_OK)
#endif

#define BEGIN(Name) namespace Name {
#define END }
#define USING(Name) using namespace Name;

// [2/5/2021 wades]
#define ENUMSPACES(MyEnum) namespace MyEnum { \
 enum MyEnum  

#define NO_EVENT		0
#define CHANGE_SCNENE	1

//  [1/18/2021 Administrator]
#define NULL_CHECK( _ptr)	\
{if( _ptr == 0){__asm { int 3 };return;}}

#define NULL_CHECK_RETURN( _ptr, _return)	\
{if( _ptr == 0){__asm { int 3 };return _return;}}

#define NULL_CHECK_MSG( _ptr, _message )		\
{if( _ptr == 0){MessageBox(NULL, _message, L"System Message",MB_OK);__asm { int 3 };}}

#define NULL_CHECK_RETURN_MSG( _ptr, _return, _message )	\
{if( _ptr == 0){MessageBox(NULL, _message, L"System Message",MB_OK);__asm { int 3 };return _return;}}


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


#define vZero(vec) ZeroMemory(&vec, sizeof(D3DXVECTOR3))

#define OBJ_DEAD 1
#define OBJ_NOEVENT 0

#define RETURN_FAILED -1
#define NONE_SCENE -1

#define __ENGINE_DEFINE_H__
#endif