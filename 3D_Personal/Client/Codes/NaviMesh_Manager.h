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
	// CBase��(��) ���� ��ӵ�
	virtual void Free() override;
};
#define __NAVIMESH_MANAGER_H__
#endif

/*
���� ���� vec2 ��ġ�� y ���� ���� 

(Ű�Է� ) -(�̵��� ���) -> (�׺�Ž� ���μ���) - ���� ��ġ�� ��� ��ġsetter  

(����ġ�� ) y�� ��� 

��� ������Ʈ���� �̰� ���� ���ϴϱ� ������Ʈ ���������� ���� ���� ���̵� ���� ���� 
onNaviMehs (��
*/