#pragma once
#include "afxdialogex.h"


// CEachData 대화 상자

class CEachData : public CDialog
{
	DECLARE_DYNAMIC(CEachData)

public:
	CEachData(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CEachData();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EACH_DATA };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	int read_val[22][28];
	int ob = 3;
	int sum_err[5];
	float per[5];
	int x[4], y[4];
	int init_x, init_y;
	int total;
	double width, height;
	CString str;
	CRect rectview;
	CRect rectcolor1, rectcolor2, rectcolor3, rectcolor4, rectcolor5;
	COLORREF pieColor[5];

	CButton m_search_date;
	CButton m_search_cursel;
	CComboBox m_start;
	CComboBox m_end;
	CListBox m_search_list;
	CButton m_button1;
	CButton m_button2;
	CStatic m_error_item1;
	CStatic m_error_item2;
	CStatic m_error_item3;
	CStatic m_error_item4;
	CStatic m_error_item5;
	CStatic m_per1;
	CStatic m_per2;
	CStatic m_per3;
	CStatic m_per4;
	CStatic m_per5;
	afx_msg void OnBnClickedSearchDate();
	afx_msg void OnBnClickedSearchCursel();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	virtual BOOL OnInitDialog();
	void GetData();
	void FillComboBox();
	void FillSearchListBox();
	void SumError(int i);
	void FillResultChart();
};
