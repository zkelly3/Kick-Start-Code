#include<cstdio>
#include<vector>
using namespace std;


long long solve(vector<vector<long long>> arr) {
    int N = arr.size();
    long long res = 0;
    for (int i=0; i<=2*N-2; i++) {
        int r = min(i, N-1);
        for (int j=r; j>=0&&i-j<N; j--) {
            if (j-1 >= 0 && (i-j-1) >= 0) {
                arr[j][i-j] += arr[j-1][i-j-1];
            }
            res = max(res, arr[j][i-j]);
        }
    }
    return res;
}

int main() {
    int T;
    scanf("%d", &T);
    for (int i=0; i<T; i++) {
        int N;
        scanf("%d", &N);
        
        vector<vector<long long>> arr(N, vector<long long>(N));
        for (int j=0; j<N; j++) {
            for (int k=0; k<N; k++) {
                scanf("%lld", &arr[j][k]);
            }
        }
        
        long long ans = solve(arr);
        printf("Case #%d: %lld\n", i+1, ans);
    }
    return 0;
}