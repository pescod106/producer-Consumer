#pragma once
#include "afxwin.h"


// libraryDlg 对话框

class libraryDlg : public CDialogEx
{
	DECLARE_DYNAMIC(libraryDlg)

public:
	libraryDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~libraryDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	CEdit m_Edit;
};
