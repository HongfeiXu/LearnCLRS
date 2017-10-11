/***************************************************************************
*  @file       IntervalTree.h
*  @author     Alex.Xu
*  @mail       icevmj@gmail.com
*  @date       7.6 2017
*  @remark     augment red-black trees to support operations on dynamic sets of intervals
*  @platform   visual studio 2013, windows 10
***************************************************************************/

#ifndef INTERVALTREE_H
#define INTERVALTREE_H

#include <iostream>
#include <utility>

namespace ch14_2
{
	enum Color { RED, BLACK };

	template<typename KeyType>
	bool isOverlap(std::pair<KeyType, KeyType> intv1, std::pair<KeyType, KeyType> intv2)
	{
		if (intv1.first <= intv2.second && intv2.first <= intv1.second)
			return true;
		else
			return false;
	}

	template<typename KeyType>
	KeyType maxOfThree(KeyType v1, KeyType v2, KeyType v3)
	{
		if (v1 >= v2)
		{
			if (v1 >= v3)
				return v1;
			else
				return v3;
		}
		else
		{
			if (v2 >= v3)
				return v2;
			else
				return v3;
		}
	}

	//////////////////////////////////////////////////////////////////////////
	// Templates for Node and OSTree

	template <typename KeyType, typename ValueType>
	class Node {
	public:
		typedef std::pair<KeyType, KeyType> IntervalType;

		Node() : lchild(nullptr), rchild(nullptr), parent(nullptr), size(1), max(0) { }
		Node(IntervalType interval_) : interval(interval_), key(interval_.first), lchild(nullptr), rchild(nullptr), parent(nullptr), size(1), max(0) { }
		Node(IntervalType interval_, ValueType value_) :interval(interval_), key(interval_.first), value(value_), lchild(nullptr), rchild(nullptr), parent(nullptr), size(1), max(0) { }

		Node* lchild;
		Node* rchild;
		Node* parent;
		KeyType key;

		// interval trees
		IntervalType interval;
		KeyType max;
		
		Color color;
		ValueType value;

		// order statistics
		unsigned size;
	};  // Template Class Node

	template <typename KeyType, typename ValueType>
	class IntervalTree {
	public:
		using IntervalNode = Node<KeyType, ValueType>;
		IntervalTree()
		{
			nil = new IntervalNode();
			nil->lchild = nil->rchild = nil->parent = nullptr;
			nil->color = BLACK;
			// interval trees
			nil->max = 0;  // 假设区间最小左边界为0
			nil->interval = std::make_pair(0, 0);
			// order statistics
			nil->size = 0;
			root = nil;
		}
		~IntervalTree()
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

		IntervalNode* search(const KeyType &key) const;
		IntervalNode* minimum() { return minimumAux(root); }
		IntervalNode* maximum() { return maximumAux(root); }
		IntervalNode* successor(const IntervalNode* pcurr_node);
		IntervalNode* predecessor(const IntervalNode* pcurr_node);

		void preorderTreeWalk(std::ostream &out) const { preorderTreeWalkAux(out, root); }
		void inorderTreeWalk(std::ostream &out) const { inorderTreeWalkAux(out, root); }
		void postorderTreeWalk(std::ostream &out) const { postorderTreeWalkAux(out, root); }
		void printTree(std::ostream &out) const { printTreeAux(out, root); }

		void insert(IntervalNode* z);
		void deleteNodeHasKey(const KeyType &key);
		void deleteNode(IntervalNode* z);

		// Retrieving an element with a given rank
		IntervalNode* osSelect(unsigned i) { return osSelectAux(root, i); }

		// Determining the rank of an element
		unsigned osRank(IntervalNode* x)
		{
			unsigned r = x->lchild->size + 1;
			IntervalNode* y = x;
			while (y != root)
			{
				if (y == y->parent->rchild)
					r += y->parent->lchild->size + 1;
				y = y->parent;
			}
			return r;
		}

		// Interval Search
		IntervalNode* intervalSearch(std::pair<KeyType, KeyType> intv)
		{
			IntervalNode * x = root;
			while (x != nil && !isOverlap(x->interval, intv))
			{
				if (x->lchild != nil && x->lchild->max >= intv.first)
					x = x->lchild;
				else
					x = x->rchild;
			}
			return x;
		}

	private:
		void leftRotate(IntervalNode* x);
		void rightRotate(IntervalNode* x);

		bool findAux(IntervalNode* sub_root, const KeyType &key) const;  // 递归版本
		bool findAux_Iterative(IntervalNode* sub_root, const KeyType &key) const;  // 迭代版本
		int treeHeightAux(const IntervalNode* pNode)
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
		int treeBlackHeightAux(IntervalNode* pNode)
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
		IntervalNode* minimumAux(IntervalNode* sub_root);
		IntervalNode* maximumAux(IntervalNode* sub_root);
		void preorderTreeWalkAux(std::ostream &out, const IntervalNode* const &sub_root) const;
		void inorderTreeWalkAux(std::ostream &out, const IntervalNode* const &sub_root) const;
		void postorderTreeWalkAux(std::ostream &out, const IntervalNode* const &sub_root) const;
		void printTreeAux(std::ostream &out, const IntervalNode* const &sub_root) const;

