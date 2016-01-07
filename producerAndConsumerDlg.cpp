
// producerAndConsumerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "producerAndConsumer.h"
#include "producerAndConsumerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define UM_RESURECEDATA WM_USER+10

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CproducerAndConsumerDlg 对话框



CproducerAndConsumerDlg::CproducerAndConsumerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CproducerAndConsumerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CproducerAndConsumerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, cmbSituation);
	DDX_Control(pDX, IDC_LOG_LIST, m_LogList);
}

BEGIN_MESSAGE_MAP(CproducerAndConsumerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_CBN_SELCHANGE(IDC_COMBO1, &CproducerAndConsumerDlg::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BTN_START, &CproducerAndConsumerDlg::OnBnClickedBtnStart)

END_MESSAGE_MAP()


// CproducerAndConsumerDlg 消息处理程序

BOOL CproducerAndConsumerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码
	cmbSituation.AddString(_T("Situation1"));
	cmbSituation.AddString(_T("Situation2"));
	cmbSituation.AddString(_T("Situation3"));
	cmbSituation.AddString(_T("Situation4"));
	cmbSituation.SetCurSel(0);

	GetDlgItem(IDC_PUTNUM_EDIT)->SetWindowTextW(_T("0"));
	GetDlgItem(IDC_GETNUM_EDIT)->SetWindowTextW(_T("0"));
	GetDlgItem(IDC_BUF_EDIT)->SetWindowTextW(_T("0"));
	GetDlgItem(IDC_PROD_EDIT)->SetWindowTextW(_T("0"));
	GetDlgItem(IDC_CONS_EDIT)->SetWindowTextW(_T("0"));

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CproducerAndConsumerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CproducerAndConsumerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CproducerAndConsumerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CproducerAndConsumerDlg::OnCbnSelchangeCombo1()
{
	// TODO:  在此添加控件通知处理程序代码
	
	switch (cmbSituation.GetCurSel())
	{
	case 2:
		GetDlgItem(IDC_PUTNUM_STATIC)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_PUTNUM_EDIT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_PUTNUM_SPIN)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_GETNUM_STATIC)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_GETNUM_EDIT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_GETNUM_SPIN)->ShowWindow(SW_HIDE);


		GetDlgItem(IDC_BUF_STATIC)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_PROD_STATIC)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CONS_STATIC)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_BUF_EDIT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_PROD_EDIT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CONS_EDIT)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_BUF_SPIN)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_PROD_SPIN)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CONS_SPIN)->ShowWindow(SW_HIDE);
		break;
	case 3:
		GetDlgItem(IDC_PUTNUM_STATIC)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_PUTNUM_EDIT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_PUTNUM_SPIN)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_GETNUM_STATIC)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_GETNUM_EDIT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_GETNUM_SPIN)->ShowWindow(SW_SHOW);

		GetDlgItem(IDC_BUF_STATIC)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_PROD_STATIC)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_CONS_STATIC)->ShowWindow(SW_SHOW);

		GetDlgItem(IDC_BUF_EDIT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_PROD_EDIT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_CONS_EDIT)->ShowWindow(SW_SHOW);

		GetDlgItem(IDC_BUF_SPIN)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_PROD_SPIN)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_CONS_SPIN)->ShowWindow(SW_SHOW);
		break;
	default:
		GetDlgItem(IDC_PUTNUM_STATIC)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_PUTNUM_EDIT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_PUTNUM_SPIN)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_GETNUM_STATIC)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_GETNUM_EDIT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_GETNUM_SPIN)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_BUF_STATIC)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_PROD_STATIC)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CONS_STATIC)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_BUF_EDIT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_PROD_EDIT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CONS_EDIT)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_BUF_SPIN)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_PROD_SPIN)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CONS_SPIN)->ShowWindow(SW_HIDE);
		break;
	}

}



const int limit = 30;  //生产总量
const int maxsize = 10; //缓冲区大小
const int kind = 7;  //水果的种类
int bufIdx = 0;    //当前缓冲区下标

int rowCount = -1;
CString buf[maxsize];    //缓冲区 （字符串）
//伪造的产品
CString product[] = { _T("AAAAA"), _T("BBBBB"), _T("CCCCC"), _T("DDDDD"), _T("EEEEE"), _T("FFFFF"), _T("GGGGG") };

HANDLE mutex, full, empty; //互斥锁，占用信号量，空闲信号量
HANDLE disp;    //用于控制屏幕打印的互斥锁

int rowNum = -1;


// 生产者子过程
DWORD WINAPI Producer(LPVOID param)
{
	CString strResu;
	int ct, idx;
	const int pwait = 100;
	srand(time(NULL)); //随机数播种

	WaitForSingleObject(disp, INFINITE);

	//CproducerAndConsumerDlg* pDlg = (CproducerAndConsumerDlg*)param;
	strResu = _T("Producer Start!");
	CString* str = new CString(strResu);
	::PostMessageA((HWND)param, UM_RESURECEDATA, (WPARAM)str, (LPARAM)str);

	//cout << "Producer Start!" << endl << endl;
	ReleaseMutex(disp);

	for (ct = 0; ct < limit; ct++)
	{
		idx = rand() % kind;

		WaitForSingleObject(disp, INFINITE);
		
		strResu.Format(_T("%s is ready!"), product[idx]);
		str = new CString(strResu);
		::PostMessageA((HWND)param, UM_RESURECEDATA, (WPARAM)str, (LPARAM)str);
		//cout << product[idx] << " is ready!" << endl << endl;
		ReleaseMutex(disp);

		WaitForSingleObject(empty, INFINITE); //请求一个空缓冲区，阻塞
		WaitForSingleObject(mutex, INFINITE); //请求互斥锁，阻塞
		buf[bufIdx++] = product[idx];

		WaitForSingleObject(disp, INFINITE);

		strResu.Format(_T("%s added to slot No.%d"), product[idx], bufIdx);
		str = new CString(strResu);
		::PostMessageA((HWND)param, UM_RESURECEDATA, (WPARAM)str, (LPARAM)str);
		//cout << product[idx] << " added to slot No. " << bufIdx << endl << endl;
		ReleaseMutex(disp);

		ReleaseMutex(mutex);    //释放互斥锁
		ReleaseSemaphore(full, 1, NULL);   //signal(full)
		Sleep(rand() % pwait + 100);  //休息一会
	}

	WaitForSingleObject(disp, INFINITE);
	strResu = _T("Producer Quit!");
	str = new CString(strResu);
	::PostMessageA((HWND)param, UM_RESURECEDATA, (WPARAM)str, (LPARAM)str);
	//cout << "Producer Quit!" << endl << endl;
	ReleaseMutex(disp);
	return 0;
}


