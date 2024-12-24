#pragma once
#include <iterator>


template<class T, class Key, class Val>
class Iterator { // : public std::iterator<std::bidirectional_iterator_tag, T>
	// using iterator_category = std::bidirectional_iterator_tag;
	using pointer = T*;
public:

	// Iterator(pointer ptr, bool reverse) : ptr_(ptr), reverse_(reverse) {};
	// Iterator(const Iterator& rhs);
	// Iterator& operator++();
	// Iterator& operator--();
	// std::pair<Key, Val>& operator*() const;
	// bool operator!=(const Iterator& rhs) const;
	// bool operator==(const Iterator& rhs) const;
	// Iterator& operator=(const Iterator& rhs);

	Iterator(pointer ptr, bool reverse) : ptr_(ptr), reverse_(reverse) {};

	Iterator(const Iterator& rhs){
		ptr_ = rhs.ptr_;
		reverse_ = rhs.reverse_;
	}

	Iterator& operator++(){
		if(ptr_ == nullptr){
			throw "bad iter";
		}
		if(reverse_){
			if(ptr_->left != nullptr){
				ptr_ = ptr_->left;
				while(ptr_->right != nullptr){
					ptr_ = ptr_->right;
				}
				}
			else {
				if(ptr_->parent != nullptr && check_parent_right_child()){
					ptr_ = ptr_->parent;
				}
				else {
					pointer tmp = ptr_;
					while(ptr_->parent != nullptr && !check_parent_right_child()){
						ptr_ = ptr_->parent;
					}
					if(ptr_->parent == nullptr){
						ptr_ = tmp->left;
					} else {
						ptr_ = ptr_->parent;
					}
				}
			}
		} else {
			if(ptr_->right != nullptr){
				ptr_ = ptr_->right;
				while(ptr_->left != nullptr){
					ptr_ = ptr_->left;
				}
			}
			else {
				if(ptr_->parent != nullptr && !check_parent_right_child()){
					ptr_ = ptr_->parent;
				}
				else {
					pointer tmp = ptr_;
					while(ptr_->parent != nullptr && check_parent_right_child()){
						ptr_ = ptr_->parent;
					}
					if(ptr_->parent == nullptr){
						ptr_ = tmp->right;
					} else {
						ptr_ = ptr_->parent;
					}
				}
			}
		}
		return *this;
	}

	Iterator& operator--(){
		if(!reverse_){
			if(ptr_->left != nullptr){
				ptr_ = ptr_->left;
				while(ptr_->right != nullptr){
					ptr_ = ptr_->right;
				}
			}
			else {
				if(ptr_->parent != nullptr && check_parent_right_child()){
					ptr_ = ptr_->parent;
				}
				else {
					pointer tmp = ptr_;
					while(ptr_->parent != nullptr && !check_parent_right_child()){
						ptr_ = ptr_->parent;
					}
					if(ptr_->parent == nullptr){
						if(tmp->left == nullptr){
							throw "bad_iter";
						}
						ptr_ = tmp->left;
					} else {
						ptr_ = ptr_->parent;
					}
				}
			}
		} else {
			if(ptr_->right != nullptr){
				ptr_ = ptr_->right;
				while(ptr_->left != nullptr){
					ptr_ = ptr_->left;
				}
			}
			else {
				if(ptr_->parent != nullptr && !check_parent_right_child()){
					ptr_ = ptr_->parent;
				}
				else {
					pointer tmp = ptr_;
					while(ptr_->parent != nullptr && check_parent_right_child()){
						ptr_ = ptr_->parent;
					}
					if(ptr_->parent == nullptr){
						if(tmp->right == nullptr){
							throw "bad iter";
						}
						ptr_ = tmp->right;
					} else {
						ptr_ = ptr_->parent;
					}
				}
			}
		}
		return *this;
	}

	std::pair<Key, Val>& operator*() const{
		return ptr_->val;
	}

	bool operator!=(const Iterator& rhs) const{
		return ptr_ != rhs.ptr_;
	}

	bool operator!=(std::nullptr_t null) const{
		return ptr_ != null;
	}

	bool operator==(const Iterator& rhs) const{
		return ptr_ == rhs.ptr_;
	}

	Iterator& operator=(const Iterator& rhs){
		ptr_ = rhs.ptr_;
		reverse_ = rhs.reverse_;
		return *this;
	}

private:

        bool check_parent_right_child(){
                T* parent = ptr_->parent;
                if(parent->right == ptr_){
                        return true;
                }
                return false;
        }

	pointer ptr_;
	bool reverse_;
};
