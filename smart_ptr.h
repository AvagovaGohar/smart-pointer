#ifndef SHARED_PTR
#define SHARED_PTR
#include <iostream>
#include <functional>


namespace smt_p{
    template<typename T>
    class shared_ptr{
    public:
        shared_ptr(); //defalult ctor
        ~shared_ptr(); // dtor
        shared_ptr(T*); // ctor with T pointer
        shared_ptr(T* , std::function<void(T*)>); // ctor with T pointer and deleter
       
        
        shared_ptr(const shared_ptr<T>&); //copy ctor
        shared_ptr(shared_ptr<T>&&); //move ctor

        void reset(T*); // set new pointer
        T* get()const; // return address of ptr pointer
        T& operator*()const; // return value in ptr piointer
        shared_ptr<T>& operator=(const shared_ptr<T>&); // two pointers point to the same address
        shared_ptr<T>& operator=(shared_ptr<T>&&); // move operator=
        bool unique()const; // return true if pointer is unique
        long use_count()const; // return count of pointers that piont to the same address
        operator bool()const; // return true if ptr isn't equal nullptr
        void swap(shared_ptr<T>&) noexcept; // swap firs pointer with second
    private:
        struct control_block{ 
            long count = 1;
            std::function<void(T*)> deleter = nullptr;
            //Also allocator, etc.
        };
        T* ptr;
        control_block* cur_block;
    };
}
#endif 
