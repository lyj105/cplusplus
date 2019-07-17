// File.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <vector>
#include <string>
#include<io.h>
#include <fstream>
using namespace std;

class Solution{
	public:
		void getFile2(string path,vector<string>& files,vector<string> &ownname ) {

			//文件句柄  
			intptr_t   hFile = 0;
			//文件信息  
			struct _finddata_t fileinfo;
			string p;

			if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
            {
				do 
				{

					//如果是目录,迭代之  
			//如果不是,加入列表  
					if ((fileinfo.attrib &  _A_SUBDIR))
					{
						if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
							getFile2(p.assign(path).append("\\").append(fileinfo.name), files, ownname);
					}
					else
					{
						files.push_back(path + "\\" + fileinfo.name);
						ownname.push_back(fileinfo.name);
					}

				} while (_findnext(hFile,&fileinfo) == 0);
				_findclose(hFile);
			}
		};


};


int main()
{
	//主函数
	std::string filePath = "F:\\vtk\\VTK-8.2.0\\VTK-8.2.0\\vtk-prefix\\lib";
	vector<string> files;
	vector<string> filesname; 

	//获取该路径下的所有文件路径 
	Solution *so = new Solution;
	so->getFile2(filePath, files, filesname);
	//获取该路径下的所有文件路径和文件名 
	//getFiles2(filePath, files, filesname);

	char str[120];
	for (int i = 0; i < files.size(); i++)
	{
		
	}
	ofstream fout;
	fout.open("planprowtext");
	for (int i=0;i<filesname.size();i++)
	{
		//cout << filesname[i].c_str() << endl;
        //#pragma comment(lib, "vtkalglib-8.1.lib")

		std::string std_ = "#pragma comment(lib, " + filesname[i] + ") \n";

		std::cout << "#pragma comment(lib, " << filesname[i].c_str() << std::endl;
		fout << std_;
	}

	
	
	
	 fout.close();
	
    std::cout << "Hello World!\n"; 
}

