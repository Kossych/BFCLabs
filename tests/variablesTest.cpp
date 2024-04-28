#include "../include/boolfun.h"

int main() {
    BF f("00001111");

    auto isDummy = f.dummyVariables();
    std::cout<<std::endl;
    std::cout<<"dummy variables: ";
    for(int i = 0; i < f.n; i++) {
        if(isDummy[i]) {
            std::cout<<"x"<<i<<" ";
        }
    }
    std::cout<<std::endl;

    auto isLinear = f.linearVariables();
    std::cout<<std::endl;
    std::cout<<"linear variables: ";
    for(int i = 0; i < f.n; i++) {
        if(isLinear[i]) {
            std::cout<<"x"<<i<<" ";
        }
    }
    std::cout<<std::endl;
}