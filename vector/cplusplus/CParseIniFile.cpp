#include "pch.h"

#include "CParseIniFile.h"

#include "CParseIniFile.h"





bool CParseIniFile::ReadConfig(const string& filename, map<string, string>& mContent, const char* section)
{
	mContent.clear();
	ifstream infile(filename.c_str());
	if (!infile)
	{
		//LOG4CXX_ERROR(logger, "file open error!");
		return false;
	}
	string line, key, value;
	int pos = 0;
	string Tsection = string("[") + section + "]";
	bool flag = false;
	while (getline(infile, line))
	{
		if (!flag)
		{
			pos = line.find(Tsection, 0);
			if (-1 == pos)
			{
				continue;
			}
			else
			{
				flag = true;
				getline(infile, line);
			}
		}
		if (0 < line.length() && '[' == line.at(0))
		{
			break;
		}
		if (0 < line.length() && AnalyseLine(line, key, value))
		{

			if (value.length() > 0)
			{
				if (value[value.size() - 1] == '\r')
				{
					value[value.size() - 1] = '\0';
				}
			}
			mContent[key] = value;
		}
	}
	infile.close();
	return true;
}

bool CParseIniFile::AnalyseLine(const string & line, string & key, string & val)
{
	if (line.empty())
	{
		return false;
	}
	int start_pos = 0, end_pos = line.size() - 1, pos = 0;
	if ((pos = line.find(COMMENT_CHAR)) != -1)
	{
		if (0 == pos)
		{//�еĵ�һ���ַ�����ע���ַ�
			return false;
		}
		end_pos = pos - 1;
	}
	string new_line = line.substr(start_pos, start_pos + 1 - end_pos);  // Ԥ����ɾ��ע�Ͳ���

	if ((pos = new_line.find('=')) == -1)
	{
		return false;  // û��=��
	}

	key = new_line.substr(0, pos);
	val = new_line.substr(pos + 1, end_pos + 1 - (pos + 1));

	Trim(key);
	if (key.empty())
	{
		return false;
	}
	Trim(val);
	return true;
}

void CParseIniFile::Trim(string & str)
{
	if (str.empty())
	{
		return;
	}
	int i, start_pos, end_pos;
	for (i = 0; i < str.size(); ++i)
	{
		if (!IsSpace(str[i]))
		{
			break;
		}
	}
	if (i == str.size())
	{ //ȫ���ǿհ��ַ���
		str = "";
		return;
	}

	start_pos = i;

	for (i = str.size() - 1; i >= 0; --i)
	{
		if (!IsSpace(str[i]))
		{
			break;
		}
	}
	end_pos = i;

	str = str.substr(start_pos, end_pos - start_pos + 1);
}

bool CParseIniFile::IsSpace(char c)
{
	if (' ' == c || '\t' == c)
	{
		return true;
	}
	return false;
}

bool CParseIniFile::IsCommentChar(char c)
{
	switch (c)
	{
	case COMMENT_CHAR:
		return true;
	default:
		return false;
	}
}

void CParseIniFile::PrintConfig(const map<string, string> & mContent)
{
	map<string, string>::const_iterator mite = mContent.begin();
	for (; mite != mContent.end(); ++mite)
	{
		cout << mite->first << "=" << mite->second << endl;
	}
}




bool CParseIniFile::writeConfig(wstring accEdit, wstring velEdit)
{
	//CFilePath *filePahtc = new CFilePath;
	wstring iniPath = L"";

	//iniPath += CONFIG_FILE;
	BOOL flage = TRUE;
	if (0 == accEdit.compare(_T("")))
	{
		return false;
	}
	else if (0 == velEdit.compare(_T("")))
	{
		return false;
	}
	else
	{
		//��Ҫ�޸ĵ�ֵ
		wstring iniText = accEdit + _T(",") + velEdit;
		wchar_t test[100] = { 0 };
		for (int i = 1; i <= 32; i++)
		{
			wstring strAccounti = to_wstring(i);
			wstring strAcounti = _T("ClientAccount") + strAccounti;
			//ȡinit����
			::GetPrivateProfileString(TEXT("Client"), strAcounti.c_str(), NULL, test, 255, iniPath.c_str());
			wstring strIniText = test;
			if (flage == TRUE)
			{
				//ѭ����ѯinit�����Ƿ��е�ǰ��ӵ��˻�
				for (size_t j = 0; j < vecInitText.size(); j++)
				{
					if (0 == accEdit.compare(to_wstring(vecInitText[j].initTextAccount).c_str()))
					{
						//::MessageBox(this->m_hWnd, _T("init�ļ������е�ǰ�˻�"), _T("����"), MB_SYSTEMMODAL | MB_ICONERROR | MB_OK);
						std::cout << "init�ļ������е�ǰ�˻�" << std::endl;
						return false;
					}
				}
				flage = FALSE;
			}
			if (0 == strIniText.compare(_T("0")))
			{
				//std::cout << "init�ļ������е�ǰ�˻�" << std::endl;
				std::cout << "�������д�뵽init" << std::endl;
				//�������д�뵽init
				::WritePrivateProfileString(TEXT("Client"), strAcounti.c_str(), iniText.c_str(), iniPath.c_str());
				memcpy(mpInitText.initTextKey, strAcounti.c_str(), 100);
				mpInitText.initTextAccount = _ttoi(accEdit.c_str());
				mpInitText.volume = _ttol(velEdit.c_str());
				vecInitText.push_back(mpInitText);
				return false;
			}
		}
	}
	return  true;
}

