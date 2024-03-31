#include "../include/boolfun.h"


std::ostream& operator <<(std::ostream &out, BF& bf)
{
    base bits = pow2(bf.n);
    base mask = 1;
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
    if(*this == bf) return *this;
    delete[]f;
    n = bf.n;
    nw = bf.nw;
    f = new base[nw];
    for(int i = 0; i < nw; i++)
    {
        f[i] = bf.f[i];
    }
    return *this;
}

bool BF::operator ==(const BF& bf)
{
    if(n != bf.n || nw != bf.nw) return false;
    for(int i = 0; i < nw; i++)
    {
        if(f[i] != bf.f[i]) return false;
    }
    return true;
}

bool BF::operator!=(BF& bf)
{
    return !(*this == bf);
}