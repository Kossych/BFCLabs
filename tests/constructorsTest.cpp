#include "../include/boolfun.h"

int main() {
    std::mt19937 random_engine;
    for(int n = 2; n <= 10; n++){
        BF bf(n);
        int w = bf.GetWeight();
        std::cout<< n << ": "<< w << std::endl;
    }

    for(int n = 1; n < 10; n++){
        BF bf(5, random_engine);
        int w = bf.GetWeight();
        base sqrn = pow2(5);
        double kn = (double)w / sqrn;   
        std::cout<<bf<<std::endl;
    }

   /* for(int n = 2; n < 32; n++){
        BF bf(n, random_engine);
        int w = bf.GetWeight();
        base sqrn = pow2(n);
        double kn = (double)w / sqrn;
        std::cout<< n << ": "<< w <<"/"<< sqrn<< " = " << kn<<std::endl;     
        //std::cout<<bf<<std::endl;
    }*/
}