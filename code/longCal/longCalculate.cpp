#include<iostream>

using namespace std;

void Error(int nCode)
{
    cout << "Error" << nCode;
    exit(1);
}

void PrintF(ostream& out,unsigned char I)
{
// or use "switch"
    if (I < 10)
        cout << I;
    else if (I == 10)
        out << "A";
    else if (I == 11)
        out << "B";
    else if (I == 12)
        out << "C";
    else if (I == 13)
        out << "D";
    else if (I == 14)
        out << "E";
    else if (I == 15)
        out << "F";
    else
        Error(100);
}

void PrintFF(ostream& out, unsigned char I)
{
    unsigned char J = I / 16;
    PrintF(out, J);
    I = I % 16;
    PrintF(out, I);
}

//build class Number
const int NLnth = 32;

class Number
{
    friend void Shift(Number& n_num, int pos);
    friend Number operator+(Number& n_num1, Number& n_num2);
    friend Number operator*(Number& n_num1, Number& n_num2);
    friend Number operator*(Number& n_num, unsigned char n);
    friend ostream& operator<<(ostream& out, const Number& n_num);
private:
    int nLnth;
    unsigned char num[NLnth];
public:
    Number();
    Number(const Number& n_num);
    void makeConstant();
    void Init(unsigned int I);
    unsigned char getnum(int i);
    bool operator<=(Number& n_num);
};
//成员函数实现 //implementation of member functions
Number::Number()
{
    nLnth = 1;
    for(int i = 0; i < NLnth; i++)
        num[i] = 0;
}

Number::Number(const Number& n_num)
{
    nLnth = n_num.nLnth;
    for (int i = 0; i < nLnth; i++)
        num[i] = n_num.num[i];
}

void Number::makeConstant() //这里做出来的常数是2^256-1
{
    nLnth = NLnth;
    for (int i = 0; i < NLnth - 1; i++)
        num[i] = 255;
    num[NLnth - 1] = 175;
}

void Number::Init(unsigned int I)
{
    for (int i = 0; i < NLnth; i++)
    {
        num[i] = I % 256;
        nLnth = i + 1;
        I = I / 256;
        if (I == 0)
            return;
    }
}

unsigned char Number::getnum(int i)
{
    return i < nLnth ? num[i] : 0;
}

bool Number::operator<=(Number& n_num) //成员函数运算符重载 //Member function operator overloading
{
    int maxLnth = max(nLnth, n_num.nLnth);
    for (int i = maxLnth - 1; i >= 0; i--)
    {
        int nA = getnum(i);
        int nB = n_num.getnum(i);
        if (nA < nB) return true;
        if (nA > nB) return false;
    }
    return true;
}
//全局函数实现 //implementation of Global function
void Shift(Number& n_num, int pos)
{
    for (int i = 31; i >= pos; i--)
        n_num.num[i] = n_num.num[i - pos];
    for (int i = pos - 1; i >= 0; i--)
        n_num.num[i] = 0;
}

Number operator+(Number& n_num1, Number& n_num2)
{
    Number n_num;
    int maxLnth = max(n_num1.nLnth, n_num2.nLnth);
    int fward = 0;
    for (int i = 0; i < maxLnth; i++)
    {
        int nA = n_num1.getnum(i);
        int nB = n_num2.getnum(i);
        int nC = fward + nA + nB;
        n_num.num[i] = nC % 256;
        if (nC >= 256)
            fward = 1;
        else
            fward = 0;
    }
    if (fward > 0 && maxLnth < NLnth)
        n_num.num[maxLnth++] = 1;
    n_num.nLnth = maxLnth;
    return n_num;
}

Number operator*(Number& n_num1, Number& n_num2)
{
    Number n_num;
    Number temp;
    n_num.Init(0);
    temp.Init(0);
    for (int i = 0; i < NLnth; i++)
    {
        temp = n_num1 * n_num2.num[i];
        Shift(temp, i);
        n_num = n_num + temp;
    }
    return n_num;
}

Number operator*(Number& n_num, unsigned char nB)
{
    Number temp(n_num);
    int fward = 0;
    for (int i = 0; i < temp.nLnth; i++)
    {
        int nA = n_num.num[i];
        int nC = fward + nA * nB;
        temp.num[i] = nC % 256;
        fward = nC / 256;
    }
    if (fward && temp.nLnth<32)
        temp.num[temp.nLnth++] = fward;
    return temp;
}

ostream& operator<<(ostream& out, const Number& n_num)
{
    for (int i = n_num.nLnth - 1; i >= 1; i--)
    {
        if (n_num.num[i] <= 0)
            continue;
        PrintFF(out, n_num.num[i]);
        out << "'";
    }
    PrintFF(out, n_num.num[0]);
    cout << endl;
    return out;
}
//测试函数 // testing function
//void test()
//{
//
//}

//task3解决方案  base^k <= 2^256
int solution()
{
    Number constant;
    Number n_num;
    constant.makeConstant();
    n_num.Init(1);
    int times = 0;
    int base = 3;
    while (n_num <= constant)
    {
        n_num = n_num * base;
        times++;
    }
    return times - 1;
}

int main()
{
    cout << "3^" << solution() << " < " << "2^256";
    return 0;
}