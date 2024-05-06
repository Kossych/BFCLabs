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

void BF::SetBit(base bitNumber) {
    f[bitNumber / base_size] |= 1 << (bitNumber % base_size);
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

base weight(base x) {
	x = x - ((x >> 1) & 0x55555555);
	x = (x & 0x33333333) + ((x >> 2) & 0x33333333);
	x = (x + (x >> 4)) & 0x0F0F0F0F;
	x = x + (x >> 8);
	x = x + (x >> 16);

	return x & 0x3F;
}


base getNextC(base prev) {
    base b = (prev + 1) & prev;
    base c = weight((b - 1) ^ prev) - 2;
    return (((((prev + 1) ^ prev) << 1) + 1) << c) ^ b;
}