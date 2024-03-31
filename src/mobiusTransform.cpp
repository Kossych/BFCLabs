#include "../include/boolfun.h"

BF& BF::MobiusTransform() 
{
    int maxStep = n <= maxN ? n: maxN;
    for(int step = 0, shift = 1; step < maxStep; step++, shift <<= 1)
    {
        for(int i = nw - 1; i >= 0; i--) 
        {
            f[i] ^= ((f[i] << shift) & MOBIUS_CONSTS[step]);
        }
    }
    for(int step = maxN, shift = 1; step < n; step++, shift <<= 1)
    {
        for(int i = nw - 1; i > 0; i -= (shift << 1))
        {
            for(int j = 0; j < shift; j++)
            {
                f[i - j] ^= f[i - j - shift];
            }
        }
    }
    return *this;
}


void BF::ANFPrint()
{
    base monomialCount = pow2(n);
    bool isPrinted = false;
    if(f[0] & 1) 
    {
        std::cout<<"1";
        isPrinted = true;
    }
    for(base i = 1; i < monomialCount; i++)
    {
        if(f[i / base_size] & (1 << (i % base_size))) 
        {
            if(isPrinted) std::cout << " + ";
            isPrinted = true;
            for(int bit = 0; bit < n; bit++) 
            {
                if(i & (1 << bit))  std::cout << "x" << (bit + 1);
            }
        }
    }
    std::cout<<std::endl;
}

int BF::GetDegree()
{
    isANF = !isANF;
    int currentDegree = this -> n;
    base currentMonom = pow2(this->n) - 1;
    while(currentDegree > 0) 
    {
        if(GetDegreeRec(currentMonom, currentDegree - 1, this -> n, currentDegree - 2)) return currentDegree;
        currentDegree--;
        currentMonom = pow2(currentDegree) - 1;
    }
    return 0;
}

bool BF::GetDegreeRec(base currentMonom, int shift, int leftLimit, int rightLimit)
{
    if(f[currentMonom / base_size] & (1 << (currentMonom % base_size))) return true;
    if((shift + 1) < leftLimit) return GetDegreeRec(currentMonom + (1 << shift), shift + 1, leftLimit, rightLimit);
    if(rightLimit >= 0 && ((rightLimit + 1) < shift)) return GetDegreeRec(currentMonom + (1 << rightLimit), rightLimit + 1, shift, rightLimit - 1);
    return false;
}

int BF::GetDegreeForce()
{
    isANF = !isANF;
    base monomCount = pow2(this->n) - 1;
    int maxDegree = 0;
    if(f[monomCount / base_size] & (1 << (monomCount % base_size))) 
        return this->n;
    for(base currentMonom = monomCount - 1; currentMonom > 0; currentMonom--)
    {
        if(f[currentMonom / base_size] & (1 << (currentMonom % base_size)))
        {
            int degree = 0;
            int monom = currentMonom;
            while(monom > 0)
            {
                monom &= (monom - 1);
                degree++;
            }
            if(degree > maxDegree) maxDegree = degree;
        }
    }
    return maxDegree;
}
