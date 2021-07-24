#pragma once

#include "pch.h"
#include <io.h>
#include <direct.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <random>
#include "wininet.h" 
#pragma comment(lib,"wininet.lib")
#pragma comment(lib,"Winmm.lib")
#pragma comment(lib, "version.lib")
#include <mmsystem.h>

using namespace std;

void MLTDAssetBundleVersionCheck(CString& VersionBuf, CString& DateBuf, CString& IndexBuf);
void MLTDAssetBundleLatestVersionCheck(CString& VersionBuf, CString& DateBuf, CString& IndexBuf);
void MLTDAssetBundleAllVersionCheck(CString& URI, CString& VersionBuf, CString& DateBuf, CString& IndexBuf);
std::vector<size_t> find_all(const std::string str, const std::string subStr);
CString AppUpdateCheck();
CString AppCurrentVersionCheck();
bool DownloadFile(LPCTSTR pszURL, LPCTSTR pszLocalFile, DWORD dwBuffSize);
DWORD GetFileSizeStat(const wchar_t* fp);
string AfxReplaceStr(string& replacedStr, string from, string to);
string TWStringToString(const wstring& arg_wstr);
wstring StringToWString(const string& arg_str);
CString APP_VER();