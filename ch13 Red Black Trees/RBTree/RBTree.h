/***************************************************************************
*  @file       RBTree.h
*  @author     Alex.Xu
*  @mail       icevmj@gmail.com
*  @date       6.2 2017
*  @remark     Implementations for algorithims from CLRS using C++ templates.
*  @platform   visual studio 2013, windows 10
***************************************************************************/

#ifndef RBTREE_H
#define RBTREE_H

#include <iostream>

namespace ch13
{
	enum Color { RED, BLACK };

	//////////////////////////////////////////////////////////////////////////
	// Templates for Node and RBTree

	template <typename KeyType, typename ValueType>
	class Node {
	public:
		Node(): lchild(nullptr), rchild(nullptr), parent(nullptr) { }
		Node(KeyType key_): key(key_), lchild(nullptr), rchild(nullptr), parent(nullptr) { }
		Node(KeyType key_, ValueType value_): key(key_), value(value_), lchild(nullptr), rchild(nullptr), parent(nullptr) { }

		Node* lchild;
		Node* rchild;
		Node* parent;
		KeyType key;
		Color color;
		ValueType value;
	};  // Template Class Node

	template <typename KeyType, typename ValueType>
	class RBTree {
	public:
		using RBNode = Node<KeyType, ValueType>;
		RBTree()
		{ 
			nil = new RBNode();
			nil->lchild = nil->rchild = nil->parent = nullptr;
			nil->color = BLACK;
			root = nil;
		}
		~RBTree() 
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

		RBNode* search(const KeyType &key) const;
		RBNode* minimum() { return minimumAux(root); }
		RBNode* maximum() { return maximumAux(root); }
		RBNode* successor(const RBNode* pcurr_node);
		RBNode* predecessor(const RBNode* pcurr_node);

		void preorderTreeWalk(std::ostream &out) const { preorderTreeWalkAux(out, root); }
		void inorderTreeWalk(std::ostream &out) const { inorderTreeWalkAux(out, root); }
		void postorderTreeWalk(std::ostream &out) const { postorderTreeWalkAux(out, root); }
		void printTree(std::ostream &out) const { printTreeAux(out, root); }

		// todo...
		void insert(RBNode* z);
		void deleteNodeHasKey(const KeyType &key);


	private:
		void leftRotate(RBNode* x);
		void rightRotate(RBNode* x);

		bool findAux(RBNode* sub_root, const KeyType &key) const;  // µÝ¹é°æ±¾
		bool findAux_Iterative(RBNode* sub_root, const KeyType &key) const;  // µü´ú°æ±¾
		int treeHeightAux(const RBNode* pNode)
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
		int treeBlackHeightAux(RBNode* pNode)
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
		RBNode* minimumAux(RBNode* sub_root);
		RBNode* maximumAux(RBNode* sub_root);
		void preorderTreeWalkAux(std::ostream &out, const RBNode* const &sub_root) const;
		void inorderTreeWalkAux(std::ostream &out, const RBNode* const &sub_root) const;
		void postorderTreeWalkAux(std::ostream &out, const RBNode* const &sub_root) const;
		void printTreeAux(std::ostream &out, const RBNode* const &sub_root) const;

		// todo...
		void transplant(RBNode *u, RBNode *v);  // transplant v to u

		void insertFixUp(RBNode* z);
		void deleteFixUp(RBNode* z);

		void release(RBNode* p);

	private:
		RBNode* nil;  // Sentry
		RBNode* root;
	};  // Template Class RBTree

	//////////////////////////////////////////////////////////////////////////
	// function decleration for RBTree_test, see RBTree_test.cpp
	void RBTree_test();
	std::ostream & operator<< (std::ostream &os, const RBTree<int, std::string>::RBNode * pNode);

