//
// Created by 欧阳磊落 on 2021/6/29.
//

//
// Created by 欧阳磊落 on 2021/5/19.
//
#include<iostream>
#include<string>

using namespace std;

int findposadd(string S)
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

int findposmul(string S)
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

bool ThisE(string E);

bool ThisF(string F)
{
    if(F[0] == '(' && F[F.length()-1] == ')')
    {
        string sub1 = F.substr(1,F.length()-2);
        return ThisE(sub1);
    }
    else if(F == "a" || F == "b")
        return true;
    else
        return false;
}

bool ThisT(string T)
{
    int pos = findposmul(T);
    if(pos == 0)
        return ThisF(T);
    string sub1 = T.substr(0,pos);
    string sub2 = T.substr(pos+1,T.length()-pos-1);
    return ThisF(sub1) && ThisT(sub2);
}

bool ThisE(string E)
{
    int pos = findposadd(E);
    if(pos == 0)
        return ThisT(E);
    string sub1 = E.substr(0,pos);
    string sub2 = E.substr(pos+1,E.length()-pos-1);
    return ThisT(sub1) && ThisE(sub2);
}

int main()
{
    string S1 = "a+(b+a*b)";
    string S2 = "a+b*b+a";
    string S3 = "(a+b))";

    cout << S1 << endl;
    if(ThisE(S1))
        cout << "YES" << endl;
    else
        cout << "NO" << endl;

    cout << S2 << endl;
    if(ThisE(S2))
        cout << "YES" << endl;
    else
        cout << "NO" << endl;

    cout << S3 << endl;
    if(ThisE(S3))
        cout << "YES" << endl;
    else
        cout << "NO" << endl;

    return 0;
}