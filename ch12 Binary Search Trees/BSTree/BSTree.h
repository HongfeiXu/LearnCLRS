/***************************************************************************
*  @file       BSTree.h
*  @author     Alex.Xu
*  @mail       icevmj@gmail.com
*  @date       4.19 2016
*  @remark     Implementations for algorithims from CLRS using C++ templates.
***************************************************************************/


#ifndef BSTREE_H
#define BSTREE_H

#include <iostream>

template <typename KeyType, typename ValueType>
class Node {
public:
	Node() : lchild(nullptr), rchild(nullptr), parent(nullptr) { }
	Node(KeyType key_) : key(key_), lchild(nullptr), rchild(nullptr), parent(nullptr) { }
	Node(KeyType key_, ValueType value_) : key(key_), value(value_), lchild(nullptr), rchild(nullptr), parent(nullptr) { }

	Node* lchild;
	Node* rchild;
	Node* parent;
	KeyType key;
	ValueType value;
};

template <typename KeyType, typename ValueType>
class BSTree {
public:
	using BSTNode = Node<KeyType, ValueType>;
	BSTree() : root(nullptr) { }
	~BSTree() {	release(root); }
	
	bool isEmpty() const { return root == nullptr; }
	void insert(BSTNode* p_node) { insertAuxIter(root, p_node);	}
	bool find(const KeyType &key) const { return findAux_Iterative(root, key); }
	int treeHeight()
	{
		return treeHeightAux(root);
	}

	BSTNode* search(const KeyType &key) const;
	BSTNode* minimum() { return minimumAux(root); }
	BSTNode* maximum() { return maximumAux(root); }
	BSTNode* successor(const BSTNode* pcurr_node);
	BSTNode* predecessor(const BSTNode* pcurr_node);

	void inorderTreeWalk(std::ostream &out) const { inorderTreeWalkAux(out, root); }
	void preorderTreeWalk(std::ostream &out) const { preorderTreeWalkAux(out, root); }
	void postorderTreeWalk(std::ostream &out) const { postorderTreeWalkAux(out, root); }

	void deleteNodeHasKey(const KeyType &key);

private:
	void insertAuxRecu(BSTNode* &sub_root, BSTNode* sub_parent, BSTNode *p_node);  // 递归版本
	void insertAuxIter(BSTNode* &sub_root, BSTNode *bst_node);  // 迭代版本
	bool findAux(BSTNode* sub_root, const KeyType &key) const;  // 递归版本
	bool findAux_Iterative(BSTNode* sub_root, const KeyType &key) const;  // 迭代版本
	int treeHeightAux(const BSTNode* pNode)
	{
		int treeHeight = 0;
		if (pNode != nullptr)
		{
			int leftHeight = treeHeightAux(pNode->lchild);
			int rightHeight = treeHeightAux(pNode->rchild);
			treeHeight = leftHeight >= rightHeight ? leftHeight + 1 : rightHeight + 1;
		}
		return treeHeight;
	}
	BSTNode* minimumAux(BSTNode* sub_root);
	BSTNode* maximumAux(BSTNode* sub_root);
	void inorderTreeWalkAux(std::ostream &out, const BSTNode* const &sub_root) const;
	void preorderTreeWalkAux(std::ostream &out, const BSTNode *const &sub_root) const;
	void postorderTreeWalkAux(std::ostream &out, const BSTNode *const &sub_root) const;
	void release(BSTNode* p);
	void transplant(BSTNode *lhs_subtree, BSTNode *rhs_subtree);  // transplant rhs_subtree to lhs_subtree

private:
	BSTNode* root;
};

template <typename KeyType, typename ValueType>
inline typename BSTree<KeyType, ValueType>::BSTNode* BSTree<KeyType, ValueType>::search(const KeyType &key) const
{
	typename BSTree<KeyType, ValueType>::BSTNode* ret = root;
	while (ret != nullptr && key != ret->key)
	{
		if (key < ret->key)
		{
			ret = ret->lchild;
		}
		else
		{
			ret = ret->rchild;
		}
	}
	return ret;
}

template <typename KeyType, typename ValueType>
inline void BSTree<KeyType, ValueType>::insertAuxRecu(BSTNode* &sub_root, BSTNode* sub_parent, BSTNode *p_node)
{
	if (sub_root == nullptr)
	{
		sub_root = new BSTree<KeyType, ValueType>::BSTNode(p_node->key, p_node->value);
		sub_root->parent = sub_parent;
	}
	else if (p_node->key < sub_root->key)
	{
		insertAuxRecu(sub_root->lchild, sub_root, p_node);
	}
	else
	{
		insertAuxRecu(sub_root->rchild, sub_root, p_node);
	}
}

template <typename KeyType, typename ValueType>
inline void BSTree<KeyType, ValueType>::insertAuxIter(BSTNode* &sub_root, BSTNode *p_node)
{
	BSTNode* pparent_node = nullptr; // 记录要插入节点的父节点
	BSTNode* temp = sub_root;
	while (temp != nullptr)
	{
		pparent_node = temp;
		if (p_node->key < temp->key)
		{
			temp = temp->lchild;
		}
		else
		{
			temp = temp->rchild;
		}
	}

	p_node->parent = pparent_node;

	if (pparent_node == nullptr)
	{
		sub_root = p_node;
	}
	else if (p_node->key < pparent_node->key)
	{
		pparent_node->lchild = p_node;
	}
	else
	{
		pparent_node->rchild = p_node;
	}
}

template <typename KeyType, typename ValueType>
inline bool BSTree<KeyType, ValueType>::findAux(BSTNode* sub_root, const KeyType &key) const
{
	if (sub_root == nullptr)
		return false;

	if (key == sub_root->key)
		return true;
	else if(key < sub_root->key)
		return findAux(sub_root->lchild, key);
	else
		return findAux(sub_root->rchild, key);
}

