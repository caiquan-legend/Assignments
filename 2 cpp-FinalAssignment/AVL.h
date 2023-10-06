#pragma once
#ifndef _AVL_
#define _AVL_
#include"Clients.h"
#include<queue>

template<typename T>struct node {
	T val;
	int height;
	node* left, * right;
	node(const T& element, int h = 1, node* le = nullptr, node* ri = nullptr);
};

template<typename T>class AVL {
public:
	AVL(void);
	//判断树是否为空
	~AVL(void);
	bool empty(void)const;
	//返回树的大小
	int size(void)const;
	//查找
	node<T>* find(const T& tmp)const;
	//插入
	void insert(const T& value);
	//删除
	node<T>* erase(const T& key);
	//中序遍历输出
	void output(ostream& os = cout);
	//返回树高
	int getHeight(void)const;
	//清空树
	void clear(void);

protected:
	//返回子树高度
	int height(node<T>* node);
	//返回平衡因子
	int getBalance(node<T>* node);
	//更新旋转后子树高度
	void updateHeight(node<T>* node);
	//节点右旋转
	node<T>* rotateRight(node<T>* node);
	//节点左旋转
	node<T>* rotateLeft(node<T>* node);
	//插入节点
	node<T>* insert(node<T>* node, T val);
	//删除节点
	node<T>* remove(node<T>* node, T val);
	//自底向上重新平衡树
	node<T>* reBalance(node<T>* node);
	void _output(ostream&os, node<T>* node);
	void _delete(node<T>* node);
private:
	node<T>* root;
	int Size;
};
#endif