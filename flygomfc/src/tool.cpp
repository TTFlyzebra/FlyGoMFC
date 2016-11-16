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
		ProcessInfo.dwSize = sizeof(ProcessInfo);  // 设置ProcessInfo的大小  
		BOOL Status = Process32First(SnapShot, &ProcessInfo);
		//提升升级工具进程权限为SE_DEBUG_NAME，否则XP下无法杀掉进程
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
			// 获取进程文件信息  
			SHGetFileInfo(ProcessInfo.szExeFile, 0, &shSmall, sizeof(shSmall), SHGFI_ICON | SHGFI_SMALLICON);
			// 检测进程是否需要关闭
			strRunProcessName = ProcessInfo.szExeFile;
			strRunProcessName.MakeLower();
			for (std::vector<CString>::size_type it = 0; it != vecProcessName.size(); ++it)	{
				strSearchName = vecProcessName[it];
				strSearchName.MakeLower();
				if (strSearchName == strRunProcessName)	{
					// 获取进程句柄，强行关闭  
					ProcessHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, ProcessInfo.th32ProcessID);
					if (ProcessHandle != NULL)
					{
						bRet = TerminateProcess(ProcessHandle, 1);
						CloseHandle(ProcessHandle);
					}
					break;
				}
			}
			// 获取下一个进程的信息  
			Status = Process32Next(SnapShot, &ProcessInfo);
		}
	}
	return  bRet;
}

CString * SplitString(CString str, char split, int& iSubStrs)
{
	int iPos = 0; //分割符位置  
	int iNums = 0; //分割符的总数  
	CString strTemp = str;
	CString strRight;
	//先计算子字符串的数量  
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
	if (iNums == 0) //没有找到分割符  
	{
		//子字符串数就是字符串本身  
		iSubStrs = 1;
		return NULL;
	}
	//子字符串数组  
	iSubStrs = iNums + 1; //子串的数量 = 分割符数量 + 1  
	CString* pStrSplit;
	pStrSplit = new CString[iSubStrs];
	strTemp = str;
	CString strLeft;
	for (int i = 0; i < iNums; i++)
	{
		iPos = strTemp.Find(split);
		//左子串  
		strLeft = strTemp.Left(iPos);
		//右子串  
		strRight = strTemp.Mid(iPos + 1, strTemp.GetLength());
		strTemp = strRight;
		pStrSplit[i] = strLeft;
	}
	pStrSplit[iNums] = strTemp;
	return pStrSplit;
}