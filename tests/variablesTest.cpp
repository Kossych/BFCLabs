#include "../include/boolfun.h"

int main() {
    BF f("1100001111000011");
    BF fcopy(f);
    fcopy.MobiusTransform();
    fcopy.ANFPrint();
    auto isDummy = f.dummyVariables();
    std::cout<<std::endl;
    std::cout<<"dummy variables: ";
    for(int i = 0; i < f.n; i++) {
        if(isDummy[i]) {
            std::cout<<"x"<<i+1<<" ";
        }
    }
    std::cout<<std::endl;

    auto isLinear = f.linearVariables();
    std::cout<<std::endl;
    std::cout<<"linear variables: ";
    for(int i = 0; i < f.n; i++) {
        if(isLinear[i]) {
            std::cout<<"x"<<i+1<<" ";
        }
    }
    std::cout<<std::endl;
}