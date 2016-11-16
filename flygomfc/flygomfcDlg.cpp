
// flygomfcDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "flygomfc.h"
#include "flygomfcDlg.h"
#include "afxdialogex.h"
#include "src/tool.h"
#include <vector>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

//��ʼ����ȫ�ֱ���
BOOL bTreadRun;
int runCount;

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	// ʵ��
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


// CflygomfcDlg �Ի���



CflygomfcDlg::CflygomfcDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CflygomfcDlg::IDD, pParent)
	, url(_T("http://v.qq.com/x/cover/4mz2zy4nxjjqqbp/k0020goctd2.html?ptag=bl.zy.bs_dfzc_41.161026&volume=0\r\nhttp://v.qq.com/x/cover/4mz2zy4nxjjqqbp/p002077glsm.html?ptag=bl.zy.bs_dfzc_42.161026&volume=0\r\nhttp://v.qq.com/x/cover/4mz2zy4nxjjqqbp/e00203bcxtq.html?ptag=bl.zy.bs_dfzc_44.161026&volume=0"))
	, loopsum(1000000)
	, loopstoptime(75)
	, myIE(_T("C:\\Program Files (x86)\\Google\\Chrome\\Application\\chrome.exe"))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CflygomfcDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, url);
	DDX_Text(pDX, IDC_EDIT2, loopsum);
	DDX_Text(pDX, IDC_EDIT3, loopstoptime);
	DDV_MinMaxInt(pDX, loopsum, 1, INT_MAX);
	DDV_MinMaxInt(pDX, loopstoptime, 0, INT_MAX);
	DDX_Text(pDX, IDC_EDIT4, myIE);
}

BEGIN_MESSAGE_MAP(CflygomfcDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CflygomfcDlg::OnBnClickedOk)
	ON_MESSAGE(WM_SHOWTASK,OnShowTask)
	ON_WM_SIZE()
	ON_WM_DESTROY()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_OPENFILE, &CflygomfcDlg::OnBnClickedOpenfile)
	ON_BN_CLICKED(IDC_STOP, &CflygomfcDlg::OnBnClickedStop)
END_MESSAGE_MAP()


// CflygomfcDlg ��Ϣ�������

BOOL CflygomfcDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	//��ʼ��
	SetWindowText(_T("Let's Go......"));
	bTreadRun = FALSE;

	//---------------------------������ʾ---------------------------------//

	m_nid.cbSize  = (DWORD)sizeof(NOTIFYICONDATA);
	m_nid.hWnd    = this->m_hWnd;
	m_nid.uID     = IDR_MAINFRAME;
	m_nid.uFlags  = NIF_ICON | NIF_MESSAGE | NIF_TIP ;
	m_nid.uCallbackMessage = WM_SHOWTASK;             // �Զ������Ϣ����
	m_nid.hIcon   = LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDR_MAINFRAME));
	wcscpy_s(m_nid.szTip, _T("Show me click me"));              // ��Ϣ��ʾ��Ϊ"����������"��VS2008 UNICODE������wcscpy_s()����
	Shell_NotifyIcon(NIM_ADD, &m_nid);                // �����������ͼ��
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CflygomfcDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CflygomfcDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CflygomfcDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CflygomfcDlg::OnBnClickedOk(){	
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//	CDialogEx::OnOK();
	//	ShellExecute(0, NULL, L"http://www.sina.com.cn", NULL,NULL, SW_NORMAL); 
	//	open_ie_with_url(L"C:\Program Files (x86)\Google\Chrome\Application\chrome.exe",L"http://www.sina.com.cn");

	UpdateData(TRUE);
	if(""==myIE){
		AfxMessageBox(_T("��ѡ���������"));
		return;
	}
	if(""==url){
		AfxMessageBox(_T("��������ַ��"));
		return;
	}
	if(!bTreadRun){
		bTreadRun = TRUE;
		pThread = AfxBeginThread(ThreadFunc,this);
		SetWindowText(_T("����ִ������....."));
	}else{
		AfxMessageBox(_T("�����������У���ֹͣ����������"));
	}
}

LRESULT CflygomfcDlg::OnShowTask(WPARAM wParam, LPARAM lParam){
	if(wParam != IDR_MAINFRAME){
		return 1;
	}
	switch(lParam)	{
	case WM_RBUTTONUP:                                        // �Ҽ�����ʱ�����˵�
		{
			LPPOINT lpoint = new tagPOINT;
			::GetCursorPos(lpoint);                    // �õ����λ��
			CMenu menu;
			menu.CreatePopupMenu();                    // ����һ������ʽ�˵�
			menu.AppendMenu(MF_STRING, WM_DESTROY, _T("�˳�"));
			menu.TrackPopupMenu(TPM_LEFTALIGN, lpoint->x ,lpoint->y, this);
			HMENU hmenu = menu.Detach();
			menu.DestroyMenu();
			delete lpoint;
		}
		break;
	case WM_LBUTTONDBLCLK:                                // ˫������Ĵ���
		{
			this->ShowWindow(SW_SHOWNORMAL);         // ��ʾ������
		}
		break;
	}
	return 0;
}


void CflygomfcDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	if(nType == SIZE_MINIMIZED) {  
		ShowWindow(SW_HIDE); // ����С���У�����������
	}  
}


void CflygomfcDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: �ڴ˴������Ϣ����������
	KillIE(myIE);
	Shell_NotifyIcon(NIM_DELETE, &m_nid);    

}


void CflygomfcDlg::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	ShowWindow(SW_HIDE); // ����С���У�����������
	//	CDialogEx::OnClose();
}

UINT CflygomfcDlg::ThreadFunc(LPVOID pParam){
	CflygomfcDlg *mDlg=(CflygomfcDlg *)pParam;
	STARTUPINFO si={sizeof(si)};
	si.dwFlags=STARTF_USESHOWWINDOW;
	si.wShowWindow=true;
	PROCESS_INFORMATION pi;
	CString cmdline;

	CString cutStr;
	CString runStr;
	int pos1 = 0;
	int num = 0;
	int j = 0;	
	CString title;
	runCount = 0;
	for(runCount=0;runCount<mDlg->loopsum;runCount++){
		if(bTreadRun==false){
			return 0;
		}
		pos1 = 0;
		num = 0;
//		leftStr = mDlg->url;
//		rightStr = mDlg->url;
		cutStr = mDlg->url;

		while (-1!=pos1){
			pos1 = cutStr.FindOneOf(_T("\n"));
			if(-1==pos1){
				runStr = cutStr;
			}else{				
				runStr =  cutStr.Left(pos1);
				num = cutStr.GetLength()-pos1-1;
				cutStr = cutStr.Right(num);
			}

			//����ǹȸ����������Ӳ���
			if(mDlg->myIE.FindOneOf(_T("chrome.exe"))){
				cmdline = '\"'+mDlg->myIE+_T("\" --disable-images \"")+runStr +'\"';
			}else{
				cmdline = '\"'+mDlg->myIE+'\"'+' '+'\"'+runStr +'\"';
			}

			CreateProcess(mDlg->myIE,(LPWSTR)(LPCWSTR)(cmdline),NULL,NULL,false,0,NULL,NULL,&si,&pi);			
			CloseHandle(pi.hThread);
			CloseHandle(pi.hProcess);
		}

		//��ʱ

		num = mDlg->loopstoptime;
		j = 0;
		while ((j<num)){
			//�ⲿ���ƽ����߳�
			title.Format(_T("����ִ�����񣬵�%d�����񣬵�ǰ����������%d��......"),runCount+1,j);
			if(!bTreadRun){
				return 0;
			}
			Sleep(1000);			
			mDlg->SetWindowText(title);
			j++;
		}	
		//�ر������
		KillIE(mDlg->myIE);

		Sleep(1000);		
	}
	mDlg->SetWindowText(_T("��������ִ����ϣ�"));
	return 0;
}


void CflygomfcDlg::OnBnClickedOpenfile()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString FilePathName;
	CFileDialog dlg(TRUE, //TRUEΪOPEN�Ի���FALSEΪSAVE AS�Ի���
		NULL,
		NULL,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		(LPCTSTR)_TEXT("EXE Files (*.exe)|*.exe|All Files (*.*)|*.*||"),
		NULL);
	if(dlg.DoModal()==IDOK) {
		myIE=dlg.GetPathName(); //�ļ�����������FilePathName��
		UpdateData(FALSE);
	}
}


void CflygomfcDlg::OnBnClickedStop()
{
	CString msg;
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(bTreadRun==FALSE){
		return;
	}
	bTreadRun = FALSE;
	SetWindowText(_T("����ֹͣ����....."));
	Sleep(1000);
	KillIE(myIE);
	SetWindowText(_T("Let's Go......"));
	msg.Format(_T("�������ֶ�ֹͣ���������%d������"),runCount);
	AfxMessageBox(msg);
}

BOOL CflygomfcDlg::KillIE(CString iePath){
	std::vector<CString> proVector;
	CString killPro;
	int pos = 0;
	pos = iePath.GetLength()-iePath.ReverseFind('\\')-1;
	killPro = iePath.Right(pos);		
	proVector.push_back(killPro);
	return LookUpProcessAndKill(proVector);
}
