#include "../include/boolfun.h"

BF::BF()
{
    nw = 1;
    n = 1;
    f = new base();
    for(int i = 0; i < nw; i++) f[i] = 0;
}

BF::BF(int count, std::mt19937&random_engine)
{
    if(count<1) throw std::invalid_argument("The function must contain more than 1 variable");
    if(count > base_size)  throw std::invalid_argument("This length is not supported. Replace base with a larger data type");
    nw = pow2(count - maxN);
    n = count;
    f = new base[nw];  
    for(int i = 0; i < nw; i++)
    {
        f[i] = random_engine();
    }
    if(n < maxN)
    {
        base mask = ~0;
        mask = ~(mask << pow2(n)); 
        f[0] &= mask;
    }
}

BF::BF(int count, bool isFilled)
{   
    if(count < 1) throw std::invalid_argument("The function must contain more than 1 variable");
    if(count > base_size)  throw std::invalid_argument("This length is not supported. Replace base with a larger data type");

    nw = pow2(count - maxN);
    n = count;
    f = new base[nw];

    base mask = 0;
    
    if(isFilled){
        mask = ~0;
    }

    for(int i = 0; i < nw; i++) f[i] = mask;
    if(n < maxN && isFilled) {
        f[0] = ~(f[0] << pow2(n));
    }
}

BF::BF(base funValue)
{
    this->n = maxN;
    this->nw = 1;
    this->f = new base(funValue);
}

BF::BF(BF& bf_copy)
{
    nw = bf_copy.nw;
    n = bf_copy.n;
    f = new base[nw];
    for(int i = 0; i < nw; i++)
    {
        f[i] = bf_copy.f[i];
    }
}

BF::BF(std::string s)
{
    int number_of_values = s.length();
    if(log2(number_of_values) > base_size) throw std::invalid_argument("The length of this function is not supported. Replace base with a larger data type");
    if(number_of_values < 1) throw std::invalid_argument("Incorrect string");
    if(number_of_values & (number_of_values - 1) != 0) throw std::invalid_argument("Length must be a power of two");
    nw = ((number_of_values - 1) >> maxN) + 1;
    n = Log2(number_of_values - 1) + 1;
    f = new base[nw];
    for(int i = 0; i < nw; i++) f[i] = 0;
    base mask = 1;
    for(int i = 0; i < number_of_values; i++)
    {
        mask = 1 << (i % base_size);
        int elem_num = i >> maxN;
        if(s[i] == '1') f[elem_num] |= mask;
    }
}

BF::~BF()
{
    delete[]f;
}
