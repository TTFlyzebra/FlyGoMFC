
// flygomfcDlg.h : 头文件
//

#pragma once

#define WM_SHOWTASK WM_USER+1
#define SWEEP_BUFFER_SIZE 10000

#include <wininet.h>

// CflygomfcDlg 对话框
class CflygomfcDlg : public CDialogEx
{
// 构造
public:
	CflygomfcDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_FLYGOMFC_DIALOG };
	enum DEL_CACHE_TYPE //要删除的类型。
	 {
	 File,//表示internet临时文件
	 Cookie //表示Cookie
	 };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
	LRESULT OnShowTask(WPARAM wParam, LPARAM lParam);
	static UINT ThreadFunc(LPVOID pParam);//线程函数声明
	static BOOL KillIE(CString iePath);
	static BOOL DeleteUrlCache(DEL_CACHE_TYPE type);
	static BOOL EmptyDirectory(LPCTSTR szPath, BOOL bDeleteDesktopIni = FALSE,   BOOL bWipeIndexDat = FALSE);
	static BOOL WipeFile(LPCTSTR szDir, LPCTSTR szFile);
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
	afx_msg void OnBnClickedOk();
	CString url;
	int loopsum;
	int loopstoptime;
	CString myIE;
	NOTIFYICONDATA m_nid;
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
	afx_msg void OnClose();
	CWinThread *m_pThread; //线程指针
	afx_msg void OnBnClickedOpenfile();
	afx_msg void OnBnClickedStop();
	CWinThread *pThread;
};
