#include <iostream>
#include "allocator.hpp"

int main(){
    Allocator a;
    a.makeAllocator(10);
    auto tmp = a.alloc(10);
    if(tmp ==  nullptr){
        std::cout << "NO\n";
    }
    else{
        std::cout<<"YES\n";
    }
    tmp = a.alloc(1);
    if(tmp ==  nullptr){
        std::cout << "NO\n";
    }
    else{
        std::cout<<"YES\n";
    }

    a.reset();
    tmp = a.alloc(10);
    if(tmp ==  nullptr){
        std::cout << "NO\n";
    }
    else{
        std::cout<<"YES\n";
    }
    a.makeAllocator(5);
}
