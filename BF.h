#ifndef BOOL_FUNCTION_H
#define BOOL_FUNCTION_H

#include <iostream>
#include <list>
#include <random>

#define base_size (sizeof(base)*8)
#define maxN int(Log2(base_size))

typedef unsigned int base;

//int sqrt2(int n);
//int Log2(int n);

class BF {
    private :
        unsigned int n,
        nw;
        unsigned int* f;
    public:
        BF();
        BF(int count, std::mt19937&);
        BF(int count, bool);
        BF(BF &); 
        BF(std::string s);
        BF(std::list<unsigned int>&);
        friend std::ostream & operator <<(std::ostream &, BF &);
        BF& operator =(const BF &);
        bool operator ==(BF &); 
        int GetWeight();
        ~BF();
        void ANFPrint();
        BF MobiusTransform();
        int GetDegree();
        int GetDegreeForce();
    private:
        bool GetDegreeRec(int currentMonom, int shift, int leftLimit, int rightLimit);
};

#endif 