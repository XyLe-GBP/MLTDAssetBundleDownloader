#include "pch.h"
#include "MLTDABD.common.h"

void MLTDAssetBundleVersionCheck(CString &VersionBuf, CString &DateBuf, CString &IndexBuf) {
	HINTERNET    hNet;
	HINTERNET    hUrl;
	HINTERNET hHttpSession;
	HINTERNET hHttpRequest;
	DWORD BufSizeTextSize = 1000;
	DWORD StatusCode = sizeof(DWORD);
	DWORD StatusCode_Size = sizeof(DWORD);
	wchar_t Path[MAX_PATH + 1], Drive[10], Dir[MAX_PATH], Name[MAX_PATH], Ext[MAX_PATH];
	wchar_t ptr[MAX_PATH] = { 0 };
	TCHAR m_cPath[MAX_PATH + 1];

	CString URL;

	if (0 != GetModuleFileName(NULL, Path, MAX_PATH)) {// 実行ファイルの完全パスを取得
		_tsplitpath_s(Path, Drive, Dir, Name, Ext);
		CString NAME = Name;
		URL = _T("https://api.matsurihi.me/mltd/v1/version/assets/197000");
	}

	// 初期化
	hNet = ::InternetOpen(L"UpdateCheck...",
		INTERNET_OPEN_TYPE_PRECONFIG,
		NULL,
		NULL,
		0);
	if (hNet == NULL)
		return;

	/* サーバへ接続 */
	hHttpSession = InternetConnect(
		hNet,
		_T("api.matsurihi.me"),
		INTERNET_DEFAULT_HTTP_PORT,
		NULL,
		NULL,
		INTERNET_SERVICE_HTTP,
		0,
		0);

	/* HTTP要求の作成 */
	hHttpRequest = HttpOpenRequest(
		hHttpSession,
		_T("GET"),
		_T(""),
		NULL,
		URL,
		NULL,
		0,
		0);

	/* 作成したHTTP要求の発行 */
	BOOL bHttpSendRequest = HttpSendRequest(
		hHttpRequest,
		NULL,
		0,
		NULL,
		0);

	if (bHttpSendRequest == 0) {
		::InternetCloseHandle(hNet);
		::InternetCloseHandle(hHttpRequest);
		::InternetCloseHandle(hHttpSession);
		return;
	}

	/* 返されたコンテンツの長さを取得 */
	HttpQueryInfo(
		hHttpRequest,
		HTTP_QUERY_STATUS_CODE | HTTP_QUERY_FLAG_NUMBER,
		&StatusCode,
		&StatusCode_Size,
		NULL);

	if (StatusCode != HTTP_STATUS_OK) {
		OutputDebugString(_T("HTTP Request failed.\n"));
		::InternetCloseHandle(hHttpRequest);
		::InternetCloseHandle(hHttpSession);
		::InternetCloseHandle(hNet);
		return;
	}
	else {
		OutputDebugString(_T("HTTP Request completed.\n"));

		// バージョンチェック用のページ
		::_tcscpy_s(m_cPath, MAX_PATH, URL);

		// URLオープン
		hUrl = ::InternetOpenUrl(hNet,
			m_cPath,
			NULL,
			0,
			INTERNET_FLAG_RELOAD,
			0);
		if (hUrl == NULL)
		{
			::InternetCloseHandle(hHttpRequest);
			::InternetCloseHandle(hHttpSession);
			::InternetCloseHandle(hNet);
			return;
		}

		// 読み込み
		TCHAR m_wBuf[256] = { sizeof(TCHAR) };
		DWORD dwReadSize = 0;
		::InternetReadFile(hUrl, m_wBuf, 256, &dwReadSize);
		if (dwReadSize == 256) {
			::InternetCloseHandle(hHttpRequest);
			::InternetCloseHandle(hHttpSession);
			::InternetCloseHandle(hUrl);
			::InternetCloseHandle(hNet);
			OutputDebugString(_T("Exception occured.\n"));
			return;
		}
		m_wBuf[dwReadSize] = '\0';

		// クローズ
		::InternetCloseHandle(hHttpRequest);
		::InternetCloseHandle(hHttpSession);
		::InternetCloseHandle(hUrl);
		::InternetCloseHandle(hNet);

		// 変換
		char m_cBuf[256];

		const int cchWideByte = ::MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)m_wBuf, -1, NULL, NULL);
		LPWSTR lpw = new WCHAR[cchWideByte];
		::MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)m_wBuf, -1, lpw, cchWideByte);

		const int cchMultiByte = ::WideCharToMultiByte(CP_ACP, 0, lpw, -1, NULL, 0, NULL, NULL);
		LPSTR lpa = new CHAR[cchMultiByte];

		const int nMultiCount = ::WideCharToMultiByte(CP_ACP, 0, lpw, -1, lpa, cchMultiByte, NULL, NULL);

		::strcpy_s(m_cBuf, 256, lpa);

		delete[] lpa;
		delete[] lpw;

		// 解析
		char cVersion[256] = { 0 };
		char* cTmp = NULL, * cNext = NULL;
		cTmp = ::strtok_s(m_cBuf, "", &cNext);
		if (::strcmp(cTmp, "\"version\"") == 0)
		{
			cTmp = ::strtok_s(NULL, "\n", &cNext);
			::strcpy_s(cVersion, 256, cTmp);
		}

		size_t pos1 = 0, pos2 = 0, pos3 = 0, npos1 = 0, npos2 = 0, npos3 = 0, npos4 = 0;
		std::string sTmp = cTmp, buf1, buf2, buf3;
		CString VER, DATE, INDEX;

		std::vector<size_t> findVec = find_all(sTmp, ": ");

		for (const auto& pos : findVec) {
			CString POS;
			POS.Format(_T("Position:%llu\n"), pos);
			OutputDebugString(POS);
			if (pos1 == 0) {
				pos1 = pos;
			}
			else {
				if (pos2 == 0) {
					pos2 = pos;
				}
				else {
					if (pos3 == 0) {
						pos3 = pos;
					}
					else {
						break;
					}
				}
			}
		}
		std::vector<size_t> findVec2 = find_all(sTmp, "\n");

		for (const auto& pos : findVec2) {
			CString POS;
			POS.Format(_T("Position:%llu\n"), pos);
			OutputDebugString(POS);
			if (npos1 == 0) {
				npos1 = pos;
			}
			else {
				if (npos2 == 0) {
					npos2 = pos;
				}
				else {
					if (npos3 == 0) {
						npos3 = pos;
					}
					else {
						if (npos4 == 0) {
							npos4 = pos;
						}
						else {
							break;
						}
					}
				}
			}
		}

		size_t len1 = 0, len1d = 0, len2 = 0, len2d = 0, len3 = 0, len3d = 0;
		len1 = npos2 - 1;
		len1d = pos1 + 2;
		len1 = len1 - len1d;
		len2 = npos3 - 2;
		len2d = pos2 + 3;
		len2 = len2 - len2d;
		len3 = npos4 - 1;
		len3d = pos3 + 3;
		len3 = len3 - len3d;

		buf1 = sTmp.substr(len1d, len1);
		buf2 = sTmp.substr(len2d, len2);
		buf3 = sTmp.substr(len3d, len3);
		VER = buf1.c_str();
		DATE = buf2.c_str();
		INDEX = buf3.c_str();

		VersionBuf = VER;
		DateBuf = DATE;
		IndexBuf = INDEX;

		return;
	}
}


