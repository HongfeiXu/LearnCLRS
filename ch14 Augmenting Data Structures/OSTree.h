/***************************************************************************
*  @file       OSTree.h
*  @author     Alex.Xu
*  @mail       icevmj@gmail.com
*  @date       7.5 2017
*  @remark     An order-statistic tree T is simply a red-black tree with additional information stored in each node.
*  @platform   visual studio 2013, windows 10
***************************************************************************/

#ifndef OSTREE_H
#define OSTREE_H

#include <iostream>

namespace ch14
{
	enum Color { RED, BLACK };

	//////////////////////////////////////////////////////////////////////////
	// Templates for Node and OSTree

	template <typename KeyType, typename ValueType>
	class Node {
	public:
		Node() : lchild(nullptr), rchild(nullptr), parent(nullptr), size(1) { }
		Node(KeyType key_) : key(key_), lchild(nullptr), rchild(nullptr), parent(nullptr), size(1) { }
		Node(KeyType key_, ValueType value_) : key(key_), value(value_), lchild(nullptr), rchild(nullptr), parent(nullptr), size(1) { }

		Node* lchild;
		Node* rchild;
		Node* parent;
		KeyType key;
		Color color;
		ValueType value;
		// for Ordered Statistic
		unsigned size;
	};  // Template Class Node

	template <typename KeyType, typename ValueType>
	class OSTree {
	public:
		using OSNode = Node<KeyType, ValueType>;
		OSTree()
		{
			nil = new OSNode();
			nil->lchild = nil->rchild = nil->parent = nullptr;
			nil->color = BLACK;
			// for Ordered Statistic
			nil->size = 0;
			root = nil;
		}
		~OSTree()
		{
			if (root != nil)
				release(root);
		}

		bool isEmpty() const { return root == nil; }
		bool find(const KeyType &key) const { return findAux_Iterative(root, key); }
		int treeHeight()
		{
			return treeHeightAux(root);
		}
		int treeBlackHeight()
		{
			return treeBlackHeightAux(root);
		}

		OSNode* search(const KeyType &key) const;
		OSNode* minimum() { return minimumAux(root); }
		OSNode* maximum() { return maximumAux(root); }
		OSNode* successor(const OSNode* pcurr_node);
		OSNode* predecessor(const OSNode* pcurr_node);

		void preorderTreeWalk(std::ostream &out) const { preorderTreeWalkAux(out, root); }
		void inorderTreeWalk(std::ostream &out) const { inorderTreeWalkAux(out, root); }
		void postorderTreeWalk(std::ostream &out) const { postorderTreeWalkAux(out, root); }
		void printTree(std::ostream &out) const { printTreeAux(out, root); }

		void insert(OSNode* z);
		void deleteNodeHasKey(const KeyType &key);

		// Retrieving an element with a given rank
		OSNode* osSelect(unsigned i) { return osSelectAux(root, i); }

		// Determining the rank of an element
		unsigned osRank(OSNode* x)
		{
			unsigned r = x->lchild->size + 1;
			OSNode* y = x;
			while (y != root)
			{
				if (y == y->parent->rchild)
					r += y->parent->lchild->size + 1;
				y = y->parent;
			}
			return r;
		}

	private:
		void leftRotate(OSNode* x);
		void rightRotate(OSNode* x);

		bool findAux(OSNode* sub_root, const KeyType &key) const;  // µÝ¹é°æ±¾
		bool findAux_Iterative(OSNode* sub_root, const KeyType &key) const;  // µü´ú°æ±¾
		int treeHeightAux(const OSNode* pNode)
		{
			int treeHeight = 0;
			if (pNode != nil)
			{
				int leftHeight = treeHeightAux(pNode->lchild);
				int rightHeight = treeHeightAux(pNode->rchild);
				treeHeight = leftHeight >= rightHeight ? leftHeight + 1 : rightHeight + 1;
			}
			return treeHeight;
		}
		int treeBlackHeightAux(OSNode* pNode)
		{
			int treeBlackHeight = 0;
			while (pNode != nil)
			{
				pNode = pNode->lchild;
				if (pNode->color == BLACK)
				{
					treeBlackHeight++;
				}
			}
			return treeBlackHeight;
		}
		OSNode* minimumAux(OSNode* sub_root);
		OSNode* maximumAux(OSNode* sub_root);
		void preorderTreeWalkAux(std::ostream &out, const OSNode* const &sub_root) const;
		void inorderTreeWalkAux(std::ostream &out, const OSNode* const &sub_root) const;
		void postorderTreeWalkAux(std::ostream &out, const OSNode* const &sub_root) const;
		void printTreeAux(std::ostream &out, const OSNode* const &sub_root) const;

