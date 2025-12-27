
// ERP SystemView.cpp: CERPSystemView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "ERP System.h"
#endif

#include "ERP SystemDoc.h"
#include "ERP SystemView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "CAllData.h"
#include "CEachData.h"

// CERPSystemView

IMPLEMENT_DYNCREATE(CERPSystemView, CFormView)

BEGIN_MESSAGE_MAP(CERPSystemView, CFormView)
	ON_BN_CLICKED(IDC_GoAll, &CERPSystemView::OnBnClickedGoall)
	ON_BN_CLICKED(IDC_GoEach, &CERPSystemView::OnBnClickedGoeach)
END_MESSAGE_MAP()

// CERPSystemView 생성/소멸

CERPSystemView::CERPSystemView() noexcept
	: CFormView(IDD_ERP_SYSTEM_FORM)
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CERPSystemView::~CERPSystemView()
{
}

void CERPSystemView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BOOL CERPSystemView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CFormView::PreCreateWindow(cs);
}

void CERPSystemView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

}


// CERPSystemView 진단

#ifdef _DEBUG
void CERPSystemView::AssertValid() const
{
	CFormView::AssertValid();
}

void CERPSystemView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CERPSystemDoc* CERPSystemView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CERPSystemDoc)));
	return (CERPSystemDoc*)m_pDocument;
}
#endif //_DEBUG


// CERPSystemView 메시지 처리기


void CERPSystemView::OnBnClickedGoall()
{
	CAllData* m_AllData = new CAllData;
	m_AllData->Create(IDD_ALL_DATA);
	m_AllData->ShowWindow(SW_SHOW);
}


void CERPSystemView::OnBnClickedGoeach()
{
	CEachData* m_EachData = new CEachData;
	m_EachData->Create(IDD_EACH_DATA);
	m_EachData->ShowWindow(SW_SHOW);
}


void CERPSystemView::OnDraw(CDC* pDC)
{
	CFont font;
	LOGFONT lf = { 0 };
	lf.lfHeight = 35;
	lf.lfWeight = FW_BOLD;
	font.CreateFontIndirect(&lf);
	pDC->SelectObject(&font);
	pDC->SetTextColor(RGB(0, 0, 0));
	pDC->TextOut(140, 30, CString(_T("W기업")));
	pDC->SetTextColor(RGB(255, 0, 0));
	pDC->TextOut(95, 65, CString(_T("ERP System")));
}
