#include <iostream>
#include <functional>
#include "smart_ptr.h"


template<typename T>
smt_p::shared_ptr<T>::shared_ptr():ptr(nullptr),cur_block(nullptr) {

}

template<typename T>
smt_p::shared_ptr<T>::~shared_ptr() {
    if(cur_block->count==1){
        cur_block->deleter==nullptr?delete ptr:cur_block->deleter(ptr);
        delete cur_block;
    }
    --cur_block->count;
}

template<typename T>
smt_p::shared_ptr<T>::shared_ptr(T* pointer):ptr(pointer),cur_block(new control_block) {

}

template<typename T>
smt_p::shared_ptr<T>::shared_ptr(T* pointer, std::function<void(T*)>deleter) {
    ptr = pointer;
    cur_block = new control_block;
    cur_block->deleter = deleter;
}

template<typename T>
smt_p::shared_ptr<T>::shared_ptr(const smt_p::shared_ptr<T>& other_ptr){
    ptr = other_ptr.ptr;
    cur_block = other_ptr.cur_block;
    ++(cur_block->count);
}

template<typename T>
smt_p::shared_ptr<T>::shared_ptr(smt_p::shared_ptr<T>&& other_ptr){
    ptr = other_ptr.ptr;
    cur_block = other_ptr;
    other_ptr.cur_block = nullptr;
    ptr = nullptr;
}

template<typename T>
void smt_p::shared_ptr<T>::reset(T* pointer) {
    delete ptr;
    ptr = pointer;
    if(cur_block==nullptr){
        cur_block=new control_block;
    }
}

template<typename T>
T* smt_p::shared_ptr<T>::get() const {
    return ptr;
}

template<typename T>
T& smt_p::shared_ptr<T>::operator*() const {
    return *ptr;
}

template<typename T>
smt_p::shared_ptr<T>& smt_p::shared_ptr<T>::operator=(const smt_p::shared_ptr<T>& other_ptr) {
    delete ptr;
    delete cur_block;
    ptr = other_ptr.ptr;
    cur_block = other_ptr.cur_block;
    ++(cur_block->count);
    return *this;
}

template<typename T>
smt_p::shared_ptr<T>& smt_p::shared_ptr<T>::operator=(smt_p::shared_ptr<T>&& other_ptr){
    ptr = other_ptr.ptr;
    cur_block = other_ptr.cur_block;
    other_ptr.cur_block = nullptr;
    ptr = nullptr;
}


template<typename T>
bool smt_p::shared_ptr<T>::unique() const {
    return cur_block->count == 1?true:false;
}

template<typename T>
long smt_p::shared_ptr<T>::use_count() const {
    return cur_block->count;
}

template<typename T>
smt_p::shared_ptr<T>::operator bool() const {
    return ptr;
}

template<typename T>
void smt_p::shared_ptr<T>::swap(smt_p::shared_ptr<T>& other_ptr) noexcept{
    smt_p::shared_ptr<T> tmp;
    tmp.ptr = ptr;
    tmp.cur_block = cur_block;
    ptr = other_ptr.ptr;
    cur_block = other_ptr.cur_block;
    other_ptr.ptr = tmp.ptr;
    other_ptr.cur_block = tmp.cur_block;
    
}


void del(int* a){
        std::cout<<"deleting";
        delete a;
}


int main(){
    smt_p::shared_ptr<int> a(new int, del);

}
