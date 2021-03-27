#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;

int solve(vector<vector<int>> &arr, vector<vector<int>> &dp, int P) {
    int N = arr.size();
    int K = arr[0].size()-1;
    for (int i=1; i<=N; i++) {
        for (int j=1; j<=P; j++) {
            int tmp = 0;
            for (int k=0; k<=j; k++) {
                if (j - k <= K)
                    tmp = max(tmp, dp[i-1][k] + arr[i-1][j-k]);
            }
            dp[i][j] = tmp;
        }
    }
    int res = 0;
    for (int i=1; i<=N; i++) res = max(res, dp[i][P]);
    
    return res;
}

int main() {
    int T;
    scanf("%d", &T);
    for (int i=0; i<T; i++) {
        int N, K, P;
        scanf("%d %d %d", &N, &K, &P);
        
        vector<vector<int>> arr(N, vector<int>(K+1));
        for (int j=0; j<N; j++) {
            for (int k=0; k<K; k++) {
                int tmp;
                scanf("%d", &tmp);
                arr[j][k+1] = arr[j][k] + tmp;
            }
        }
        vector<vector<int>> dp(N+1, vector<int>(P+1));
        int ans = solve(arr, dp, P);
        printf("Case #%d: %d\n", i+1, ans);
    }
    return 0;
}