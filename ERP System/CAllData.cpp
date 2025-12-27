// CAllData.cpp: 구현 파일
//

#include "pch.h"
#include "ERP System.h"
#include "afxdialogex.h"
#include "CAllData.h"

#include <iostream>
#include <fstream>
using namespace std;

// CAllData 대화 상자

IMPLEMENT_DYNAMIC(CAllData, CDialog)

CAllData::CAllData(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_ALL_DATA, pParent)
{

}

CAllData::~CAllData()
{

}

void CAllData::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_SEARCH_DATE, m_search_date);
	DDX_Control(pDX, IDC_SEARCH_CURSEL, m_search_cursel);
	DDX_Control(pDX, IDC_START, m_start);
	DDX_Control(pDX, IDC_END, m_end);
	DDX_Control(pDX, IDC_BUTTON1, m_button1);
	DDX_Control(pDX, IDC_BUTTON2, m_button2);
	DDX_Control(pDX, IDC_SEARCH_LIST, m_search_list);
	DDX_Control(pDX, IDC_RESULT_LIST, m_result_list);
}


BEGIN_MESSAGE_MAP(CAllData, CDialog)
	ON_BN_CLICKED(IDC_SEARCH_DATE, &CAllData::OnBnClickedSearchDate)
	ON_BN_CLICKED(IDC_SEARCH_CURSEL, &CAllData::OnBnClickedSearchCursel)
	ON_BN_CLICKED(IDC_BUTTON1, &CAllData::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CAllData::OnBnClickedButton2)
END_MESSAGE_MAP()


// CAllData 메시지 처리기


BOOL CAllData::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_search_date.SetCheck(1);
	m_button2.EnableWindow(false);
	m_search_list.EnableWindow(false);

	GetData();
	FillComboBox();
	FillSearchListBox();

	m_start.SetCurSel(0);
	m_end.SetCurSel(0);

	CFont m_resultFont;
	m_resultFont.CreatePointFont(130, _T("굴림"));
	m_result_list.SetFont(&m_resultFont);

	return TRUE;
}



void CAllData::OnBnClickedSearchDate()
{
	m_button1.EnableWindow(true);
	m_button2.EnableWindow(false);
	m_result_list.ResetContent();
	m_search_list.EnableWindow(false);
	m_start.EnableWindow(true);
	m_end.EnableWindow(true);
	m_search_list.SelItemRange(false, 0, 21);
}


void CAllData::OnBnClickedSearchCursel()
{
	m_button1.EnableWindow(false);
	m_button2.EnableWindow(true);
	m_result_list.ResetContent();
	m_search_list.EnableWindow(true);
	m_start.EnableWindow(false);
	m_end.EnableWindow(false);
	m_search_list.SelItemRange(false, 0, 21);
}


void CAllData::OnBnClickedButton1()
{
	m_result_list.ResetContent();

	int start = m_start.GetCurSel();
	int end = m_end.GetCurSel();

	if (start > end) {
		MessageBox(_T("시작하는 날짜가 끝나는 날짜보다 빨라야합니다."), _T("오류"), MB_OK | MB_ICONERROR);
	}
	else {
		for (int i = start; i <= end; i++) {
			FillResultListBox(i);
		}
	}
}


void CAllData::OnBnClickedButton2()
{
	m_result_list.ResetContent();

	int cnt = m_search_list.GetCount();
	
	for (int i = 0; i < cnt; i++) {
		if (m_search_list.GetSel(i)) {
			FillResultListBox(i);
		}
	}

}


void CAllData::GetData()
{
	ifstream fin;
	fin.open("IC-PBLdata.txt");
	int i = 0;
	int j = 0;
	while (!fin.eof()) {
		fin >> read_val[i][j];
		j++;
		if (j == 28) {
			i++;
			j = 0;
		}
	}
}


void CAllData::FillComboBox()
{
	for (int i = 0; i < 22; i++) {
		CString str;
		str.Format(_T("%d  %02d"), read_val[i][0], read_val[i][1]);
		m_start.AddString(str);
		m_end.AddString(str);
	}
}


void CAllData::FillSearchListBox()
{
	m_search_list.ResetContent();
	for (int i = 0; i < 22; i++) {
		CString str;
		str.Format(_T(" %d             %02d                %d"), 
			            read_val[i][0], read_val[i][1], read_val[i][2]);
		m_search_list.AddString(str);
	}
}


void CAllData::FillResultListBox(int i)
{
	sum_list = 0;		// 주문내역 합계
	sum_make = 0;		// 생산부 생산 수량
	sum_check = 0;		// 품질관리팀 검사 수량
	make_work = 0;		// 생산부 남은 업무량
	check_work = 0;		// 품질관리팀 남은 업무량
	per_work = 0;		// 진행률
	make_cost = 0;		// 생산부 손실액
	check_cost = 0;		// 품질관리팀 손실액
	sum_cost = 0;		// 총 손실액
	complete = "";		// 완료 여부

	for(int j = 0; j < 5; j++) {
		sum_list += read_val[i][j+3];
		sum_make += read_val[i][j+8];
		sum_check += read_val[i][j+13];
	}

	if (sum_list == sum_make && sum_list == sum_check) {
		complete = "O";
	}
	else {
		complete = "X";
	}

	make_work = sum_list - sum_make;
	check_work = sum_list - sum_check;
	per_work = (float)(sum_make + sum_check) / (sum_list * 2) * 100;

	make_cost = (read_val[i][18] * 6000) + (read_val[i][19] * 7000) + (read_val[i][20] * 8000) + (read_val[i][21] * 4000) + (read_val[i][22] * 10000);
	check_cost = (read_val[i][23] * 10000) + (read_val[i][24] * 12000) + (read_val[i][25] * 15000) + (read_val[i][26] * 9000) + (read_val[i][27] * 20000);
	sum_cost = make_cost + check_cost;

	str.Format(_T("%4d    %02d      %d\t%4d\t%4d\t%4d\t%4d\t%4d\t%4d\t%s   |       %3d\t%3d\t%3d%%\t|   \\  %6d\t\\  %7d\t\\  %7d"),
		             read_val[i][0], read_val[i][1], read_val[i][2], read_val[i][3], read_val[i][4], read_val[i][5], read_val[i][6], read_val[i][7], 
	                 	sum_list, complete, make_work, check_work, per_work, make_cost, check_cost, sum_cost);
	m_result_list.AddString(str);
}
