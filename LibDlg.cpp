// LibDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "producerAndConsumer.h"
#include "LibDlg.h"
#include "afxdialogex.h"


// LibDlg 对话框

IMPLEMENT_DYNAMIC(LibDlg, CDialogEx)

LibDlg::LibDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(LibDlg::IDD, pParent)
{

}

LibDlg::~LibDlg()
{
}

void LibDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(LibDlg, CDialogEx)
END_MESSAGE_MAP()


// LibDlg 消息处理程序
