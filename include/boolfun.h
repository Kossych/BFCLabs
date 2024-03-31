#pragma once
#ifndef BOOL_FUNCTION_H
#define BOOL_FUNCTION_H

#include <iostream>
#include <random>
#include <chrono>
#include <bitset>
#include <ctime>
#include <iterator>

typedef unsigned int base;

#define base_size (sizeof(base)*8)
#define maxN int(Log2(base_size))

base pow2(int n);
base Log2(base x);
const unsigned int MOBIUS_CONSTS[5] = {0xAAAAAAAA, 0xCCCCCCCC, 0xF0F0F0F0, 0xFF00FF00, 0xFFFF0000};

class BF {
    public :
        base n,
        nw;
        base* f;
        bool isANF = false;
    public:
        BF();
        BF(int count, std::mt19937&);
        BF(int count, bool = true);
        BF(BF &); 
        BF(std::string s);
        friend std::ostream & operator <<(std::ostream &, BF &);
        BF& operator =(const BF &);
        bool operator ==(const BF &); 
        bool operator !=(BF &);
        int GetWeight();
        ~BF();
        void ANFPrint();
        BF& MobiusTransform();
        int GetDegree();
        int GetDegreeForce();
    private:
        bool GetDegreeRec(base currentMonom, int shift, int leftLimit, int rightLimit);
};

#endif 