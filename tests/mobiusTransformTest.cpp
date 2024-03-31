#include "../include/boolfun.h"

bool mobiusTransformTest(std::mt19937&random_engine) 
{
    int count = 5;
    for(int i = 0; i < count; i++)
    {
        int n = 25;
        BF bf(n, random_engine);
        BF bfCopy = bf;
        if(bf.MobiusTransform().MobiusTransform() != bfCopy) 
            return false;
    }
    return true;
}

void compareGetDegreeMethods(std::mt19937&random_engine) {
    int bfCount = 250;
    int n = 25;
    BF** bf = new BF*[bfCount];
    for(int i = 0; i < bfCount; i++)
    {
        bf[i] = new BF(n, true);
        bf[i]->MobiusTransform();
    }
    std::cout<<"*"<<std::endl;
    std::chrono::steady_clock::time_point timePoint1 = std::chrono::steady_clock::now();
    for(int i = 0; i < bfCount; i++)
    {
        bf[i]->GetDegree();
    }
    std::chrono::steady_clock::time_point timePoint2 = std::chrono::steady_clock::now();

    std::cout << "GetDegreeTime = " << std::chrono::duration_cast<std::chrono::nanoseconds>(timePoint2 - timePoint1).count() << std::endl;
    timePoint1 = std::chrono::steady_clock::now();
    for(int i = 0; i < bfCount; i++)
    {
        bf[i]->GetDegreeForce();
    }
    timePoint2 = std::chrono::steady_clock::now();
    std::cout << "GetDegreeForceTime = " << std::chrono::duration_cast<std::chrono::nanoseconds> (timePoint2 - timePoint1).count() << std::endl;

    for(int i = 0; i < bfCount; i++)
    {
        if(bf[i]->GetDegreeForce() != bf[i]->GetDegree()) throw "the results of the two methods are not identical";
    }
    
}

int main() {
    std::mt19937 random_engine;
    BF bf(6, true);
    //std::cout<<bf<<bf.MobiusTransform();
    bf = BF(6, false);
    //std::cout<<bf<<bf.MobiusTransform();

    if(mobiusTransformTest(random_engine)) std::cout<<"passed"<<std::endl;
    else std::cout<<"not passed"<<std::endl;

    bf = BF("1010110110101101101011011010110110101101101011011010110110101101");
    std::chrono::steady_clock::time_point timePoint1 = std::chrono::steady_clock::now();
    bf = bf.MobiusTransform();
    std::chrono::steady_clock::time_point timePoint2 = std::chrono::steady_clock::now();
    std::cout << "t(u) = " << std::chrono::duration_cast<std::chrono::nanoseconds>(timePoint2 - timePoint1).count() << std::endl;
}