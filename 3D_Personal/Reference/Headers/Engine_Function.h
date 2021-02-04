#pragma once

#ifndef __ENGINE_FUNCTION_H__

template <typename T>
void SafeDelete(T& ptr)
{
	if (ptr)
	{
		delete ptr;
		ptr = nullptr;
	}
}

template <typename T>
void SafeDeleteArray(T& ptr)
{
	if (ptr)
	{
		delete[] ptr;
		ptr = nullptr;
	}
}

template <typename T>
_uint SafeAddRef(T& ptr)
{
	unsigned int iRefCnt = 0;

	if (ptr)
	{
		iRefCnt = ptr->AddRef();
	}

	return iRefCnt;
}

template <typename T>
_uint SafeRelease(T& ptr)
{
	unsigned int iRefCnt = 0;

	if (ptr)
	{
		iRefCnt = ptr->Release();

		if (0 == iRefCnt)
		{
			ptr = nullptr;
		}
	}

	return iRefCnt;
}


//////////////////////////////////////////////////////////////////////////Functor//////////////////////////////////////////////////////////////////////////

class CTagFinder
{
public:
	explicit CTagFinder(const _tchar* pTag)
		:m_pTag(pTag)
	{}
	~CTagFinder() {}
public:
	template<typename T>
	_bool operator() (const T& pair)
	{
		if (0 == lstrcmpW(m_pTag, pair.first))
		{
			return true;
		}
		return false;
	}
private:
	const _tchar* m_pTag = nullptr;
};

// ���������̳� ������
class CDeleteMap
{
public:
	explicit CDeleteMap(void) {}
	~CDeleteMap(void) {}
public: // operator	
	template <typename T>
	void operator () (T& Pair)
	{
		_ulong dwRefCnt = 0;
		dwRefCnt = Pair.second->Release();

		if (0 == dwRefCnt)
			Pair.second = NULL;
	}
};

class CDeleteObj
{
public:
	explicit CDeleteObj(void) {}
	~CDeleteObj(void) {}
public: // operator
	template <typename T>
	void operator () (T& pInstance)
	{
		_ulong dwRefCnt = 0;

		dwRefCnt = pInstance->Release();

		if (0 == dwRefCnt)
			pInstance = nullptr;
	}
};

#define __ENGINE_FUNCTION_H__
#endif