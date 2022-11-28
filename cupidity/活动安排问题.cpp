#include <bits/stdc++.h>
#define N 100
using namespace std;
class Solution {
public:
    int ActiveManage(int s[], int f[], int B[], int n);
    void Work();
};

void Solution::Work() {
    int s[N], f[N], B[N] = {0};
    int m;
    cout << "请输入活动数：" << endl;
    cin >> m;
    // int s[N] = {1,3,0,5,3,5,6,8,8,2,12};
    // int f[N] = {4,5,6,7,8,9,10,11,12,13,14};
    cout << "请依次输入开始时间：" << endl;
    for (int i = 0; i < m; i++) {
        cin >> s[i];
    }
    cout << "请依次输入结束时间：" << endl;
    for (int i = 0; i < m; i++) {
        cin >> f[i];
    }

    int k = ActiveManage(s, f, B, m);
    cout << "最多可安排的活动个数是：" << k << endl;
    cout << "具体的活动是：";
    for (int i = 0; i < m; i++) {
        if (B[i] == 1) {
            cout<<"活动" << i << ":（" << s[i] << "," << f[i] << "）  ";
        }   
    }   
    cout << endl;
}

int Solution::ActiveManage(int s[], int f[], int B[], int n) {
    int i, j, count;
    B[0] = 1;
    j = 1;
    count = 1;
    for (i = 1; i < n; i++) {//依次考察每一个活动
        if (s[i] >= f[j]) {//活动i与集合B中最后结束的活动j相容
            B[i] = 1;
            j = i;
            count++;
        }  else {
            B[i] = 0;
        }    
    }
    //  返回已安排的活动个数
    return count;                          
}

int main() {
    Solution s;
    s.Work();
    system("pause");
    return 0;
}