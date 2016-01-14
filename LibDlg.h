#pragma once


// LibDlg 对话框

class LibDlg : public CDialogEx
{
	DECLARE_DYNAMIC(LibDlg)

public:
	LibDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~LibDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
