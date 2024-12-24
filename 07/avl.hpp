#pragma once
#include <iostream>
#include <memory>
#include "iterator.hpp"

template<class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<std::pair<Key, T>>>
class Avl{
	struct Node{
		std::pair<Key, T> val;
		Node* left;
		Node* right;
		Node* parent;
		int h;
		Node(const std::pair<Key, T>& val)
			: val(val), left(nullptr), right(nullptr), parent(nullptr),  h(0){};
	};

	Node* root = nullptr;
	using NodeAllocator = typename std::allocator_traits<Allocator>::template rebind_alloc<Node>;
	using NodeAllocTraits = std::allocator_traits<NodeAllocator>;
	Compare compare;
	NodeAllocator alloc;
	size_t countNode = 0;
	using iterator = Iterator<Node, Key, T>;

	// Node* findBegin() const;
	// Node* findRBegin() const;
	// Node* find(Node* node, const Key& key) const;
	// void leftRotate(Node* a);
	// void rightRotate(Node* a);
	// int balance(Node* node);
	// std::pair<Node*, bool> insert(Node* node, const std::pair<Key, T>& keyValue);
	// std::pair<Node*, bool> removeMin(Node* node, const Key& key);
	// bool erase(Node* node, const Key& key);
	// void destroy(Node* node);
	// void print(Node* node, size_t h);

	Node* findBegin() const{
		Node* node = root;
		while(node->left != nullptr){
			node = node->left;
		}
		return node;
	}

	Node* findRBegin() const{
		Node* node = root;
		while(node->right != nullptr){
			node = node->right;
		}
		return node;
	}

	Node* find(Node* node, const Key& key) const{
		if(compare(key, node->val.first)){
			if(node->left == nullptr){
				return nullptr;
			}
			return find(node->left, key);
		}
		else if(compare(node->val.first, key)) {
			if(node->right == nullptr){
				return nullptr;
			}
			return find(node->right, key);
		} else {
			return node;
		}
	}

	void leftRotate(Node* a){
		Node* b = a->right;
		a->right = b->left;
		if(b->left != nullptr){
			b->left->parent = a;
		}
		b->left = a;
		b->parent = a->parent;
		if(a->parent != nullptr){
			if(a->parent->left == a){
				a->parent->left = b;
			} else {
				a->parent->right = b;
			}
		}
		a->parent = b;
		if(a == root){
			root = b;
		}
	}

	void rightRotate(Node* a){
		Node* b = a->left;
		a->left = b->right;
		if(b->right != nullptr){
			b->right->parent = a;
		}
		b->right = a;
		b->parent = a->parent;
		if(a->parent != nullptr){
			if(a->parent->left == a){
				a->parent->left = b;
			} else {
				a->parent->right = b;
			}
		}
		a->parent = b;
		if(a == root){
			root = b;
		}
	}

	int balance(Node* node){
		Node* a = node;
		if(node->h == -2){
			Node* b = node->right;
			if(b->h != 1){
				leftRotate(a);
				if(b->h == -1){
					a->h = 0;
					b->h = 0;
				} else {
					a->h = -1;
					b->h = 1;
				}
				node = b;
			} else {
				Node* c = b->left;
				rightRotate(b);
				leftRotate(a);
				if(c->h == 1){
					a->h = 0;
					b->h = -1;
				}
				else if (c->h == -1){
					a->h = 1;
					b->h = 0;
				}
				else {
					a->h = 0;
					b->h = 0;
				}
				c->h = 0;
				node = c;
			}
		}
		else {
			Node* b = node->left;
			if(b->h != -1){
				rightRotate(a);
				if(b->h == 1){
					a->h = 0;
					b->h = 0;
				} else {
					a->h = 1;
					b->h = -1;
				}
				node = b;
			} else {
				Node* c = b->right;
				leftRotate(b);
				rightRotate(a);
				if(c->h == 1){
					a->h = -1;
					b->h = 0;
				}
				else if (c->h == -1){
					a->h = 0;
					b->h = 1;
				}
				else {
					a->h = 0;
					b->h = 0;
				}
				c->h = 0;
				node = c;
			}
		}
		return node->h;
	}

	std::pair<Node*, bool> insert(Node* node, const std::pair<Key, T>& keyValue) {
		std::pair<Node*, bool> check;
		if(compare(keyValue.first, node->val.first)){
			if(node->left == nullptr){
				node->left = NodeAllocTraits::allocate(alloc, 1);
				NodeAllocTraits::construct(alloc, node->left, keyValue);
				node->left->parent = node;
				node->h++;
				return {node->left, node->h == 0};
			}
			check = insert(node->left, keyValue);
			if(!check.second){
				node->h++;
			}
		}
		else if(compare(node->val.first, keyValue.first)) {
			if(node->right == nullptr){
				node->right = NodeAllocTraits::allocate(alloc, 1);
				NodeAllocTraits::construct(alloc, node->right, keyValue);
				node->right->parent = node;
				node->h--;
				return {node->right, node->h == 0};
			}
			check = insert(node->right, keyValue);
			if(!check.second){
				node->h--;
			}
		} else {
			return {node, true};
		}
		if(node->h == 0){
			check.second = true;
		} else if(abs(node->h) == 2){
			check.second = (balance(node) == 0);
		}
		return check;
	}

