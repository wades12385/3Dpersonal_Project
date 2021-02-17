
// MFCApplication1View.h : CMFCApplicationView Ŭ������ �������̽�
//
#pragma once
class CMFCApplicationDoc;
class CMFCApplicationView : public CView
{
protected: // serialization������ ��������ϴ�.
	CMFCApplicationView();
	DECLARE_DYNCREATE(CMFCApplicationView)

// Ư���Դϴ�.
public:
	CMFCApplicationDoc* GetDocument() const;
	class CNaviModifyTab* m_pNaviModiTab;
// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// �����Դϴ�.
public:
	virtual ~CMFCApplicationView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);


private:

	void Peeking_Process(const CPoint& point);
};

#ifndef _DEBUG  // MFCApplication1View.cpp�� ����� ����
inline CMFCApplicationDoc* CMFCApplicationView::GetDocument() const
   { return reinterpret_cast<CMFCApplicationDoc*>(m_pDocument); }
#endif

