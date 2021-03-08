#include "stdafx.h"
#include "Player.h"
//////////////////////////////////////////////////////////////////////////
#include "PlayerCore.h"
#include "PlayerCamera.h"

CPlayer::CPlayer(LPDIRECT3DDEVICE9 pDevice)
	:CGameObject(pDevice)
{
}

CPlayer::CPlayer(const CPlayer& other)
	:CGameObject(other)
	,m_fMoveSpeed(other.m_fMoveSpeed)
	,m_fSpinSpeed(other.m_fSpinSpeed)
	, m_bIsMoving(false)
{
}

HRESULT CPlayer::Ready_Prototype()
{
	m_fMoveSpeed = 2.5f;
	m_fSpinSpeed = 90.f;
	return S_OK;
}

HRESULT CPlayer::Awake_GameObject()
{
	m_pTrans = CTransform::Create(m_pDevice);
	CGameObject::Add_Component(eComponentID::Transform, m_pTrans);
	m_pCollider = CCollider::Create(m_pDevice);
	CGameObject::Add_Component(eComponentID::Collider, m_pCollider);

	return S_OK;
}

HRESULT CPlayer::Ready_GameObject()
{
	m_pCore		= (CPlayerCore*)CManagement::Get_Instance()->Get_GameObjet(L"Layer_PlayerCore");
	m_pCamera	= (CPlayerCamera*)CManagement::Get_Instance()->Get_GameObjet(L"Layer_PlayerCamera");
	m_pCore->AddRef();
	m_pCamera->AddRef();

	//////////////////////////////////////////////////////////////////////////
	// 맴버 초기화
	m_pCollider->Set_BoundTypeFitMesh(eBoundType::Sphere, m_pCore->Get_trans(), m_pCore->Get_Mesh());
	cout << " 초기 값  : " << m_pCollider->Get_Bound().fRadius << endl;

	m_vMoveEndPos = vZero;
	m_vCoreAxis = vZero;
	m_pTrans->Set_Position(_vec3(25, 0, -5.f));
	m_pTrans->Update_Component();
	m_eRenderID = eRenderID::NoAlpha;
	Update_Core(vZero, 0);
	m_pCore->Update_CoreTrans(vZero, 0);

	//////////////////////////////////////////////////////////////////////////
	m_iNavID = 0;
	if (FAILED(CNaviMesh_Manager::Get_Instance()->Get_Mesh()[0]->Find_CurCellIdx(m_pTrans->Get_Position(), m_iNaviCellIdx)))
	{
		MSG_BOX(L"Faild find cell");
	}
	return S_OK;
}

_uint CPlayer::Update_GameObject(const _float & fDeltaTime)
{
	Test_Radius();
	Key_Input(fDeltaTime);
	Update_Move();
	Update_Camera();
	Update_Core(m_vCoreAxis, fDeltaTime);

	



	return 0;
}

_uint CPlayer::LateUpdate_GameObject(const _float & fDeltaTime)
{
	CManagement::Get_Instance()->Add_Renderer(m_eRenderID, this);
	return 0;
}

HRESULT CPlayer::RenderGameObject()
{

	m_pCollider->Render_Collider();

	return S_OK;
}

void CPlayer::Key_Input(const _float & fDeltaTime)
{
	Move_Input(fDeltaTime);
}

void CPlayer::Move_Input(const _float & fDeltaTime)
{
	m_bIsMoving = false;
	m_vCoreAxis = vZero;
	m_fCoreSpinSpeed = 0.f;

	//front 
	if (KeyPress(DIK_W) && KeyPress(DIK_I))
	{
		m_bIsMoving = true;
		m_vCoreAxis = m_pTrans->Get_Right();
		m_vMoveDir = m_pTrans->Get_Look();
		Move_Navi(m_pTrans->Get_Look() * m_fMoveSpeed * fDeltaTime);
	}
	//back
	if (KeyPress(DIK_S) && KeyPress(DIK_K))
	{
		m_bIsMoving = true;
		m_vCoreAxis = -m_pTrans->Get_Right();
		m_vMoveDir = -m_pTrans->Get_Look();

		Move_Navi(-m_pTrans->Get_Look() * m_fMoveSpeed * fDeltaTime);
	}
	//right
	if (KeyPress(DIK_D) && KeyPress(DIK_L))
	{
		m_bIsMoving = true;

		m_vCoreAxis = -m_pTrans->Get_Look();
		m_vMoveDir = m_pTrans->Get_Right();

		Move_Navi(m_pTrans->Get_Right() * m_fMoveSpeed * fDeltaTime);
	}
	//left
	if (KeyPress(DIK_A) && KeyPress(DIK_J))
	{
		m_bIsMoving = true;
		m_vCoreAxis = m_pTrans->Get_Look();
		m_vMoveDir = -m_pTrans->Get_Right();

		Move_Navi(-m_pTrans->Get_Right() * m_fMoveSpeed * fDeltaTime);
	}

	//left spin
	if (KeyPress(DIK_S) && KeyPress(DIK_I))
	{
		m_pTrans->AddRotate(_vec3(0, m_fSpinSpeed * -fDeltaTime, 0));
	}
	//right spin
	if (KeyPress(DIK_W) && KeyPress(DIK_K))
	{

		m_pTrans->AddRotate(_vec3(0, m_fSpinSpeed * fDeltaTime, 0));
	}
}

