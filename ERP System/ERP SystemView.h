
// ERP SystemView.h: CERPSystemView 클래스의 인터페이스
//

#pragma once


class CERPSystemView : public CFormView
{
protected: // serialization에서만 만들어집니다.
	CERPSystemView() noexcept;
	DECLARE_DYNCREATE(CERPSystemView)

public:
#ifdef AFX_DESIGN_TIME
	enum{ IDD = IDD_ERP_SYSTEM_FORM };
#endif

// 특성입니다.
public:
	CERPSystemDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual void OnInitialUpdate(); // 생성 후 처음 호출되었습니다.

// 구현입니다.
public:
	virtual ~CERPSystemView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedGoall();
	afx_msg void OnBnClickedGoeach();
	virtual void OnDraw(CDC* /*pDC*/);
};

#ifndef _DEBUG  // ERP SystemView.cpp의 디버그 버전
inline CERPSystemDoc* CERPSystemView::GetDocument() const
   { return reinterpret_cast<CERPSystemDoc*>(m_pDocument); }
#endif

