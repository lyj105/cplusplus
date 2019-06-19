// PublicFunction.h: interface for the CPublicFunction class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PUBLICFUNCTION_H__654F176C_F11F_4843_AEA0_F53676D52341__INCLUDED_)
#define AFX_PUBLICFUNCTION_H__654F176C_F11F_4843_AEA0_F53676D52341__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define SLEEP_RETURN(x)\
{\
	if ( ::WaitForSingleObject ( m_hEvtEndModule, x ) == WAIT_OBJECT_0 )\
		return FALSE;\
}
#define SLEEP_BREAK(x)\
{\
	if ( ::WaitForSingleObject ( m_hEvtEndModule, x ) == WAIT_OBJECT_0 )\
		break;\
}
// �����ټ���
#define EnterCRIT(pCRIT,CRITName,FileName,Line) \
{\
	(pCRIT)->Lock ();\
	TRACE ( "--------> %s , EnterCriticalSection ,%s ( %d )\n", CRITName, FileName, Line );\
}
// �뿪�ټ���
#define LeaveCRIT(pCRIT,CRITName,FileName,Line) \
{\
	TRACE ( "<-------- %s , LeaveCriticalSection ,%s ( %d )\n", CRITName, FileName, Line );\
	(pCRIT)->Unlock();\
}

class CHwDir
{
public:
	CHwDir(
		LPCTSTR lpszBasePathOrFile,
		BOOL bSerachSubDir = TRUE,		// ������Ŀ¼
		BOOL bAbsolutePath = TRUE,		// �Ǿ���·��
		CHwDir **ppHwDir = NULL			// ��������ָ�봫��ȥ��������
	);
	virtual ~CHwDir();

public:
	ULONGLONG GetAmountBytes();
	CStringArray *m_pStrAryResFile, *m_pStrArySubDirectory;
	char m_szBasePathFile[MAX_PATH];
	void Cancel();
private:
	DWORD FindAllFileUnderOneDir(LPCTSTR lpszFileName, LPCTSTR lpszDirectory, BOOL bFindDir);
	DWORD Dir();
	int HandleOneFile(LPCTSTR lpszDirectory, WIN32_FIND_DATA* pFindData, BOOL bFindDir);
	DWORD FindDirAndFile(LPCTSTR lpszDirectory);
private:
	BOOL m_bCancel;
	CStringArray *m_pStrArySubDirectory_Private;
	DWORD m_dwDirNum;
	ULONGLONG m_AmountBytes;
	BOOL m_bSerachSubDir;
	BOOL m_bAbsolutePath;			//�Ƿ�Ҫ�������·��
	DWORD m_dwRelativePathStartPos;	//���·������ʼλ��
	char m_strFilter[MAX_PATH / 2];
};


class CHwDirEx
{
public:
	CHwDirEx(
		LPCTSTR lpszMultiFindPath,					// Ҫ������·�����硰E:\\winnt\\;d:\temp\\;��
		LPCTSTR lpszMultiFindFilter,				// Ҫ�����Ĺ����������硰*.bmp;*.exe;��
		LPCTSTR lpszMultiExcludeFilter = NULL,		// Ҫ�ų��Ĺ����������硰*.bmp;*.exe;��
		BOOL bSerachSubDir = TRUE,					// ������Ŀ¼
		BOOL bAbsolutePath = TRUE,					// �Ǿ���·��
		CHwDirEx **ppHwDirEx = NULL					// ��������ָ�봫��ȥ��������
	);
	ULONGLONG GetAmountBytes();
	virtual ~CHwDirEx();
	void Cancel();