		void transplant(IntervalNode *u, IntervalNode *v);  // transplant v to u

		void insertFixUp(IntervalNode* z);
		void deleteFixUp(IntervalNode* z);

		IntervalNode* osSelectAux(IntervalNode* x, unsigned i)
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

		void release(IntervalNode* p);

	private:
		IntervalNode* nil;  // Sentry
		IntervalNode* root;
	};  // Template Class OSTree

	//////////////////////////////////////////////////////////////////////////
	// function decleration for OSTree_test, see OSTree_test.cpp
	void IntervalTree_test();
	std::ostream & operator<< (std::ostream &os, const IntervalTree<int, std::string>::IntervalNode * pNode);

	//////////////////////////////////////////////////////////////////////////
	// Template class member methods
	template <typename KeyType, typename ValueType>
	inline typename IntervalTree<KeyType, ValueType>::IntervalNode* IntervalTree<KeyType, ValueType>::search(const KeyType &key) const
	{
		typename IntervalTree<KeyType, ValueType>::IntervalNode* ret = root;
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
	inline typename IntervalTree<KeyType, ValueType>::IntervalNode* IntervalTree<KeyType, ValueType>::successor(const IntervalNode* pcurr_node)
	{
		if (pcurr_node->rchild != nil)
			return minimumAux(pcurr_node->rchild);
		IntervalNode* p_node = pcurr_node->parent;
		while (p_node != nil && pcurr_node == p_node->rchild)
		{
			pcurr_node = p_node;
			p_node = p_node->parent;
		}
		return p_node;
	}

	template <typename KeyType, typename ValueType>
	inline typename IntervalTree<KeyType, ValueType>::IntervalNode* IntervalTree<KeyType, ValueType>::predecessor(const IntervalNode* pcurr_node)
	{
		if (pcurr_node->lchild != nil)
			return minimumAux(pcurr_node->lchild);
		IntervalNode* p_node = pcurr_node->parent;
		while (p_node != nil && pcurr_node == p_node->lchild)
		{
			pcurr_node = p_node;
			p_node = p_node->parent;
		}
		return p_node;
	}

	template <typename KeyType, typename ValueType>
	inline void IntervalTree<KeyType, ValueType>::insert(IntervalNode* z)
	{
		IntervalNode* y = nil;
		IntervalNode* x = root;
		while (x != nil)
		{
			y = x;

			// update size
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

		// update max
		z->max = maxOfThree(z->lchild->max, z->rchild->max, z->interval.second);
		IntervalNode * pz = z;
		while (pz->parent != nil)
		{
			pz = pz->parent;
			pz->max = maxOfThree(pz->lchild->max, pz->rchild->max, pz->interval.second);
		}


		z->color = RED;
		insertFixUp(z);
	}

	template <typename KeyType, typename ValueType>
	inline void IntervalTree<KeyType, ValueType>::deleteNodeHasKey(const KeyType &key)
	{
		IntervalNode* z = search(key);
		deleteNode(z);
	}

	template <typename KeyType, typename ValueType>
	inline void IntervalTree<KeyType, ValueType>::deleteNode(IntervalNode* z)
	{
		if (z == nil)
			return;
		IntervalNode* y = z;
		Color y_original_color = y->color;
		IntervalNode* x = nullptr;
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
			IntervalNode *py = y;
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

				// update max from y's parent to z's child
				IntervalNode *py_2 = y;
				while (py_2->parent != z)
				{
					py_2 = py_2->parent;
					py_2->max = maxOfThree(py_2->lchild->max, py_2->rchild->max, py_2->interval.second);
				}

				y->rchild = z->rchild;
				y->rchild->parent = y;

			}
			transplant(z, y);
			y->lchild = z->lchild;
			y->lchild->parent = y;
			y->color = z->color;

			// update size of y
			y->size = z->size - 1;

			// update max of y
			y->max = maxOfThree(y->lchild->max, y->rchild->max, y->interval.second);
		}

		// update size from z's parent to root
		IntervalNode *pz = z;
		while (pz->parent != nil)
		{
			pz = pz->parent;
			pz->size -= 1;
		}
		// update max from z's parent to root
		IntervalNode *pz_2 = z;
		while (pz_2->parent != nil)
		{
			pz_2 = pz_2->parent;
			pz_2->max = maxOfThree(pz_2->lchild->max, pz_2->rchild->max, pz_2->interval.second);
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
	|    b   c      a   b    //左旋
	-----------------------------------------------------------*/
	template <typename KeyType, typename ValueType>
	inline void IntervalTree<KeyType, ValueType>::leftRotate(IntervalNode* x)
	{
		IntervalNode* y = x->rchild;  // set y
		x->rchild = y->lchild;  // turn y’s left subtree into x’s right subtree
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

		// update size
		y->size = x->size;
		x->size = x->lchild->size + x->rchild->size + 1;

		// update max
		y->max = x->max;
		x->max = maxOfThree(x->lchild->max, x->rchild->max, x->interval.second);
	}

	/*-----------------------------------------------------------
	|      |               |
	|      x               y
	|     / \             / \
	|    y   c   ==>     a   x
	|   / \                 / \
	|  a   b               b   c  //右旋
	-----------------------------------------------------------*/
	template <typename KeyType, typename ValueType>
	inline void IntervalTree<KeyType, ValueType>::rightRotate(IntervalNode* x)
	{
		IntervalNode* y = x->lchild;
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

		// update size
		y->size = x->size;
		x->size = x->lchild->size + x->rchild->size + 1;

		// update max
		y->max = x->max;
		x->max = maxOfThree(x->lchild->max, x->rchild->max, x->interval.second);
	}

	template <typename KeyType, typename ValueType>
	inline bool IntervalTree<KeyType, ValueType>::findAux(IntervalNode* sub_root, const KeyType &key) const
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
	inline typename IntervalTree<KeyType, ValueType>::IntervalNode* IntervalTree<KeyType, ValueType>::minimumAux(IntervalNode* sub_root)
	{
		if (sub_root == nil)
		{
			std::cerr << "RBTree is Empty! minimumAux() cannot work!" << std::endl;
			exit(EXIT_FAILURE);
		}
		IntervalNode* p = sub_root;
		while (p->lchild != nil)
			p = p->lchild;
		return p;
	}

	template <typename KeyType, typename ValueType>
	inline typename IntervalTree<KeyType, ValueType>::IntervalNode* IntervalTree<KeyType, ValueType>::maximumAux(IntervalNode* sub_root)
	{
		if (sub_root == nil)
		{
			std::cerr << "RBTree is Empty! maximumAux() cannot work!" << std::endl;
			exit(EXIT_FAILURE);
		}
		IntervalNode* p = sub_root;
		while (p->rchild != nil)
			p = p->rchild;
		return p;
	}

	template <typename KeyType, typename ValueType>
	inline bool IntervalTree<KeyType, ValueType>::findAux_Iterative(IntervalNode* sub_root, const KeyType &key) const
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
	inline void IntervalTree<KeyType, ValueType>::inorderTreeWalkAux(std::ostream &out, const IntervalNode* const &sub_root) const
	{
		if (sub_root != nil)
		{
			inorderTreeWalkAux(out, sub_root->lchild);
			out << "key: "<< sub_root->key << " interval: (" << sub_root->interval.first << "," << sub_root->interval.second << ")" << " value:" << sub_root->value << " max:" << sub_root->max << (sub_root->color == BLACK ? "  BLACK " : "  RED ") << std::endl;
			inorderTreeWalkAux(out, sub_root->rchild);
		}

	}

	template <typename KeyType, typename ValueType>
	inline void IntervalTree<KeyType, ValueType>::preorderTreeWalkAux(std::ostream &out, const IntervalNode* const &sub_root) const
	{
		if (sub_root != nil)
		{
			out << sub_root->key << " " << sub_root->value << "\n";
			preorderTreeWalkAux(out, sub_root->lchild);
			preorderTreeWalkAux(out, sub_root->rchild);
		}
	}

	template <typename KeyType, typename ValueType>
	inline void IntervalTree<KeyType, ValueType>::postorderTreeWalkAux(std::ostream &out, const IntervalNode* const &sub_root) const
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
	inline void IntervalTree<KeyType, ValueType>::printTreeAux(std::ostream &out, const IntervalNode* const &sub_root) const
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
	inline void IntervalTree<KeyType, ValueType>::release(IntervalNode* p)
	{
		if (p->lchild != nil)
			release(p->lchild);
		if (p->rchild != nil)
			release(p->rchild);
		if (p != nil)
			delete p;
	}

	template <typename KeyType, typename ValueType>
	inline void IntervalTree<KeyType, ValueType>::insertFixUp(IntervalNode* z)
	{
		while (z->parent->color == RED)
		{
			if (z->parent == z->parent->parent->lchild)
			{
				IntervalNode* y = z->parent->parent->rchild;
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
				IntervalNode* y = z->parent->parent->lchild;
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
	inline void IntervalTree<KeyType, ValueType>::deleteFixUp(IntervalNode* x)
	{
		while (x != root && x->color == BLACK)
		{
			if (x == x->parent->lchild)
			{
				IntervalNode* w = x->parent->rchild;
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
				IntervalNode* w = x->parent->lchild;
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
	inline void IntervalTree<KeyType, ValueType>::transplant(IntervalNode *u, IntervalNode *v)
	{
		if (u->parent == nil)
			root = v;
		else if (u == u->parent->lchild)
			u->parent->lchild = v;
		else
			u->parent->rchild = v;
		v->parent = u->parent;
	}

} // namespace ch14_2

#endif // !INTERVALTREE
