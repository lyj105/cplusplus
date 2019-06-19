
#include "pch.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include "Vector.h"
using namespace std;

//Case 5 : Sorting the 2D Vector on basis of no.of columns in row in ascending order.
//In this type of sorting, 2D vector is sorted on basis of a no.of column in ascending order.This is achieved by passing a third argument in “sort()” as a call to user defined explicit function.
bool sizecom(const vector<int>& v1,const vector<int>& v2) {
	return  v1.size() < v2.size();
}

void SortByFirstAndSecond();

int main()
{
	vector<vector<int>> vect{ {1, 2},
							   {3, 4, 5},
							   {6} };
	for (int i=0;i<vect.size();i++)
	{
		for (int j=0;j<vect[i].size();j++)
		{
			cout << vect[i][j] << " ";
		}
		cout << endl;
	}
	sort(vect.begin(), vect.end(), sizecom);
   // Displaying the 2D vector after sorting 
	cout << "The Matrix after sorting is:\n";
	for (int i = 0; i < vect.size(); i++)
	{
		//loop till the size of particular 
		//row 
		for (int j = 0; j < vect[i].size(); j++)
			cout << vect[i][j] << " ";
		cout << endl;
	}
	// Use of "sort()" for sorting first row 
	sort(vect[0].begin(), vect[0].end());

	//Sorting Vector of Pairs in C++ | Set 1 (Sort by first and second)
	std::cout << "Sorting Vector of Pairs in C++ | Set 1 (Sort by first and second)\n";
	SortByFirstAndSecond();

	std::cout << "Case 4 : To sort the entire 2D vector on basis of a particular column in descending order.\n";
	sortEntireVectoerP();
	
	inputOfrowAndTakeTh();
	std::cout << "vector erase() and clear() in C++.\n";
	vectoreraseandclearinC();
}


//Sorting Vector of Pairs in C++ | Set 1 (Sort by first and second)
void SortByFirstAndSecond() {
	vector<pair<int, int>> vect;

	int arr[] = { 10, 20, 5, 40 };
	int arrs[] = { 30, 60, 20, 50 };
	
	int n = sizeof(arr) / sizeof(arrs[0]);

	for (int i = 0; i < n; i++)
		vect.push_back(make_pair(arr[i], arrs[i]));

	//
	sort(vect.begin(), vect.end());

	for (int i = 0; i < n; i++)
	{
		cout << vect[i].first << " "
			<< vect[i].second << endl;
	}
}

