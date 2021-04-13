#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;

struct Stone {
    int S;
    int E;
    int L;
};

bool comp(Stone a, Stone b) {
    return (a.S * b.L) < (b.S * a.L);
}

int solve(vector<Stone> &arr) {
    int N = arr.size();
    sort(arr.begin(), arr.end(), comp);
    
    int total = 0;
    for (int i=0; i<N; i++) total += arr[i].S;
    
    vector<vector<int>> dp(total*2+2, vector<int>(N));
    for(int i=total; i>=0; i--) {
        dp[i][N-1] = max(0, arr[N-1].E - i*arr[N-1].L);
        for(int j=N-2; j>=0; j--) {
            dp[i][j] = max(dp[i][j+1], arr[j].E - i*arr[j].L + dp[i+arr[j].S][j+1]);
        }
    }
    
    return dp[0][0];
}

int main() {
    int T;
    scanf("%d", &T);
    for (int i=0; i<T; i++) {
        int N;
        scanf("%d", &N);
        
        vector<Stone> arr(N);
        for (int j=0; j<N; j++) {
            int tmp1, tmp2, tmp3;
            scanf("%d %d %d", &tmp1, &tmp2, &tmp3);
            arr[j] = Stone{tmp1, tmp2, tmp3};
        }
        int ans = solve(arr);
        printf("Case #%d: %d\n", i+1, ans);
    }
    return 0;
}