	std::pair<Node*, bool> removeMin(Node* node, const Key& key){
		std::pair<Node*, bool> check;
		if(node->right != nullptr){
			check = removeMin(node->right, key);
			if(!check.second){
				node->h++;
			}
		} else {
			if(node->parent->left == node){
				node->parent->left = node->left;
			}
			else {
				node->parent->right = node->left;
			}
			if(node->left != nullptr){
				node->left->parent = node->parent;
			}
			check = {node, false};
			return check;
		}
		if(abs(node->h) == 1){
			check.second = true;
		} else if(abs(node->h) == 2){
			check.second = (abs(balance(node)) == 1);
		}
		return check;
	}

	bool erase(Node* node, const Key& key){
		bool check;
		if(compare(key, node->val.first)){
			if(node->left == nullptr){
				return true;
			}
			check = erase(node->left, key);
			if(!check){
				node->h--;
			}
		}
		else if(compare(node->val.first, key)) {
			if(node->right == nullptr){
				return true;
			}
			check = erase(node->right, key);
			if(!check){
				node->h++;
			}
		} else {
			if(node->right == nullptr && node->left == nullptr){
				if(node->parent != nullptr){
					if(node->parent->right == node){
						node->parent->right = nullptr;
					}
					else {
						node->parent->left = nullptr;
					}
				} else {
					root = nullptr;
				}
				NodeAllocTraits::destroy(alloc, node);
				NodeAllocTraits::deallocate(alloc, node, 1);
				return false;
			}
			else if(node->left == nullptr){
				if(node->parent != nullptr){
					if(node->parent->right == node){
						node->parent->right = node->right;
					}
					else {
						node->parent->left = node->right;
					}
				} else {
					root = node->right;
				}
				node->right->parent = node->parent;
				NodeAllocTraits::destroy(alloc, node);
				NodeAllocTraits::deallocate(alloc, node, 1);
				return false;
			} else {
				std::pair<Node*, bool> check1 = removeMin(node->left, key);
				swap(node->val, check1.first->val);
				NodeAllocTraits::destroy(alloc, node);
				NodeAllocTraits::deallocate(alloc, check1.first, 1);
				check = check1.second;
				if(!check){
					node->h--;
				}
			}
		}
		if(abs(node->h) == 1){
			check = true;
		} else if(abs(node->h) == 2){
			check = (abs(balance(node)) == 1);
		}
		return check;
	}

	void destroy(Node* node){
		if(node == nullptr){
			return;
		}
		destroy(node->left);
		destroy(node->right);
		NodeAllocTraits::destroy(alloc, node);
		NodeAllocTraits::deallocate(alloc, node, 1);
	}


	void print(Node* node, size_t h){
		if(node == nullptr){
			return;
		}
		print(node->right, h + 1);
		for(size_t i = 0 ; i < h ; ++i){
			std::cout << '\t';
		}
		std::cout << node->val.first << ' ' << node->val.second << '(' << node->h << ')' << '\n';
		print(node->left, h + 1);
	}


public:
	// iterator begin();
	// iterator rbegin();
	// iterator end();
	// iterator rend();
	// T& operator[](const Key& key);
	// const T& at(const Key& key) const;
	// std::pair<iterator, bool> insert(const std::pair<Key, T>& keyValue);
	// iterator erase(iterator pos);
	// iterator find(const Key& key) const;
	// size_t erase(const Key& key);
	// bool contains(const Key& key) const;
	// bool empty() const;
	// size_t size() const;
	// void clear();
	// void print();
	// ~Avl();

	iterator begin(){
		return iterator(findBegin(), false);
	}

	iterator rbegin(){
		return iterator(findRBegin(), true);
	}

	iterator end(){
		return iterator(nullptr, false);
	}

	iterator rend(){
		return iterator(nullptr, true);
	}

	T& operator[](const Key& key){
		if(root == nullptr || find(root, key) == nullptr){
			countNode++;
		}
		Node* res;
		if(root == nullptr){
			Node* node = NodeAllocTraits::allocate(alloc, 1);
			NodeAllocTraits::construct(alloc, node, std::make_pair(key, T{}));
			root = node;
			res = node;
			return (res->val).second;
		}
		res = insert(root, std::make_pair(key, T{})).first;
		return (res->val).second;
	}

	T& at(const Key& key) const {
		Node* res = find(root, key);
		if(res == nullptr){
			throw "out_of_range";
		}
		return res->val.second;
	}

	std::pair<iterator, bool> insert(const std::pair<Key, T>& keyValue){
		countNode++;
		if(root == nullptr){
			Node* node = NodeAllocTraits::allocate(alloc, 1);
			NodeAllocTraits::construct(alloc, node, keyValue);
			root = node;
			return {iterator(node, false), true};
		}
		return {iterator(insert(root, keyValue).first, false), true};
	}

	iterator erase(iterator pos){
		if(pos == end() || pos == rend()){
			throw "wrong iterator";
		}
		iterator pos1 = pos;
		++pos;
		erase(root, (*pos1).first);
		--countNode;
		return pos;
	}

	iterator find(const Key& key) const{
		if(root == nullptr){
			return iterator(nullptr, false);
		}
		Node* node = find(root, key);
		if(node == nullptr){
			return iterator(nullptr, false);
		}
		return iterator(node, false);
	}

	size_t erase(const Key& key) {
		iterator it = find(key);
		if(it == end()){
			return 0;
		}
		erase(it);
		return 1;
	}

	bool contains(const Key& key) const{
		if(root == nullptr || find(root, key) == nullptr){
			return false;
		}
		return true;
	}

	bool empty() const{
		return countNode == 0;
	}

	size_t size() const{
		return countNode;
	}

	void clear(){
		destroy(root);
		countNode = 0;
		root = nullptr;
	}

	void print(){
		print(root, 0);
	}

	~Avl(){
		clear();
	}

};
