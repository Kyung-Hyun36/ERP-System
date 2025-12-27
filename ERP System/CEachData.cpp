// CEachData.cpp: 구현 파일
//

#include "pch.h"
#include "ERP System.h"
#include "afxdialogex.h"
#include "CEachData.h"

#include <math.h>
#include <iostream>
#include <fstream>
using namespace std;

const double pi = 3.1415926535;
// CEachData 대화 상자

IMPLEMENT_DYNAMIC(CEachData, CDialog)

CEachData::CEachData(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_EACH_DATA, pParent)
{
}

CEachData::~CEachData()
{
}

void CEachData::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SEARCH_DATE, m_search_date);
	DDX_Control(pDX, IDC_SEARCH_CURSEL, m_search_cursel);
	DDX_Control(pDX, IDC_START, m_start);
	DDX_Control(pDX, IDC_END, m_end);
	DDX_Control(pDX, IDC_SEARCH_LIST, m_search_list);
	DDX_Control(pDX, IDC_BUTTON1, m_button1);
	DDX_Control(pDX, IDC_BUTTON2, m_button2);
	DDX_Control(pDX, IDC_ERROR_ITEM1, m_error_item1);
	DDX_Control(pDX, IDC_ERROR_ITEM2, m_error_item2);
	DDX_Control(pDX, IDC_ERROR_ITEM3, m_error_item3);
	DDX_Control(pDX, IDC_ERROR_ITEM4, m_error_item4);
	DDX_Control(pDX, IDC_ERROR_ITEM5, m_error_item5);
	DDX_Control(pDX, IDC_PER1, m_per1);
	DDX_Control(pDX, IDC_PER2, m_per2);
	DDX_Control(pDX, IDC_PER3, m_per3);
	DDX_Control(pDX, IDC_PER4, m_per4);
	DDX_Control(pDX, IDC_PER5, m_per5);
}


BEGIN_MESSAGE_MAP(CEachData, CDialog)
	ON_BN_CLICKED(IDC_SEARCH_DATE, &CEachData::OnBnClickedSearchDate)
	ON_BN_CLICKED(IDC_SEARCH_CURSEL, &CEachData::OnBnClickedSearchCursel)
	ON_BN_CLICKED(IDC_BUTTON1, &CEachData::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CEachData::OnBnClickedButton2)	
END_MESSAGE_MAP()


// CEachData 메시지 처리기


BOOL CEachData::OnInitDialog()
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

	m_error_item1.SetWindowText(_T(""));
	m_error_item2.SetWindowText(_T(""));
	m_error_item3.SetWindowText(_T(""));
	m_error_item4.SetWindowText(_T(""));
	m_error_item5.SetWindowText(_T(""));
	m_per1.SetWindowText(_T(""));
	m_per2.SetWindowText(_T(""));
	m_per3.SetWindowText(_T(""));
	m_per4.SetWindowText(_T(""));
	m_per5.SetWindowText(_T(""));

	GetDlgItem(IDC_VIEW)->GetWindowRect(&rectview);
	ScreenToClient(&rectview);

	GetDlgItem(IDC_COLOR1)->GetWindowRect(&rectcolor1);
	ScreenToClient(&rectcolor1);
	GetDlgItem(IDC_COLOR2)->GetWindowRect(&rectcolor2);
	ScreenToClient(&rectcolor2);
	GetDlgItem(IDC_COLOR3)->GetWindowRect(&rectcolor3);
	ScreenToClient(&rectcolor3);
	GetDlgItem(IDC_COLOR4)->GetWindowRect(&rectcolor4);
	ScreenToClient(&rectcolor4);
	GetDlgItem(IDC_COLOR5)->GetWindowRect(&rectcolor5);
	ScreenToClient(&rectcolor5);

	x[0] = rectview.CenterPoint().x;
	y[0] = rectview.CenterPoint().y;
	init_x = rectview.CenterPoint().x;
	init_y = rectview.CenterPoint().y;
	width = rectview.Width() / 2.0;
	height = rectview.Height() / 2.0;
	pieColor[0] = RGB(255, 0, 0);
	pieColor[1] = RGB(255, 255, 0);
	pieColor[2] = RGB(0, 255, 0);
	pieColor[3] = RGB(0, 0, 255);
	pieColor[4] = RGB(255, 0, 255);

	return TRUE;
}


void CEachData::OnBnClickedSearchDate()
{
	m_button1.EnableWindow(true);
	m_button2.EnableWindow(false);
	m_search_list.EnableWindow(false);
	m_start.EnableWindow(true);
	m_end.EnableWindow(true);
	m_search_list.SelItemRange(false, 0, 21);
}


void CEachData::OnBnClickedSearchCursel()
{
	m_button1.EnableWindow(false);
	m_button2.EnableWindow(true);
	m_search_list.EnableWindow(true);
	m_start.EnableWindow(false);
	m_end.EnableWindow(false);
	m_search_list.SelItemRange(false, 0, 21);
}


void CEachData::OnBnClickedButton1()
{
	int start = m_start.GetCurSel();
	int end = m_end.GetCurSel();

	sum_err[0] = 0;
	sum_err[1] = 0;
	sum_err[2] = 0;
	sum_err[3] = 0;
	sum_err[4] = 0;

	if (start > end) {
		MessageBox(_T("시작하는 날짜가 끝나는 날짜보다 빨라야합니다."), _T("오류"), MB_OK | MB_ICONERROR);
	}
	else {
		for (int i = start; i <= end; i++) {
			SumError(i);
			FillResultChart();
		}
	}
}


