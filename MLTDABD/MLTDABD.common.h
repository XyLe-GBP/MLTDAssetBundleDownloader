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

void MLTDAssetBundleVersionCheck(CString& VersionBuf, CString& DateBuf, CString& IndexBuf);
void MLTDAssetBundleLatestVersionCheck(CString& VersionBuf, CString& DateBuf, CString& IndexBuf);
void MLTDAssetBundleAllVersionCheck(CString& URI, CString& VersionBuf, CString& DateBuf, CString& IndexBuf);
std::vector<size_t> find_all(const std::string str, const std::string subStr);
CString AppUpdateCheck();
CString AppCurrentVersionCheck();
bool DownloadFile(LPCTSTR pszURL, LPCTSTR pszLocalFile, DWORD dwBuffSize);
DWORD GetFileSizeStat(const wchar_t* fp);
CString APP_VER();