bool CParseIniFile::writeConfigToken(wstring token)
{
	CFilePath *filePahtc = new CFilePath;
	wstring iniPath = filePahtc->GetInitPath();
	std::fstream _file;
	_file.open(iniPath.c_str(), ios::in);
	if (!_file)
	{
		cout << "Cannot find file:" << endl;
		//�����ļ���
		ofstream fout(iniPath);
		exit(-1);
	}
	if (token.length()<=0) {
		return false;
	}
	wstring iniText = L"ClientUserId";
	iniText.append(token);
	BOOL flage = ::WritePrivateProfileString(TEXT("USER"), iniText.c_str(), token.c_str(), iniPath.c_str());
	if (flage) {
		cout << "д��ɹ�" << endl;
	}
	else {
		cout << "д��ʧ��" << endl;
	}
	
	return  true;
}

CFilePath::CFilePath() {}
CFilePath::~CFilePath() {}
wstring CFilePath::GetInitPath() {
	//���exeִ��·��
	TCHAR tcExePath[MAX_PATH] = { 0 };
	::GetModuleFileName(NULL, tcExePath, MAX_PATH);
	TCHAR *pFind = _tcsrchr(tcExePath, '\\');
	if (pFind == NULL)
	{
		return _T("");
	}
	*pFind = '\0';
	CString szIniPath = tcExePath;
	szIniPath += "\\";
	szIniPath += CONFIG_FILE;
	return szIniPath.GetString();

};




void CFilePath::GetInitText()
{

	CFilePath *filePahtc = new CFilePath;
	wstring iniPath = filePahtc->GetInitPath();
	std::fstream _file;
	_file.open(iniPath.c_str(), ios::in);
	if (!_file)
	{
		cout << "Cannot find file:" << endl;
		//�����ļ���
		ofstream fout(iniPath);
		exit(-1);
	}

	wchar_t test[100] = { 0 };
	//vector<wstring> vecSegString;
	//vecSegString.clear();
	wstring rrr = _T("1e");

	wstring strAcounti = _T("LocalUserID");
	//std::string strAcounti = "LocalUserID";
	DWORD num = ::GetPrivateProfileString(TEXT("LOCAL"), strAcounti.c_str(), NULL, test, 100, iniPath.c_str());
	if (0 != num)
	{
		wstring strIniText = test;

	//	if (strIniText && *strIniText != '\0')
			if (0 != strIniText.compare(_T("0")))
  
		{
			//��Ϊ��
			//string sa;
			//sa = strIniText;
			std::cout << "û���ҵ�sa:" << std::endl;
		}
	}
	else
	{
		std::cout << "û���ҵ�AccountCon.ini�ļ�" << std::endl;
		PostQuitMessage(0);
		return;
	}

	delete filePahtc;
}

std::string CFilePath::WStringToString(const std::wstring &wstr)
{
	std::string str;
	int nLen = (int)wstr.length();
	str.resize(nLen, ' ');
	int nResult = WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)wstr.c_str(), nLen, (LPSTR)str.c_str(), nLen, NULL, NULL);
	if (nResult == 0)
	{
		return "";
	}
	return str;
}

int CFilePath::GetlogingIsNotUserId()
{

	CFilePath *filePahtc = new CFilePath;
	wstring iniPath = filePahtc->GetInitPath();
	
	map<string, string>fname;
	CParseIniFile config;

	std::string pathe = filePahtc->WStringToString(iniPath);
	bool flage = config.ReadConfig(pathe.c_str(), fname, "LOCAL");
	if (flage)
	{
		std::cout << "ReadConfig" << stod(fname["ClientUserID"])<< std::endl;
		cout << fname["ClientUserID"] << endl;
		cout << fname["ClientUserID"] << endl;
		cout << stod(fname["ClientUserID"]) << endl;
	}



	wchar_t test[100] = { 0 };
	//vector<wstring> vecSegString;
	//vecSegString.clear();
	wstring rrr = _T("1e");

	wstring strAcounti = _T("LocalUserID");
	//std::string strAcounti = "LocalUserID";
	DWORD num = ::GetPrivateProfileString(TEXT("LOCAL"), strAcounti.c_str(), NULL, test, 100, iniPath.c_str());
	if (0 != num)
	{
		wstring strIniText = test;

		//	if (strIniText && *strIniText != '\0')
		if (0 != strIniText.compare(_T("0")))

		{
			//::MessageBox(this->m_hWnd, TEXT("ɾ���ɹ�"), TEXT("��ʾ"), MB_OK); */
			//��Ϊ��
			//string sa;
			//sa = strIniText;
			std::cout << "û���ҵ�sa:" << std::endl;
		}
	}
	else
	{
		std::cout << "û���ҵ�AccountCon.ini�ļ�" << std::endl;
		PostQuitMessage(0);
		return 1;
	}

	delete filePahtc;

	return 1;
}