#include<bits/stdc++.h>
using namespace std;

// 最长子序列问题
class Solution {
public:
    int lcs(string text1, string text2);
    void Work();
};

int Solution::lcs(string text1, string text2) {
        vector< vector< int > > dp(text1.size() + 1, vector<int> (text2.size() + 1, 0));
        for (int i = 1; i <= text1.size(); i++) {
            for (int j = 1; j <= text2.size(); j++) {
                // 挨个字符进行比较
                if(text1[i - 1] == text2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                    // 测试
                    //cout << "dp[" << i - 1 << "][" << j - 1 << "] = " << dp[i - 1][j - 1] << std::endl;
                    //cout << "dp[" << i << "][" << j << "] = " << dp[i][j] << std::endl;
                }else {
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                    // 测试
                    //cout << "dp[" << i << "][" << j << "] = " << dp[i][j] << std::endl;
                }
            }
        }
        return dp[text1.size()][text2.size()];
    }

void Solution::Work() {
    string text1, text2;
    cin >> text1 >> text2;
    int result = lcs(text1, text2);
    cout << "result = " << result << endl;
}

int main() {
    Solution s;
    s.Work();
    system("pause");
    return 0;
}