// 消费者子过程
DWORD WINAPI Consumer(LPVOID param)
{
	CString strResu;
	//CString* pstrResu;
	int ct;
	const int cwait = 300;
	CString stuff;
	srand(time(NULL));

	WaitForSingleObject(disp, INFINITE);
	CproducerAndConsumerDlg* pDlg = (CproducerAndConsumerDlg*)param;
	strResu = _T("Consumer Start!");
	CString* str = new CString(strResu);
	::PostMessageA((HWND)param, UM_RESURECEDATA, (WPARAM)str, (LPARAM)str);
	//cout << "Consumer Start!" << endl << endl;
	ReleaseMutex(disp);

	for (ct = 0; ct < limit; ct++)
	{
		WaitForSingleObject(full, INFINITE); //请求一个满缓冲区，阻塞
		WaitForSingleObject(mutex, INFINITE); //请求互斥锁，阻塞
		stuff = buf[--bufIdx];

		WaitForSingleObject(disp, INFINITE);
		strResu.Format(_T("Consumer get %s from slot No. %d"), stuff, (bufIdx + 1));
		str = new CString(strResu);
		::PostMessageA((HWND)param, UM_RESURECEDATA, (WPARAM)str, (LPARAM)str);
		//cout << "Consumer get " << stuff << " from slot No. " << (bufIdx + 1) << endl << endl;
		ReleaseMutex(disp);

		ReleaseMutex(mutex);    //释放互斥锁
		ReleaseSemaphore(empty, 1, NULL);   //signal(empty)
		Sleep(rand() % cwait + 100);  //休息一会
	}

	WaitForSingleObject(disp, INFINITE);
	strResu = _T("Consumer Quit!");
	str = new CString(strResu);
	::PostMessageA((HWND)param, UM_RESURECEDATA, (WPARAM)str, (LPARAM)str);
	//cout << "Consumer Quit!" << endl << endl;
	ReleaseMutex(disp);
	return 0;
}


LRESULT CproducerAndConsumerDlg::OnResuReceData(WPARAM Wparam, LPARAM Lparam)
{
	//CString strResu = (LPCTSTR)Lparam;
	//m_LogList.InsertString(++rowCount, strResu);
	CString* str = (CString*)Lparam;
	m_LogList.InsertString(++rowCount, *str);
	 
	//GetDlgItem(IDC_LOG_LIST)->SetWindowTextW((LPCTSTR)Lparam);
	return TRUE;
}


// 第三种情况
void CproducerAndConsumerDlg::Situation3()
{
	//生产者线程与消费者线程的线程ID
	DWORD ProducerID, ConsumerID;
	//线程句柄
	HANDLE ProducerHandle, ConsumerHandle;

	//创建屏幕打印互斥锁
	disp = CreateMutex(NULL, FALSE, NULL);

	//创建生产者线程
	ProducerHandle = CreateThread(NULL, 0, Producer, (LPVOID)m_hWnd, 0, &ProducerID);
	//创建消费者线程
	ConsumerHandle = CreateThread(NULL, 0, Consumer, (LPVOID)m_hWnd, 0, &ConsumerID);
	
	MSG msg;
	while (::PeekMessageA(&msg, m_hWnd, WM_USER + 10, WM_USER + 10, PM_REMOVE))
	{
		if (msg.message == UM_RESURECEDATA)
		{
			WindowProc(msg.message,msg.wParam,msg.lParam);
			break;
		}
	}

	//创建互斥锁
	mutex = CreateMutex(NULL, FALSE, NULL);
	//创建缓冲区占用信号量
	full = CreateSemaphore(NULL, 0, maxsize, _T("full"));
	//创建缓冲区空闲信号量
	empty = CreateSemaphore(NULL, maxsize, maxsize, _T("empty"));

	//等待直到生产者线程执行完成
	if (ProducerHandle != NULL)
	{
		WaitForSingleObject(ProducerHandle, INFINITE);
		CloseHandle(ProducerHandle);
	}
	//等待直到消费者线程执行完成
	if (ConsumerHandle != NULL)
	{
		WaitForSingleObject(ConsumerHandle, INFINITE);
		CloseHandle(ConsumerHandle);
	}
}


void CproducerAndConsumerDlg::OnBnClickedBtnStart()
{
	// TODO:  在此添加控件通知处理程序代码


	switch (cmbSituation.GetCurSel())
	{
	case 0:
		
		break;
	case 1:
		break;
	case 2:
		Situation3();
		break;
	case 3:
		break;
	}
}


LRESULT CproducerAndConsumerDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	// TODO:  在此添加专用代码和/或调用基类
	if (message == UM_RESURECEDATA)
	{
		OnResuReceData(wParam,lParam);
	}
	else
		return CDialogEx::WindowProc(message, wParam, lParam);
}
