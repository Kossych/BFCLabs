#include "../include/boolfun.h"

std::vector<short> BF::walshAdamar() {
    base monomCount = pow2(n);
    std::vector<short> char_vec = std::vector<short>(monomCount);
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

base BF::nonlinearity() {
    auto waTransformation = this->walshAdamar();
    for(int i = 0; i < waTransformation.size(); i++) {
        if(waTransformation[i] < 0) {
            waTransformation[i] *= -1;
        }
    }
    std::sort(waTransformation.begin(), waTransformation.end());

    return (1 << (this->n - 1)) - (waTransformation[0]) >> 1;
}

std::vector<base> BF::bestAffineApprox() {
    auto waTransformation = this->walshAdamar();
    base maxAbs = 0;
    for(auto it: waTransformation) {
        auto abs = std::abs(it);
        if(maxAbs < abs) {
            maxAbs = abs;
        }
    }
    
    auto result = std::vector<base>();
    base lastValue = 1 << this->n;
    for(base funValue = 0; funValue < lastValue; funValue++) {
        if(maxAbs == std::abs(waTransformation[funValue])) {
            base baa = 0;
            if(waTransformation[funValue] < 0) baa |= 1;
            for(base monom = 0; monom < this->n; monom++) {
                if((funValue & (1 << monom)) != 0) {
                    baa |= (1 << monom);
                }
            }
            result.push_back(baa);
        }
    }
    return result;
}