void MLTDAssetBundleLatestVersionCheck(CString& VersionBuf, CString& DateBuf, CString& IndexBuf) {
	HINTERNET    hNet;
	HINTERNET    hUrl;
	HINTERNET hHttpSession;
	HINTERNET hHttpRequest;
	DWORD BufSizeTextSize = 1000;
	DWORD StatusCode = sizeof(DWORD);
	DWORD StatusCode_Size = sizeof(DWORD);
	wchar_t Path[MAX_PATH + 1], Drive[10], Dir[MAX_PATH], Name[MAX_PATH], Ext[MAX_PATH];
	wchar_t ptr[MAX_PATH] = { 0 };
	TCHAR m_cPath[MAX_PATH + 1];

	CString URL;

	if (0 != GetModuleFileName(NULL, Path, MAX_PATH)) {// 実行ファイルの完全パスを取得
		_tsplitpath_s(Path, Drive, Dir, Name, Ext);
		CString NAME = Name;
		URL = _T("https://api.matsurihi.me/mltd/v1/version/latest");
	}

	// 初期化
	hNet = ::InternetOpen(L"UpdateCheck...",
		INTERNET_OPEN_TYPE_PRECONFIG,
		NULL,
		NULL,
		0);
	if (hNet == NULL)
		return;

	/* サーバへ接続 */
	hHttpSession = InternetConnect(
		hNet,
		_T("api.matsurihi.me"),
		INTERNET_DEFAULT_HTTP_PORT,
		NULL,
		NULL,
		INTERNET_SERVICE_HTTP,
		0,
		0);

	/* HTTP要求の作成 */
	hHttpRequest = HttpOpenRequest(
		hHttpSession,
		_T("GET"),
		_T(""),
		NULL,
		URL,
		NULL,
		0,
		0);

	/* 作成したHTTP要求の発行 */
	BOOL bHttpSendRequest = HttpSendRequest(
		hHttpRequest,
		NULL,
		0,
		NULL,
		0);

	if (bHttpSendRequest == 0) {//bHttpSendRequestが0の場合はインターネットに接続されていないので、エラーを返す。
		::InternetCloseHandle(hNet);
		::InternetCloseHandle(hHttpRequest);
		::InternetCloseHandle(hHttpSession);
		return;//106:ERR_INTERNET_DISCONNECTED
	}

	/* 返されたコンテンツの長さを取得 */
	HttpQueryInfo(
		hHttpRequest,
		HTTP_QUERY_STATUS_CODE | HTTP_QUERY_FLAG_NUMBER,
		&StatusCode,
		&StatusCode_Size,
		NULL);

	if (StatusCode != HTTP_STATUS_OK) {
		OutputDebugString(_T("HTTP Request failed.\n"));
		::InternetCloseHandle(hHttpRequest);
		::InternetCloseHandle(hHttpSession);
		::InternetCloseHandle(hNet);
		return;
	}
	else {
		OutputDebugString(_T("HTTP Request completed.\n"));

		// バージョンチェック用のページ
		::_tcscpy_s(m_cPath, MAX_PATH, URL);

		// URLオープン
		hUrl = ::InternetOpenUrl(hNet,
			m_cPath,
			NULL,
			0,
			INTERNET_FLAG_RELOAD,
			0);
		if (hUrl == NULL)
		{
			::InternetCloseHandle(hHttpRequest);
			::InternetCloseHandle(hHttpSession);
			::InternetCloseHandle(hNet);
			return;
		}

		// 読み込み
		TCHAR m_wBuf[300] = { sizeof(TCHAR) };
		DWORD dwReadSize = 0;
		::InternetReadFile(hUrl, m_wBuf, 300, &dwReadSize);
		if (dwReadSize == 300) {
			::InternetCloseHandle(hHttpRequest);
			::InternetCloseHandle(hHttpSession);
			::InternetCloseHandle(hUrl);
			::InternetCloseHandle(hNet);
			OutputDebugString(_T("Exception occured.\n"));
			return;
		}
		m_wBuf[dwReadSize] = '\0';

		// クローズ
		::InternetCloseHandle(hHttpRequest);
		::InternetCloseHandle(hHttpSession);
		::InternetCloseHandle(hUrl);
		::InternetCloseHandle(hNet);

		// 変換
		char m_cBuf[300];

		const int cchWideByte = ::MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)m_wBuf, -1, NULL, NULL);
		LPWSTR lpw = new WCHAR[cchWideByte];
		::MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)m_wBuf, -1, lpw, cchWideByte);

		const int cchMultiByte = ::WideCharToMultiByte(CP_ACP, 0, lpw, -1, NULL, 0, NULL, NULL);
		LPSTR lpa = new CHAR[cchMultiByte];

		const int nMultiCount = ::WideCharToMultiByte(CP_ACP, 0, lpw, -1, lpa, cchMultiByte, NULL, NULL);

		::strcpy_s(m_cBuf, 300, lpa);

		delete[] lpa;
		delete[] lpw;

		// 解析
		char cVersion[300] = { 0 };
		char* cTmp = NULL, * cNext = NULL;
		cTmp = ::strtok_s(m_cBuf, "", &cNext);
		if (::strcmp(cTmp, "\"version\"") == 0)
		{
			cTmp = ::strtok_s(NULL, "\n", &cNext);
			::strcpy_s(cVersion, 300, cTmp);
		}

		int lp = 0;
		size_t pos1 = 0, pos2 = 0, pos3 = 0, npos1 = 0, npos2 = 0, npos3 = 0;
		std::string sTmp = cTmp, buf1, buf2, buf3;
		CString VER, DATE, INDEX;

		std::vector<size_t> findVec = find_all(sTmp, ": ");

		for (const auto& pos : findVec) {
			CString POS;
			POS.Format(_T("Position:%llu\n"), pos);
			OutputDebugString(POS);
			if (lp == 5) {
				pos1 = pos;
			}
			if (lp == 6) {
				pos2 = pos;
			}
			if (lp == 7) {
				pos3 = pos;
			}
			lp++;
		}
		lp = 0;
		std::vector<size_t> findVec2 = find_all(sTmp, "\n");

		for (const auto& pos : findVec2) {
			CString POS;
			POS.Format(_T("Position:%llu\n"), pos);
			OutputDebugString(POS);
			if (lp == 7) {
				npos1 = pos;
			}
			if (lp == 8) {
				npos2 = pos;
			}
			if (lp == 9) {
				npos3 = pos;
			}
			lp++;
		}
		lp = 0;

		size_t len1 = 0, len1d = 0, len2 = 0, len2d = 0, len3 = 0, len3d = 0;
		len1 = npos1 - 1;
		len1d = pos1 + 2;
		len1 = len1 - len1d;
		len2 = npos2 - 2;
		len2d = pos2 + 3;
		len2 = len2 - len2d;
		len3 = npos3 - 1;
		len3d = pos3 + 3;
		len3 = len3 - len3d;

		buf1 = sTmp.substr(len1d, len1);
		buf2 = sTmp.substr(len2d, len2);
		buf3 = sTmp.substr(len3d, len3);
		VER = buf1.c_str();
		DATE = buf2.c_str();
		INDEX = buf3.c_str();

		VersionBuf = VER;
		DateBuf = DATE;
		IndexBuf = INDEX;

		return;
	}
}


