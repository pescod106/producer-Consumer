
// producerAndConsumerDlg.h : 头文件
//

#pragma once
#include "afxwin.h"


// CproducerAndConsumerDlg 对话框
class CproducerAndConsumerDlg : public CDialogEx
{
// 构造
public:
	CproducerAndConsumerDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_PRODUCERANDCONSUMER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	// 对应四种情况
	CComboBox cmbSituation;
	afx_msg void OnCbnSelchangeCombo1();
	//int BufferCapacity = 0;
	// 输入日志
	CListBox m_LogList;
	int BufferCapacity;//buffen容量
	int ProdNum;//生产个数
	int ConsNum;//消费个数
	int ProducerNum;//生产者个数
	int ConsumerNum;//消费者个数
	// 第四种情况
	void Situation3();
	afx_msg LRESULT OnResuReceData(WPARAM Wparam,LPARAM Lparam);
	afx_msg void OnBnClickedBtnStart();
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
};
