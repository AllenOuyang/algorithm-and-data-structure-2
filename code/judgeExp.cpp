//
// Created by 欧阳磊落 on 2021/5/19.
//
#include<iostream>
#include<string>

using namespace std;

class op
{
public:
    char type;
    string str;
public:
    op():type('E'){}
    op(char t, string s):type(t),str(s){}
};

class Prod
{
public:
    char L;
    string R;
};

class Grammar
{
public:
    Prod PPP[7];
public:
    int findposadd(string S);
    int findposmul(string S);
    bool Run(op S);
};

int Grammar::findposadd(string S)
{
    int flag = 0;
    for (int i = 0; i < S.length(); i++)
    {
        if(S[i] == '(')
            flag++;
        if(S[i] == ')')
            flag--;
        if (S[i] == '+' && flag == 0)
            return i;
    }
    return 0;
}

int Grammar::findposmul(string S)
{
    int flag = 0;
    for (int i = 0; i < S.length(); i++)
    {
        if(S[i] == '(')
            flag++;
        if(S[i] == ')')
            flag--;
        if (S[i] == '*' && flag == 0)
            return i;
    }
    return 0;
}

bool Grammar::Run(op S)
{
    if(S.type == 'E')
    {
        int pos = findposadd(S.str);
        if(pos == 0)
        {
            S.type = 'T';
            return Run(S);
        }
        op sub1('T',S.str.substr(0,pos));
        op sub2('E',S.str.substr(pos+1,S.str.length()-pos-1));
        return Run(sub1) && Run(sub2);
    }
    else if(S.type == 'T')
    {
        int pos = findposmul(S.str);
        if(pos == 0)
        {
            S.type = 'F';
            return Run(S);
        }
        op sub1('F',S.str.substr(0,pos));
        op sub2('T',S.str.substr(pos+1,S.str.length()-pos-1));
        return Run(sub1) && Run(sub2);
    }
    else
    {
        if(S.str[0] == '(' && S.str[S.str.length()-1] == ')')
        {
            op sub1('E',S.str.substr(1,S.str.length()-2));
            return Run(sub1);
        }
        else if(S.str == "a" || S.str == "b")
            return true;
        else
            return false;
    }
}

//int main()
//{
//    Grammar G;
//    G.PPP[0].L = 'E';
//    G.PPP[0].R = "T";
//
//    G.PPP[1].L = 'E';
//    G.PPP[1].R = "T+E";
//
//    G.PPP[2].L = 'T';
//    G.PPP[2].R = "T";
//
//    G.PPP[3].L = 'T';
//    G.PPP[3].R = "F+T";
//
//    G.PPP[4].L = 'F';
//    G.PPP[4].R = "a";
//
//    G.PPP[5].L = 'F';
//    G.PPP[5].R = "b";
//
//    G.PPP[6].L = 'F';
//    G.PPP[6].R = "(E)";
//
//    op S('E',"a*(a+b)+a+b+a*b");
//    cout << S.str << endl;
//    if(G.Run(S))
//        cout << "YES" << endl;
//    else
//        cout << "NO" << endl;
//
//    return 0;
//}