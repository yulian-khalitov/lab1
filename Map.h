#pragma once
#include <string>
#include <vector>
#include <iostream>

template<class T_key, class T_val>
class Map {
	enum color { RED, BLACK };
	struct Node {
		T_key key;
		T_val value;
		color col;
		Node* p;
		Node* left;
		Node* right;
		Node(color col) : col{ col } {}
		Node(T_key key, T_val value, color col = RED) : key{ key }, value{ value },
			p{ nil }, left{ nil }, right{ nil }, col{ col } {}
	};
	Node* root;
	inline static size_t size = 0;
	inline static Node* nil = new Node(BLACK);
	void left_rotate(Node* z);
	void right_rotate(Node* x);
	void insert_fixup(Node* z);
	auto minimum(Node* x);
	void transplant(Node* x, Node* y);
	void remove_fixup(Node* x);
	void clear_subtree(Node* x);
	void get_keys_subtree(Node* x, std::vector<T_key>& v);
	void get_values_subtree(Node* x, std::vector<T_val>& v);
	void print_subtree(Node* x);
public:
	Map() : root{ nil } {}
	void insert(T_key key, T_val val);
	void remove(T_key key);
	T_val find(T_key key, T_val nil_val);
	void clear();
	std::vector<T_key> get_keys();
	std::vector<T_val> get_values();
	void print();
};

template <class T_key, class T_val>
void Map<T_key, T_val>::left_rotate(Node* x)
{
	Node* y = x->right;
	x->right = y->left;
	if (y->left != nil) y->left->p = x;
	y->p = x->p;
	if (x->p == nil) root = y;
	else if (x == x->p->left) x->p->left = y;
	else x->p->right = y;
	y->left = x;
	x->p = y;
}

template <class T_key, class T_val>
void Map<T_key, T_val>::right_rotate(Node * x)
{
	Node* y = x->left;
	x->left = y->right;
	if (y->right != nil) y->right->p = x;
	y->p = x->p;
	if (x->p == nil) root = y;
	else if (x == x->p->left) x->p->left = y;
	else x->p->right = y;
	y->right = x;
	x->p = y;
}

template <class T_key, class T_val>
void Map<T_key, T_val>::insert_fixup(Node * z)
{
	Node* y;
	while (z->p->col == RED)
	{
		if (z->p == z->p->p->left)
		{
			y = z->p->p->right;
			if (y->col == RED)
			{
				z->p->col = BLACK;
				y->col = BLACK;
				z->p->p->col = RED;
				z = z->p->p;
			}
			else {
				if (z == z->p->right) {
					z = z->p;
					left_rotate(z);
				}
				z->p->col = BLACK;
				z->p->p->col = RED;
				right_rotate(z->p->p);
			}
		}
		else
		{
			y = z->p->p->left;
			if (y->col == RED)
			{
				z->p->col = BLACK;
				y->col = BLACK;
				z->p->p->col = RED;
				z = z->p->p;
			}
			else
			{
				if (z == z->p->left) {
					z = z->p;
					right_rotate(z);
				}
				z->p->col = BLACK;
				z->p->p->col = RED;
				left_rotate(z->p->p);
			}
		}
	}
	root->col = BLACK;
}

template <class T_key, class T_val>
void Map<T_key, T_val>::insert(T_key key, T_val val)
{
	Node* y = nil;
	Node* x = root;
	while (x != nil && x->key != key)
	{
		y = x;
		if (key < x->key) x = x->left;
		else x = x->right;
	}
	if (x == nil)
	{
		Node* z = new Node(key, val);
		z->p = y;
		if (y == nil) root = z;
		else if (z->key < y->key) y->left = z;
		else y->right = z;
		insert_fixup(z);
		++size;
	}
	else x->value = val;
}

template <class T_key, class T_val>
auto Map<T_key, T_val>::minimum(Node* x)
{
	while (x->left != nil) x = x->left;
	return x;
}

template <class T_key, class T_val>
void Map<T_key, T_val>::transplant(Node* x, Node* y)
{
	if (x->p == nil) root = y;
	else if (x == x->p->left) x->p->left = y;
	else x->p->right = y;
	y->p = x->p;
}

