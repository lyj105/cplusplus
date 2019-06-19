#include "pch.h"

#include "Vector.h"
bool sortcol(const vector<int>& v1, const vector<int>& v2) {

	return v1[1] > v2[1];
}

void sortEntireVectoerP() {
     
	vector<vector<int>> vect{ {3, 5, 1},
								{4, 8, 6},
								{7, 2, 9},
								{7, 3, 9} };

	int m = vect.size();

	int n = vect[0].size();

	for (int i=0;i<m;i++)
	{
		for (int j = 0; j < n; j++)
			cout << vect[i][j] << " ";
		cout << endl;
	}
	cout << "The Matrix after sorting is:\n";
	sort(vect.begin(), vect.end(), sortcol);

	for (int i=0;i<m;i++)
	{
		for (int j=0;j<n;j++)
			cout << vect[i][j] << " ";
		cout << endl;
	}

}

void inputOfrowAndTakeTh() {

	int row = 5;
	int colom[] = { 5,3,4,2,1 };

	// Create a vector of vector with size 
   // equal to row. 
	vector<vector<int>> vec(row);

	for (int i=0;i<row;i++)
	{
		int col;
		col = colom[i];
		
		vec[i] = vector<int> (col);

		for (int j = 0; j < col; j++)
			vec[i][j] = j + 1;

	}

	for (int i=0;i<row;i++)
	{
		for (int j=0;j<vec[i].size();j++)
			cout << vec[i][j] << " ";
		cout << endl;
	}


}


//C ++中的矢量erase（）和clear（）
//向量与动态数组相同，能够在插入或删除元素时自动调整自身大小，其存储由容器自动处理。
//Case 4 : To sort the entire 2D vector on basis of a particular column in descending order.

void vectoreraseandclearinC() {

	vector<int> myvector;
	myvector.push_back(1);
	myvector.push_back(2);
	myvector.push_back(3);
	myvector.push_back(4);
	myvector.push_back(5);

	// Vector becomes 1, 2, 3, 4, 5 

	myvector.clear();
	// vector becomes empty 

	// Printing the vector 
	for (auto it = myvector.begin(); it != myvector.end(); ++it)
		cout << ' ' << *it;

	vector<int> myvector_{ 1,2,3,4,5 };
	vector<int>::iterator it;

	it = myvector_.begin();
	myvector_.erase(it);

	for (auto it = myvector_.begin(); it != myvector_.end(); ++it)
	{
		cout << ' ' << *it;
	}



}