#include <bits/stdc++.h>
using namespace std;
 
#define N 100   //默认有99个物品。第一个不使用

class Solution{
private:
    int w[N];    //每个物品的重量
    int v[N];    //每个物品的价值
    int x[N];     //x[i]=1：物品i放入背包，0代表不放入
    int n,c;       //n：一共有多少物品，c：背包的最大容量
    
    //CurWeight 和 CurValue存储当前放入背包的数据，随着对解空间的不断深入而变化
    int CurWeight;  //当前放入背包的物品总重量
    int CurValue;   //当前放入背包的物品总价值
    
    //BestValue 和 BestX在找到一个叶子节点时进行 约束函数 判断，满足的话就连同修改储存的最优解
    int BestValue;  //最优值；当前的最大价值，初始化为0
    int BestX[N];       //最优解；BestX[i]=1代表物品i放入背包，0代表不放入

public:
    void input();
    void output();
    void backtrack(int t);
    void Work();
};

void Solution::input() {
    CurWeight = 0;
    CurValue = 0;
    BestValue = 0;
    cout<<"请输入物品的个数："<<endl;
    cin>>n;
    cout<<"请输入每个物品的重量及价值(如12 22):"<<endl;
    for(int i = 1; i <= n; i++) {
        cin>>w[i]>>v[i];
    }
    cout<<"请输入背包的容量："<<endl;
    cin>>c;
}

void Solution::output() {
    cout<<"最优值是:"<<BestValue<<endl;
    cout<<"(";
    for(int i=1;i<=n;i++) {
        cout<<BestX[i]<<" ";
    }
    cout<<")";
}

/*
*回溯函数 参数t表示当前处在第几层做抉择，t=1时表示当前在决定是否将第一个物品放入背包
*/
void Solution::backtrack(int t) {
    //叶子节点，输出结果
    if(t>n) {
        //如果找到了一个更优的解
        if(CurValue>BestValue) {
            //保存更优的值和解
            BestValue = CurValue;
            for(int i=1; i<=n; ++i) {
                BestX[i] = x[i];
            }
        }
    } else {
        //遍历当前节点的子节点：0 不放入背包，1放入背包
        for(int i=0; i<=1; ++i) {
            x[t]=i;
 
            if(i==0) {//不放入背包
                backtrack(t+1);
            }
            else {//放入背包
                //约束条件：放的下
                if((CurWeight+w[t])<=c) {
                    CurWeight += w[t];
                    CurValue += v[t];
                    backtrack(t+1);
                    CurWeight -= w[t];
                    CurValue -= v[t];
                }
            }
        }
    }
}

void Solution::Work() {
    input();
    backtrack(1);
    output();
}

int main() {
    Solution s;
    s.Work();
    system("pause");
    return 0;
}