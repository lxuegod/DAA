#include <bits/stdc++.h>
#include <math.h>
#include<algorithm>
#define N 100
using namespace std;
struct point {           //点结构
    double x, y;
};

//按y升排序辅助函数
bool cmp(point a, point b) {          
    return a.y < b.y;
}

//按x升排序辅助函数
bool cmp2(point a, point b) {          
    return a.x < b.x;
}

class Solution {
public:
    double Distance(point a, point b);
    double closestPoint(point s[], int low, int high, point rec[]);
    void Work();

};

double Solution::Distance(point a, point b) {
    return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}

double Solution::closestPoint(point s[], int low, int high, point rec[]) {
    double d1, d2, d3, d;
    int mid, i, j, index;
    double x1, y1, x2, y2;         //记录点对的位置
    point P[high-low+1], temp1[2], temp2[2], temp3[2];         //辅助空间
    if (high-low == 1) {             //两个点的情况
            rec[0].x = s[low].x;
            rec[0].y = s[low].y;
            rec[1].x = s[high].x;
            rec[1].y = s[high].y;
            return Distance(s[low], s[high]);
        }
    if (high-low == 2) {            //三个点的情况
        d1 = Distance(s[low], s[low+1]);
        d2 = Distance(s[low+1], s[high]);
        d3 = Distance(s[low], s[high]);
        if((d1 < d2) && (d1 < d3)) {
            rec[0].x = s[low].x;
            rec[0].y = s[low].y;
            rec[1].x = s[low+1].x;
            rec[1].y = s[low+1].y;
            return d1;
        }
        else if(d2 < d3) {
            rec[0].x = s[low+1].x;
            rec[0].y = s[low+1].y;
            rec[1].x = s[high].x;
            rec[1].y = s[high].y;
            return d2;
        }
        else {
            rec[0].x = s[low].x;
            rec[0].y = s[low].y;
            rec[1].x = s[high].x;
            rec[1].y = s[high].y;
            return d3;
        }
    }
    mid = (low+high)/2;       //其他情况递归
    d1 = closestPoint(s, low, mid, rec);
    temp1[0] = rec[0];
    temp1[1] = rec[1];
    d2 = closestPoint(s, mid+1, high, rec);
    temp2[0] = rec[0];
    temp2[1] = rec[1];
    if(d1 < d2) {
        d = d1;
        rec[0] = temp1[0];
        rec[1] = temp1[1];
    }
    else {
        d = d2;
        rec[0] = temp2[0];
        rec[1] = temp2[1];
    }
    index = 0;
    for (i = mid;(i >= low) && ((s[mid].x-s[i].x) < d);i--) {//点集合p1
        P[index++] = s[i];
    }   
    for (i = mid+1;(i <= high) && ((s[i].x-s[mid].x) < d);i++) {//点集合p2
        P[index++] = s[i];
    }     
    sort(P, P+index, cmp);                    //升序排列
    for(i = 0;i < index;i++) {
        for(j = j+1; j < index; i++) {
            if((P[j].y-P[i].y) >= d) {
                break;
            } else {
                d3 = Distance(P[i], P[j]);
                if(d3 < d) {
                    rec[0].x = P[i].x;
                    rec[0].y = P[i].y;
                    rec[1].x = P[j].x;
                    rec[1].y = P[j].y;
                    d = d3;
                }
            }
        }
    }
    return d;
}

void Solution::Work() {
    point p[N];            //设定点的集合
    int n;
    double minDist;
    cout << "输入点的个数：\n";      //输入点的个数
    cin>>n;
    cout << "输入点集:（x, y）\n";
    for(int i = 0;i < n;i++) {
        cin >> p[i].x >> p[i].y;
    }
        
    sort(p, p+n, cmp2);      //对输入的点先排序
    point index[2];
    minDist = closestPoint(p, 0, n-1, index);
    cout << "最小距离点对为：(" << index[0].x << ", " << index[0].y << "), (" << index[1].x << ", " << index[1].y << ")" << endl;
    cout << "最小距离为：" << endl << minDist << endl;      //输出点对的最小问题
}

int main() {
    Solution s;
    s.Work();
    system("pause");
    return 0;
}

