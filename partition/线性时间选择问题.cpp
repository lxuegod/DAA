#include <bits/stdc++.h>
#define N 100
using namespace std;
class Solution {
private:
	//一维数组容器
	int num[N];
public:
	//线性选择算法寻找第k小的元素
	int linearTimeSelection(int,int,int);
	void Work();
};

void Solution::Work() {
    int n, k;
    cout << "输入数组大小:";
    cin >> n;
    if(n>N || n<1) {
        cout<<"预留空间不足或数组大小非法！";
        exit(0);
    }

    cout << "输入数组元素:";
    for(int i=0;i<n;i++) {
		cin >> num[i];
	}

    cout << "查找第几小的元素：";
    cin >> k;
    if(k > n || k < 1) {
        cout<<"查找位置非法！";
        exit(0);
    }
    cout << linearTimeSelection(0,n-1,k) << endl;
}
/*
    left 进行线性选择的首位下标
    right 进行线性选择的末尾下标
    k 寻找第k位小的元素
*/
int Solution::linearTimeSelection(int left,int right,int k){
    if(left >= right) return num[left];
    int point = num[left];
    int i = left,
        j = right+1;

    while(1){
        do{i++;}while(num[i] < point);
        do{j--;}while(num[j] > point);
        if(i>=j) break;
        swap(num[i],num[j]);
    }

    if(j-left+1 == k) return point;
    num[left] = num[j];
    num[j] = point;

    if(j-left+1 < k) return linearTimeSelection(j+1,right,k-(j+1-left));	//向右找
    return linearTimeSelection(left,j-1,k);	//向左找
}

int main() {
	Solution s;
	s.Work();
	system("pause");
	return 0;
}
