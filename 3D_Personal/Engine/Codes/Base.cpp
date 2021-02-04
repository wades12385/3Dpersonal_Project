#include "Base.h"

USING(Engine)
CBase::CBase()
	:m_iRefCnt(0)
{
}

_uint CBase::AddRef()
{
	return ++m_iRefCnt;
}

_uint CBase::Release()
{
	if (0 == m_iRefCnt)
	{
		Free();
		delete this;
		return 0;
	}

	return m_iRefCnt--;
}



