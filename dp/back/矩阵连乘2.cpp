#include<iostream>
using namespace std;
 
#define N 7  //N为7，实际表示有6个矩阵
/*
*矩阵链构造函数：构造m[][]和s[][]
*m中存储的值是计算出来的最小乘法次数，比如m[1][5]就是A1A2A3A4A5的最小乘法次数
*s中存储的是获取最小乘法次数时的断链点，s[1][5]对应的就是如何拆分A1A2A3A4A5,
*比如S[1][5]=3可表示：(A1A2A3)(A4A5)，当然内部断链还会继续划分A1A2A3
*/
int MatrixChain(int *p, int n, int m[][N], int s[][N]){
    for(int i=1;i<=n;i++){     //矩阵链中只有一个矩阵时，次数为0，注意m[0][X]时未使用的
        m[i][i]=0;
    }
    for(int r=2;r <= n;r++){    //矩阵链长度,从长度为2开始
        for(int i=1;i <= n-r+1;i++){    //根据链长度，控制链最大的可起始点
            int j = i+(r-1);  //矩阵链的末尾矩阵，注意r-1，因为矩阵链为2时，实际是往右+1
            m[i][j] = m[i][i]+m[i+1][j]+p[i-1]*p[i]*p[j];   //先设置最好的划分方法就是直接右边开刀，后续改正，也可合并到下面的for循环中
            s[i][j]=i;
            for(int k=i+1;k < j;k++){   //这里面将断链点从i+1开始，可以断链的点直到j-1为止
                int t = m[i][k]+m[k+1][j]+p[i-1]*p[k]*p[j];
                if(t<m[i][j]){
                    m[i][j] = t;
                    s[i][j] = k;
                }
 
            }
 
        }
    }
}
/*
*追踪函数：根据输入的i,j限定需要获取的矩阵链的始末位置，s存储断链点
*/
void Traceback(int i,int j, int s[][N]){
    if(i==j)       //回归条件
    {
        cout<<"A"<<i;
    }
    else       //按照最佳断点一分为二，接着继续递归
    {
        cout<<"(";
        Traceback(i,s[i][j],s);
        Traceback(s[i][j]+1,j,s);
        cout<<")";
    }
}
int main(){
	int p[N]={30,35,15,5,10,20,25};
	int m[N][N],s[N][N];
 
	MatrixChain(p,N-1,m,s);//N-1因为只有六个矩阵
    Traceback(1,6,s);
	return 0;
}
 