std::vector<size_t> find_all(const std::string str, const std::string subStr) {
	std::vector<size_t> result;

	size_t subStrSize = subStr.size();
	size_t pos = str.find(subStr);

	while (pos != std::string::npos) {
		result.push_back(pos);
		pos = str.find(subStr, static_cast<std::basic_string<char, std::char_traits<char>, std::allocator<char>>::size_type>(pos) + subStrSize);
	}

	return result;
}


void MLTDAssetBundleAllVersionCheck(CString& URI, CString& VersionBuf, CString& DateBuf, CString& IndexBuf) {
	HINTERNET    hNet;
	HINTERNET    hUrl;
	HINTERNET hHttpSession;
	HINTERNET hHttpRequest;
	DWORD BufSizeTextSize = 1000;
	DWORD StatusCode = sizeof(DWORD);
	DWORD StatusCode_Size = sizeof(DWORD);
	wchar_t Path[MAX_PATH + 1], Drive[10], Dir[MAX_PATH], Name[MAX_PATH], Ext[MAX_PATH];
	wchar_t ptr[MAX_PATH] = { 0 };
	TCHAR m_cPath[MAX_PATH + 1];

	CString URL;

	if (0 != GetModuleFileName(NULL, Path, MAX_PATH)) {// 実行ファイルの完全パスを取得
		_tsplitpath_s(Path, Drive, Dir, Name, Ext);
		CString NAME = Name;
		URL = URI;
	}

	// 初期化
	hNet = ::InternetOpen(L"UpdateCheck...",
		INTERNET_OPEN_TYPE_PRECONFIG,
		NULL,
		NULL,
		0);
	if (hNet == NULL)
		return;

	/* サーバへ接続 */
	hHttpSession = InternetConnect(
		hNet,
		_T("api.matsurihi.me"),
		INTERNET_DEFAULT_HTTP_PORT,
		NULL,
		NULL,
		INTERNET_SERVICE_HTTP,
		0,
		0);

	/* HTTP要求の作成 */
	hHttpRequest = HttpOpenRequest(
		hHttpSession,
		_T("GET"),
		_T(""),
		NULL,
		URL,
		NULL,
		0,
		0);

	/* 作成したHTTP要求の発行 */
	BOOL bHttpSendRequest = HttpSendRequest(
		hHttpRequest,
		NULL,
		0,
		NULL,
		0);

	if (bHttpSendRequest == 0) {//bHttpSendRequestが0の場合はインターネットに接続されていないので、エラーを返す。
		::InternetCloseHandle(hNet);
		::InternetCloseHandle(hHttpRequest);
		::InternetCloseHandle(hHttpSession);
		return;//106:ERR_INTERNET_DISCONNECTED
	}

	/* 返されたコンテンツの長さを取得 */
	HttpQueryInfo(
		hHttpRequest,
		HTTP_QUERY_STATUS_CODE | HTTP_QUERY_FLAG_NUMBER,
		&StatusCode,
		&StatusCode_Size,
		NULL);

	if (StatusCode != HTTP_STATUS_OK) {
		OutputDebugString(_T("HTTP Request failed.\n"));
		::InternetCloseHandle(hHttpRequest);
		::InternetCloseHandle(hHttpSession);
		::InternetCloseHandle(hNet);
		return;
	}
	else {
		OutputDebugString(_T("HTTP Request completed.\n"));

		// バージョンチェック用のページ
		::_tcscpy_s(m_cPath, MAX_PATH, URL);

		// URLオープン
		hUrl = ::InternetOpenUrl(hNet,
			m_cPath,
			NULL,
			0,
			INTERNET_FLAG_RELOAD,
			0);
		if (hUrl == NULL)
		{
			::InternetCloseHandle(hHttpRequest);
			::InternetCloseHandle(hHttpSession);
			::InternetCloseHandle(hNet);
			return;
		}

		// 読み込み
		TCHAR m_wBuf[300] = { sizeof(TCHAR) };
		DWORD dwReadSize = 0;
		::InternetReadFile(hUrl, m_wBuf, 300, &dwReadSize);
		if (dwReadSize == 300) {
			::InternetCloseHandle(hHttpRequest);
			::InternetCloseHandle(hHttpSession);
			::InternetCloseHandle(hUrl);
			::InternetCloseHandle(hNet);
			OutputDebugString(_T("Exception occured.\n"));
			return;
		}
		m_wBuf[dwReadSize] = '\0';

		// クローズ
		::InternetCloseHandle(hHttpRequest);
		::InternetCloseHandle(hHttpSession);
		::InternetCloseHandle(hUrl);
		::InternetCloseHandle(hNet);

		// 変換
		char m_cBuf[300];

		const int cchWideByte = ::MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)m_wBuf, -1, NULL, NULL);
		LPWSTR lpw = new WCHAR[cchWideByte];
		::MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)m_wBuf, -1, lpw, cchWideByte);

		const int cchMultiByte = ::WideCharToMultiByte(CP_ACP, 0, lpw, -1, NULL, 0, NULL, NULL);
		LPSTR lpa = new CHAR[cchMultiByte];

		const int nMultiCount = ::WideCharToMultiByte(CP_ACP, 0, lpw, -1, lpa, cchMultiByte, NULL, NULL);

		::strcpy_s(m_cBuf, 300, lpa);

		delete[] lpa;
		delete[] lpw;

		// 解析
		char cVersion[300] = { 0 };
		char* cTmp = NULL, * cNext = NULL;
		cTmp = ::strtok_s(m_cBuf, "", &cNext);
		if (::strcmp(cTmp, "\"version\"") == 0)
		{
			cTmp = ::strtok_s(NULL, "\n", &cNext);
			::strcpy_s(cVersion, 300, cTmp);
		}

		int lp = 0;
		size_t pos1 = 0, pos2 = 0, pos3 = 0, npos1 = 0, npos2 = 0, npos3 = 0;
		std::string sTmp = cTmp, buf1, buf2, buf3;
		CString VER, DATE, INDEX;

		std::vector<size_t> findVec = find_all(sTmp, ": ");

		for (const auto& pos : findVec) {
			CString POS;
			POS.Format(_T("Position:%llu\n"), pos);
			OutputDebugString(POS);
			if (lp == 5) {
				pos1 = pos;
			}
			if (lp == 6) {
				pos2 = pos;
			}
			if (lp == 7) {
				pos3 = pos;
			}
			lp++;
		}
		lp = 0;
		std::vector<size_t> findVec2 = find_all(sTmp, "\n");

		for (const auto& pos : findVec2) {
			CString POS;
			POS.Format(_T("Position:%llu\n"), pos);
			OutputDebugString(POS);
			if (lp == 7) {
				npos1 = pos;
			}
			if (lp == 8) {
				npos2 = pos;
			}
			if (lp == 9) {
				npos3 = pos;
			}
			lp++;
		}
		lp = 0;

		size_t len1 = 0, len1d = 0, len2 = 0, len2d = 0, len3 = 0, len3d = 0;
		len1 = npos1 - 1;
		len1d = pos1 + 2;
		len1 = len1 - len1d;
		len2 = npos2 - 2;
		len2d = pos2 + 3;
		len2 = len2 - len2d;
		len3 = npos3 - 1;
		len3d = pos3 + 3;
		len3 = len3 - len3d;

		buf1 = sTmp.substr(len1d, len1);
		buf2 = sTmp.substr(len2d, len2);
		buf3 = sTmp.substr(len3d, len3);
		VER = buf1.c_str();
		DATE = buf2.c_str();
		INDEX = buf3.c_str();

		VersionBuf = VER;
		DateBuf = DATE;
		IndexBuf = INDEX;

		return;
	}
}


