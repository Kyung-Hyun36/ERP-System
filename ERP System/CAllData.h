#pragma once
#include "afxdialogex.h"


// CAllData 대화 상자

class CAllData : public CDialog
{
	DECLARE_DYNAMIC(CAllData)

public:
	CAllData(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CAllData();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ALL_DATA };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	int read_val[22][28];
	int ob = 3;
	int sum_list, sum_make, sum_check;
	int make_work, check_work, per_work;
	int make_cost, check_cost, sum_cost;
	CString str, complete;

	CButton m_search_date;
	CButton m_search_cursel;
	CComboBox m_start;
	CComboBox m_end;
	CListBox m_search_list;
	CListBox m_result_list;
	CButton m_button1;
	CButton m_button2;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedSearchDate();
	afx_msg void OnBnClickedSearchCursel();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	void GetData();
	void FillComboBox();
	void FillSearchListBox();
	void FillResultListBox(int i);
};
