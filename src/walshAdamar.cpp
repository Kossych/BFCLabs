#include "../include/boolfun.h"

std::vector<int> BF::walshAdamar() {
    base monomCount = pow2(n);
    std::vector<int> char_vec = std::vector<int>(monomCount);
    for(base i = 0; i < monomCount; i++) {
        switch((f[i / base_size] & (1 << (i % base_size))) == 0) {
            case true: 
                char_vec[i] = 1;
                break;
            case false:
                char_vec[i] = -1;
                break;
        }
    }
    for(base step = 1; step < monomCount; step <<= 1) {
        for(base i = 0; i < monomCount; i += (step << 1)) {
            for(base j = 0; j < step; j++) {
                char_vec[i + j] += char_vec[i + j + step];
                char_vec[i + j + step] = char_vec[i + j] - (char_vec[i + j + step] << 1);
            }
        }
    }
    return char_vec;
}

base BF::cor() {
    auto wac = walshAdamar();
    for(int k = 1; k <= n; k++) {
        base binComb = ((1 << k) - 1) << (n - k); 
        while(binComb < (1 << this->n)) {
            if(wac[binComb] != 0) return k - 1;
            binComb = getNextC(binComb);
        }
    }
    return this->n;
}