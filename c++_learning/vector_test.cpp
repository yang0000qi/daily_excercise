/*************************************************************************
	> File Name: vector_test.cpp
	> Author: 
	> Mail: 
	> Created Time: 2019年06月19日 星期三 19时53分30秒
 ************************************************************************/

#include<iostream>
#include <string.h>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
	vector <int> obj;
	for(int i=0; i<10; i++)
	{
		obj.push_back(i);
		cout << obj[i] << ",";
	}

	for(int i=0; i<5; i++)
	{
		obj.pop_back();
	}

	cout << "\n" << endl;

	for(int i=0; i<obj.size();i++)
	{
		cout << obj[i] << ",";
	}

	cout << "\n" << endl;

	/*sort*/
	cout << "sort big to little" << endl;
	reverse(obj.begin(), obj.end());
	for(int i=0;i<obj.size();i++)
	{
		cout << obj[i] << ",";
	}
	cout << "\n" << endl;

	/*使用迭代器将容器中的数据输出*/
	cout << "使用迭代器: " << endl;
	vector<int>:: iterator it;
	for(it=obj.begin(); it!=obj.end(); it++)
	{
		cout << *it << ",";
	}
	cout << "\n" << endl;

	return 0;
}

