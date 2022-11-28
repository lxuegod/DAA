#include <bits/stdc++.h>
#define M 1000
#define N 10
using namespace std;
class Solution {
public:
    int Partition(int nums[], int  first, int end);
    void QuickSort(int nums[], int first, int end);
    void Work();
};

void Solution::Work() {
    int nums[N];
    srand(int(time(0)));
    for (int i = 0; i < N; i++) {
        nums[i] = (rand() % M);
    }
    cout<<"随机生成10个数字，排序前："<<endl;
    for (int i = 0; i < N; i++) {
        cout << nums[i] << " ";
    }
    cout << endl;
    
    QuickSort(nums, 0, N-1);
    cout << "排序后：" << endl;
    for (int i = 0; i < N; i++) {
        cout<<nums[i]<<" ";
    }
    cout << endl;
}

//  划分
int Solution::Partition(int nums[ ], int first, int end) {
    //  初始化待划分区间
    int i = first, j=end;                       
    while (i < j)
    {
        while (i < j && nums[i] <= nums[j]) {
            //  右侧扫描
            j--; 
        }    

        if (i < j) {
            int temp = nums[i];
            nums[i] = nums[j];
            nums[j] = temp;     // 将较小记录交换到前面
            i++;
        }

        while (i < j && nums[i] <= nums[j]) {
            //  左侧扫描
            i++;         
        }
            
        if (i < j) {
            int temp = nums[i];
            nums[i] = nums[j];
            nums[j] = temp;     // 将较大记录交换到后面
            j--;
        }
    }
    // 返回轴值记录的位置
    return i;                                
}

//  快速排序
void Solution::QuickSort(int nums[], int first, int end) {
    int pivot;
    if (first < end) {
        pivot = Partition(nums, first, end);    // 划分，pivot是轴值在序列中的位置
        QuickSort(nums, first, pivot-1);      //   求解子问题1，对左侧子序列进行快速排序
        QuickSort(nums, pivot+1, end);      // 求解子问题2，对右侧子序列进行快速排序
    }
}

int main() {
    Solution s;
    s.Work();
    system("pause"); 
    return 0;
}
