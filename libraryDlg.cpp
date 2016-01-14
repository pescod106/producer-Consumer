// libraryDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "producerAndConsumer.h"
#include "libraryDlg.h"
#include "afxdialogex.h"
#include <locale.h>

// libraryDlg 对话框

IMPLEMENT_DYNAMIC(libraryDlg, CDialogEx)

libraryDlg::libraryDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(libraryDlg::IDD, pParent)
{

}

libraryDlg::~libraryDlg()
{
}

void libraryDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_Edit);
}


BEGIN_MESSAGE_MAP(libraryDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &libraryDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// libraryDlg 消息处理程序


void libraryDlg::OnBnClickedButton1()
{
	// TODO:  在此添加控件通知处理程序代码
	// TODO:  在此添加控件通知处理程序代码
	setlocale(LC_CTYPE, "chs");
	m_Edit.GetDlgItem(IDC_EDIT1);

	CStdioFile file;
	CString str;
	CString str2;
	if (file.Open(_T("my.txt"), CFile::modeRead))
	{
		while (file.ReadString(str))
		{
			str2 += str + _T("\r\n");
		}
		m_Edit.SetWindowText(str2);

		str.ReleaseBuffer();
	}
	else
	{
		MessageBox(_T("提示"), _T("文件读取失败！"), MB_OK);
	}
}
