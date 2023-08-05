#include <iostream>
#include <ginac/ginac.h>
#include <chrono>
using namespace std;
using namespace GiNaC;
vector<ex> factor_parser(ex f){
    vector<ex> ans;
    int cnt=0;
    string cur="";
    return ans;
}


int main() {
    symbol s("s");
    symbol t("t"); // Declare a GiNaC symbol 'x'
    symtab table;
    table["s"] = s;
    table["t"] = t;
    parser reader(table);
    ex e=reader("4*s^4 + s^2*t^2 + s^2 + 6*t");
    matrix A(17,17);
    for(int i=0;i<17;i++)
        for(int j=0;j<17;j++)
            A(i,j)=rand()%5-2;
    // cout<<determinant(A)<<endl;
    lst t1={s==0.1,t==0.1};
    double sss=ex_to<numeric>(subs(e,t1)).to_double();
    cout<<sss<<endl;
    // cout<<ex_to<double>(subs(e,t1))<<endl;
        // 获取当前时间点，作为程序开始运行的时间
    // auto start_time = std::chrono::high_resolution_clock::now();

    // // 模拟程序运行，这里用一个简单的循环做示例
    // for (int i = 0; i < 10000000; ++i) {
    //     // do something
    // }

    // // 获取当前时间点，作为程序结束运行的时间
    // auto end_time = std::chrono::high_resolution_clock::now();

    // // 计算程序运行时间
    // auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);

    // // 输出程序运行时间（以秒为单位）
    // std::cout << "程序运行时间：" << duration.count() << " 秒" << std::endl;

    // return 0;
    // cout<<e<<endl;
    // ex curh=quo(e,s*s+4*s-4,s);
    // ex r=rem(e,s*s+4*s-4,s);
    // cout<<e<<endl;
    // cout<<r<<endl;
    // curh=expand(curh);
    // cout<<curh<<endl;
}
