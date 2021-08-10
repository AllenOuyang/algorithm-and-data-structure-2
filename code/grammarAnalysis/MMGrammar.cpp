//
// Created by 欧阳磊落 on 2021/7/9.
//

//алгоритм разбор сверху вниз
#include <iostream>
#include <string>
#include <ctime>
using namespace std;
const int NNN=7;
string S="(a+((a+b)+b))*((a+b)+b)";
class Production{
public:
    char Left;
    string Right;
    void Init(char L,string R);
};

class Gramma{
public:
    Production PPP[NNN];
    bool Run(string Input);
    bool Run(string Input,string Wish);
};

void Production::Init(char Left,string Right){
    this->Left=Left;
    this->Right=Right;
}

bool Gramma::Run(string Input,string Wish){
    int IS=Input.size();
    int WS=Wish.size();
    if(IS==0 && WS==0)
        return true;
    else if(IS==0 || WS==0)
        return false;
    char CW=Wish[0];
    if(CW!='E'&& CW!='T' && CW!='F'){
        if(CW!=Input[0])
            return false;
        return Run(Input.substr(1,IS-1),Wish.substr(1,WS-1));
    }
    for(int i=0;i<NNN;i++){
        if(PPP[i].Left!=Wish[0])
            continue;
        if(Run(Input,PPP[i].Right+Wish.substr(1,WS-1)))
            return true;
    }
    return false;
}

bool Gramma::Run(string Input){
    char CW=PPP[0].Left;
    string Wish(1,CW);
    return Run(Input,Wish);
}

int main(){
    double start=clock();
    Gramma GGG;
    GGG.PPP[0].Init('E',"T");
    GGG.PPP[1].Init('E',"T+E");
    GGG.PPP[2].Init('T',"F");
    GGG.PPP[3].Init('T',"F*T");
    GGG.PPP[4].Init('F',"a");
    GGG.PPP[5].Init('F',"b");
    GGG.PPP[6].Init('F',"(E)");
    if(GGG.Run(S))
        cout<<"true"<<endl;
    else
        cout<<"false"<<endl;
    cout<<(clock()-start)/CLOCKS_PER_SEC<<endl;
    return 0;
}