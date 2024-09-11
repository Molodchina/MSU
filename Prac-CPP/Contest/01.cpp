#include <iostream>

struct Sum{
    long long sum;
    Sum(long a, long b){
        sum = a + b;
    }
    Sum(Sum a, long b){
        sum = a.sum + b;
    }
    long long get() const{
        return this->sum;
    }
};
