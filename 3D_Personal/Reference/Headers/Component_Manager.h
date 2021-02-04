#pragma once
#ifndef __COMPONENTMANAGER_H__
#include "Base.h"

#include "Transform.h"

BEGIN(Engine)
class ENGINE_DLL CComponent_Manager : public CBase
{
	DECLARE_SINGLETON(CComponent_Manager)
	typedef unordered_map<const _tchar*, CComponent*> COMPMAP;
public:
	explicit CComponent_Manager();
	virtual ~CComponent_Manager() = default;

	// CBase을(를) 통해 상속됨
	virtual void Free() override;
public:

private:
	HRESULT Ready_Resourece(LPDIRECT3DDEVICE9 pDevice, const _tchar* pCompTag, const eResourcesID& eCompID , const CComponent* pComp);
	CComponent*	Clone(const _tchar* pCompTag, const eResourcesID& eResourcesID);

	HRESULT ExisitCheck_Comp(const _tchar* pCompTag, const eResourcesID& eResourceID);
	HRESULT FindCheck_Comp(COMPMAP::iterator& iter , const eResourcesID& eResourceID);

private:
	COMPMAP m_mapComponets[(_uint)eResourcesID::End];
};
END
#define __COMPONENTMANAGER_H__
#endif // !__COMPONENTMANAGER_H__


/*
// 매쉬나 버퍼종류만 매니저 내부에서 
리소스로 분류를 하기로 약속을 잡고 그 이외 컴포넌트는 다른 함수로 그냥 생성 해서 사용할거임 



client에서는 

obj 내부에서 매니저 호출로 컴포넌트 복제해서 가져오고  리소느는 가져오고 이외는 생성해서 


boj의 add 컴포넌트로 넣을떄 중복등등 체크 하고 
애초에 컴포넌트에 래퍼런스 체크가  에바인데 

오브젝트가 존재한 이상 꺼내오면 정상적 상태이면 객체이고 
매번 getter로 받아온다고 하면 받아오는 오브젝트의 수명과 같으니 댕글링 문제는 아니고 

계속 보관해서 써먹는거나 트렌스폼의 Parent 가 문제인데 

그럼 트렌스 폼의 패런트를 댕글이 원천 차단을 위해서 트렌스폼이 갖고 있지말고 매번 쓰는걸로 


*/
