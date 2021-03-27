#include<cstdio>
#include<vector>
using namespace std;

int solve(vector<int> &arr) {
    int K = arr.size();
    vector<vector<int>> dp(K, vector<int>(4));
    for (int i=1; i<K; i++) {
        for (int j=0; j<4; j++) {
            if (arr[i-1] > arr[i]) {
                if (j == 3) {
                    int small = dp[i-1][0];
                    for (int k=0; k<4; k++) small = min(small, dp[i-1][k]);
                    dp[i][j] = small + 1;
                }
                else {
                    int small = dp[i-1][j+1];
                    for (int k=j+1; k<4; k++) small = min(small, dp[i-1][k]);
                    dp[i][j] = small;
                }
            }
            else if (arr[i-1] == arr[i]) dp[i][j] = dp[i-1][j];
            else {
                if (j == 0) {
                    int small = dp[i-1][0];
                    for (int k=0; k<4; k++) small = min(small, dp[i-1][k]);
                    dp[i][j] = small + 1;
                }
                else {
                    int small = dp[i-1][0];
                    for (int k=0; k<j; k++) small = min(small, dp[i-1][k]);
                    dp[i][j] = small;
                }
            }
        }
    }
    int res = dp[K-1][0];
    for (int i=1; i<4; i++) res = min(res, dp[K-1][i]);
    return res;
}

int main() {
    int T;
    scanf("%d", &T);
    for (int i=0; i<T; i++) {
        int K;
        scanf("%d", &K);
        
        vector<int> arr(K);
        for (int j=0; j<K; j++) {
            scanf("%d", &arr[j]);
        }
        int ans = solve(arr);
        printf("Case #%d: %d\n", i+1, ans);
    }
    return 0;
}