	//////////////////////////////////////////////////////////////////////////
	// Template class member methods
	template <typename KeyType, typename ValueType>
	inline typename RBTree<KeyType, ValueType>::RBNode* RBTree<KeyType, ValueType>::search(const KeyType &key) const
	{
		typename RBTree<KeyType, ValueType>::RBNode* ret = root;
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
	inline typename RBTree<KeyType, ValueType>::RBNode* RBTree<KeyType, ValueType>::successor(const RBNode* pcurr_node)
	{
		if (pcurr_node->rchild != nil)
			return minimumAux(pcurr_node->rchild);
		RBNode* p_node = pcurr_node->parent;
		while (p_node != nil && pcurr_node == p_node->rchild)
		{
			pcurr_node = p_node;
			p_node = p_node->parent;
		}
		return p_node;
	}

	template <typename KeyType, typename ValueType>
	inline typename RBTree<KeyType, ValueType>::RBNode* RBTree<KeyType, ValueType>::predecessor(const RBNode* pcurr_node)
	{
		if (pcurr_node->lchild != nil)
			return minimumAux(pcurr_node->lchild);
		RBNode* p_node = pcurr_node->parent;
		while (p_node != nil && pcurr_node == p_node->lchild)
		{
			pcurr_node = p_node;
			p_node = p_node->parent;
		}
		return p_node;
	}

	template <typename KeyType, typename ValueType>
	inline void RBTree<KeyType, ValueType>::insert(RBNode* z)
	{
		RBNode* y = nil;
		RBNode* x = root;
		while (x != nil)
		{
			y = x;
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
	inline void RBTree<KeyType, ValueType>::deleteNodeHasKey(const KeyType &key)
	{
		RBNode* z = search(key);
		if (z == nil)
			return;
		RBNode* y = z;
		Color y_original_color = y->color;
		RBNode* x = nullptr;
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
	inline void RBTree<KeyType, ValueType>::leftRotate(RBNode* x)
	{
		RBNode* y = x->rchild;  // set y
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
	inline void RBTree<KeyType, ValueType>::rightRotate(RBNode* x)
	{
		RBNode* y = x->lchild;
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
	}

	template <typename KeyType, typename ValueType>
	inline bool RBTree<KeyType, ValueType>::findAux(RBNode* sub_root, const KeyType &key) const
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
	inline typename RBTree<KeyType, ValueType>::RBNode* RBTree<KeyType, ValueType>::minimumAux(RBNode* sub_root)
	{
		if (sub_root == nil)
		{
			std::cerr << "RBTree is Empty! minimumAux() cannot work!" << std::endl;
			exit(EXIT_FAILURE);
		}
		RBNode* p = sub_root;
		while (p->lchild != nil)
			p = p->lchild;
		return p;
	}

	template <typename KeyType, typename ValueType>
	inline typename RBTree<KeyType, ValueType>::RBNode* RBTree<KeyType, ValueType>::maximumAux(RBNode* sub_root)
	{
		if (sub_root == nil)
		{
			std::cerr << "RBTree is Empty! maximumAux() cannot work!" << std::endl;
			exit(EXIT_FAILURE);
		}
		RBNode* p = sub_root;
		while (p->rchild != nil)
			p = p->rchild;
		return p;
	}

	template <typename KeyType, typename ValueType>
	inline bool RBTree<KeyType, ValueType>::findAux_Iterative(RBNode* sub_root, const KeyType &key) const
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
	inline void RBTree<KeyType, ValueType>::inorderTreeWalkAux(std::ostream &out, const RBNode* const &sub_root) const
	{
		if (sub_root != nil)
		{
			inorderTreeWalkAux(out, sub_root->lchild);
			out << sub_root->key << " " << sub_root->value << (sub_root->color == BLACK ? "  BLACK " : "  RED ") << std::endl;
			inorderTreeWalkAux(out, sub_root->rchild);
		}

	}

	template <typename KeyType, typename ValueType>
	inline void RBTree<KeyType, ValueType>::preorderTreeWalkAux(std::ostream &out, const RBNode* const &sub_root) const
	{
		if (sub_root != nil)
		{
			out << sub_root->key << " " << sub_root->value << "\n";
			preorderTreeWalkAux(out, sub_root->lchild);
			preorderTreeWalkAux(out, sub_root->rchild);
		}
	}

	template <typename KeyType, typename ValueType>
	inline void RBTree<KeyType, ValueType>::postorderTreeWalkAux(std::ostream &out, const RBNode* const &sub_root) const
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
	inline void RBTree<KeyType, ValueType>::printTreeAux(std::ostream &out, const RBNode* const &sub_root) const
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
	inline void RBTree<KeyType, ValueType>::release(RBNode* p)
	{
		if (p->lchild != nil)
			release(p->lchild);
		if (p->rchild != nil)
			release(p->rchild);
		if (p != nil)
			delete p;
	}

	template <typename KeyType, typename ValueType>
	inline void RBTree<KeyType, ValueType>::insertFixUp(RBNode* z)
	{
		while (z->parent->color == RED)
		{
			if (z->parent == z->parent->parent->lchild)
			{
				RBNode* y = z->parent->parent->rchild;
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
				RBNode* y = z->parent->parent->lchild;
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
	inline void RBTree<KeyType, ValueType>::deleteFixUp(RBNode* x)
	{
		while (x != root && x->color == BLACK)
		{
			if (x == x->parent->lchild)
			{
				RBNode* w = x->parent->rchild;
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
				RBNode* w = x->parent->lchild;
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
	inline void RBTree<KeyType, ValueType>::transplant(RBNode *u, RBNode *v)
	{
		if (u->parent == nil)
			root = v;
		else if (u == u->parent->lchild)
			u->parent->lchild = v;
		else
			u->parent->rchild = v;
		v->parent = u->parent;
	}

} // namespace ch13

#endif // !RBTREE_H
