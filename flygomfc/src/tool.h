#ifndef TOOL_H
#define TOOL_H

#include <Windows.h>
#include <vector>


BOOL  LookUpProcessAndKill(const std::vector<CString>  &vecProcessName);

CString * SplitString(CString str, char split, int& iSubStrs);

#endif