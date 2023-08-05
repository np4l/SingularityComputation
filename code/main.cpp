#include <iostream>
#include <ginac/ginac.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <cstdio>
using namespace std;
using namespace GiNaC;

const symbol & get_symbol(const string & s)
{
    static map<string, symbol> directory;
    map<string, symbol>::iterator i = directory.find(s);
    if (i != directory.end())
        return i->second;
    else
        return directory.insert(make_pair(s, symbol(s))).first->second;
}
// #define CREATE_VARIABLE_NAME(index) a##index
symbol x("x"), y("y"), z("z"),w("w");
symbol s("s"), t("t");
symbol a("a"), b("b"), c("c"), d("d");
static int deg;
vector<ex> f(4);
int get_idx(int i,int j){
    return i*deg+j;
}
//组合数来生成计算minor
void generateCombination(vector<int>& candidates, int start, int p, vector<int>& combination, vector<vector<int>>& result) {
    if (p == 0) {
        result.push_back(combination);
        return;
    }

    for (int i = start; i < candidates.size(); ++i) {
        combination.push_back(candidates[i]);
        generateCombination(candidates, i + 1, p - 1, combination, result);
        combination.pop_back();
    }
}

vector<vector<int> > getCombinations(int k, int p) {
    vector<vector<int> > result;
    vector<int> candidates;
    for (int i = 0; i < k; ++i) {
        candidates.push_back(i);
    }

    vector<int> combination;
    generateCombination(candidates, 0, p - 1, combination, result);
    return result;
}
matrix random_matrix(int n,int m,int k){
    matrix cur(n,m);
    int rem;//
    if(k>10)
        rem=2;
    else
        rem=10;
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            cur(i,j)=rand()%rem;
    return cur;
}
ex KKS(matrix N,int p,int k)
{
    srand(time(0));
    matrix U1=random_matrix(p-1,p,k);
    matrix U2=random_matrix(p-1,p,k);
    matrix V1=random_matrix(k,p-1,k);
    matrix V2=random_matrix(k,p-1,k);
    matrix curU1=U1.mul(N);
    matrix curU2=U2.mul(N);
    matrix resU1=curU1.mul(V1);
    matrix resU2=curU2.mul(V2);
    // cout<<resU1<<endl;
    // cout<<"....."<<endl;
    // cout<<resU2<<endl;
    // return 1;
    ex g1=determinant(resU1);
    // cout<<"123"<<endl;
    ex g2=determinant(resU2);
    return gcd(g1,g2);
}
vector<ex> factor_parser(ex f,parser &reader){
    vector<ex> ans;
    if(!is_a<mul>(f))
    {
        ans.push_back(f);
        return ans;
    }
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
void checktime(auto &st){
    auto ed=std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(ed-st);
    st=ed;
    std::cout << duration.count() << " ms" << std::endl;
}
int main()
{
    freopen("a.out","w",stdout);
    auto st = std::chrono::high_resolution_clock::now();
        symtab table;
    table["s"] = s;
    table["t"] = t;
    parser reader(table);
    // random
    //Ex 4.6
    //Cone
    f[0]=reader("-t*(-s^2 + 1)");
    f[1]=reader("2*s*t");
    f[2]=reader(" t*(s^2 + 1)");
    f[3]=reader(" s^2 + 1");
    //Ex 4.2
    // f[0]=reader("(2*t^2 - 6*t + 4)*s^2 + 4*(t - 1)*s + 1");
    // f[1]=reader(" -2*(t^2 - 3*t + 1)*s^2 + (4*t - 2)*s");
    // f[2]=reader(" (t^2 - 4*t + 3)*s^2 - 2*(t - 1)^2 * s");
    // f[3]=1;
    // f[0]=(2*pow(t,2)-6*t+4)*pow(s,2)+4*(t-1)*s+1;
    // f[1]=-2*(pow(t,2)-3*t+1)*pow(s,2)+(4*t-2)*s;
    // f[2]=(pow(t,2)-4*t+3)*pow(s,2)-2*pow((t-1),2)*s;
    // f[3]=1;

    // Ex 6.1 Correct!
    // f[0]=s+3+t;
    // f[1]=1+t*s*s+t;
    // f[2]=s*s-3*s+2*s*t+1;
    // f[3]=s+s*t+3*t;
    //Ex 6.2 Correct!
    // f[0]=s*s+t;
    // f[1]=t*(s*s+1)+s*s+1;
    // f[2]=-s*s*s+2*s*s*t+s*s+1;
    // f[3]=t*(s*s*s+3)+1;
    //Ex 6.3
    // f[0]=-pow(s,3)*(t*t-1);
    // f[1]=(s+2)*s*t;
    // f[2]=-pow(t,3)*(pow(s,2)-4);
    // f[3]=pow(s,3);
    //Ex 6.4 
    // f[0]=reader("4*s^3 + s*t^2 + 4*s^2 - 12*s*t + t^2 + s + 1");
    // f[1]=reader("4*s^4 + s^2*t^2 + s^2 + 6*t");
    // f[2]=reader("6*t^2");
    // f[3]=reader("4*s^2 + t^2 + 1");
    //Ex 6.5
    // f[0]=reader("4*s^3 + s*t^2 + 4*s^2 - 12*s*t + t^2 + s + 1");
    // f[1]=reader("4*s^4 + s^2*t^2 + s^2 + 6*t");
    // f[2]=reader("6*t^2");
    // f[3]=reader("4*s^2 + t^2 + 1");
    for(int i=0;i<4;i++)
        cout<<f[i]<<endl;
    cout<<".........."<<endl;
    int d1=-10,d2=-10;
    for(int i=0;i<f.size();i++){
        d1=max(d1,f[i].degree(s));
        d2=max(d2,f[i].degree(t));
    }
    // cout<<d1<<" "<<d2<<endl;
    int v1,v2;
    if(d1>=d2)//保证ex4.2是3，1，理论上应该是>=
        v1=d1-1,v2=2*d2-1;//s v1,t v2
    else
        v1=2*d1-1,v2=d2-1;
    // cout<<v1<<' '<<v2<<endl;
    deg=2*d1*d2;
    //basefunc of moving planes, also matrix
    vector<ex> basefunc;

    //O(2*d1*d2)
    for(int i=0;i<=v2;i++)
    {
        for(int j=0;j<=v1;j++){
            basefunc.push_back(pow(s,j)*pow(t,i));
        }
    }
    // for(int i=0;i<deg;i++)
    //     cout<<basefunc[i]<<endl;
    
    vector<ex> matbasefunc;//存储乘后的结果，用来解线性方程组
    lst matbasefunc_lst;
    //O((d2+v2)*(d2+v2)) 近似于 O(d1*d2)
    for(int i=0;i<=(d2+v2);i++)
        for(int j=0;j<=(d1+v1);j++)
        {
            matbasefunc.push_back(pow(s,j)*pow(t,i));
            matbasefunc_lst.append(pow(s,j)*pow(t,i));
        }
    //生成用来求解的未知数变量
    //O(d1*d2)
    vector<ex> matvar;
    for(int i=0;i<4;i++)
        for(int j=0;j<2*d1*d2;j++){
            string cur="a";
            cur=cur+to_string(get_idx(i,j));
            matvar.push_back(get_symbol(cur));
        }
    lst eqns={};
    lst vars={};

    //添加到vars当中
    for(int i=0;i<matvar.size();i++)
        vars.append(matvar[i]);
    vector<ex> l;
    for(int i=0;i<4;i++)
    {
        ex cur=0;
        for(int j=0;j<deg;j++)
        {
            int idx=get_idx(i,j);
            cur=cur+matvar[idx]*basefunc[j];
        }
        l.push_back(cur);
    }
    //多维的分离系数存在问题，不能直接使用coeff
    ex mulres=0;
    for(int i=0;i<4;i++)
        mulres=mulres+l[i]*f[i];
    mulres=expand(mulres);
    // cout<<mulres<<endl;
    mulres.collect(matbasefunc_lst,true);//collect也不好用，并不能按照规定合并，合并之后的结果包含a1*s*t+a2*s*t
    //因此需要使用map累加所有的同类项
    // cout<<mulres<<endl;
    int cnt=0;
    map<ex,ex,ex_is_less> mp;//ex不支持比较，声明map的时候必须像这样声明
    for (const auto& term : mulres) {//遍历多项式中的每一项
        ex cur;
        //coeff无法求两个symbol对应的度数，因此需要用除法来求解
        int curd1=term.degree(s),curd2=term.degree(t);
        ex pl=pow(s,curd1)*pow(t,curd2);
        cur=quo(term,pl,x);//计算商
        if(mp.find(pl)!=mp.end())
            mp[pl]=mp[pl]+cur;
        else
            mp[pl]=cur;
        // cout<<cur<<"......"<<term<<endl;
        // eqns.append(cur==0);
    }
    for(auto &i:mp){
        eqns.append(i.second==0);
        // cout<<i.second<<endl;
        // cnt++;
    }
    // cout<<cnt<<endl;
    // checktime(st);
    ex ans=lsolve(eqns,vars);//存储答案
    // checktime(st);
    // cout<<ans<<endl;
    //判断自由变量
    vector<ex> freevar;
    for (int i=0;i<matvar.size();i++)
    {
        if(lhs(ans[i])==rhs(ans[i]))
            freevar.push_back(lhs(ans[i]));
    }
    //计算这一向量空间的基，也就是计算无穷组解组成的向量空间的基
    //最多有 自由变量+1个基（1是自由变量全0的时候，不过有可能自由变量全0的时候解为0向量，需要特判）
    lst cureqns=eqns;
    for(int j=0;j<freevar.size();j++)
    {
        cureqns.append(freevar[j]==0);
    }
    ex curans=lsolve(cureqns,vars);
    int flag=0;
    for(int i=0;i<matvar.size();i++){
        if(rhs(curans[i])!=0)
            flag=1; 
    }
    // checktime(st);
    int p=2*d1*d2,k;//p*k维矩阵
    //特判k的大小
    if(flag==1)
    {
        k=freevar.size()+1;
    }
    else
        k=freevar.size();
    matrix M(p,k);//全0,从0开始计算idx
    matrix N(p,k);//直接求，不做替换
    // cout<<M<<endl;
    //如果为1，则要加入答案当中
    vector<ex> ff;
    ff.push_back(x);
    ff.push_back(y);
    ff.push_back(z);
    ff.push_back(w);   
    if(flag==1)
    {
        for(int i=0;i<4;i++)
        {
            for(int j=0;j<2*d1*d2;j++)
            {
                ex varans=rhs(curans[get_idx(i,j)]);
                if(varans!=0)//取出答案
                {
                    M(j,p-1)=M(j,p-1)+varans*ff[i];
                    N(j,p-1)=N(j,p-1)+varans*f[i];
                }
            }
        }
    }
    // cout<<p<<" "<<k<<endl;
    
    for(int i=0;i<freevar.size();i++){
        lst cureqns=eqns;
        for(int j=0;j<freevar.size();j++)
        {
            if(j!=i)
                cureqns.append(freevar[j]==0);
        }
        cureqns.append(freevar[i]==1);
        ex curans=lsolve(cureqns,vars);
        for(int ii=0;ii<4;ii++)
        {
            for(int j=0;j<2*d1*d2;j++)
            {
                ex varans=rhs(curans[get_idx(ii,j)]);
                if(varans!=0)//取出答案
                {
                    N(j,i)=N(j,i)+varans*f[ii];
                    M(j,i)=M(j,i)+varans*ff[ii];
                }
            }
        }

    }
    // checktime(st);
    int testflag;
    testflag=0;
    if(testflag)
    {    ex H=0;
        vector<ex> ni;//用于存储所有可能的minor
        //计算H，相当于计算矩阵所有可能的p-1 *p-1维度的minor，然后求解GCD
        //先递归找到所有的列组合
        vector<vector<int> > combinations = getCombinations(k, p);
        // matrix calmat=ex_to<matrix>(sub_matrix(N,0,p-2,0,p-2));
        // cout<<determinant(calmat)<<endl;
        for(int i=0;i<p;i++)
        {
            for(auto &nums:combinations)
            {
                //由于不支持选取不连续的几行几列，并且reduce去除矩阵的某行某列时必须同时提供行列
                //先构建一个p*p的矩阵，p行是为了构建完矩阵后删除某一行，因此需要对应的多加一列
                //因为最后一列是全0列，直接删就行
                matrix curmat(p,p);
                for(int j=0;j<nums.size();j++)
                {
                    int col=nums[j];//选取出某一列
                    for(int k=0;k<p;k++){
                        curmat(k,j)=N(k,col);
                    }
                }
                matrix calmat=ex_to<matrix>(reduced_matrix(curmat,i,p-1));
                ni.push_back(determinant(calmat));
            }
            cout<<i<<endl;
        }
        //求解GCD,即H
        for(int i=0;i<ni.size();i++)
        {
            if(i==0)
                H=ni[0];
            else
                H=gcd(H,ni[i]);
        }
        H=expand(H);
        //对H因式分解
        cout<<H<<endl;
        cout<<"..........."<<endl;
        ex curh=factor(H);
        cout<<curh<<endl;
        cout<<"-------------"<<endl;
    }   
        //尝试先不带入xyzw的表达式，来加速,但是发现带入后计算的更快？？可能存在消项
        //因为在计算GCD的时候先带入表达式再计算GCD和先计算GCD再带入表达式求出结果完全一样
    ex quickH=KKS(N,p,k);
    quickH=expand(quickH);
    quickH=factor(quickH);
    // lst factors=ex_to<lst>(factor(quickH));
    cout<<quickH<<endl;
    cout<<"..........."<<endl;
    // checktime(st);
    vector<ex> h=factor_parser(quickH,reader);
    for(auto &i:h)
        if(!is_a<numeric>(i))//skip numeric
            cout<<i<<endl;

    //ALG2
    vector<int> order;
    for(auto &i:h){//处理每一个h
        int s_deg=i.degree(s);
        int t_deg=i.degree(t);
        
    }

    return 0;
}
