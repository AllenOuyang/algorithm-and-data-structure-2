//#include<iostream>
//using namespace std;
//
//int f(int n,int s)
//{
//    if( n<0 || n<s || s>6*n )
//        return 0;
//    if( n == 1 )
//        return 1;
//
//    int res;
//    res = f(n-1,s-1)+f(n-1,s-2)+f(n-1,s-3)+f(n-1,s-4)+f(n-1,s-5)+f(n-1,s-6);
//    return res;
//}//
//
//int main()
//{
//    int n,i;
//
//    cout << "Input n = ";
//    cin >> n;
//
//    for(i=n ; i<6*n ; ++i)
//    {
//        cout << "f("<<n<<","<<i<<") = " << f(n,i) << endl;
//    }
//    return 0;
//
//}
// Created by 欧阳磊落 on 2021/5/28.
//

