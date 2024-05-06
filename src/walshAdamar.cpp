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
    short maxAbsValue = 0;
    for(int i = 0; i < waTransformation.size(); i++) {
        short absValue = waTransformation[i];
        if(absValue < 0) absValue *= -1;
        if(maxAbsValue < absValue) {
            maxAbsValue = absValue;
        }
    }
    return (1 << (this->n - 1)) - ((maxAbsValue) >> 1);
}

std::vector<BF*> BF::bestAffineApprox() {
    auto waTransformation = this->walshAdamar();
    base maxAbs = 0;
    for(auto it: waTransformation) {
        auto abs = std::abs(it);
        if(maxAbs < abs) {
            maxAbs = abs;
        }
    }
    auto result = std::vector<BF*>();
    base lastValue = waTransformation.size();
    for(base value = 0; value < lastValue; value++) {
        if(maxAbs == std::abs(waTransformation[value])) {
            BF* baa = new BF(n, false);
            if(waTransformation[value] < 0) baa->SetBit(0);
            for(base monomNumber = 0; monomNumber < this->n; monomNumber++) {
                if((value & (1 << (monomNumber)))) {
                    baa->SetBit(1 << monomNumber);
                }
            }
            result.push_back(baa);
        }
    }
    return result;
}

std::vector<short> BF::autoCor() {
    auto autoCorVec = this->walshAdamar();

    for(int i = 0; i < autoCorVec.size(); i++) {
        autoCorVec[i] *= autoCorVec[i];
    }

    for(int step = 1; step < autoCorVec.size(); step <<= 1) {
        for(int i = 0; i < autoCorVec.size(); i += (step << 1)) {
            for(int j = 0; j < step; j++) {
                autoCorVec[i + j] += autoCorVec[i + j + step];
                autoCorVec[i + j + step] = autoCorVec[i + j] - (autoCorVec[i + j + step] << 1);
            }
        }
    }

    for(int i = 0; i < autoCorVec.size(); i++) {
        autoCorVec[i] >>= n;
    }
    
    return autoCorVec;
}