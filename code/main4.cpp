#include <iostream>
#include <ginac/ginac.h>

using namespace std;
using namespace GiNaC;

// 递归函数，将表达式中的所有子项存储到列表中
void collect_sub_expressions(const ex& expr, lst& sub_expressions) {
    if (is_a<add>(expr) || is_a<mul>(expr)) {
        for (const auto& op : expr) {
            collect_sub_expressions(op, sub_expressions);
        }
    } else {
        sub_expressions.append(expr);
    }
}

int main() {
    int cnt=0;
    for(double i=-10;i<=10;i+=0.1)
      for(double j=-10;j<=10;j=j+0.1)
      {
        // lst t1={s==i,t==j};
        // double curw=ex_to<numeric>(subs(f[3],t1)).to_double();
        // if(curw>=-0.01&&curw<=0.01) 
        //   continue;
        // double curx=ex_to<numeric>(subs(f[0],t1)).to_double();
        // double cury=ex_to<numeric>(subs(f[1],t1)).to_double();
        // double curz=ex_to<numeric>(subs(f[2],t1)).to_double();
        // points(cnt,0)=curx/curw;
        // points(cnt,1)=cury/curw;
        // points(cnt,2)=curz/curw;  
        cnt++;
      }
    cout<<cnt<<endl;
    return 0;   
}
