#include <iostream>
#include <vector>
#include <ginac/ginac.h>
#include<string>
#include<sstream>
#include<cstdio>
using namespace std;
using namespace GiNaC;
symbol s("s");
symbol t("t");
vector<ex> factor_parser(ex f,parser &reader){
    vector<ex> ans;
    int cnt=0;
    string cur="";
    int i=0;
    stringstream ss;
    ss<<f;
    string curs;
    getline(ss,curs);
    while(i<curs.size()){// * (  )
        if(curs[i]=='*'){
            if(cnt==0)
            {
                ans.push_back(reader(cur));
                cur="";
            }
            else 
                cur+=curs[i];
        }
        else if(curs[i]=='('){
            cur+=curs[i];
            cnt++;
        }
        else if(curs[i]==')'){
            cur+=curs[i];
            cnt--;
        }
        else
            cur+=curs[i];
        i++;
    }
    ans.push_back(reader(cur));
    return ans;
}
int main() {
    // symbol s("s");
    // symbol t("t");
    symtab table;
    table["s"] = s;
    table["t"] = t;
    parser reader(table);
    ex expression = reader("1/4*(33+t^4*(1+26*s^3+18*s^2+5*s^6+s^4-2*s^5)+14*s^3-98*s^2+2*(-7+4*s^3+8*s^2-17*s^6+25*s^4-6*s^5)*t^2-8*(-2+8*s^3+8*s^2+s^6)*t^3-51*s^6+8*t*(-6+18*s^2+11*s^6-14*s^4+6*s^5)+89*s^4-50*s^5)*s^2");
    // vector<ex> ans=factor_parser(expression,reader);
    // cout<<ans.size()<<endl;
    // for(auto i:ans)
    //     cout<<i<<endl;
    cout<<ex_to<lst>(expression)[1];

    // expression=factor(expression);
    // stringstream ss;
    // ss<<expression;
    // string curs;
    // getline(ss,curs);
    // cout<<curs<<endl;
    // for(int i=0;i<curs.size();i++)
    // {
        
    // }
    // lst factors=ex_to<lst>(factor(expression));

    // cout<<ex_to<lst>(factor(expression)).nops()<<endl;
    // for(auto &i:ex_to<lst>(factor(expression)))
    //     cout<<i<<endl;
    // const lst &factors = ex_to<lst>(expression);
    // if (is_a<mul>(expression)) {
    //     const lst &factors = ex_to<lst>(expression);
    //     vector<ex> factors_vector;

    //     for (const auto &factor : factors) {
    //         factors_vector.push_back(factor);
    //     }

    //     cout << "Factors:" << endl;
    //     for (const auto &factor : factors_vector) {
    //         cout << factor << endl;
    //     }
    // } else {
    //     // The expression is not a product, so it's already factored or a single term.
    //     cout << "The expression is not factored or is a single term." << endl;
    // }

    return 0;
}