template <class T_key, class T_val>
void Map<T_key, T_val>::remove_fixup(Node* x)
{
	while (x != root && x->col == BLACK)
	{
		if (x == x->p->left)
		{
			Node* y = x->p->right;
			if (y->col == RED)
			{
				y->col = BLACK;
				x->p->col = RED;
				left_rotate(x->p);
				y = x->p->right;
			}
			if (y->left->col == BLACK && y->right->col == BLACK)
			{
				y->col = RED;
				x = x->p;
			}
			else
			{
				if (y->right->col == BLACK)
				{
					y->left->col = BLACK;
					y->col = RED;
					right_rotate(y);
					y = x->p->right;
				}
				y->col = x->p->col;
				x->p->col = BLACK;
				y->right->col = BLACK;
				left_rotate(x->p);
				x = root;
			}
		}
		else
		{
			Node* y = x->p->left;
			if (y->col == RED)
			{
				y->col = BLACK;
				x->p->col = RED;
				right_rotate(x->p);
				y = x->p->left;
			}
			if (y->right->col == BLACK && y->left->col == BLACK)
			{
				y->col = RED;
				x = x->p;
			}
			else
			{
				if (y->left->col == BLACK)
				{
					y->right->col = BLACK;
					y->col = RED;
					left_rotate(y);
					y = x->p->left;
				}
				y->col = x->p->col;
				x->p->col = BLACK;
				y->left->col = BLACK;
				right_rotate(x->p);
				x = root;
			}
		}
	}
	x->col = BLACK;
}

template <class T_key, class T_val>
void Map<T_key, T_val>::remove(T_key key)
{
	Node* z = root;
	while (z != nil && z->key != key)
	{
		if (key < z->key) z = z->left;
		else z = z->right;
	}
	if (z == nil) throw std::out_of_range{ "remove element out of range" };
	Node * y = z;
	Node * x;
	color y_orig_color = y->col;
	if (z->left == nil)
	{
		x = z->right;
		transplant(z, z->right);
	}
	else if (z->right == nil)
	{
		x = z->left;
		transplant(z, z->left);
	}
	else
	{
		y = minimum(z->right);
		y_orig_color = y->col;
		x = y->right;
		if (y->p == z)
		{
			x->p = y;
		}
		else
		{
			transplant(y, y->right);
			y->right = z->right;
			y->right->p = y;
		}
		transplant(z, y);
		y->left = z->left;
		y->left->p = y;
		y->col = z->col;
	}
	if (y_orig_color == BLACK) remove_fixup(x);
}

template <class T_key, class T_val>
T_val Map<T_key, T_val>::find(T_key key, T_val nil_value)
{
	Node* x = root;
	while (x != nil)
	{
		if (key == x->key) return x->value;
		else if (key < x->key) x = x->left;
		else x = x->right;
	}
	return nil_value;
}

template <class T_key, class T_val>
void Map<T_key, T_val>::clear_subtree(Node* x)
{
	if (x != nil)
	{
		clear_subtree(x->left);
		clear_subtree(x->right);
		delete x;
	}
}

template <class T_key, class T_val>
void Map<T_key, T_val>::clear()
{
	clear_subtree(root);
	root = nil;
}

template <class T_key, class T_val>
void Map<T_key, T_val>::get_keys_subtree(Node* x, std::vector<T_key>& v)
{
	if (x != nil)
	{
		get_keys_subtree(x->left, v);
		v.push_back(x->key);
		get_keys_subtree(x->right, v);
	}
}

template <class T_key, class T_val>
std::vector<T_key> Map<T_key, T_val>::get_keys()
{
	std::vector<T_key> v;
	get_keys_subtree(root, v);
	return v;
}

template <class T_key, class T_val>
void Map<T_key, T_val>::get_values_subtree(Node* x, std::vector<T_val>& v)
{
	if (x != nil)
	{
		get_values_subtree(x->left, v);
		v.push_back(x->value);
		get_values_subtree(x->right, v);
	}
}

template <class T_key, class T_val>
std::vector<T_val> Map<T_key, T_val>::get_values()
{
	std::vector<T_val> v;
	get_values_subtree(root, v);
	return v;
}

template <class T_key, class T_val>
void Map<T_key, T_val>::print_subtree(Node * x)
{
	if (x != nil)
	{
		print_subtree(x->left);
		std::cout << "(key: " << x->key << ", value: " << x->value << ")" << std::endl;
		print_subtree(x->right);
	}
}

template <class T_key, class T_val>
void Map<T_key, T_val>::print()
{
	print_subtree(root);
}