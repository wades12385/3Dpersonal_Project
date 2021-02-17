#include "StaticMesh.h"

USING(Engine)

Engine::CStaticMesh::CStaticMesh(LPDIRECT3DDEVICE9 pDevice)
	: CMesh(pDevice)
	, m_ppTextures(nullptr)
	, m_bNoTexture(false)
{

}

Engine::CStaticMesh::CStaticMesh(const CStaticMesh& other)
	: CMesh(other)
	, m_pAdjacency(other.m_pAdjacency)
	, m_pSubset(other.m_pSubset)
	, m_pMesh(other.m_pMesh)
	, m_pMtrl(other.m_pMtrl)
	, m_dwSubsetCnt(other.m_dwSubsetCnt)
	, m_pOriMesh(other.m_pOriMesh)
	, m_pVtxPos(other.m_pVtxPos)
	, m_dwVtxCnt(other.m_dwVtxCnt)
	, m_ppTextures(nullptr)
	, m_bNoTexture(other.m_bNoTexture)
{
	if (!(other.m_pMtrl[0].pTextureFilename == nullptr))
	{
		m_ppTextures = new LPDIRECT3DTEXTURE9[other.m_dwSubsetCnt];

		for (_ulong i = 0; i < other.m_dwSubsetCnt; ++i)
		{
			m_ppTextures[i] = other.m_ppTextures[i];
			m_ppTextures[i]->AddRef();
		}
	}

	m_pMesh->AddRef();
	m_pOriMesh->AddRef();
	m_pSubset->AddRef();
	m_pAdjacency->AddRef();
}

HRESULT Engine::CStaticMesh::Ready_Meshes(const _tchar* pFilePath, const _tchar* pFileName)
{
	_tchar szFullPath[MAX_PATH] = L"";


	lstrcpy(szFullPath, pFilePath);
	lstrcat(szFullPath, pFileName);

	if (FAILED(D3DXLoadMeshFromX(szFullPath, D3DXMESH_MANAGED, m_pDevice,
		&m_pAdjacency, &m_pSubset, NULL, &m_dwSubsetCnt, &m_pOriMesh)))
		return E_FAIL;
	//fvf �� �븻���� �˻� �� �߰� 
	_ulong	dwFVF = m_pOriMesh->GetFVF();
	if (!(dwFVF & D3DFVF_NORMAL))
	{
		m_pOriMesh->CloneMeshFVF(m_pOriMesh->GetOptions(), dwFVF | D3DFVF_NORMAL, m_pDevice, &m_pMesh);
		// ������ �븻�� ����Ͽ� �޽� ��ü�� �������ִ� �Լ�
		D3DXComputeNormals(m_pMesh, (_ulong*)m_pAdjacency->GetBufferPointer());
	}
	else
		m_pOriMesh->CloneMeshFVF(m_pOriMesh->GetOptions(), dwFVF, m_pDevice, &m_pMesh);

	// �޽� ũ�⿡ �´� �ٿ�� �ڽ� ����
	void*		pVertex = nullptr;
	m_dwVtxCnt = m_pMesh->GetNumVertices();	
	m_pVtxPos = new _vec3[m_dwVtxCnt];
	//////////////////////////////////////////////////////////////////////////
	m_pMesh->LockVertexBuffer(0, &pVertex);

	//���ؽ� ������Ʈ ����ü
	/*
	WORD    Stream;     // Stream index
	WORD    Offset;     // Offset in the stream in bytes
	BYTE    Type;       // Data type
	BYTE    Method;     // Processing method
	BYTE    Usage;      // Semantics
	BYTE    UsageIndex; // Semantic index
	*/
	D3DVERTEXELEMENT9			Decl[MAX_FVF_DECL_SIZE];
	ZeroMemory(Decl, sizeof(D3DVERTEXELEMENT9) * MAX_FVF_DECL_SIZE);

	m_pMesh->GetDeclaration(Decl);
	_ubyte byOffSet = 0;

	for (_ulong i = 0; i < MAX_FVF_DECL_SIZE; ++i)
	{
		if (Decl[i].Usage == D3DDECLUSAGE_POSITION)
		{
			byOffSet = (_ubyte)Decl[i].Offset;
			break;
		}
	}
	// fvf ������ ���� �޽��� ���� ������ ũ�⸦ ����� �� �ִ�.
	m_dwStride = D3DXGetFVFVertexSize(dwFVF);

	//����ũ�⸦ ������ �������� ���� �����ϳ�ũ��+��ġ����offset -> �������� ��ġ���� �ּҽ����� ��ȸ 
	for (_ulong i = 0; i < m_dwVtxCnt; ++i)
	{
		m_pVtxPos[i] = *((_vec3*)(((_ubyte*)pVertex) + (i * m_dwStride + byOffSet)));
	}

	m_pMesh->UnlockVertexBuffer();
	//////////////////////////////////////////////////////////////////////////

	// LPD3DXBUFFER�� ��� �ִ� ������ ���� ù ��° �ּҸ� ����

	/*
	typedef struct _D3DXMATERIAL
{
	D3DMATERIAL9  MatD3D;
	LPSTR         pTextureFilename;
} D3DXMATERIAL;
	*/
	m_pMtrl = (D3DXMATERIAL*)m_pSubset->GetBufferPointer();

	//������ ����ƽ �Ž� �ε��Ҷ� �ؽ��� ���� ��� 
	if (m_dwSubsetCnt == 1 && m_pMtrl[0].pTextureFilename == nullptr)
	{
		m_bNoTexture = true;
		return S_OK;
	}

	m_ppTextures = new LPDIRECT3DTEXTURE9[m_dwSubsetCnt];

	for (_ulong i = 0; i < m_dwSubsetCnt; ++i)
	{
		_tchar	szFileName[MAX_PATH] = L"";
		lstrcpy(szFullPath, pFilePath);

	

		MultiByteToWideChar(CP_ACP, 0, m_pMtrl[i].pTextureFilename,
			strlen(m_pMtrl[i].pTextureFilename), szFileName, MAX_PATH);

		lstrcat(szFullPath, szFileName);


		if (FAILED(D3DXCreateTextureFromFile(m_pDevice, szFullPath, &m_ppTextures[i])))
			return E_FAIL;
	}


	return S_OK;
}

