#include "stdafx.h"
#include "tool.h"
#include "tlhelp32.h" 

BOOL  LookUpProcessAndKill(const std::vector<CString>  &vecProcessName)
{
	BOOL bRet = FALSE;
	HANDLE SnapShot, ProcessHandle;
	SHFILEINFO shSmall;
	PROCESSENTRY32 ProcessInfo;
	CString strSearchName;
	CString strRunProcessName;
	SnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (SnapShot != NULL){
		ProcessInfo.dwSize = sizeof(ProcessInfo);  // ����ProcessInfo�Ĵ�С  
		BOOL Status = Process32First(SnapShot, &ProcessInfo);
		//�����������߽���Ȩ��ΪSE_DEBUG_NAME������XP���޷�ɱ������
		HANDLE hToken;
		if (OpenProcessToken(GetCurrentProcess(), TOKEN_ALL_ACCESS, &hToken)){
			LUID luid;
			if (LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &luid)){
				TOKEN_PRIVILEGES TokenPrivileges;
				TokenPrivileges.PrivilegeCount = 1;
				TokenPrivileges.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
				TokenPrivileges.Privileges[0].Luid = luid;
				AdjustTokenPrivileges(hToken, FALSE, &TokenPrivileges, 0, NULL, NULL);
			}
			CloseHandle(hToken);
		}
		while (Status){
			// ��ȡ�����ļ���Ϣ  
			SHGetFileInfo(ProcessInfo.szExeFile, 0, &shSmall, sizeof(shSmall), SHGFI_ICON | SHGFI_SMALLICON);
			// �������Ƿ���Ҫ�ر�
			strRunProcessName = ProcessInfo.szExeFile;
			strRunProcessName.MakeLower();
			for (std::vector<CString>::size_type it = 0; it != vecProcessName.size(); ++it)	{
				strSearchName = vecProcessName[it];
				strSearchName.MakeLower();
				if (strSearchName == strRunProcessName)	{
					// ��ȡ���̾����ǿ�йر�  
					ProcessHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, ProcessInfo.th32ProcessID);
					if (ProcessHandle != NULL)
					{
						bRet = TerminateProcess(ProcessHandle, 1);
						CloseHandle(ProcessHandle);
					}
					break;
				}
			}
			// ��ȡ��һ�����̵���Ϣ  
			Status = Process32Next(SnapShot, &ProcessInfo);
		}
	}
	return  bRet;
}

CString * SplitString(CString str, char split, int& iSubStrs)
{
	int iPos = 0; //�ָ��λ��  
	int iNums = 0; //�ָ��������  
	CString strTemp = str;
	CString strRight;
	//�ȼ������ַ���������  
	while (iPos != -1)
	{
		iPos = strTemp.Find(split);
		if (iPos == -1)
		{
			break;
		}
		strRight = strTemp.Mid(iPos + 1, str.GetLength());
		strTemp = strRight;
		iNums++;
	}
	if (iNums == 0) //û���ҵ��ָ��  
	{
		//���ַ����������ַ�������  
		iSubStrs = 1;
		return NULL;
	}
	//���ַ�������  
	iSubStrs = iNums + 1; //�Ӵ������� = �ָ������ + 1  
	CString* pStrSplit;
	pStrSplit = new CString[iSubStrs];
	strTemp = str;
	CString strLeft;
	for (int i = 0; i < iNums; i++)
	{
		iPos = strTemp.Find(split);
		//���Ӵ�  
		strLeft = strTemp.Left(iPos);
		//���Ӵ�  
		strRight = strTemp.Mid(iPos + 1, strTemp.GetLength());
		strTemp = strRight;
		pStrSplit[i] = strLeft;
	}
	pStrSplit[iNums] = strTemp;
	return pStrSplit;
}