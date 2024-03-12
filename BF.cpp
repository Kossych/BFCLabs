#include "BF.h"
#include <bitset>
#include <ctime>

#include <iterator>
#include <chrono>


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

BF::BF()
{
    nw = 1;
    n = 1;
    f = new base();
    for(int i = 0; i < nw; i++) f[i] = 0;
}

BF::BF(int count, std::mt19937&random_engine)
{
    if(count<1) throw std::invalid_argument("The function must contain more than 1 variable");
    nw = pow2(count - maxN);
    n = count;
    f = new base[nw];  
    for(int i = 0; i < nw; i++)
    {
        f[i] = random_engine();
    }
    if(n < maxN)
    {
        base mask = 0xFFFFFFFF;
        mask = ~(mask << pow2(n)); 
        f[0] &= mask;
    }
}

BF::BF(int count, bool isFilled = true)
{   
    if(count < 1) throw std::invalid_argument("The function must contain more than 1 variable");

    nw = pow2(count - maxN);
    n = count;
    f = new base[nw];

    base mask = 0;
    
    if(isFilled){
        mask = 0xFFFFFFFF;
    }

    for(int i = 0; i < nw; i++) f[i] = mask;
    if(n < maxN && isFilled) {
        f[0] = ~(f[0] << pow2(n));
    }
}

BF::BF(BF& bf_copy)
{
    nw = bf_copy.nw;
    n = bf_copy.n;
    f = new base[nw];
    for(int i = 0; i < nw; i++)
    {
        f[i] = bf_copy.f[i];
    }
}

BF::BF(std::string s)
{
    int number_of_values = s.length();
    if(number_of_values < 1) throw std::invalid_argument("Incorrect string");
    if(number_of_values & (number_of_values - 1) != 0) throw std::invalid_argument("Length must be a power of two");
    nw = ((number_of_values - 1) >> maxN) + 1;
    n = Log2(number_of_values - 1) + 1;
    f = new base[nw];
    for(int i = 0; i < nw; i++) f[i] = 0;
    base mask = 1;
    for(int i = 0; i < number_of_values; i++)
    {
        mask = 1 << (i % base_size);
        int elem_num = i >> maxN;
        if(s[i] == '1') f[elem_num] |= mask;
    }
}

BF::~BF()
{
    delete[]f;
}

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
    n = bf.n;
    nw = bf.nw;
    f = new base[nw];
    for(int i = 0; i < nw; i++)
    {
        f[i] = bf.f[i];
    }
    return *this;
}

bool BF::operator ==(BF& bf)
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

BF& BF::MobiusTransform()
{
    base count = pow2(n);
    base* fCopy = new base[nw];
    for(int i = 0; i < nw; i++)
    {
        fCopy[i] = this->f[i];
        this->f[i] = 0;
    }
    this->f[0] |= (fCopy[0] & 1);
    for(base i = 1; i < count; i++) 
    {
        base bit = 0;
        for(int j = 0; j < nw - 1; j++) 
        {
            bit = fCopy[j + 1] & 1;
            fCopy[j] = fCopy[j] ^ ((fCopy[j] >> 1) | (bit << (base_size - 1)));
        }
        fCopy[nw - 1] = fCopy[nw - 1] ^ (fCopy[nw - 1] >> 1);

        this->f[i/base_size] |= ((fCopy[0] & 1) << (i % base_size));
    }
    return *this;
}

BF& BF::MobiusTransform2() 
{
    std::string val = "01010000100011011101011110001110";
    int maxStep = n <= maxN ? n: maxN;
    for(int step = 0, shift = 1; step < maxStep; step++, shift <<= 1)
    {
        for(int i = nw - 1; i >= 0; i--) 
        {
            f[i] ^= ((f[i] << shift) & MOBIUS_CONSTS[step]);
        }
    }
    for(int step = maxN, shift = 1; step < n; step++, shift <<= 1)
    {
        for(int i = nw - 1; i > 0; i -= (shift << 1))
        {
            for(int j = 0; j < shift; j++)
            {
                f[i - j] ^= f[i - j - shift];
            }
        }
    }
    return *this;
}


void BF::ANFPrint()
{
    base monomialCount = pow2(n);
    bool isPrinted = false;
    if(f[0] & 1) 
    {
        std::cout<<"1";
        isPrinted = true;
    }
    for(base i = 1; i < monomialCount; i++)
    {
        if(f[i / base_size] & (1 << (i % base_size))) 
        {
            if(isPrinted) std::cout << " + ";
            isPrinted = true;
            for(int bit = 0; bit < n; bit++) 
            {
                if(i & (1 << bit))  std::cout << "x" << (bit + 1);
            }
        }
    }
    std::cout<<std::endl;
}



int BF::GetDegree()
{
    isANF = !isANF;
    int currentDegree = this -> n;
    base currentMonom = pow2(this->n) - 1;
    while(currentDegree > 0) 
    {
        if(GetDegreeRec(currentMonom, currentDegree - 1, this -> n, currentDegree - 2)) return currentDegree;
        currentDegree--;
        currentMonom = pow2(currentDegree) - 1;
    }
    return 0;
}

