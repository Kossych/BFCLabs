#include "../include/boolfun.h"

base TEST_FUNC_VALUE[11] =
{
    0x06609009, 0x1698a443, 0x0ff0f00f,
    0x17e8e817, 0x1bd8e427, 0x1be4e41b,
    0x1ee1e11e, 0x3cc3c33c, 0x69969669,
    0x3ddae697, 0x6ff6f99f
};

base EXPECTED_COR_VALUE[11] = 
{
    2, 2, 2,
    2, 2, 2,
    2, 3, 4,
    2, 2
};

int main() 
{
    for(int i = 0; i < 11; i ++) 
    {
        BF bf(TEST_FUNC_VALUE[i]);
        if(bf.cor() != EXPECTED_COR_VALUE[i]) {
            throw "error";
        }
    }
}