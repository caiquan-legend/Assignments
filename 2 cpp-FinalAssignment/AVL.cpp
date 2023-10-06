#include"AVL.h"
using std::max;
using std::queue;

template<typename T>node<T>::node(const T& element, int h, node* le, node* ri) :
	val(element), height(h), left(le), right(ri) {}



template<typename T>AVL<T>::AVL(void) : root(nullptr), Size(0) {}
template<typename T>AVL<T>::~AVL(void) { clear(); }
template<typename T>bool AVL<T>::empty(void)const { return Size == 0; }
template<typename T>int AVL<T>::size(void)const { return Size; }
template<typename T>void AVL<T>::output(ostream& os) { _output(os, root); }
template<typename T>int AVL<T>::getHeight(void)const { return height(root); }
template<typename T>void AVL<T>::clear(void) { _delete(root); }



template<typename T>int AVL<T>::height(node<T>* _node) {
	return _node ? _node->height : 0;
}
template<typename T>int AVL<T>::getBalance(node<T>* _node) {
	return _node ? height(_node->left) - height(_node->right) : 0;
}
template<typename T>void AVL<T>::updateHeight(node<T>* _node) {
	_node->height = max(height(_node->left), height(_node->right)) + 1;
}




template<typename T>inline node<T>* AVL<T>::rotateLeft(node<T>* _node) {
	node<T>* newRoot = _node->right;
	_node->right = newRoot->left;
	newRoot->left = _node;
	updateHeight(_node);
	updateHeight(newRoot);
	return newRoot;
}
template<typename T>inline node<T>* AVL<T>::rotateRight(node<T>* _node) {
	node<T>* newRoot = _node->left;
	_node->left = newRoot->right;
	newRoot->right = _node;
	updateHeight(_node);
	updateHeight(newRoot);
	return newRoot;
}
template<typename T>node<T>* AVL<T>::reBalance(node<T>* _node) {
	int balance = getBalance(_node);
	if (balance > 1) {
		if (getBalance(_node->left) < 0)
			_node->left = rotateLeft(_node->left);
		return rotateRight(_node);
	}
	else if (balance < -1) {
		if (getBalance(_node->right) > 0)
			_node->right = rotateRight(_node->right);
		return rotateLeft(_node);
	}
	return _node;
}


template<typename T>void AVL<T>::insert(const T& value) {
	Size++; root = insert(root, value);
}
template<typename T>node<T>* AVL<T>::erase(const T& key) {
	if (!empty()) {
		Size--;
		remove(root, key);
	}
	return nullptr;
}
template<typename T>node<T>* AVL<T>::find(const T& key)const {
	node<T>* cur = root;
	while (cur) {
		if (key < cur->val)
			cur = cur->left;
		else if (key > cur->val)
			cur = cur->right;
		else return cur;
	}
	return nullptr;
}
template<typename T>node<T>* AVL<T>::insert(node<T>* _node, T val) {
	if (_node == nullptr)return new node(val, 1);
	if (_node->val == val) {
		_node->val = val;
		return _node;
	}
	if (val < _node->val)
		_node->left = insert(_node->left, val);
	else if (val > _node->val)
		_node->right = insert(_node->right, val);
	updateHeight(_node);
	return reBalance(_node);
}
template<typename T>node<T>* AVL<T>::remove(node<T>* _node, T val) {
	auto getMin = [&](node<T>* _node)->node<T>*{
		node<T>* cur = _node;
		while (cur->left)cur = cur->left;
		return cur;
	};
	if (_node == nullptr)return nullptr;
	if (val < _node->val)_node->left = remove(_node->left, val);
	else if (val > _node->val)_node->right = remove(_node->right, val);
	else {
		if (!_node->left && !_node->right) {
			delete _node;
			return nullptr;
		}
		else if (!_node->left) {
			node<T>* tmp = _node->right;
			delete _node;
			return tmp;
		}
		else if (!_node->right) {
			node<T>* tmp = _node->left;
			delete _node;
			return tmp;
		}
		else {
			node<T>* tmp = getMin(_node->right);
			_node->val = tmp->val;
			_node->right = remove(tmp->right, val);
		}
	}
	updateHeight(_node);
	return reBalance(_node);
}

template<typename T>void AVL<T>::_output(ostream&os, node<T>* node) {
	if (node == nullptr)return;
	_output(node->left);
	node->val.display(os);
	_output(node->right);
}

template<typename T>void AVL<T>::_delete(node<T>* node) {
	if (node == nullptr)return;
	_delete(node->left);
	_delete(node->right);
	delete node;
}