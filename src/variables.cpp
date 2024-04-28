#include "../include/boolfun.h"

std::vector<bool> BF::linearVariables() {
    BF copy(*this);
    copy.MobiusTransform();

    base tmp = 0;

    for(base value = 0; value < (1 << copy.n); value++) {
        if(copy.f[value / base_size] & (1 << (value % base_size))) {
            tmp |= value;
        }
    }

    base _tmp = 0;

    for(base value = 0; value < (1 << copy.n); value++) {
        if(copy.f[value / base_size] & (1 << (value % base_size)) && (weight(value) != 1)) {
            _tmp |= value;
        }
    }

    for(int monomNum = 0; monomNum < copy.n; monomNum++) {
        _tmp ^= (1 << monomNum);
    }

    tmp &= _tmp;

    auto isLinear = std::vector<bool>(copy.n);

    for(base variableNum = 0; variableNum < copy.n; variableNum++) {
        if(tmp & (1 << variableNum)) {
            isLinear[variableNum] = true;
        } else isLinear[variableNum] = false;
    }

    return isLinear;
}

std::vector<bool> BF::dummyVariables() {
    BF copy(*this);
    copy.MobiusTransform();

    base tmp = 0;

    for(base value = 0; value < (1 << copy.n); value++) {
        if(copy.f[value / base_size] & (1 << (value % base_size))) {
            tmp |= value;
        }
    }
    auto isDummy = std::vector<bool>(copy.n);
    for(base variableNum = 0; variableNum < copy.n; variableNum++) {
        if((tmp & (1 << variableNum)) == 0) {
            isDummy[variableNum] = true;
        } else isDummy[variableNum] = false;
    }
    return isDummy;
}