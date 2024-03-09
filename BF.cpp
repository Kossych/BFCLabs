#include "BF.h"
#include <bitset>
#include <ctime>

#include <iterator>


unsigned int pow2(int n)
{
    if(n < 1) return 1;
    return (1LL << n);
}

unsigned int Log2(int x)
{
    int n = 0;
    while(x > 1)
    {
        n++;
        x >>= 1;
    }
    return n;
}

BF::BF()
{
    f = new unsigned int();
    for(int i = 0; i < nw; i++) f[i] = 0;
    nw = 1;
    n = 1;
}

BF::BF(int count, std::mt19937&random_engine)
{
    if(count<1) throw std::invalid_argument("The function must contain more than 1 variable");
    nw = pow2(count - maxN);
    n = count;
    f = new unsigned int[nw];  
    for(int i = 0; i < nw; i++)
    {
        f[i] = random_engine();
    }
    if(n < maxN)
    {
        unsigned int mask = 0xFFFFFFFF;
        mask = ~(mask << pow2(n)); 
        f[0] &= mask;
    }
}

BF::BF(int count, bool isFilled = true)
{   
    if(count < 1) throw std::invalid_argument("The function must contain more than 1 variable");

    nw = pow2(count - maxN);
    n = count;
    f = new unsigned int[nw];

    unsigned int mask = 0;
    
    if(isFilled){
        mask = 0xFFFFFFFF;
    }

    for(int i = 0; i < nw; i++) f[i] = mask;
    if(n < maxN && isFilled) {
        f[0] = ~(f[0] << pow2(n));
    }
}

BF::BF(BF& bf_copy)
{
    nw = bf_copy.nw;
    n = bf_copy.n;
    f = new unsigned int[nw];
    for(int i = 0; i < nw; i++)
    {
        f[i] = bf_copy.f[i];
    }
}

BF::BF(std::string s)
{
    int number_of_values = s.length();
    if(number_of_values < 1) throw std::invalid_argument("Incorrect string");
    if(number_of_values & (number_of_values - 1) != 0) throw std::invalid_argument("Length must be a power of two");
    nw = ((number_of_values - 1) >> maxN) + 1;
    n = Log2(number_of_values - 1) + 1;
    f = new unsigned int[nw];
    for(int i = 0; i < nw; i++) f[i] = 0;
    unsigned int mask = 1;
    for(int i = 0; i < number_of_values; i++)
    {
        mask = 1 << (i % base_size);
        int elem_num = i >> maxN;
        if(s[i] == '1') f[elem_num] |= mask;
    }
}

BF::BF(std::list<unsigned int>& anf)
{
    unsigned int num = anf.back();
    n = Log2(num) + 1;
    nw = (num >> maxN) + 1;   
    f = new unsigned int[nw];
    for(int i = 0; i < nw; i++) {
        f[i] = 0;
    }
    for(auto const &x: anf)
    {
        f[x >> maxN] |= (((unsigned int)1) << (x % base_size));
    }
}

BF::~BF()
{
    delete[]f;
}

std::ostream& operator <<(std::ostream &out, BF& bf)
{
    unsigned int bits = pow2(bf.n);
    unsigned int mask = 1;
    out<<"f = (";
    for(int i = 0; i < bits; i++)
    {
        int idx = i>>maxN;
        if((bf.f[idx] & (mask<<(i % base_size))) != 0) out<<"1";
        else out<<"0";
    }
    out<<')'<<std::endl;
    return out;
}

BF& BF::operator =(const BF& bf)
{
    n = bf.n;
    nw = bf.nw;
    f = new unsigned int[nw];
    for(int i = 0; i < nw; i++)
    {
        f[i] = bf.f[i];
    }
    return *this;
}

bool BF::operator ==(BF& bf)
{
    if(n != bf.n || nw != bf.nw) return false;
    for(int i = 0; i < nw; i++)
    {
        if(f[i] != bf.f[i]) return false;
    }
    return true;
}

int BF::GetWeight()
{
    unsigned int no_low_bit,
        weight = 0;
    for(int i = 0; i < nw; i++)
    {
        no_low_bit = f[i];
        while(no_low_bit != 0)
        {
            no_low_bit &= (no_low_bit - 1);
            weight++;
        }
    }
    return weight;
}

std::list<unsigned int> BF::ANF()
{
    std::list<unsigned int> res;
    unsigned int u = 0;
    unsigned int mask = 1;
    int val = pow2(n);
    for(; u < val; u++)
    {
        int idx = u >> maxN;
        mask = 1 << u;
        if((f[idx] & mask) == mask)
        {
            res.push_back(u);
        }
    }
    return res;
}

BF BF::MobiusTransform()
{
    BF res(this->n, false);

    int count = pow2(n);
    
    unsigned int* fCopy = new unsigned int[nw];
    for(int i = 0; i < nw; i++)
        fCopy[i] = this->f[i];
    
    res.f[0] |= (fCopy[0] & 1);
    for(int i = 1; i < count; i++) 
    {
        unsigned int bit = 0;
        for(int j = 0; j < nw - 1; j++) 
        {
            bit = fCopy[j + 1] & 1;
            fCopy[j] = fCopy[j] ^ ((fCopy[j] >> 1) | (bit << (base_size - 1)));
        }
        fCopy[nw - 1] = fCopy[nw - 1] ^ (fCopy[nw - 1] >> 1);

        res.f[i/base_size] |= ((fCopy[0] & 1) << (i % base_size));
    }
    return res;
}

void ANFOutput(std::list<unsigned int>& list)
{
    std::list<unsigned int>::iterator x = list.begin();
    if(*x == 0)
    { 
        std::cout<<"1";
        x++;
    }
    for(; x != list.end(); x++) 
    {
        if(x != list.begin()) std::cout<<" + ";
        unsigned int mask = 1;
        for(int bit = 0; bit < base_size; bit++)
        {
            mask = 1 << bit;
            if(((*x) & mask) == mask) std::cout<<"x"<< (bit+1);
        }
        
    }
    std::cout<<std::endl;
}

void lab1(std::mt19937&random_engine) {
    for(int n = 2; n <= 10; n++){
        BF bf(n);
        int w = bf.GetWeight();
        std::cout<< n << ": "<< w << std::endl;
    }

    for(int n = 1; n < 10; n++){
        BF bf(5, random_engine);
        int w = bf.GetWeight();
        unsigned int sqrn = pow2(5);
        double kn = (double)w / sqrn;   
        std::cout<<bf<<std::endl;
    }

   /* for(int n = 2; n < 32; n++){
        BF bf(n, random_engine);
        int w = bf.GetWeight();
        unsigned int sqrn = pow2(n);
        double kn = (double)w / sqrn;
        std::cout<< n << ": "<< w <<"/"<< sqrn<< " = " << kn<<std::endl;     
        //std::cout<<bf<<std::endl;
    }*/
}

void lab2(std::mt19937&random_engine) {
    BF bf("00111000");
    bf = bf.MobiusTransform();
    std::cout<<bf<<std::endl;
    auto anf = bf.ANF();
    ANFOutput(anf);
}

int main()
{
    std::mt19937 random_engine;
    random_engine.seed(std::time(nullptr));

    //BF bf("1010");
    //std::cout<<bf;

    lab2(random_engine);
}