		void transplant(OSNode *u, OSNode *v);  // transplant v to u

		void insertFixUp(OSNode* z);
		void deleteFixUp(OSNode* z);

		OSNode* osSelectAux(OSNode* x, unsigned i)
		{
			if (i > x->size)
				return nil;
			unsigned r = x->lchild->size + 1;
			if (i == r)
				return x;
			else if (i < r)
				return osSelectAux(x->lchild, i);
			else
				return osSelectAux(x->rchild, i - r);
		}

		void release(OSNode* p);

	private:
		OSNode* nil;  // Sentry
		OSNode* root;
	};  // Template Class OSTree

	//////////////////////////////////////////////////////////////////////////
	// function decleration for OSTree_test, see OSTree_test.cpp
	void OSTree_test();
	std::ostream & operator<< (std::ostream &os, const OSTree<int, std::string>::OSNode * pNode);

	//////////////////////////////////////////////////////////////////////////
	// Template class member methods
	template <typename KeyType, typename ValueType>
	inline typename OSTree<KeyType, ValueType>::OSNode* OSTree<KeyType, ValueType>::search(const KeyType &key) const
	{
		typename OSTree<KeyType, ValueType>::OSNode* ret = root;
		while (ret != nil && key != ret->key)
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
	inline typename OSTree<KeyType, ValueType>::OSNode* OSTree<KeyType, ValueType>::successor(const OSNode* pcurr_node)
	{
		if (pcurr_node->rchild != nil)
			return minimumAux(pcurr_node->rchild);
		OSNode* p_node = pcurr_node->parent;
		while (p_node != nil && pcurr_node == p_node->rchild)
		{
			pcurr_node = p_node;
			p_node = p_node->parent;
		}
		return p_node;
	}

	template <typename KeyType, typename ValueType>
	inline typename OSTree<KeyType, ValueType>::OSNode* OSTree<KeyType, ValueType>::predecessor(const OSNode* pcurr_node)
	{
		if (pcurr_node->lchild != nil)
			return minimumAux(pcurr_node->lchild);
		OSNode* p_node = pcurr_node->parent;
		while (p_node != nil && pcurr_node == p_node->lchild)
		{
			pcurr_node = p_node;
			p_node = p_node->parent;
		}
		return p_node;
	}

	template <typename KeyType, typename ValueType>
	inline void OSTree<KeyType, ValueType>::insert(OSNode* z)
	{
		OSNode* y = nil;
		OSNode* x = root;
		while (x != nil)
		{
			y = x;
			y->size += 1;

			if (z->key < x->key)
			{
				x = x->lchild;
			}
			else
			{
				x = x->rchild;
			}
		}
		z->parent = y;
		if (y == nil)
		{
			root = z;
		}
		else
		{
			if (z->key < y->key)
			{
				y->lchild = z;
			}
			else
			{
				y->rchild = z;
			}
		}
		z->lchild = nil;
		z->rchild = nil;
		z->color = RED;
		insertFixUp(z);
	}

	template <typename KeyType, typename ValueType>
	inline void OSTree<KeyType, ValueType>::deleteNodeHasKey(const KeyType &key)
	{
		OSNode* z = search(key);
		if (z == nil)
			return;
		OSNode* y = z;
		Color y_original_color = y->color;
		OSNode* x = nullptr;
		if (z->lchild == nil)
		{
			x = z->rchild;
			transplant(z, z->rchild);
		}
		else if (z->rchild == nil)
		{
			x = z->lchild;
			transplant(z, z->lchild);
		}
		else
		{
			y = minimumAux(z->rchild);

			// update size from y'parent to z's child
			OSNode *py = y;
			while (py->parent != z)
			{
				py = py->parent;
				py->size -= 1;
			}

			y_original_color = y->color;
			x = y->rchild;
			if (y->parent == z)
				x->parent = y;
			else
			{
				transplant(y, y->rchild);
				y->rchild = z->rchild;
				y->rchild->parent = y;

			}
			transplant(z, y);
			y->lchild = z->lchild;
			y->lchild->parent = y;
			y->color = z->color;

			// update size of y
			y->size = z->size - 1;
		}

		// update size from z's parent to root
		OSNode *pz = z;
		while (pz->parent != nil)
		{
			pz = pz->parent;
			pz->size -= 1;
		}

		if (y_original_color == BLACK)
			deleteFixUp(x);
	}

	/*-----------------------------------------------------------
	|    |              |
	|    x              y
	|   / \    ==>     / \
	|  a   y          x   c
	|     / \        / \
	|    b   c      a   b    //×óÐý
	-----------------------------------------------------------*/
	template <typename KeyType, typename ValueType>
	inline void OSTree<KeyType, ValueType>::leftRotate(OSNode* x)
	{
		OSNode* y = x->rchild;  // set y
		x->rchild = y->lchild;  // turn y¡¯s left subtree into x¡¯s right subtree
		if (y->lchild != nil)
		{
			y->lchild->parent = x;
		}
		y->parent = x->parent;  // link x's parent to y
		if (x->parent == nil)
		{
			root = y;
		}
		else if (x == x->parent->lchild)
		{
			x->parent->lchild = y;
		}
		else
		{
			x->parent->rchild = y;
		}
		y->lchild = x;  // put x on y's left
		x->parent = y;

		y->size = x->size;
		x->size = x->lchild->size + x->rchild->size + 1;
	}

	/*-----------------------------------------------------------
	|      |               |
	|      x               y
	|     / \             / \
	|    y   c   ==>     a   x
	|   / \                 / \
	|  a   b               b   c  //ÓÒÐý
	-----------------------------------------------------------*/
	template <typename KeyType, typename ValueType>
	inline void OSTree<KeyType, ValueType>::rightRotate(OSNode* x)
	{
		OSNode* y = x->lchild;
		x->lchild = y->rchild;
		if (y->rchild != nil)
		{
			y->rchild->parent = x;
		}
		y->parent = x->parent;
		if (x->parent == nil)
		{
			root = y;
		}
		else if (x == x->parent->lchild)
		{
			x->parent->lchild = y;
		}
		else
		{
			x->parent->rchild = y;
		}
		y->rchild = x;
		x->parent = y;

		y->size = x->size;
		x->size = x->lchild->size + x->rchild->size + 1;
	}

	template <typename KeyType, typename ValueType>
	inline bool OSTree<KeyType, ValueType>::findAux(OSNode* sub_root, const KeyType &key) const
	{
		if (sub_root == nil)
			return false;

		if (key == sub_root->key)
			return true;
		else if (key < sub_root->key)
			return findAux(sub_root->lchild, key);
		else
			return findAux(sub_root->rchild, key);
	}

	template <typename KeyType, typename ValueType>
	inline typename OSTree<KeyType, ValueType>::OSNode* OSTree<KeyType, ValueType>::minimumAux(OSNode* sub_root)
	{
		if (sub_root == nil)
		{
			std::cerr << "RBTree is Empty! minimumAux() cannot work!" << std::endl;
			exit(EXIT_FAILURE);
		}
		OSNode* p = sub_root;
		while (p->lchild != nil)
			p = p->lchild;
		return p;
	}

	template <typename KeyType, typename ValueType>
	inline typename OSTree<KeyType, ValueType>::OSNode* OSTree<KeyType, ValueType>::maximumAux(OSNode* sub_root)
	{
		if (sub_root == nil)
		{
			std::cerr << "RBTree is Empty! maximumAux() cannot work!" << std::endl;
			exit(EXIT_FAILURE);
		}
		OSNode* p = sub_root;
		while (p->rchild != nil)
			p = p->rchild;
		return p;
	}

	template <typename KeyType, typename ValueType>
	inline bool OSTree<KeyType, ValueType>::findAux_Iterative(OSNode* sub_root, const KeyType &key) const
	{
		while (sub_root != nil && key != sub_root->key)
		{
			if (key < sub_root->key)
				sub_root = sub_root->lchild;
			else
				sub_root = sub_root->rchild;
		}
		if (sub_root == nil)
			return false;
		else
			return true;
	}

	template <typename KeyType, typename ValueType>
	inline void OSTree<KeyType, ValueType>::inorderTreeWalkAux(std::ostream &out, const OSNode* const &sub_root) const
	{
		if (sub_root != nil)
		{
			inorderTreeWalkAux(out, sub_root->lchild);
			out << "key: " << sub_root->key << " value:" << sub_root->value << " size:" << sub_root->size << (sub_root->color == BLACK ? "  BLACK " : "  RED ") << std::endl;
			inorderTreeWalkAux(out, sub_root->rchild);
		}

	}

	template <typename KeyType, typename ValueType>
	inline void OSTree<KeyType, ValueType>::preorderTreeWalkAux(std::ostream &out, const OSNode* const &sub_root) const
	{
		if (sub_root != nil)
		{
			out << sub_root->key << " " << sub_root->value << "\n";
			preorderTreeWalkAux(out, sub_root->lchild);
			preorderTreeWalkAux(out, sub_root->rchild);
		}
	}

	template <typename KeyType, typename ValueType>
	inline void OSTree<KeyType, ValueType>::postorderTreeWalkAux(std::ostream &out, const OSNode* const &sub_root) const
	{
		if (sub_root != nil)
		{
			postorderTreeWalkAux(out, sub_root->lchild);
			postorderTreeWalkAux(out, sub_root->rchild);
			out << sub_root->key << " " << sub_root->value << "\n";
		}
	}

	/*-----------------------------------------------------------
	|      x
	|     / \
	|    y   c
	|     \
	|      b
	|
	|  output: x(y(,b),c)
	-----------------------------------------------------------*/
	template <typename KeyType, typename ValueType>
	inline void OSTree<KeyType, ValueType>::printTreeAux(std::ostream &out, const OSNode* const &sub_root) const
	{
		if (sub_root != nil)
		{

			out << sub_root->key;

			if (sub_root->lchild != nil || sub_root->rchild != nil)
				out << "(";

			printTreeAux(out, sub_root->lchild);

			if (sub_root->lchild != nil || sub_root->rchild != nil)
				out << ",";

			printTreeAux(out, sub_root->rchild);

			if (sub_root->lchild != nil || sub_root->rchild != nil)
				out << ")";
		}
	}

	template <typename KeyType, typename ValueType>
	inline void OSTree<KeyType, ValueType>::release(OSNode* p)
	{
		if (p->lchild != nil)
			release(p->lchild);
		if (p->rchild != nil)
			release(p->rchild);
		if (p != nil)
			delete p;
	}

	template <typename KeyType, typename ValueType>
	inline void OSTree<KeyType, ValueType>::insertFixUp(OSNode* z)
	{
		while (z->parent->color == RED)
		{
			if (z->parent == z->parent->parent->lchild)
			{
				OSNode* y = z->parent->parent->rchild;
				if (y->color == RED)
				{
					z->parent->color = BLACK;
					y->color = BLACK;
					z->parent->parent->color = RED;
					z = z->parent->parent;
				}
				else
				{
					if (z == z->parent->rchild)
					{
						z = z->parent;
						leftRotate(z);
					}
					z->parent->color = BLACK;
					z->parent->parent->color = RED;
					rightRotate(z->parent->parent);
				}
			}
			else
			{
				OSNode* y = z->parent->parent->lchild;
				if (y->color == RED)
				{
					z->parent->color = BLACK;
					y->color = BLACK;
					z->parent->parent->color = RED;
					z = z->parent->parent;
				}
				else
				{
					if (z == z->parent->lchild)
					{
						z = z->parent;
						rightRotate(z);
					}
					z->parent->color = BLACK;
					z->parent->parent->color = RED;
					leftRotate(z->parent->parent);
				}
			}
		}
		root->color = BLACK;
	}

	template <typename KeyType, typename ValueType>
	inline void OSTree<KeyType, ValueType>::deleteFixUp(OSNode* x)
	{
		while (x != root && x->color == BLACK)
		{
			if (x == x->parent->lchild)
			{
				OSNode* w = x->parent->rchild;
				if (w->color == RED)  // case 1
				{
					w->color = BLACK;
					x->parent->color = RED;
					leftRotate(x->parent);
					w = x->parent->rchild;
				}
				if (w->lchild->color == BLACK && w->rchild->color == BLACK)  // case 2
				{
					w->color = RED;
					x = x->parent;
				}
				else
				{
					if (w->rchild->color == BLACK)
					{
						w->lchild->color = BLACK;
						w->color = RED;
						rightRotate(w);
						w = x->parent->rchild;
					}
					w->color = x->parent->color;
					x->parent->color = BLACK;
					w->rchild->color = BLACK;
					leftRotate(x->parent);
					x = root;
				}
			}
			else
			{
				OSNode* w = x->parent->lchild;
				if (w->color == RED)  // case 1
				{
					w->color = BLACK;
					x->parent->color = RED;
					rightRotate(x->parent);
					w = x->parent->lchild;
				}
				if (w->rchild->color == BLACK && w->lchild->color == BLACK)  // case 2
				{
					w->color = RED;
					x = x->parent;
				}
				else
				{
					if (w->lchild->color == BLACK)
					{
						w->rchild->color = BLACK;
						w->color = RED;
						leftRotate(w);
						w = x->parent->lchild;
					}
					w->color = x->parent->color;
					x->parent->color = BLACK;
					w->lchild->color = BLACK;
					rightRotate(x->parent);
					x = root;
				}
			}
		}
		x->color = BLACK;
	}

	template <typename KeyType, typename ValueType>
	inline void OSTree<KeyType, ValueType>::transplant(OSNode *u, OSNode *v)
	{
		if (u->parent == nil)
			root = v;
		else if (u == u->parent->lchild)
			u->parent->lchild = v;
		else
			u->parent->rchild = v;
		v->parent = u->parent;
	}

} // namespace ch14

#endif // !OSTREE_H