void Engine::CStaticMesh::Render_Meshes()
{

	for (_ulong i = 0; i < m_dwSubsetCnt; ++i)
	{
		if (m_bNoTexture)
		{
			m_pDevice->SetTexture(0, nullptr);
			m_pDevice->SetMaterial(&m_pMtrl[i].MatD3D);
		}
		else
		{
			m_pDevice->SetMaterial(&m_pMtrl[i].MatD3D);
			m_pDevice->SetTexture(0, m_ppTextures[i]);
		}


		m_pMesh->DrawSubset(i);
	}
}

Engine::CStaticMesh* Engine::CStaticMesh::Create(LPDIRECT3DDEVICE9 pDevice, const _tchar* pFilePath, const _tchar* pFileName)
{
	CStaticMesh*	pIns = new CStaticMesh(pDevice);

	if (FAILED(pIns->Ready_Meshes(pFilePath, pFileName)))
		SafeRelease(pIns);

	return pIns;
}

CComponent * CStaticMesh::Clone()
{
	return new CStaticMesh(*this);
}

void Engine::CStaticMesh::Free()
{

	if (m_bNoTexture == false)
	{

	for (_ulong i = 0; i < m_dwSubsetCnt; ++i)
		SafeRelease(m_ppTextures[i]);
	}

	SafeDeleteArray(m_ppTextures);

	if (false == m_bClone)
		SafeDeleteArray(m_pVtxPos);
	SafeRelease(m_pMesh);
	SafeRelease(m_pOriMesh);
	SafeRelease(m_pSubset);
	SafeRelease(m_pAdjacency);

	CMesh::Free();
}
