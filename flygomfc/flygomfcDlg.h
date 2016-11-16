
// flygomfcDlg.h : ͷ�ļ�
//

#pragma once

#define WM_SHOWTASK WM_USER+1
#define SWEEP_BUFFER_SIZE 10000

#include <wininet.h>

// CflygomfcDlg �Ի���
class CflygomfcDlg : public CDialogEx
{
// ����
public:
	CflygomfcDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_FLYGOMFC_DIALOG };
	enum DEL_CACHE_TYPE //Ҫɾ�������͡�
	 {
	 File,//��ʾinternet��ʱ�ļ�
	 Cookie //��ʾCookie
	 };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
	LRESULT OnShowTask(WPARAM wParam, LPARAM lParam);
	static UINT ThreadFunc(LPVOID pParam);//�̺߳�������
	static BOOL KillIE(CString iePath);
	static BOOL DeleteUrlCache(DEL_CACHE_TYPE type);
	static BOOL EmptyDirectory(LPCTSTR szPath, BOOL bDeleteDesktopIni = FALSE,   BOOL bWipeIndexDat = FALSE);
	static BOOL WipeFile(LPCTSTR szDir, LPCTSTR szFile);
// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
	CWinThread *m_pThread; //�߳�ָ��
	afx_msg void OnBnClickedOpenfile();
	afx_msg void OnBnClickedStop();
	CWinThread *pThread;
};
