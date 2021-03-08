#include "Datatable_Manager.h"

USING(Engine)
IMPLEMENT_SINGLETON(CDatatable_Manager)


CDatatable_Manager::CDatatable_Manager()
{
}

//(ID), (sacle) , (tag) , (Size) , (Weight) , IsDeco , Float, Stationary
HRESULT CDatatable_Manager::Load_DataTable(const _tchar * pFilePath)
{
	OBJDATA tTemp;
	FILE* pFile = nullptr;
	TCHAR szWord[MAX_PATH + 1] = TEXT("");
	if (0 != _tfopen_s(&pFile, pFilePath, TEXT("r")))
	{
		MSG_BOX(L"failed Load");
		return E_FAIL;
	} 
	_int iDeco, iFloat, iStat;
	int i = 0;
	while (EOF != _ftscanf_s(pFile, TEXT("%s"), szWord, MAX_PATH))
	{
		if (isdigit(szWord[0]))
		{
			tTemp.iItemID = _ttoi(szWord);
			_ftscanf_s(pFile, TEXT("%s"), szWord, MAX_PATH);
			tTemp.wstrTag = wstring(szWord);
			_ftscanf_s(pFile, TEXT("%f %f %f %d %d %d\n")
				,&tTemp.fSacle, &tTemp.fSize, &tTemp.fWeight 
				,&iDeco,&iFloat,&iStat);

			tTemp.bDecoration =  (i != iDeco);
			tTemp.bFloating =   ( i != iFloat);
			tTemp.bStationary = (i != iStat);


			m_vecDataTble.emplace_back(tTemp);
		}
	}
	fclose(pFile);

	return S_OK;
}

HRESULT CDatatable_Manager::Save_DataTable(const _tchar * pFilePath)
{
	FILE* pFile = nullptr;
	TCHAR szWord[MAX_PATH + 1] = TEXT("");
	if (0 != _tfopen_s(&pFile, pFilePath, TEXT("w")))
	{
		MSG_BOX(L"failed Load");
		return E_FAIL;
	}
	_ftprintf(pFile, L"ID\tTag\tScale\tSize\tWeight\tDecoration\tFloating\tStationary\n");
	for(_uint i = 0 ; i < m_vecDataTble.size(); ++i)
	{
		_ftprintf(pFile, L"%d\t",i);
		 lstrcpy(szWord ,m_vecDataTble[i].wstrTag.c_str());
		_ftprintf(pFile, L"%s\t", szWord);
		_ftprintf(pFile, L"%f\t%f\t%f\t%d\t%d\t%d\n", m_vecDataTble[i].fSacle, m_vecDataTble[i].fSize, m_vecDataTble[i].fWeight
			, m_vecDataTble[i].bDecoration, m_vecDataTble[i].bFloating, m_vecDataTble[i].bStationary);
	}
	fclose(pFile);
	return S_OK;
}

void CDatatable_Manager::Free()
{
	m_vecDataTble.clear();
	m_vecDataTble.shrink_to_fit();
}
