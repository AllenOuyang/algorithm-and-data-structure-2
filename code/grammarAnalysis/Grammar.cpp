//
// Created by 欧阳磊落 on 2021/5/21.
//

#include <iostream>
#include <string>

using namespace std;

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
    bool Run(string Input, string S);
};

bool Grammar::Run(string Input, string S)
{
    if(Input[0] == 'E' || Input[0] == 'T' || Input[0] == 'F')
    {
        if(Input[0] == 'E')
        {
            string sub1 = Input;
            string sub2 = Input;
            return Run(sub1.replace(0, 1, PPP[1].R), S) || Run(sub2.replace(0, 1, PPP[0].R), S);
        }
        if(Input[0] == 'T')
        {
            string sub1 = Input;
            string sub2 = Input;
            return Run(sub1.replace(0,1,PPP[3].R),S) || Run(sub2.replace(0,1,PPP[2].R),S);
        }
        if(Input[0] == 'F')
        {
            string sub1 = Input;
            string sub2 = Input;
            string sub3 = Input;
            return Run(sub1.replace(0,1,PPP[6].R),S) || Run(sub2.replace(0,1,PPP[5].R),S) || Run(sub3.replace(0,1,PPP[4].R),S);
        }

    }
    else if(Input[0] == 'a' || Input[0] == 'b' || Input[0] == '*' || Input[0] == '+' || Input[0] == '(' || Input[0] == ')')
    {
        if(Input == S)
            return true;
        if(Input[0] == S[0])
            return Run(Input.substr(1,Input.length()-1),S.substr(1,S.length()-1));
        else
            return false;
    }
    return false;
}

int main()
{
    Grammar G;
    G.PPP[0].L = 'E';
    G.PPP[0].R = "T";

    G.PPP[1].L = 'E';
    G.PPP[1].R = "T+E";

    G.PPP[2].L = 'T';
    G.PPP[2].R = "F";

    G.PPP[3].L = 'T';
    G.PPP[3].R = "F*T";

    G.PPP[4].L = 'F';
    G.PPP[4].R = "a";

    G.PPP[5].L = 'F';
    G.PPP[5].R = "b";

    G.PPP[6].L = 'F';
    G.PPP[6].R = "(E)";

    if(G.Run("E","(a+b)*b+a"))
        cout << "YES" << endl;
    else
        cout << "NO" << endl;

    return 0;
}