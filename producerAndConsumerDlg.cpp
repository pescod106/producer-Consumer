
// producerAndConsumerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "producerAndConsumer.h"
#include "producerAndConsumerDlg.h"
#include "afxdialogex.h"
#include <List>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define UM_RESURECEDATA WM_USER+10
#define UM_BUFFINFO1 WM_USER+11
#define UM_BUFFINFO2 WM_USER+12
#define UM_BUFFINFO3 WM_USER+13
#define UM_PUTEDNUM WM_USER+14
#define UM_GETEDNUM WM_USER+15

#define ID_TIMER 1

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
	//DDX_Control(pDX, IDC_COMBO1, cmbSituation);
	DDX_Control(pDX, IDC_LOG_LIST, m_LogList);
}

BEGIN_MESSAGE_MAP(CproducerAndConsumerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//ON_CBN_SELCHANGE(IDC_COMBO1, &CproducerAndConsumerDlg::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BTN_START, &CproducerAndConsumerDlg::OnBnClickedBtnStart)

//	ON_WM_TIMER()
ON_BN_CLICKED(IDC_BTN_PAUSE, &CproducerAndConsumerDlg::OnBnClickedBtnPause)
ON_WM_TIMER()
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


	initEditToZero();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CproducerAndConsumerDlg::initEditToZero()
{
	//对所有的数字输入框置0
	GetDlgItem(IDC_PUTNUM_EDIT)->SetWindowTextW(_T("30"));
	GetDlgItem(IDC_GETNUM_EDIT)->SetWindowTextW(_T("30"));
	GetDlgItem(IDC_BUF1_EDIT)->SetWindowTextW(_T("10"));
	GetDlgItem(IDC_BUF2_EDIT)->SetWindowTextW(_T("10"));
	GetDlgItem(IDC_BUF3_EDIT)->SetWindowTextW(_T("10"));
	GetDlgItem(IDC_PROD_EDIT)->SetWindowTextW(_T("2"));
	GetDlgItem(IDC_CONS_EDIT)->SetWindowTextW(_T("2"));
	GetDlgItem(IDC_PUT_SPEED_EDIT)->SetWindowTextW(_T("500"));
	GetDlgItem(IDC_GET_SPEED_EDIT)->SetWindowTextW(_T("3000"));
	GetDlgItem(IDC_MOVE_SPEED_EDIT)->SetWindowTextW(_T("2000"));
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

int haveFinished = 0;//用于记录线程完成的个数
bool isFinishProduce = false;
HANDLE FinishedHandle;

 int putNum = 0;//生产数量
 int getNum = 0;//消费数量
 int buffer1_capacity = 0;//Buffer1容量
 int buffer2_capacity = 0;//Buffer2容量
 int buffer3_capacity = 0; //Buffer3容量
 int producer_num = 0;//生产者数目
 int consumer_num = 0;//消费者数目
 int put_speed = 0;//生产速度
 int get_speed = 0;//消费速度
 int move_speed = 0;//移动速度

int limit = 30;  //生产总量
const int maxsize = 10; //缓冲区大小
int buf1Idx = 0;    //当前缓冲区1下标
int buf2Idx = 0;    //当前缓冲区2下标
int buf3Idx = 0;    //当前缓冲区3下标

int putedNum = 0;
int getedNum = 0;

int rowCount = -1;
char buf1[maxsize];//缓冲1区 （字符串）
char buf2[maxsize];//缓冲2区 （字符串）
char buf3[maxsize];//缓冲3区 （字符串）

HANDLE buf1Idx_Mutex; //Buffer1下标的互斥锁

HANDLE buf1_Mutex, buf1_Full, buf1_Empty; //Buffer1的互斥锁，占用信号量，空闲信号量
HANDLE buf2_Mutex, buf2_Full, buf2_Empty; //Buffer2的互斥锁，占用信号量，空闲信号量
HANDLE buf3_Mutex, buf3_Full, buf3_Empty; //Buffer3的互斥锁，占用信号量，空闲信号量
HANDLE disp;    //用于控制屏幕打印的互斥锁

int rowNum = -1;

//产生随即字符
char randomCharcter()
{
	char result;
	srand(GetTickCount());
	result = rand() % 93 + 33;
	return result;
}

// 生产者子过程
UINT Producer(LPVOID param)
{
	ParamInfo* paramInfo = (ParamInfo*)param;
	int speed = paramInfo->speed;
	int id = paramInfo->id;
	HWND hWnd = paramInfo->m_hWnd;
	CString strResu;
	CList<char> list;
	int ct;
	const int pwait = 100;
	srand(GetTickCount()); //随机数播种

	WaitForSingleObject(disp, INFINITE);

	CString currentTime = CTime::GetCurrentTime().Format("%H:%M:%S");
	strResu.Format(_T("%s  生产者%d开始生产!"), currentTime, id);
	GetDlgItem(hWnd, IDC_LOG_LIST);
	
	CString* str = new CString(strResu);
	::PostMessage(hWnd, UM_RESURECEDATA, (WPARAM)str, (LPARAM)str);

	ReleaseMutex(disp);
	while (putedNum < putNum)
	{
		char result = randomCharcter();

		WaitForSingleObject(buf1_Empty, INFINITE); //请求一个空缓冲区，阻塞
		WaitForSingleObject(buf1_Mutex, INFINITE); //请求互斥锁，阻塞
		buf1[buf1Idx++] = result;
		putedNum++;

		//发送显示已经生产的数量信息
		WaitForSingleObject(disp, INFINITE);
		strResu.Format(_T("%d"), putedNum);
		str = new CString(strResu);
		::PostMessage(hWnd, UM_PUTEDNUM, (WPARAM)str, (LPARAM)str);
		ReleaseMutex(disp);

		//发送已经生产的所有产品
		WaitForSingleObject(disp, INFINITE);
		strResu=buf1; 
		strResu.Left(buf1Idx);
		str = new CString(strResu);
		::PostMessage(hWnd, UM_BUFFINFO1, (WPARAM)str, (LPARAM)str);
		ReleaseMutex(disp);

		WaitForSingleObject(disp, INFINITE);
		currentTime = CTime::GetCurrentTime().Format("%H:%M:%S");
		strResu.Format(_T("%s  生产者%d将 %s 加入到Buffer1【%d】"), currentTime, id,CString(result), buf1Idx);
		str = new CString(strResu);
		::PostMessage(hWnd, UM_RESURECEDATA, (WPARAM)str, (LPARAM)str);		
		ReleaseMutex(disp);

		ReleaseMutex(buf1_Mutex);    //释放互斥锁
		ReleaseSemaphore(buf1_Full, 1, NULL);   //signal(full)
		Sleep(rand() % pwait + speed);  //休息一会
	}
	WaitForSingleObject(FinishedHandle, INFINITE);
	haveFinished++;
	isFinishProduce = true;
	ReleaseMutex(FinishedHandle);

	WaitForSingleObject(disp, INFINITE);
	currentTime = CTime::GetCurrentTime().Format("%H:%M:%S");
	strResu.Format(_T("%s  生产者%d结束生产!"), currentTime, id);
	str = new CString(strResu);
	::PostMessage(hWnd, UM_RESURECEDATA, (WPARAM)str, (LPARAM)str);
	ReleaseMutex(disp);

	//发送已经生产的所有产品
	WaitForSingleObject(disp, INFINITE);
	strResu = buf1;
	strResu.Left(buf1Idx);
	str = new CString(strResu);
	::PostMessage(hWnd, UM_BUFFINFO1, (WPARAM)str, (LPARAM)str);
	ReleaseMutex(disp);

	return 0;
}


// 消费者子过程
UINT Consumer(LPVOID param)
{
	ParamInfo* paramInfo = (ParamInfo*)param;
	int speed = paramInfo->speed;
	int id = paramInfo->id;
	HWND hWnd = paramInfo->m_hWnd;
	CString strResu;
	//CString* pstrResu;
	int ct;
	const int cwait = 100;
	CString stuff;
	srand(GetTickCount());

	WaitForSingleObject(disp, INFINITE);
	CproducerAndConsumerDlg* pDlg = (CproducerAndConsumerDlg*)param;
	CString currentTime = CTime::GetCurrentTime().Format("%H:%M:%S");
	strResu.Format(_T("%s  消费者%d开始消费!"),currentTime,id);
	CString* str = new CString(strResu);
	::PostMessage(hWnd, UM_RESURECEDATA, (WPARAM)str, (LPARAM)str);
	ReleaseMutex(disp);
	bool isReturn = false;
	int maxNum;
	if (getNum<=putNum)
	{
		maxNum = getNum;
	}
	else
	{
		maxNum = putNum;
	}
	while (getedNum< maxNum)
	{
		while (true)
		{
			if (WAIT_TIMEOUT == WaitForSingleObject(buf3_Full, 100))
			{
				if (WAIT_TIMEOUT == WaitForSingleObject(buf2_Full, 100))
				{
					continue;
				}
				else
				{
					WaitForSingleObject(buf2_Mutex, INFINITE); //请求互斥锁，阻塞
					stuff = buf2[--buf2Idx];
					getedNum++;
					
					WaitForSingleObject(disp, INFINITE);
					currentTime = CTime::GetCurrentTime().Format("%H:%M:%S");
					strResu.Format(_T("%s  消费者%d从Buffer2取得 %s 序号为【%d】"), currentTime, id, stuff, (buf2Idx + 1));
					str = new CString(strResu);
					::PostMessage(hWnd, UM_RESURECEDATA, (WPARAM)str, (LPARAM)str);
					ReleaseMutex(disp);	

					WaitForSingleObject(disp, INFINITE);
					strResu.Format(_T("%d"), getedNum);
					str = new CString(strResu);
					::PostMessage(hWnd, UM_GETEDNUM, (WPARAM)str, (LPARAM)str);
					ReleaseMutex(disp);

					WaitForSingleObject(disp, INFINITE);
					strResu = buf2;
					strResu.Left(buf2Idx);
					str = new CString(strResu);
					::PostMessage(hWnd, UM_BUFFINFO3, (WPARAM)str, (LPARAM)str);
					ReleaseMutex(disp);

					ReleaseMutex(buf2_Mutex);    //释放互斥锁
					ReleaseSemaphore(buf2_Empty, 1, NULL);   //signal(empty)
					Sleep(rand() % speed+cwait);  //休息一会
					
					break;
				}
			}
			else
			{
				WaitForSingleObject(buf3_Mutex, INFINITE); //请求互斥锁，阻塞
				stuff = buf3[--buf3Idx];
				getedNum++;
				
				WaitForSingleObject(disp, INFINITE);
				currentTime = CTime::GetCurrentTime().Format("%H:%M:%S");
				strResu.Format(_T("%s  消费者%d从Buffer3取得 %s 序号【%d】"), currentTime, id, stuff, (buf3Idx + 1));
				str = new CString(strResu);
				::PostMessage(hWnd, UM_RESURECEDATA, (WPARAM)str, (LPARAM)str);
				ReleaseMutex(disp);

				WaitForSingleObject(disp, INFINITE);
				strResu.Format(_T("%d"), getedNum);
				str = new CString(strResu);
				::PostMessage(hWnd, UM_GETEDNUM, (WPARAM)str, (LPARAM)str);
				ReleaseMutex(disp);

				WaitForSingleObject(disp, INFINITE);
				strResu = buf3;
				strResu.Left(buf3Idx);
				str = new CString(strResu);
				::PostMessage(hWnd, UM_BUFFINFO2, (WPARAM)str, (LPARAM)str);
				ReleaseMutex(disp);

				ReleaseMutex(buf3_Mutex);    //释放互斥锁
				ReleaseSemaphore(buf3_Empty, 1, NULL);   //signal(empty)
				Sleep(rand() % speed+cwait);  //休息一会
				
				break;
			}
		}
	}

	WaitForSingleObject(disp, INFINITE);
	currentTime = CTime::GetCurrentTime().Format("%H:%M:%S");
	strResu.Format(_T("%s  消费者%d消费结束!"),currentTime,id);
	str = new CString(strResu);
	::PostMessage(hWnd, UM_RESURECEDATA, (WPARAM)str, (LPARAM)str);
	ReleaseMutex(disp);

	WaitForSingleObject(disp, INFINITE);
	strResu = buf2;
	strResu.Left(buf2Idx);
	str = new CString(strResu);
	::PostMessage(hWnd, UM_BUFFINFO3, (WPARAM)str, (LPARAM)str);
	ReleaseMutex(disp);

	WaitForSingleObject(disp, INFINITE);
	strResu = buf3;
	strResu.Left(buf3Idx);
	str = new CString(strResu);
	::PostMessage(hWnd, UM_BUFFINFO2, (WPARAM)str, (LPARAM)str);
	ReleaseMutex(disp);

	WaitForSingleObject(FinishedHandle, INFINITE);
	haveFinished++;
	ReleaseMutex(FinishedHandle);

	return 0;
}


UINT Move1(LPVOID param)
{
	CString strResu;
	//CString* pstrResu;
	int ct;
	const int cwait = 300;
	CString stuff;
	srand(GetTickCount());

	WaitForSingleObject(disp, INFINITE);
	CproducerAndConsumerDlg* pDlg = (CproducerAndConsumerDlg*)param;
	CString currentTime = CTime::GetCurrentTime().Format("%H:%M:%S");
	strResu = currentTime + _T("  Move1 Start!");
	CString* str = new CString(strResu);
	::PostMessage((HWND)param, UM_RESURECEDATA, (WPARAM)str, (LPARAM)str);
	ReleaseMutex(disp);
	char currentChar;
	int maxGet;
	if (putNum<getNum)
	{
		maxGet = putNum;
	}
	else
	{
		maxGet = getNum;
	}
	while (getedNum<maxGet)
	{
		if (isFinishProduce&&(buf1Idx==0))
		{
			break;
		}
		WaitForSingleObject(buf1_Full, INFINITE); //请求一个满缓冲区，阻塞		
		WaitForSingleObject(buf1_Mutex, INFINITE); //请求互斥锁，阻塞
		WaitForSingleObject(buf2_Empty, INFINITE);
		WaitForSingleObject(buf2_Mutex, INFINITE);
		currentChar = buf1[--buf1Idx];
		buf2[buf2Idx++] = currentChar;

		WaitForSingleObject(disp, INFINITE);
		currentTime = CTime::GetCurrentTime().Format("%H:%M:%S");
		strResu.Format(_T("%s  字符 %s 移动到Buffer2 序号Buffer1【%d】"), currentTime, CString(currentChar), (buf1Idx + 1));
		str = new CString(strResu);
		::PostMessage((HWND)param, UM_RESURECEDATA, (WPARAM)str, (LPARAM)str);
		ReleaseMutex(disp);

		//发送已经生产的所有产品
		WaitForSingleObject(disp, INFINITE);
		strResu = buf1;
		strResu.Left(buf1Idx);
		str = new CString(strResu);
		::PostMessage((HWND)param, UM_BUFFINFO1, (WPARAM)str, (LPARAM)str);
		ReleaseMutex(disp);

		//
		WaitForSingleObject(disp, INFINITE);
		strResu = buf2;
		strResu.Left(buf2Idx);
		str = new CString(strResu);
		::PostMessage((HWND)param, UM_BUFFINFO2, (WPARAM)str, (LPARAM)str);
		ReleaseMutex(disp);

		ReleaseMutex(buf2_Mutex);
		ReleaseSemaphore(buf2_Full, 1, NULL);

		ReleaseMutex(buf1_Mutex);    //释放互斥锁
		ReleaseSemaphore(buf1_Empty, 1, NULL);   //signal(empty)
		Sleep(rand() % move_speed + 100);  //休息一会
	}

	WaitForSingleObject(disp, INFINITE);
	currentTime = CTime::GetCurrentTime().Format("%H:%M:%S");
	strResu = currentTime + _T("  移动1结束!");
	str = new CString(strResu);
	::PostMessage((HWND)param, UM_RESURECEDATA, (WPARAM)str, (LPARAM)str);
	ReleaseMutex(disp);

	//发送已经生产的所有产品
	WaitForSingleObject(disp, INFINITE);
	strResu = buf1;
	strResu.Left(buf1Idx);
	str = new CString(strResu);
	::PostMessage((HWND)param, UM_BUFFINFO1, (WPARAM)str, (LPARAM)str);
	ReleaseMutex(disp);

	WaitForSingleObject(disp, INFINITE);
	strResu = buf2;
	strResu.Left(buf2Idx);
	str = new CString(strResu);
	::PostMessage((HWND)param, UM_BUFFINFO2, (WPARAM)str, (LPARAM)str);
	ReleaseMutex(disp);

	WaitForSingleObject(FinishedHandle, INFINITE);
	haveFinished++;
	ReleaseMutex(FinishedHandle);

	return 0;
}

UINT Move2(LPVOID param)
{
	CString strResu;
	//CString* pstrResu;
	int ct;
	const int cwait = 300;
	CString stuff;
	srand(GetTickCount());

	WaitForSingleObject(disp, INFINITE);
	CproducerAndConsumerDlg* pDlg = (CproducerAndConsumerDlg*)param;
	CString currentTime = CTime::GetCurrentTime().Format("%H:%M:%S");
	strResu = currentTime + _T("  Move2 Start!");
	CString* str = new CString(strResu);
	::PostMessage((HWND)param, UM_RESURECEDATA, (WPARAM)str, (LPARAM)str);
	ReleaseMutex(disp);
	char currentChar;//从buffer1中获取的字符
	int maxGet;
	if (putNum<getNum)
	{
		maxGet = putNum;
	}
	else
	{
		maxGet = getNum;
	}
	while (getedNum<maxGet)
	{
		if (isFinishProduce && (buf1Idx == 0))
		{
			break;
		}
		WaitForSingleObject(buf1_Full, INFINITE); //请求一个满缓冲区，阻塞		
		WaitForSingleObject(buf1_Mutex, INFINITE); //请求互斥锁，阻塞

		WaitForSingleObject(buf3_Empty, INFINITE);
		WaitForSingleObject(buf3_Mutex, INFINITE);
		currentChar = buf1[--buf1Idx];
		buf2[buf3Idx++] = currentChar;

		WaitForSingleObject(disp, INFINITE);
		currentTime = CTime::GetCurrentTime().Format("%H:%M:%S");
		strResu.Format(_T("%s  字符 %s 移动到Buffer3 序号Buffer1【%d】"), currentTime, CString(currentChar),(buf1Idx+1));
		str = new CString(strResu);
		::PostMessage((HWND)param, UM_RESURECEDATA, (WPARAM)str, (LPARAM)str);		
		ReleaseMutex(disp);

		//发送已经生产的所有产品
		WaitForSingleObject(disp, INFINITE);
		strResu = buf1;
		strResu.Left(buf1Idx);
		str = new CString(strResu);
		::PostMessage((HWND)param, UM_BUFFINFO1, (WPARAM)str, (LPARAM)str);
		ReleaseMutex(disp);

		WaitForSingleObject(disp, INFINITE);
		strResu = buf3;
		strResu.Left(buf3Idx);
		str = new CString(strResu);
		::PostMessage((HWND)param, UM_BUFFINFO3, (WPARAM)str, (LPARAM)str);
		ReleaseMutex(disp);

		ReleaseMutex(buf3_Mutex);
		ReleaseSemaphore(buf3_Full, 1, NULL);

		ReleaseMutex(buf1_Mutex);    //释放互斥锁
		ReleaseSemaphore(buf1_Empty, 1, NULL);   //signal(empty)
		Sleep(rand() % move_speed + 100);  //休息一会
	}

	WaitForSingleObject(disp, INFINITE);
	currentTime = CTime::GetCurrentTime().Format("%H:%M:%S");
	strResu = currentTime + _T("  移动2结束!");
	str = new CString(strResu);
	::PostMessage((HWND)param, UM_RESURECEDATA, (WPARAM)str, (LPARAM)str);
	ReleaseMutex(disp);

	//发送已经生产的所有产品
	WaitForSingleObject(disp, INFINITE);
	strResu = buf1;
	strResu.Left(buf1Idx);
	str = new CString(strResu);
	::PostMessage((HWND)param, UM_BUFFINFO1, (WPARAM)str, (LPARAM)str);
	ReleaseMutex(disp);

	WaitForSingleObject(disp, INFINITE);
	strResu = buf3;
	strResu.Left(buf3Idx);
	str = new CString(strResu);
	::PostMessage((HWND)param, UM_BUFFINFO3, (WPARAM)str, (LPARAM)str);
	ReleaseMutex(disp);

	WaitForSingleObject(FinishedHandle, INFINITE);
	haveFinished++;
	ReleaseMutex(FinishedHandle);

	return 0;
}


// 显示已经生产与消费的个数

LRESULT CproducerAndConsumerDlg::showNumberOfP(WPARAM Wparam, LPARAM Lparam)
{
	CString *str = (CString*)Lparam;
	GetDlgItem(IDC_BUFIN_EDIT)->SetWindowText(*str);
	return TRUE;
}

LRESULT CproducerAndConsumerDlg::showBuffer1Content(WPARAM Wparam, LPARAM Lparam)
{
	//int currentRow = 0;
	//m_buff1List.ResetContent();
	CString *str = (CString*)Lparam;
	CString strResu = CString(*str);
	GetDlgItem(IDC_BUF1_CONTENT_EDIT)->SetWindowText(strResu);
	//m_buff1List.InsertString(currentRow, strResu);
	/*CString strAdd;
	int length = strResu.GetLength();
	char content = NULL;
	for (int i = 0; i < length; i++)
	{
		strAdd = strResu.Mid(i, i + 1);
		m_buff1List.InsertString(currentRow, strAdd);
		currentRow++;
	}*/
	return TRUE;
}

LRESULT CproducerAndConsumerDlg::showBuffer2Content(WPARAM Wparam, LPARAM Lparam)
{
	CString *str = (CString*)Lparam;
	CString strResu = CString(*str);
	GetDlgItem(IDC_BUF2_CONTENT_EDIT)->SetWindowText(strResu);
	return TRUE;
}

LRESULT CproducerAndConsumerDlg::showBuffer3Content(WPARAM Wparam, LPARAM Lparam)
{
	CString *str = (CString*)Lparam;
	CString strResu = CString(*str);
	GetDlgItem(IDC_BUF3_CONTENT_EDIT)->SetWindowText(strResu);
	return TRUE;
}

LRESULT CproducerAndConsumerDlg::showNumberOfC(WPARAM Wparam, LPARAM Lparam)
{
	CString *str = (CString*)Lparam;
	GetDlgItem(IDC_BUFOUT_EDIT)->SetWindowText(*str);
	return TRUE;
}


LRESULT CproducerAndConsumerDlg::OnResuReceData(WPARAM Wparam, LPARAM Lparam)
{
	CString* str = (CString*)Lparam;
	m_LogList.InsertString(++rowCount, *str);
	m_LogList.SetCurSel(rowCount);
	return TRUE;
}



/*
初始化所有的全局变量
*/
void CproducerAndConsumerDlg::initGlobalVariable()
{
	CString str;
	GetDlgItem(IDC_PUTNUM_EDIT)->GetWindowText(str);
	putNum = _ttoi(str);
	GetDlgItem(IDC_GETNUM_EDIT)->GetWindowText(str);
	getNum = _ttoi(str);
	GetDlgItem(IDC_BUF1_EDIT)->GetWindowText(str);
	buffer1_capacity = _ttoi(str);
	GetDlgItem(IDC_BUF2_EDIT)->GetWindowText(str);
	buffer2_capacity = _ttoi(str);
	GetDlgItem(IDC_BUF3_EDIT)->GetWindowText(str);
	buffer3_capacity = _ttoi(str);
	GetDlgItem(IDC_PROD_EDIT)->GetWindowText(str);
	producer_num = _ttoi(str);
	GetDlgItem(IDC_CONS_EDIT)->GetWindowText(str);
	consumer_num = _ttoi(str);
	GetDlgItem(IDC_PUT_SPEED_EDIT)->GetWindowText(str);
	put_speed = _ttoi(str);
	GetDlgItem(IDC_GET_SPEED_EDIT)->GetWindowText(str);
	get_speed = _ttoi(str);
	GetDlgItem(IDC_MOVE_SPEED_EDIT)->GetWindowText(str);
	move_speed = _ttoi(str);
	putedNum = 0;
	getedNum = 0;
	rowCount = -1;
	buf1Idx = 0;    //当前缓冲区1下标
	buf2Idx = 0;    //当前缓冲区2下标
	buf3Idx = 0;
}
long timeStart = GetTickCount();
void CproducerAndConsumerDlg::OnBnClickedBtnStart()
{
	// TODO:  在此添加控件通知处理程序代码
	m_LogList.ResetContent();		
	initGlobalVariable();
	SetTimer(1,1,0);
	Situation();
	int startThreadNum = 2;
	CString str;
	GetDlgItem(IDC_PROD_EDIT)->GetWindowText(str);
	startThreadNum += _ttoi(str);
	GetDlgItem(IDC_CONS_EDIT)->GetWindowText(str);
	startThreadNum += _ttoi(str);
	str.Format(_T("%d"),startThreadNum);
	SetDlgItemText(IDC_THREADNUM_STATIC,str);
}

LRESULT CproducerAndConsumerDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	// TODO:  在此添加专用代码和/或调用基类
	if (message == UM_RESURECEDATA)
	{
		OnResuReceData(wParam,lParam);
	}
	else if (message == UM_PUTEDNUM)
	{
		showNumberOfP(wParam, lParam);
	}
	else if (message == UM_GETEDNUM)
	{
		showNumberOfC(wParam, lParam);
	}
	else if (message == UM_BUFFINFO1)
	{
		showBuffer1Content(wParam, lParam);
	}
	else if (message == UM_BUFFINFO2)
	{
		showBuffer2Content(wParam, lParam);
	}
	else if (message == UM_BUFFINFO3)
	{
		showBuffer3Content(wParam, lParam);
	}

	else 
		return CDialogEx::WindowProc(message, wParam, lParam);
}


//线程句柄
CWinThread* Move1Handle;
CWinThread* Move2Handle;
CList<CWinThread*> ProducerHandle;
CList<CWinThread*> ConsumerHandle;
// 第四种情况
void CproducerAndConsumerDlg::Situation()
{
	//生产者线程与消费者线程的线程ID
	DWORD ProducerID, ConsumerID, Move1ID, Move2ID;
	
	FinishedHandle = CreateMutex(NULL,FALSE,NULL);
	//创建屏幕打印互斥锁
	disp = CreateMutex(NULL, FALSE, NULL);

	//创建互斥锁
	buf1_Mutex = CreateMutex(NULL, FALSE, NULL);
	//创建缓冲区占用信号量
	buf1_Full = CreateSemaphore(NULL, 0, maxsize, _T("full1"));
	//创建缓冲区空闲信号量
	buf1_Empty = CreateSemaphore(NULL, maxsize, maxsize, _T("empty1"));
	//
	buf2_Mutex = CreateMutex(NULL, FALSE, NULL);

	buf2_Full = CreateSemaphore(NULL, 0, maxsize, _T("full2"));

	buf2_Empty = CreateSemaphore(NULL, maxsize, maxsize, _T("empty2"));

	buf3_Mutex = CreateMutex(NULL, FALSE, NULL);

	buf3_Full = CreateSemaphore(NULL, 0, maxsize, _T("full3"));

	buf3_Empty = CreateSemaphore(NULL, maxsize, maxsize, _T("empty3"));

	for (int i = 1; i <= producer_num; i++)
	{
		ParamInfo *producerSpeed = new  ParamInfo;
		producerSpeed->id = i;
		producerSpeed->speed = put_speed;
		producerSpeed->m_hWnd = m_hWnd;
		//创建生产者线程
		ProducerHandle.AddTail(AfxBeginThread(Producer, (LPVOID)producerSpeed, 0, 0, 0, NULL));
	}
	
	//move线程
	Move1Handle = AfxBeginThread(Move1, (LPVOID)m_hWnd, 0, 0, 0, NULL);
	Move2Handle = AfxBeginThread(Move2, (LPVOID)m_hWnd, 0, 0, 0, NULL);
	for (int i = 1; i <= consumer_num; i++)
	{
		ParamInfo *consumerSpeed = new  ParamInfo;
		consumerSpeed->id = i;
		consumerSpeed->speed = get_speed;
		consumerSpeed->m_hWnd = m_hWnd;
		//创建消费者线程
		ProducerHandle.AddTail(AfxBeginThread(Consumer, (LPVOID)consumerSpeed, 0, 0, 0, NULL));
	}
	SetTimer(2,10,NULL);

	MSG msg;
	while (::PeekMessageA(&msg, m_hWnd, WM_USER + 10, WM_USER + 10, PM_REMOVE))
	{
		if (msg.message == UM_RESURECEDATA)
		{
			WindowProc(msg.message, msg.wParam, msg.lParam);
			break;
		}
	}

	//等待直到生产者线程执行完成
	if (!ProducerHandle.IsEmpty())
	{
		HANDLE handle;
		for (int i = 0; i < ProducerHandle.GetCount(); i++)
		{
			handle = ProducerHandle.GetAt(ProducerHandle.FindIndex(i));
			WaitForSingleObject(handle, INFINITE);
			TerminateThread(handle, NULL);
		}
		
	}
	//等待直到消费者线程执行完成
	if (!ConsumerHandle.IsEmpty())
	{
		HANDLE handle;
		
		for (int i = 0; i < ConsumerHandle.GetCount(); i++)
		{
			handle = ConsumerHandle.GetAt(ConsumerHandle.FindIndex(i));
			WaitForSingleObject(handle, INFINITE);
			TerminateThread(handle, NULL);
			//CloseHandle(handle);
		}
		TerminateThread(Move1Handle,NULL);
		TerminateThread(Move2Handle,NULL);
		
	}
}

void CproducerAndConsumerDlg::showBufferContent()
{
	int i;
	m_buff1List.ResetContent();
	for (i = 0; i < buf1Idx; i++)
	{
		m_buff1List.InsertString(i, CString(buf1[i]));
	}
}
bool pause = false;
void CproducerAndConsumerDlg::OnBnClickedBtnPause()
{
	// TODO:  在此添加控件通知处理程序代码
	if (!pause)
	{
		if (Move1Handle)
		{
			Move1Handle->SuspendThread();
		}
		if (Move2Handle)
		{
			Move2Handle->SuspendThread();
		}
		if (!ProducerHandle.IsEmpty())
		{
			CWinThread* handle;
			for (int i = 0; i < ProducerHandle.GetCount(); i++)
			{
				handle = ProducerHandle.GetAt(ProducerHandle.FindIndex(i));
				handle->SuspendThread();
			}
		}
		if (!ConsumerHandle.IsEmpty())
		{
			CWinThread* handle;
			for (int i = 0; i < ConsumerHandle.GetCount(); i++)
			{
				handle = ConsumerHandle.GetAt(ConsumerHandle.FindIndex(i));
				handle->SuspendThread();
			}
		}
		pause = true;
	}
	else
	{
		if (Move1Handle)
		{
			Move1Handle->ResumeThread();
		}
		if (Move2Handle)
		{
			Move2Handle->ResumeThread();
		}
		if (!ProducerHandle.IsEmpty())
		{
			CWinThread* handle;
			for (int i = 0; i < ProducerHandle.GetCount(); i++)
			{
				handle = ProducerHandle.GetAt(ProducerHandle.FindIndex(i));
				handle->ResumeThread();
			}
		}
		if (!ConsumerHandle.IsEmpty())
		{
			CWinThread* handle;
			for (int i = 0; i < ConsumerHandle.GetCount(); i++)
			{
				handle = ConsumerHandle.GetAt(ConsumerHandle.FindIndex(i));
				handle->ResumeThread();
			}
		}
		pause = false;
	}
}


void CproducerAndConsumerDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	CString str;
	long timeEnd;
	long timeUse;
	int numberOfRunThread = 0;
	DWORD code;
	CWinThread* handle;
	GetDlgItem(IDC_RUN_NUM_STATIC)->GetWindowText(str);
	if (str == "0")
	{
		KillTimer(1);
		KillTimer(2);
	}
	switch (nIDEvent)
	{
	case 1:		
		timeEnd = GetTickCount();
		timeUse = timeEnd - timeStart;
		str.Format(_T("%d"), timeUse);
		GetDlgItem(IDC_BUFTIME_EDIT)->SetWindowText(str);
		break;
	case 2:
		GetExitCodeThread(Move1Handle->m_hThread, &code);
		if (code == STILL_ACTIVE)
		{
			numberOfRunThread++;
		}
		GetExitCodeThread(Move2Handle->m_hThread, &code);
		if (code == STILL_ACTIVE)
		{
			numberOfRunThread++;
		}
		for (int i = 0; i < ProducerHandle.GetCount(); i++)
		{
			handle = ProducerHandle.GetAt(ProducerHandle.FindIndex(i));
			GetExitCodeThread(handle->m_hThread, &code);
			if (code == STILL_ACTIVE)
			{
				numberOfRunThread++;
			}
		}
		for (int i = 0; i < ConsumerHandle.GetCount(); i++)
		{
			handle = ConsumerHandle.GetAt(ConsumerHandle.FindIndex(i));
			GetExitCodeThread(handle->m_hThread, &code);
			if (code == STILL_ACTIVE)
			{
				numberOfRunThread++;
			}
		}
		str.Format(_T("%d"), numberOfRunThread);
		SetDlgItemText(IDC_RUN_NUM_STATIC,str);
		break;
	default:
		CDialogEx::OnTimer(nIDEvent);
		break;
	}	
}