CString AppUpdateCheck() {
	HINTERNET    hNet;
	HINTERNET    hUrl;
	HINTERNET hHttpSession;
	HINTERNET hHttpRequest;
	DWORD BufSizeTextSize = 1000;
	DWORD StatusCode = sizeof(DWORD);
	DWORD StatusCode_Size = sizeof(DWORD);
	wchar_t Path[MAX_PATH + 1], Drive[10], Dir[MAX_PATH], Name[MAX_PATH], Ext[MAX_PATH];
	wchar_t ptr[MAX_PATH] = { 0 };
	TCHAR m_cPath[MAX_PATH + 1];

	CString URL;
	CString URL2;

	if (0 != GetModuleFileName(NULL, Path, MAX_PATH)) {// 実行ファイルの完全パスを取得
		_tsplitpath_s(Path, Drive, Dir, Name, Ext);
		CString NAME = Name;
		URL = _T("https://raw.githubusercontent.com/XyLe-GBP/MLTDAssetBundleDownloader/master/VERSIONINFO");
	}

	// 初期化
	hNet = ::InternetOpen(L"UpdateCheck...",
		INTERNET_OPEN_TYPE_PRECONFIG,
		NULL,
		NULL,
		0);
	if (hNet == NULL)
		return NULL;

	/* サーバへ接続 */
	hHttpSession = InternetConnect(
		hNet,
		_T("raw.githubusercontent.com"),
		INTERNET_DEFAULT_HTTP_PORT,
		NULL,
		NULL,
		INTERNET_SERVICE_HTTP,
		0,
		0);

	/* HTTP要求の作成 */
	hHttpRequest = HttpOpenRequest(
		hHttpSession,
		_T("GET"),
		_T(""),
		NULL,
		URL,
		NULL,
		0,
		0);

	/* 作成したHTTP要求の発行 */
	BOOL bHttpSendRequest = HttpSendRequest(
		hHttpRequest,
		NULL,
		0,
		NULL,
		0);

	if (bHttpSendRequest == 0) {//bHttpSendRequestが0の場合はインターネットに接続されていないので、エラーを返す。
		::InternetCloseHandle(hNet);
		::InternetCloseHandle(hHttpRequest);
		::InternetCloseHandle(hHttpSession);
		return NULL;//106:ERR_INTERNET_DISCONNECTED
	}

	/* 返されたコンテンツの長さを取得 */
	HttpQueryInfo(
		hHttpRequest,
		HTTP_QUERY_STATUS_CODE | HTTP_QUERY_FLAG_NUMBER,
		&StatusCode,
		&StatusCode_Size,
		NULL);

	if (StatusCode != HTTP_STATUS_OK) {
		OutputDebugString(_T("HTTP Request failed.\n"));
		::InternetCloseHandle(hHttpRequest);
		::InternetCloseHandle(hHttpSession);
		::InternetCloseHandle(hNet);
		return NULL;
	}
	else {
		OutputDebugString(_T("HTTP Request completed.\n"));

		// バージョンチェック用のページ
		::_tcscpy_s(m_cPath, MAX_PATH, URL);

		// URLオープン
		hUrl = ::InternetOpenUrl(hNet,
			m_cPath,
			NULL,
			0,
			INTERNET_FLAG_RELOAD,
			0);
		if (hUrl == NULL)
		{
			::InternetCloseHandle(hHttpRequest);
			::InternetCloseHandle(hHttpSession);
			::InternetCloseHandle(hNet);
			return NULL;
		}

		// 読み込み
		TCHAR m_wBuf[256] = { sizeof(TCHAR) };
		DWORD dwReadSize = 0;
		::InternetReadFile(hUrl, m_wBuf, 256, &dwReadSize);
		if (dwReadSize == 256) {
			::InternetCloseHandle(hHttpRequest);
			::InternetCloseHandle(hHttpSession);
			::InternetCloseHandle(hUrl);
			::InternetCloseHandle(hNet);
			OutputDebugString(_T("Exception occured.\n"));
			return _T("-1");
		}
		m_wBuf[dwReadSize] = '\0';

		// クローズ
		::InternetCloseHandle(hHttpRequest);
		::InternetCloseHandle(hHttpSession);
		::InternetCloseHandle(hUrl);
		::InternetCloseHandle(hNet);

		// 変換
		char m_cBuf[256];

		const int cchWideByte = ::MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)m_wBuf, -1, NULL, NULL);
		LPWSTR lpw = new WCHAR[cchWideByte];
		::MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)m_wBuf, -1, lpw, cchWideByte);

		const int cchMultiByte = ::WideCharToMultiByte(CP_ACP, 0, lpw, -1, NULL, 0, NULL, NULL);
		LPSTR lpa = new CHAR[cchMultiByte];

		const int nMultiCount = ::WideCharToMultiByte(CP_ACP, 0, lpw, -1, lpa, cchMultiByte, NULL, NULL);

		::strcpy_s(m_cBuf, 256, lpa);

		delete[] lpa;
		delete[] lpw;

		// 解析
		char cVersion[256] = { 0 };
		char* cTmp = NULL, * cNext = NULL;
		cTmp = ::strtok_s(m_cBuf, ":", &cNext);
		if (::strcmp(cTmp, "version") == 0)
		{
			cTmp = ::strtok_s(NULL, "\n", &cNext);
			::strcpy_s(cVersion, 256, cTmp);
		}
		CString FINAL;
		FINAL = cVersion;

		return FINAL;
	}
}


