#pragma once
#ifndef __NAVIMESH_MANAGER_H__
#include "Base.h"
USING(Engine)
class CNaviMesh_Manager : public CBase
{
	DECLARE_SINGLETON(CNaviMesh_Manager)
private:
	explicit CNaviMesh_Manager();
	virtual ~CNaviMesh_Manager();
public:
	HRESULT						Load(LPDIRECT3DDEVICE9 pDevice, const _tchar* pFilePath);
	void						ClearMesh();
	vector<CNaviMesh*>&			Get_Mesh();

//////////////////////////////////////////////////////////////////////////
	HRESULT						Lading_Navi( _vec3& vPos, const _int& iNavID, const _int& iCellIdx);
	void						Render_Navi();
private:
	vector<CNaviMesh*>			m_vecNaviMesh;
private:
	// CBase을(를) 통해 상속됨
	virtual void Free() override;
};
#define __NAVIMESH_MANAGER_H__
#endif

/*
무브 이후 vec2 위치로 y 값을 잡음 

(키입력 ) -(이동량 계산) -> (네비매쉬 프로세스) - 최종 위치로 대상 위치setter  

(현위치로 ) y값 계싼 

모든 오브젝트들이 이걸 통해 야하니깐 오브젝트 내부적으로 현재 내비 아이디 값을 값고 
onNaviMehs (자
*/