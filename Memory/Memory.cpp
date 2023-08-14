#include <iostream>
#include <vector>
#include "CustomAllocator.h"
#include "CustomSharedPtr.h"

using namespace std;

int main()
{
	vector<int, CustomAllocator<int>> vec;
	vec.push_back(12);
	vec.push_back(345);
	vec.push_back(56);
	vec.push_back(235);
	
	for (auto val : vec)
	{
		cout << val << endl;
	}
	


	//if(1)
	//{
	//	int* value = new int(10);
	//	// Create shared ptr 
	//	CustomSharedPtr<int> myPtr = CustomSharedPtr<int>(value);
	//	cout << *myPtr << endl;
	//	cout << "================================" << endl;
	//	{
	//		CustomSharedPtr<int> myPtr1 = myPtr;
	//		cout << *myPtr << endl;
	//		cout << *myPtr1 << endl;
	//		{
	//			CustomSharedPtr<int> myPtr2 = myPtr1;
	//			cout << *myPtr << endl;
	//			cout << *myPtr1 << endl;
	//			cout << *myPtr2 << endl;
	//		}


	//	}
	//}
	//cout << "================================" << endl;
	


	return 0;
}