int BF::GetDegreeForce()
{
    isANF = !isANF;
    base monomCount = pow2(this->n) - 1;
    int maxDegree = 0;
    if(f[monomCount / base_size] & (1 << (monomCount % base_size))) 
        return this->n;
    for(int currentMonom = monomCount; currentMonom >= 0; currentMonom--)
    {
        if(f[currentMonom / base_size] & (1 << (currentMonom % base_size)))
        {
            int degree = 0;
            int monom = currentMonom;
            while(monom > 0)
            {
                monom &= (monom - 1);
                degree++;
            }
            if(degree > maxDegree) maxDegree = degree;
        }
    }
    return maxDegree;
}

bool BF::GetDegreeRec(base currentMonom, int shift, int leftLimit, int rightLimit)
{
    if(f[currentMonom / base_size] & (1 << (currentMonom % base_size))) return true;
    if((shift + 1) < leftLimit) return GetDegreeRec(currentMonom + (1 << shift), shift + 1, leftLimit, rightLimit);
    if(rightLimit >= 0 && ((rightLimit + 1) < shift)) return GetDegreeRec(currentMonom + (1 << rightLimit), rightLimit + 1, shift, rightLimit - 1);
    return false;
}


void lab1(std::mt19937&random_engine) 
{
    for(int n = 2; n <= 10; n++){
        BF bf(n);
        int w = bf.GetWeight();
        std::cout<< n << ": "<< w << std::endl;
    }

    for(int n = 1; n < 10; n++){
        BF bf(5, random_engine);
        int w = bf.GetWeight();
        base sqrn = pow2(5);
        double kn = (double)w / sqrn;   
        std::cout<<bf<<std::endl;
    }

   /* for(int n = 2; n < 32; n++){
        BF bf(n, random_engine);
        int w = bf.GetWeight();
        base sqrn = pow2(n);
        double kn = (double)w / sqrn;
        std::cout<< n << ": "<< w <<"/"<< sqrn<< " = " << kn<<std::endl;     
        //std::cout<<bf<<std::endl;
    }*/
}

bool mobiusTransformTest(std::mt19937&random_engine) 
{
    int count = 1;
    for(int i = 0; i < count; i++)
    {
        int n = 31;
        BF bf(n, random_engine);
        BF bfCopy = bf;
        std::cout<<(bf.nw >> 18);
        if(bf.MobiusTransform2().MobiusTransform2() != bfCopy) 
            return false;
    }
    return true;
}

void compareGetDegreeMethods(std::mt19937&random_engine) {
    int bfCount = 10;
    int n = 18;
    BF** bf = new BF*[bfCount];
    for(int i = 0; i < bfCount; i++)
    {
        bf[i] = new BF(n);
        bf[i]->MobiusTransform();
    }
    std::chrono::steady_clock::time_point timePoint1 = std::chrono::steady_clock::now();
    for(int i = 0; i < bfCount; i++)
    {
        bf[i]->GetDegree();
    }
    std::chrono::steady_clock::time_point timePoint2 = std::chrono::steady_clock::now();
    for(int i = 0; i < bfCount; i++)
    {
        bf[i]->GetDegreeForce();
    }
    std::chrono::steady_clock::time_point timePoint3 = std::chrono::steady_clock::now();
    for(int i = 0; i < bfCount; i++)
    {
        if(bf[i]->GetDegreeForce() != bf[i]->GetDegree()) throw "the results of the two methods are not identical";
    }
    std::cout << "GetDegreeTime = " << std::chrono::duration_cast<std::chrono::nanoseconds>(timePoint2 - timePoint1).count() << std::endl;
    std::cout << "GetDegreeForceTime = " << std::chrono::duration_cast<std::chrono::nanoseconds> (timePoint3 - timePoint2).count() << std::endl;
}

void lab2(std::mt19937&random_engine)
{
    BF bf(6);
    std::cout<<bf<<bf.MobiusTransform();
    bf = BF(6, false);
    std::cout<<bf<<bf.MobiusTransform();

    if(mobiusTransformTest(random_engine)) std::cout<<"passed"<<std::endl;
    else std::cout<<"not passed"<<std::endl;

    bf = BF(31, random_engine);
    std::chrono::steady_clock::time_point timePoint1 = std::chrono::steady_clock::now();
    bf = bf.MobiusTransform();
    std::chrono::steady_clock::time_point timePoint2 = std::chrono::steady_clock::now();
    std::cout << "t(u) = " << std::chrono::duration_cast<std::chrono::milliseconds>(timePoint2 - timePoint1).count() << std::endl;
}

int main()
{
    std::mt19937 random_engine;
    random_engine.seed(std::time(nullptr));
    //compareGetDegreeMethods(random_engine);
    //BF bf(7, random_engine);
    //BF bfcopy(bf);
    if(mobiusTransformTest(random_engine)) std::cout<<"success";
}