CString AppCurrentVersionCheck() {
	DWORD dwLen, dwHandle;
	TCHAR cBuf[256] = { NULL };
	wchar_t Path[MAX_PATH + 1];

	if (0 != GetModuleFileName(NULL, Path, MAX_PATH)) {// 実行ファイルの完全パスを取得
	}
	const TCHAR* const AppName = Path;

	dwLen = ::GetFileVersionInfoSize(AppName, &dwHandle);
	if (dwLen > 0)
	{
		char* lpData = new char[static_cast<DWORD64>(dwLen) + 1];
		::GetFileVersionInfo(AppName, NULL, dwLen, lpData);

		// 情報を取得する
		void* pvVersion;
		UINT VersionLen;
		::VerQueryValue(lpData, L"\\StringFileInfo\\041104b0\\ProductVersion", &pvVersion, &VersionLen);

		::_stprintf_s(cBuf, 256, _T("%s"), static_cast<wchar_t*>(pvVersion));

		delete[] lpData;
	}
	return cBuf;
}


bool DownloadFile(LPCTSTR pszURL, LPCTSTR pszLocalFile, DWORD dwBuffSize) {
	//TCHAR		pszHeader[] = _T("Accept: */*\r\n\r\n");
	BOOL		ret;
	DWORD		dwReadSize;
	DWORD		dwWrittenSize;
	BYTE* pcbBuff;
	HINTERNET	hInternet;
	HINTERNET	hConnect;
	HANDLE		hFile;

	hInternet = ::InternetOpen(NULL, INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
	if (hInternet == NULL)
		return	false;

	hConnect = ::InternetOpenUrl(hInternet, pszURL, NULL, -1, INTERNET_FLAG_DONT_CACHE, 0);
	pcbBuff = new BYTE[dwBuffSize];
	if (hConnect == NULL || pcbBuff == NULL)
	{
		if (hConnect)
			::InternetCloseHandle(hConnect);
		::InternetCloseHandle(hInternet);
		if (pcbBuff)
			delete[]	pcbBuff;
		return	false;
	}

	//保存先のファイルを作る。ファイルがあった場合は失敗
	hFile = ::CreateFile(pszLocalFile, GENERIC_WRITE, 0, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
	ret = (hFile == INVALID_HANDLE_VALUE) ? FALSE : TRUE;

	while (ret)
	{
		::Sleep(0);
		ret = ::InternetReadFile(hConnect, pcbBuff, dwBuffSize, &dwReadSize);
		if (ret == FALSE || dwReadSize == 0)
			break;

		ret = ::WriteFile(hFile, pcbBuff, dwReadSize, &dwWrittenSize, NULL);
	}

	if (hFile != INVALID_HANDLE_VALUE)
	{
		::CloseHandle(hFile);

		//失敗時は作成したファイルを削除
		if (ret == FALSE)
			::DeleteFile(pszLocalFile);
	}

	::InternetCloseHandle(hConnect);
	::InternetCloseHandle(hInternet);

	delete[]	pcbBuff;

	return	ret ? true : false;
}


DWORD GetFileSizeStat(const wchar_t* fp) {
	struct _stat st;
	if (_wstat(fp, &st) != 0) {
		return NULL;
	}
	if ((st.st_mode & S_IFMT) != S_IFREG) {
		return NULL;
	}

	return st.st_size;
}


string AfxReplaceStr(string& replacedStr, string from, string to) {
	const size_t pos = replacedStr.find(from);
	const size_t len = from.length();

	if (pos == string::npos || from.empty()) {
		return replacedStr;
	}

	return replacedStr.replace(pos, len, to);
}


string TWStringToString(const wstring& arg_wstr)
{
	size_t length = arg_wstr.size();
	size_t convLength;
	char* c = (char*)malloc(sizeof(char) * length * 2);
	wcstombs_s(&convLength, c, sizeof(char) * length * 2, arg_wstr.c_str(), length * 2);
	string result(c);
	free(c);

	return result;
};


wstring StringToWString(const string& arg_str)
{
	size_t length = arg_str.size();
	size_t convLength;
	wchar_t* wc = (wchar_t*)malloc(sizeof(wchar_t) * (length + 2));
	mbstowcs_s(&convLength, wc, length + 1, arg_str.c_str(), _TRUNCATE);
	wstring str(wc);
	free(wc);

	return str;
};

//VersionInfoString


CString APP_VER() {
	CString FUNCTION = _T("1.1.0.1 (v1101)"); //major.minor.build.revision
	return FUNCTION;
}

