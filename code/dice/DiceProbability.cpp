//
// Created by Оуян Лэйло on 2021/5/28.
//

#include <iostream>
#include <iomanip>

using namespace std;

class Dice
{
public:
    int dice_num;
    long long times[100];
public:
    Dice();
    Dice(int num);
    int SumTime();
    void generateTimes(Dice& , Dice&);
    void PrintTimes();
};

Dice::Dice()
{
    dice_num = 0;
    for(int i = 0; i < 100; i++)
        times[i] = 0;
}

Dice::Dice(int num)
{
    dice_num = num;
    for(int i = 0; i < 100; i++)
        times[i] = 0;
    if(dice_num == 1)
        for(int i = 1; i <= 6; i++)
            times[i] = 1;
}

int Dice::SumTime()
{
    int sum = 0;
    for(int i = 0; i < dice_num; i++)
        sum *= 6;
    return sum;
}

void Dice::generateTimes(Dice& pre_dice1, Dice& pre_dice2)
{
    for(int i = pre_dice1.dice_num; i <= pre_dice1.dice_num * 6; i++)
        for(int j = pre_dice2.dice_num; j <= pre_dice2.dice_num * 6; j++)
            times[i+j] += pre_dice1.times[i] * pre_dice2.times[j];
}

void Dice::PrintTimes()
{
    for(int i = dice_num; i <= dice_num * 6; i++)
        cout << left << setw(15) << i;
    cout << endl;
    for(int i = dice_num; i <= dice_num * 6; i++)
        cout << left << setw(15) << times[i];
    cout << endl;
}

int main()
{
    Dice empty;
    Dice one(1);
    Dice two(2);
    Dice three(3);
    Dice four(4);
    Dice five(5);
    Dice six(6);
    Dice seven(7);
    Dice eight(8);
    Dice nine(9);
    Dice ten(10);
    Dice eleven(11);
    Dice twelve(12);
    Dice thirteen(13);
    Dice fourteen(14);
    Dice fifteen(15);
    Dice sixteen(16);
    two.generateTimes(one, one);
    three.generateTimes(one,two);
    four.generateTimes(one,three);
    five.generateTimes(one,four);
    six.generateTimes(three,three);
    seven.generateTimes(three,four);
    eight.generateTimes(three,five);
    nine.generateTimes(five,four);
    ten.generateTimes(five,five);
    eleven.generateTimes(six,five);
    twelve.generateTimes(one,eleven);
    thirteen.generateTimes(one,twelve);
    fourteen.generateTimes(one,thirteen);
    fifteen.generateTimes(one,fourteen);
    sixteen.generateTimes(eight,eight);
    one.PrintTimes();
    cout << "/////////////////////////////////////////////////////////////////////////////////////////////////" << endl;
    two.PrintTimes();
    cout << "/////////////////////////////////////////////////////////////////////////////////////////////////" << endl;
    three.PrintTimes();
    cout << "/////////////////////////////////////////////////////////////////////////////////////////////////" << endl;
    four.PrintTimes();
    cout << "/////////////////////////////////////////////////////////////////////////////////////////////////" << endl;
    five.PrintTimes();
    cout << "/////////////////////////////////////////////////////////////////////////////////////////////////" << endl;
    six.PrintTimes();
    cout << "/////////////////////////////////////////////////////////////////////////////////////////////////" << endl;
    seven.PrintTimes();
    cout << "/////////////////////////////////////////////////////////////////////////////////////////////////" << endl;
    eight.PrintTimes();
    cout << "/////////////////////////////////////////////////////////////////////////////////////////////////" << endl;
    nine.PrintTimes();
    cout << "/////////////////////////////////////////////////////////////////////////////////////////////////" << endl;
    ten.PrintTimes();
    cout << "/////////////////////////////////////////////////////////////////////////////////////////////////" << endl;
    eleven.PrintTimes();
    cout << "/////////////////////////////////////////////////////////////////////////////////////////////////" << endl;
    twelve.PrintTimes();
    cout << "/////////////////////////////////////////////////////////////////////////////////////////////////" << endl;
    thirteen.PrintTimes();
    cout << "/////////////////////////////////////////////////////////////////////////////////////////////////" << endl;
    fourteen.PrintTimes();
    cout << "/////////////////////////////////////////////////////////////////////////////////////////////////" << endl;
    fifteen.PrintTimes();
    cout << "/////////////////////////////////////////////////////////////////////////////////////////////////" << endl;
    sixteen.PrintTimes();
    cout << "/////////////////////////////////////////////////////////////////////////////////////////////////" << endl;

    return 0;
}