#pragma once
#include<utility>
#include<assert.h>
using namespace std;
template<class K, class V>
struct AVLTreeNode
{
	AVLTreeNode(const pair<K, V>& kv)
		:_left(nullptr)
		, _right(nullptr)
		, _parent(nullptr)
		, _kv(kv)
		, _bf(0)
	{}
	AVLTreeNode<K, V>* _left;
	AVLTreeNode<K, V>* _right;
	AVLTreeNode<K, V>* _parent;
	pair<K, V> _kv;
	int _bf; //balance factor
};

template<class K,class V>
class AVLTree
{
	typedef AVLTreeNode<K, V> Node;
public:
	bool Insert(const pair<K, V>& kv);
	void InOrder();
	bool IsBalance();
private:
	void RotateL(Node* parent);//����
	void RotateR(Node* parent);//�ҵ���
	void RotateLR(Node* parent);//����˫��
	void RotateRL(Node* parent);//����˫��
	void _InOrder(Node* root);
	bool _IsBalance(Node* root);
	int _Height(Node* root);
private:
	Node* _root = nullptr;
};

template<class K, class V>
bool AVLTree<K, V>::Insert(const pair<K, V>& kv)
{
	if (_root == nullptr)
	{
		_root = new Node(kv);
		return true;
	}
	Node* parent = nullptr;
	Node* cur = _root;
	while (cur)
	{
		if (cur->_kv.first < kv.first)
		{
			parent = cur;
			cur = cur->_right;
		}
		else if (cur->_kv.first > kv.first)
		{
			parent = cur;
			cur = cur->_left;
		}
		else
			return false;
	}
	cur = new Node(kv);
	if(parent->_kv.first < kv.first)
		parent->_right = cur;
	if (parent->_kv.first > kv.first)
		parent->_left = cur;
	cur->_parent = parent;
	//����ƽ������
	while (parent)
	{
		if (cur == parent->_right)
			parent->_bf++;
		else
			parent->_bf--;
		if (parent->_bf == 1 || parent->_bf == -1)
		{
			//��������
			cur = parent;
			parent = parent->_parent;
		}
		else if (parent->_bf == 0)
			break;
		else if (parent->_bf == 2 || parent->_bf == -2)
		{
			//��Ҫ��ת���� -- 1�����������ƽ�� 2��������������ĸ߶�
			if (parent->_bf == 2 && cur->_bf == 1)
				RotateL(parent);
			else if (parent->_bf == -2 && cur->_bf == -1)
				RotateR(parent);
			else if (parent->_bf == -2 && cur->_bf == 1)
				RotateLR(parent);
			else if (parent->_bf == 2 && cur->_bf == -1)
				RotateRL(parent);
			else
				assert(false);
			break;
		}
		else
			assert(false);
	}
	return true;
}
template<class K, class V>
void AVLTree<K, V>::RotateL(Node* parent)//����
{
	Node* subR = parent->_right;
	Node* subRL = subR->_left;

	parent->_right = subRL;
	if (subRL != nullptr)
		subRL->_parent = parent;

	Node* ppnode = parent->_parent;

	parent->_parent = subR;
	subR->_left = parent;

	if (ppnode == nullptr)
	{
		_root = subR;
		_root->_parent = nullptr;
	}
	else
	{
		if (ppnode->_left == parent)
			ppnode->_left = subR;
		else
			ppnode->_right = subR;
		subR->_parent = ppnode;
	}
	parent->_bf = subR->_bf = 0;
}
template<class K, class V>
void AVLTree<K, V>::RotateR(Node* parent)//�ҵ���
{
	Node* subL = parent->_left;
	Node* subLR = subL->_right;

	parent->_left = subLR;
	if (subLR != nullptr)
		subLR->_parent = parent;

	Node* ppnode = parent->_parent;

	parent->_parent = subL;
	subL->_right = parent;
	if (ppnode == nullptr)
	{
		_root = subL;
		_root->_parent = nullptr;
	}
	else
	{
		if (ppnode->_left == parent)
			ppnode->_left = subL;
		else
			ppnode->_right = subL;
		subL->_parent = ppnode;
	}
	parent->_bf = subL->_bf = 0;
}
template<class K, class V>
void AVLTree<K, V>::RotateLR(Node* parent)//����˫��
{
	Node* subL = parent->_left;
	Node* subLR = subL->_right;
	int bf = subLR->_bf;
	RotateL(parent->_left);
	RotateR(parent);
	if (bf == 1)
	{
		parent->_bf = 0;
		subLR->_bf = 0;
		subL->_bf = -1;
	}
	else if (bf == -1)
	{
		parent->_bf = 1;
		subLR->_bf = 0;
		subL->_bf = 0;
	}
	else if (bf == 0)
	{
		parent->_bf = 0;
		subLR->_bf = 0;
		subL->_bf = 0;
	}
	else
		assert(false);
}
template<class K, class V>
void AVLTree<K, V>::RotateRL(Node* parent)//����˫��
{
	Node* subR = parent->_right;
	Node* subRL = subR->_left;
	int bf = subRL->_bf;
	RotateR(parent->_right);
	RotateL(parent);
	if (bf == 1)
	{
		parent->_bf = -1;
		subRL->_bf = 0;
		subR->_bf = 0;
	}
	else if (bf == -1)
	{
		parent->_bf = 0;
		subRL->_bf = 0;
		subR->_bf = 1;
	}
	else if (bf == 0)
	{
		parent->_bf = 0;
		subRL->_bf = 0;
		subR->_bf = 0;
	}
	else
		assert(false);
}
template<class K, class V>
void AVLTree<K, V>::InOrder()
{
	_InOrder(_root);
	cout << endl;
}
template<class K, class V>
void AVLTree<K, V>::_InOrder(Node* root)
{
	if (root == nullptr)
		return;
	_InOrder(root->_left);
	cout << root->_kv.first << " ";
	_InOrder(root->_right);
}
template<class K, class V>
bool AVLTree<K, V>::IsBalance()
{
	return _IsBalance(_root);
}
template<class K, class V>
bool AVLTree<K, V>::_IsBalance(Node* root)
{
	if (root == nullptr)
		return true;
	int leftH = _Height(root->_left);
	int rightH = _Height(root->_right);
	if (rightH - leftH != root->_bf)
	{
		cout << root->_kv.first << "�ڵ�ƽ�������쳣��" << endl;
		return false;
	}
	return abs(leftH - rightH) <= 1 && _IsBalance(root->_left) && _IsBalance(root->_right);
}
template<class K, class V>
int AVLTree<K, V>::_Height(Node* root)
{
	if (root == nullptr)
		return 0;
	int leftH = _Height(root->_left);
	int rightH = _Height(root->_right);
	return leftH > rightH ? leftH + 1 : rightH + 1;
}