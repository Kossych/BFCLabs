#include "../include/boolfun.h"

int BF::GetWeight()
{
    base no_low_bit,
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

base pow2(int n)
{
    if(n < 1) return 1;
    return (1LL << n);
}

base Log2(base x)
{
    base n = 0;
    while(x > 1)
    {
        n++;
        x >>= 1;
    }
    return n;
}