	CStringArray *m_pStrAryResFile, *m_pStrArySubDirectory;
private:
	CHwDir* m_pHwDir;
	BOOL m_bCancel;
	void DirAll(
		LPCTSTR lpszFindPath,						// Ҫ������·�����硰E:\\winnt\\��
		LPCTSTR lpszMultiFindFilter,				// Ҫ�����Ĺ����������硰*.bmp;*.exe;��
		LPCTSTR lpszMultiExcludeFilter = NULL,		// Ҫ�ų��Ĺ����������硰*.bmp;*.exe;��
		BOOL bSerachSubDir = TRUE,					// ������Ŀ¼
		BOOL bAbsolutePath = TRUE					// �Ǿ���·��
	);
	void Dir(
		LPCTSTR lpszFindPath,						// Ҫ������·�����硰E:\\winnt\\��
		LPCTSTR lpszMultiFindFilter,				// Ҫ�����Ĺ����������硰*.bmp;*.exe;��
		CStringArray &StrAryResFile,				// �������ļ����浽��
		CStringArray &StrArySubDirectory,			// ��������Ŀ¼���浽��
		DWORD &dwAmountBytes,						// ���ֽ������浽��
		BOOL bSerachSubDir = TRUE,					// ������Ŀ¼
		BOOL bAbsolutePath = TRUE					// �Ǿ���·��
	);
	DWORD m_dwDirNum;
	ULONGLONG m_AmountBytes;
};
//==========================================================================
// ���ò�����
//==========================================================================
#define GET_VALID_STRING_FROM_TOW(cs1,cs2) ( (cs1.GetLength()>0)?cs1:cs2 )
#define GET_SAFE_STRING(str) ( (str)?(str):"" )
#define NULL_STRING_FOR_DB ""
#define GET_VALID_CSTRING(cs) ( (cs).GetLength()>0?(cs):((cs),(cs)=NULL_STRING_FOR_DB) )
#define GET_VALID_CSTRING_P(csp) ( (csp)?(*(csp)):"" )
#define STRNCPY_CS(sz,cs) strncpy((char*)(sz),(cs).GetBuffer(0),sizeof(sz))
#define STRNCPY_SZ(sz1,sz2) strncpy(((char*)(sz1)),(sz2)?((char*)(sz2)):"",sizeof(sz1))
#define STRNCPY(sz1,sz2,size) \
{\
	strncpy(((char*)(sz1)),(sz2)?((char*)(sz2)):"",(size));\
	((char*)(sz1))[(size)-1] = '\0';\
}
// ʱ�����͵����ݳ���
#define DATETIME_TYPE_LENGTH				20
#define STRCPY(sz1,sz2) strcpy ( (char*)(sz1), (char*)((sz2)?(sz2):"") )
#define STRLEN_SZ(sz) ((sz)?strlen((char*)(sz)):0)
#define COPMNC_CS_SZ(cs,sz) ( (sz) && ((cs).CompareNoCase(sz)==0) )
#define STRCMP_SAFE(sz1,sz2) (strcmp((char*)GET_SAFE_STRING(sz1),(char*)GET_SAFE_STRING(sz2)))
#define STRLEN_SAFE(sz) ((sz)?strlen((char*)(sz)):0)
#define ATOI_SAFE(sz) (atoi((const char*)(GET_SAFE_STRING((char*)(sz)))))
#define ASSERT_ADDRESS(p,size) ASSERT((p)!=NULL && AfxIsValidAddress((p),(size),TRUE))
#define VALID_IP_PORT(ip,port) ((STRLEN_SAFE(ip)>0) && (port)>1000)
#define LENGTH(x) sizeof(x)/sizeof(x[0])
#define MIN(x,y) (((DWORD)(x)<(DWORD)(y))?(x):(y))
#define MAX(x,y) (((DWORD)(x)>(DWORD)(y))?(x):(y))
// ��Ч�ľ��
#define HANDLE_IS_VALID(h) ((HANDLE)(h) && ((HANDLE)(h)!=INVALID_HANDLE_VALUE))
// �رվ��
#define CLOSE_HANDLE(h)\
{\
	if ( HANDLE_IS_VALID(h) )\
	{\
		::CloseHandle ( h );\
		(h) = NULL;\
	}\
}
//
// ��������õ��Զ�����Ϣ���ŵ������ˣ��Ա�֤Ψһ��
//
enum
{
	WM_SHOWLOG = WM_USER + 0x01000,
};
int ConvertStrToCTime(char *chtime, CTime &cTime);
CString GetOneLine(CString &str);
int GetMouthByShortStr(LPCTSTR lpszShortMonth);
CString hwFormatMessage(DWORD dwErrorCode);
int WriteDataToFile(LPCTSTR filename, char* data, long size, LPCTSTR mode, int nStartPos = -1);
CString Data2HexString(int nOffset, char *data, int size);
void DbgLog(LPCTSTR lpszFormat, ...);
int ReadDataFromFile(LPCTSTR filename, char* data, long size, int nStartPos = -1);
char* MakeSureDirectory(LPCTSTR lpszDirName);
int hwSnprintf(char *buffer, int count, const char *format, ...);
BOOL PartPathAndFileAndExtensionName(
	IN LPCTSTR lpszFilePath,			// ȫ·����(�����ļ���)
	OUT CString *pcsOnlyPath,			// �����·����û���ļ�����
	OUT CString *pcsOnlyFileName,		// ������ļ�����û��·����
	OUT CString *pcsExtensionName		// �����չ��
);
BOOL PartFileAndPathByFullPath(
	LPCTSTR lpszFilePath,
	char *szOnlyFileName,
	int nFileNameSize,
	char *szOnlyPath = NULL,
	int nPathSize = 0
);
DWORD GetCurTimeString(char *buf, time_t tNow = 0);
CString GetCurTimeString(time_t tNow = 0);

template<class T1, class T2>
int FindFromArray(IN T1 &Ary, IN T2 Find)
{
	int nCount = Ary.GetSize();
	for (int i = 0; i < nCount; i++)
	{
		if (Ary.GetAt(i) == Find)
			return i;
	}
	return -1;
}

template<class T1, class T2, class T3, class T4>
int FindFromArray(IN T1 &Ary, IN T2 Find, IN T3 &AppAry, IN T4 AppFind)
{
	int nCount = Ary.GetSize();
	for (int i = 0; i < nCount; i++)
	{
		if (Ary.GetAt(i) == Find &&
			AppAry.GetAt(i) == AppFind)
		{
			return i;
		}
	}
	return -1;
}
void StandardizationPathBuffer(char *szPath, int nSize, char cFlagChar = '\\');
CString StandardizationFileForPathName(LPCTSTR lpszFileOrPathName, BOOL bIsFileName, char cReplaceChar = '_');
char *hwStrrChr(const char *string, int c);
char *hwStrChr(const char *string, int c);
BOOL PartFileAndExtensionName(
	IN LPCTSTR lpszFileName,
	OUT char *szFileName,
	IN int nFileNameSize,
	OUT char *szExtensionName = NULL,
	IN int nExtensionNameSize = 0);
BOOL hwDeleteFolder(LPCTSTR lpszFolder);
BOOL CopyFileAppend(LPCTSTR lpszFileName_Src, LPCTSTR lpszFileName_Dst, int nOffset);
BOOL CreateNullFile(LPCTSTR lpszFileName, int nFileSize);
BOOL WaitForThreadEnd(HANDLE hThread, DWORD dwWaitTime = 5000);
DWORD SelectPathByCommonDlg(LPSTR lpszPathName, HWND hwndOwner = NULL);
BOOL SelectPathByCommonDlg(CWnd *pDlg, UINT nEditID);
CString FormatFileSize(double fFileSize);

#endif // !defined(AFX_PUBLICFUNCTION_H__654F176C_F11F_4843_AEA0_F53676D52341__INCLUDED_)