void CPlayer::Update_Move()
{
	//키입력이 들어올때만 m_vMoveEndPos이걸  setpos를 해줘는걸로?
	if (m_bIsMoving)
	{
		m_fCoreSpinSpeed = 90.f;
	}
	else
	{
		m_vMoveEndPos = m_pTrans->Get_Position();
	}
	CNaviMesh_Manager::Get_Instance()->Lading_Navi(m_vMoveEndPos, m_iNavID, m_iNaviCellIdx);
	m_vMoveEndPos.y += m_pCollider->Get_Bound().fRadius; // 스케일로 반지름값 계산해서 보정 
	if (m_bIsMoving)
	{
		_vec3 vPos = m_pTrans->Get_Position();
		_vec3 vDir = m_vMoveScala = m_vMoveEndPos - vPos;;
		D3DXVec3Normalize(&vDir, &vDir);

		_float fResult = D3DXVec3Dot(D3DXVec3Normalize(&m_vMoveDir, &m_vMoveDir), &vDir);
		if (fResult > 1.f)
			fResult = 1.f;
		if (vDir.y > 0.f)
		{
			_float fDegree = D3DXToDegree(acosf(fResult));
			if (!_finite(fDegree))
			{
				MSG_BOX(L"finite Angle");
				return;
			}
			cout << fDegree << endl;

			D3DXVec3Lerp(&m_vMoveScala, &vZero, &m_vMoveScala, (90.f-fDegree) / 90.f);

			m_vMoveEndPos = vPos + m_vMoveScala;
		}
	}




	m_pTrans->Set_Position(m_vMoveEndPos);
	m_pTrans->Update_Component();
}

void CPlayer::Update_Core(const _vec3& vAxis, const _float& fDeltaTime)
{

	//스칼라 / 코어의 둘레  * 360'   = 코어의 회전 각도 

	_float fRound = 2 * D3DX_PI * m_pCollider->Get_Bound().fRadius;
	 float  fSpinAngle =  D3DXVec3Length(&m_vMoveScala) / fRound * 360;
	 
	m_pCore->Get_trans()->Set_Position(m_pTrans->Get_Position());
	//m_pCore->Update_CoreTrans(vAxis, m_fCoreSpinSpeed * fDeltaTime);
	if (m_bIsMoving)
	{
		cout << "fSpin Angle :: " << fSpinAngle << endl;
		m_pCore->Update_CoreTrans(vAxis, fSpinAngle);
	}
}

void CPlayer::Update_Camera()
{
	m_pCamera->Update_Move(m_pTrans, m_pCollider);
}

void CPlayer::Move_Navi(const _vec3 & vScala)
{
	m_vMoveScala = vScala;
	m_vMoveEndPos = CNaviMesh_Manager::Get_Instance()->
		Get_Mesh()[m_iNavID]->MoveNaviMesh(m_iNavID, m_iNaviCellIdx, m_pTrans->Get_Position(), vScala, 0.f);
}

void CPlayer::Test_Radius()
{
	//static _float fRadius = m_pCollider->Get_Bound().fRadius;
	//static _float fRadius = 10.f;
	static _float fSacle = 10.f;

	if (KeyPress(DIK_1))
	{
		fSacle -= 0.1f;
		m_pCore->Get_trans()->Set_Scale(fSacle, fSacle, fSacle);
		m_pCore->Get_trans()->Update_Component();
		//m_pCollider->Set_BoundTypeFitMesh(eBoundType::Sphere, m_pCore->Get_trans(), m_pCore->Get_Mesh());
		m_pCollider->Set_BoundSize(fSacle);
		cout << "Scale : " << fSacle << endl;

	}

	if (KeyPress(DIK_2))
	{
		fSacle += 0.1f;
		m_pCore->Get_trans()->Set_Scale(fSacle, fSacle, fSacle);
		m_pCore->Get_trans()->Update_Component();
		//m_pCollider->Set_BoundTypeFitMesh(eBoundType::Sphere, m_pCore->Get_trans(), m_pCore->Get_Mesh());
		m_pCollider->Set_BoundSize(fSacle);
		cout << "Scale : " << fSacle << endl;

	}

	if (KeyDown(DIK_3))
	{
		system("cls");
		cout << "Scale : " << fSacle << endl;
		cout << "fRadius :  " << m_pCollider->Get_Bound().fRadius << endl;
		cout << "Camera dis :" << m_pCamera->Get_CameraDis() << endl;
	}
}

CPlayer * CPlayer::Create(LPDIRECT3DDEVICE9 pDevice)
{
	CPlayer* pIns = new CPlayer(pDevice);
	if (FAILED(pIns->Ready_Prototype()))
	{
		SafeRelease(pIns);
		return nullptr;
	}
	return pIns;
}

CGameObject * CPlayer::Clone()
{
	return new CPlayer(*this);
}

void CPlayer::Free()
{
	SafeRelease(m_pCore);
	SafeRelease(m_pCamera);
	CGameObject::Free();
}
