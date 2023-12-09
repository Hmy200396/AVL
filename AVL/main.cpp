#include<iostream>
#include"AVLTree.h"
using namespace std;

void Test_AVLTree1()
{
	//int a[] = { 16,3,7,11,9,26,18,14,15 };
	int a[] = { 4,2,6,1,3,5,15,7,16,14 };
	AVLTree<int, int> t1;
	for (auto e : a)
	{
		t1.Insert(make_pair(e, 0));
	}
	t1.InOrder();
	cout << t1.IsBalance();
}
int main()
{
	Test_AVLTree1();
	return 0;
}