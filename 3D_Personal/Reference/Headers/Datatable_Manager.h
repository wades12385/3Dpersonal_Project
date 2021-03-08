#pragma once
#ifndef __DATATABLE_MANAGER_H__
#include "Base.h"
BEGIN(Engine)
class CDatatable_Manager : public CBase
{
	DECLARE_SINGLETON(CDatatable_Manager)
private:
	explicit CDatatable_Manager();
	virtual ~CDatatable_Manager() =default;
public:
	//csv Load
	HRESULT Load_DataTable(const _tchar* pFilePath);
	HRESULT Save_DataTable(const _tchar* pFilePath);
	vector<OBJDATA>*		Get_DataTableVector() { return &m_vecDataTble; }
private:
	vector<OBJDATA>			m_vecDataTble;
private:
	virtual void Free() override;
};
END
#define __DATATABLE_MANAGER_H__
#endif