void CEachData::OnBnClickedButton2()
{
	int cnt = m_search_list.GetCount();

	sum_err[0] = 0;
	sum_err[1] = 0;
	sum_err[2] = 0;
	sum_err[3] = 0;
	sum_err[4] = 0;

	for (int i = 0; i < cnt; i++) {
		if (m_search_list.GetSel(i)) {
			SumError(i);
			FillResultChart();
		}
	}
}


void CEachData::GetData()
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


void CEachData::FillComboBox()
{
	for (int i = 0; i < 22; i++) {
		CString str;
		str.Format(_T("%d  %02d"), read_val[i][0], read_val[i][1]);
		m_start.AddString(str);
		m_end.AddString(str);
	}
}


void CEachData::FillSearchListBox()
{
	m_search_list.ResetContent();
	for (int i = 0; i < 22; i++) {
		CString str;
		str.Format(_T(" %d             %02d                %d"), read_val[i][0], read_val[i][1], read_val[i][2]);
		m_search_list.AddString(str);
	}
}


void CEachData::SumError(int i)
{
	for (int j = 0; j < 5; j++) {
		sum_err[j] += read_val[i][18+j] + read_val[i][23+j];
	}

	str.Format(_T("%d"), sum_err[0]);
	m_error_item1.SetWindowTextW(str + "개");
	str.Format(_T("%d"), sum_err[1]);
	m_error_item2.SetWindowTextW(str + "개");
	str.Format(_T("%d"), sum_err[2]);
	m_error_item3.SetWindowTextW(str + "개");
	str.Format(_T("%d"), sum_err[3]);
	m_error_item4.SetWindowTextW(str + "개");
	str.Format(_T("%d"), sum_err[4]);
	m_error_item5.SetWindowTextW(str + "개");

	total = sum_err[0] + sum_err[1] + sum_err[2] + sum_err[3] + sum_err[4];

	for (int i = 0; i < 5; i++)
	{
		per[i] = (float)(sum_err[i]) / total * 100;
	}

	str.Format(_T("%.1f"), per[0]);
	m_per1.SetWindowText(str + "%");
	str.Format(_T("%.1f"), per[1]);
	m_per2.SetWindowText(str + "%");
	str.Format(_T("%.1f"), per[2]);
	m_per3.SetWindowText(str + "%");
	str.Format(_T("%.1f"), per[3]);
	m_per4.SetWindowText(str + "%");
	str.Format(_T("%.1f"), per[4]);
	m_per5.SetWindowText(str + "%");
}


void CEachData::FillResultChart()
{
	x[0] = (int)(width * cos((360 * per[0] / 100) * pi / 180)) + rectview.CenterPoint().x;
	y[0] = (int)(height * sin((360 * per[0] / 100) * pi / 180)) + rectview.CenterPoint().y;

	x[1] = (int)(width * cos((360 * (per[0] + per[1]) / 100) * pi / 180)) + rectview.CenterPoint().x;
	y[1] = (int)(height * sin((360 * (per[0] + per[1]) / 100) * pi / 180)) + rectview.CenterPoint().y;

	x[2] = (int)(width * cos((360 * (per[0] + per[1] + per[2]) / 100) * pi / 180)) + rectview.CenterPoint().x;
	y[2] = (int)(height * sin((360 * (per[0] + per[1] + per[2]) / 100) * pi / 180)) + rectview.CenterPoint().y;

	x[3] = (int)(width * cos((360 * (per[0] + per[1] + per[2] + per[3]) / 100) * pi / 180)) + rectview.CenterPoint().x;
	y[3] = (int)(height * sin((360 * (per[0] + per[1] + per[2] + per[3]) / 100) * pi / 180)) + rectview.CenterPoint().y;

	CClientDC dc(this);

	CBrush brush[5];
	brush[0].CreateSolidBrush(pieColor[0]);
	brush[1].CreateSolidBrush(pieColor[1]);
	brush[2].CreateSolidBrush(pieColor[2]);
	brush[3].CreateSolidBrush(pieColor[3]);
	brush[4].CreateSolidBrush(pieColor[4]);

	dc.SelectObject(&brush[0]);
	dc.Rectangle(&rectcolor1);
	dc.SelectObject(&brush[1]);
	dc.Rectangle(&rectcolor2);
	dc.SelectObject(&brush[2]);
	dc.Rectangle(&rectcolor3);
	dc.SelectObject(&brush[3]);
	dc.Rectangle(&rectcolor4);
	dc.SelectObject(&brush[4]);
	dc.Rectangle(&rectcolor5);

	if (sum_err[0])
	{
		dc.SelectObject(&brush[0]);
		dc.Ellipse(&rectview);
	}

	if (sum_err[1])
	{
		dc.SelectObject(&brush[1]);
		dc.Pie(rectview.TopLeft().x, rectview.TopLeft().y, rectview.BottomRight().x, rectview.BottomRight().y, init_x, init_y, x[0], y[0]);
	}

	if (sum_err[2])
	{
		dc.SelectObject(&brush[2]);
		dc.Pie(rectview.TopLeft().x, rectview.TopLeft().y, rectview.BottomRight().x, rectview.BottomRight().y, init_x, init_y, x[1], y[1]);
	}

	if (sum_err[3])
	{
		dc.SelectObject(&brush[3]);
		dc.Pie(rectview.TopLeft().x, rectview.TopLeft().y, rectview.BottomRight().x, rectview.BottomRight().y, init_x, init_y, x[2], y[2]);
	}

	if (sum_err[4])
	{
		dc.SelectObject(&brush[4]);
		dc.Pie(rectview.TopLeft().x, rectview.TopLeft().y, rectview.BottomRight().x, rectview.BottomRight().y, init_x, init_y, x[3], y[3]);
	}
}