template <typename KeyType, typename ValueType>
inline typename BSTree<KeyType, ValueType>::BSTNode* BSTree<KeyType, ValueType>::minimumAux(BSTNode* sub_root)
{
	if (sub_root == nullptr)
	{
		std::cerr << "BSTree is Empty! minimumAux() cannot work!" << std::endl;
		exit(EXIT_FAILURE);
	}
	BSTNode* p = sub_root;
	while (p->lchild != nullptr)
		p = p->lchild;
	return p;
}

template <typename KeyType, typename ValueType>
inline typename BSTree<KeyType, ValueType>::BSTNode* BSTree<KeyType, ValueType>::maximumAux(BSTNode* sub_root)
{
	if (sub_root == nullptr)
	{
		std::cerr << "BSTree is Empty! maximumAux() cannot work!" << std::endl;
		exit(EXIT_FAILURE);
	}
	BSTNode* p = sub_root;
	while (p->rchild != nullptr)
		p = p->rchild;
	return p;
}

template <typename KeyType, typename ValueType>
inline typename BSTree<KeyType, ValueType>::BSTNode* BSTree<KeyType, ValueType>::successor(const BSTNode* pcurr_node)
{
	if (pcurr_node->rchild != nullptr)
		return minimumAux(pcurr_node->rchild);
	BSTNode* p_node = pcurr_node->parent;
	while (p_node != nullptr && pcurr_node == p_node->rchild)
	{
		pcurr_node = p_node;
		p_node = p_node->parent;
	}
	return p_node;
}

template <typename KeyType, typename ValueType>
inline typename BSTree<KeyType, ValueType>::BSTNode* BSTree<KeyType, ValueType>::predecessor(const BSTNode* pcurr_node)
{
	if (pcurr_node->lchild != nullptr)
		return minimumAux(pcurr_node->lchild);
	BSTNode* p_node = pcurr_node->parent;
	while (p_node != nullptr && pcurr_node == p_node->lchild)
	{
		pcurr_node = p_node;
		p_node = p_node->parent;
	}
	return p_node;
}

template <typename KeyType, typename ValueType>
inline void BSTree<KeyType, ValueType>::deleteNodeHasKey(const KeyType &key)
{
	BSTNode* p_key = search(key);
	if (p_key == nullptr)  // the key is not in the tree node
		return;
	if (p_key->lchild == nullptr)
		transplant(p_key, p_key->rchild);
	else if (p_key->rchild == nullptr)
		transplant(p_key, p_key->lchild);
	else
	{
		BSTNode* p_bigger = minimumAux(p_key->rchild);
		if (p_bigger->parent != p_key)
		{
			transplant(p_bigger, p_bigger->rchild);
			p_bigger->rchild = p_key->rchild;
			p_key->rchild->parent = p_bigger;
		}
		transplant(p_key, p_bigger);
		p_bigger->lchild = p_key->lchild;
	}
	delete p_key;
}

template <typename KeyType, typename ValueType>
inline bool BSTree<KeyType, ValueType>::findAux_Iterative(BSTNode* sub_root, const KeyType &key) const
{
	while (sub_root != nullptr && key != sub_root->key)
	{
		if (key < sub_root->key)
			sub_root = sub_root->lchild;
		else
			sub_root = sub_root->rchild;
	}
	if (sub_root == nullptr)
		return false;
	else
		return true;
}

template <typename KeyType, typename ValueType>
inline void BSTree<KeyType, ValueType>::inorderTreeWalkAux(std::ostream &out, const BSTNode* const &sub_root) const
{
	if (sub_root != nullptr)
	{
		inorderTreeWalkAux(out, sub_root->lchild);
		out << sub_root->key << " " << sub_root->value << "\n";
		inorderTreeWalkAux(out, sub_root->rchild);
	}
	
}

template <typename KeyType, typename ValueType>
inline void BSTree<KeyType, ValueType>::preorderTreeWalkAux(std::ostream &out, const BSTNode* const &sub_root) const
{
	if (sub_root != nullptr)
	{
		out << sub_root->key << " " << sub_root->value << "\n";
		preorderTreeWalkAux(out, sub_root->lchild);
		preorderTreeWalkAux(out, sub_root->rchild);
	}
}

template <typename KeyType, typename ValueType>
inline void BSTree<KeyType, ValueType>::postorderTreeWalkAux(std::ostream &out, const BSTNode* const &sub_root) const
{
	if (sub_root != nullptr)
	{
		postorderTreeWalkAux(out, sub_root->lchild);
		postorderTreeWalkAux(out, sub_root->rchild);
		out << sub_root->key << " " << sub_root->value << "\n";
	}
}

template <typename KeyType, typename ValueType>
inline void BSTree<KeyType, ValueType>::release(BSTNode* p)
{
	if (p->lchild != nullptr)
		release(p->lchild);
	if (p->rchild != nullptr)
		release(p->rchild);
	delete p;
}

template <typename KeyType, typename ValueType>
inline void BSTree<KeyType, ValueType>::transplant(BSTNode *lhs_subtree, BSTNode *rhs_subtree)
{
	if (lhs_subtree->parent == nullptr)
		root = rhs_subtree;
	else if (lhs_subtree->parent->lchild == lhs_subtree)
		lhs_subtree->parent->lchild = rhs_subtree;
	else
		lhs_subtree->parent->rchild = rhs_subtree;
	if (rhs_subtree != nullptr)
		rhs_subtree->parent = lhs_subtree->parent;
}

#endif // !BSTREE_H

