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
	
	bool isEmpty() const { return root == nullptr; }
	void insert(const BSTNode &bst_node)
	{ 
		//insertAuxRecu(root, nullptr, bst_node); 
		insertAuxIter(root, bst_node);
	}
	bool find(const KeyType &key) const { return findAux_Iterative(root, key); }

	BSTNode* search(const KeyType &key) const;

	const BSTNode* minimum() const { return minimumAux(root); }
	const BSTNode* maximum() const { return maximumAux(root); }
	const BSTNode* successor(const BSTNode* pcurr_node) const;
	const BSTNode* predecessor(const BSTNode* pcurr_node) const;

	void inorderTreeWalk(std::ostream &out) const { inorderTreeWalkAux(out, root); }
	void preorderTreeWalk(std::ostream &out) const { preorderTreeWalkAux(out, root); }
	void postorderTreeWalk(std::ostream &out) const { postorderTreeWalkAux(out, root); }
	
	// TODO...
	void remove(const KeyType &key);

protected:
	void insertAuxRecu(BSTNode* &sub_root, BSTNode* sub_parent, const BSTNode &bst_node);  // 递归版本
	void insertAuxIter(BSTNode* &sub_root, const BSTNode &bst_node);  // 迭代版本
	bool findAux(const BSTNode* const &sub_root, const KeyType &key) const;  // 递归版本
	bool findAux_Iterative(const BSTNode* sub_root, const KeyType &key) const;  // 迭代版本
	const BSTNode* minimumAux(const BSTNode* sub_root) const;
	const BSTNode* maximumAux(const BSTNode* sub_root) const;
	void inorderTreeWalkAux(std::ostream &out, const BSTNode* const &sub_root) const;
	void preorderTreeWalkAux(std::ostream &out, const BSTNode *const &sub_root) const;
	void postorderTreeWalkAux(std::ostream &out, const BSTNode *const &sub_root) const;

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
inline void BSTree<KeyType, ValueType>::insertAuxRecu(BSTNode* &sub_root, BSTNode* sub_parent, const BSTNode &bst_node)
{
	if (sub_root == nullptr)
	{
		sub_root = new BSTree<KeyType, ValueType>::BSTNode(bst_node.key, bst_node.value);
		sub_root->parent = sub_parent;
	}
	else if (bst_node.key < sub_root->key)
	{
		insertAuxRecu(sub_root->lchild, sub_root, bst_node);
	}
	else if(bst_node.key > sub_root->key)
	{
		insertAuxRecu(sub_root->rchild, sub_root, bst_node);
	}
	else
	{
		std::cerr << "data " << bst_node.key << " already in the bstree" << std::endl;
		exit(EXIT_FAILURE);
	}
}

template <typename KeyType, typename ValueType>
inline void BSTree<KeyType, ValueType>::insertAuxIter(BSTNode* &sub_root, const BSTNode &bst_node)
{
	BSTNode* pparent_node = nullptr; // 记录要插入节点的父节点
	BSTNode* temp = sub_root;
	while (temp != nullptr)
	{
		pparent_node = temp;
		if (bst_node.key < temp->key)
		{
			temp = temp->lchild;
		}
		else if(bst_node.key > temp->key)
		{
			temp = temp->rchild;
		}
		else
		{
			std::cerr << "data " << bst_node.key << " already in the bstree" << std::endl;
			exit(EXIT_FAILURE);
		}
	}

	BSTNode* p_node = new BSTree<KeyType, ValueType>::BSTNode(bst_node.key, bst_node.value);
	p_node->parent = pparent_node;

	if (pparent_node == nullptr)
	{
		sub_root = p_node;
	}
	else if (p_node->key < pparent_node->key)
	{
		pparent_node->lchild = p_node;
	}
	else if (p_node->key > pparent_node->key)
	{
		pparent_node->rchild = p_node;
	}
}

template <typename KeyType, typename ValueType>
inline bool BSTree<KeyType, ValueType>::findAux(const BSTNode* const &sub_root, const KeyType &key) const
{
	if (sub_root == nullptr)
	{
		return false;
	}

	if (key == sub_root->key)
	{
		return true;
	}
	else if(key < sub_root->key)
	{
		return findAux(sub_root->lchild, key);
	}
	else
	{
		return findAux(sub_root->rchild, key);
	}
}

template <typename KeyType, typename ValueType>
inline const typename BSTree<KeyType, ValueType>::BSTNode* BSTree<KeyType, ValueType>::minimumAux(const BSTNode* sub_root) const
{
	if (sub_root == nullptr)
	{
		std::cerr << "BSTree is Empty! minimumAux() cannot work!" << std::endl;
		exit(EXIT_FAILURE);
	}
	const BSTNode* p = sub_root;
	while (p->lchild != nullptr)
	{
		p = p->lchild;
	}
	return p;
}

template <typename KeyType, typename ValueType>
inline const typename BSTree<KeyType, ValueType>::BSTNode* BSTree<KeyType, ValueType>::maximumAux(const BSTNode* sub_root) const
{
	if (sub_root == nullptr)
	{
		std::cerr << "BSTree is Empty! maximumAux() cannot work!" << std::endl;
		exit(EXIT_FAILURE);
	}
	const BSTNode* p = sub_root;
	while (p->rchild != nullptr)
	{
		p = p->rchild;
	}
	return p;
}

template <typename KeyType, typename ValueType>
inline const typename BSTree<KeyType, ValueType>::BSTNode* BSTree<KeyType, ValueType>::successor(const BSTNode* pcurr_node) const
{
	if (pcurr_node->rchild != nullptr)
	{
		return minimumAux(pcurr_node->rchild);
	}
	auto p_node = pcurr_node->parent;
	while (p_node != nullptr && pcurr_node == p_node->rchild)
	{
		pcurr_node = p_node;
		p_node = p_node->parent;
	}
	return p_node;
}

template <typename KeyType, typename ValueType>
inline const typename BSTree<KeyType, ValueType>::BSTNode* BSTree<KeyType, ValueType>::predecessor(const BSTNode* pcurr_node) const
{
	if (pcurr_node->lchild != nullptr)
	{
		return minimumAux(pcurr_node->lchild);
	}
	auto p_node = pcurr_node->parent;
	while (p_node != nullptr && pcurr_node == p_node->lchild)
	{
		pcurr_node = p_node;
		p_node = p_node->parent;
	}
	return p_node;
}

template <typename KeyType, typename ValueType>
inline bool BSTree<KeyType, ValueType>::findAux_Iterative(const BSTNode* sub_root, const KeyType &key) const
{
	while (sub_root != nullptr && key != sub_root->key)
	{
		if (key < sub_root->key)
		{
			sub_root = sub_root->lchild;
		}
		else
		{
			sub_root = sub_root->rchild;
		}
	}
	if (sub_root == nullptr)
	{
		return false;
	}
	else
	{
		return true;
	}
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

#endif // !BSTREE_H

