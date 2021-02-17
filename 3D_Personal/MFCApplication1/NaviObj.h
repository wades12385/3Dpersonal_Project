#pragma once
#ifndef __TOOLNAVIOBJ_H__
#include "Gameobject.h"
USING(Engine)
class CNaviObj : public CGameObject
{
private:
	explicit CNaviObj(LPDIRECT3DDEVICE9 pDevice);
	virtual ~CNaviObj() = default;
public:
	// CGameObject을(를) 통해 상속됨
	virtual HRESULT		  Ready_Prototype() override;
	virtual HRESULT		  Awake_GameObject() override;
	virtual HRESULT		  Ready_GameObject() override;
	virtual _uint		  UpdateGameObject(const _float & fDeltaTime) override;
	virtual _uint		  LateUpdateGameObject(const _float & fDeltaTime) override;
	virtual HRESULT		  RenderGameObject() override;
	virtual CGameObject*  Clone() override;

	void	Set_Tag(const _tchar* pTag) { lstrcpy(m_szNaviTag, pTag); } ;

	void	Render_CellVertex();
	_bool	Vertex_Peeking(_vec2 pt, OUT int& idx);
	_bool	Cell_Peeking(_vec2 pt, OUT int& idx);
	void	SetUpRay(const _vec2& pt, OUT _vec3& RayPos, OUT _vec3& RayDir);


	HRESULT   SaveFile(const _tchar* pFilePath);
	static CNaviObj* Create(LPDIRECT3DDEVICE9 pDevice, const _tchar* pComTag);

public:
	CStaticMesh*	m_pStaticMesh = nullptr;
	CNaviMesh*		m_pNaviCom = nullptr;
	CTransform*		m_pTrans = nullptr;

	TCHAR m_szNaviTag[MAX_PATH];

	
	_bool				m_bModding;
	_bool				m_bHide;
	_bool				m_bHideCell;
	_bool				m_bHideVtx;

	virtual void Free();
};

#define __TOOLNAVIOBJ_H__
#endif


// 저장할거 버텍스 위치랑 쉘인덱스 
/*
네비매쉬 아이디
위치 m_vecIndex 
인덱스 m_vecIndex

쉘 속성  , 라인 속성 (색깔?? , 라인 타입 연결된 매쉬 아이디 , 연결된 매쉬 쉘 인덱스 )  매쉬 아이디 

*/