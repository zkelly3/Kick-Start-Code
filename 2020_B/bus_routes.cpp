#include<cstdio>
#include<vector>
using namespace std;

long long solve(vector<long long> &arr, long long D) {
    int N = arr.size();
    long long res = D;
    for (int i=N-1; i>=0; i--) {
        res = (res / arr[i]) * arr[i];
    }
    return res;
}

int main() {
    int T;
    scanf("%d", &T);
    for (int i=0; i<T; i++) {
        int N;
        long long D;
        scanf("%d %lld", &N, &D);
        
        vector<long long> arr(N);
        for (int j=0; j<N; j++) {
            scanf("%lld", &arr[j]);
        }
        long long ans = solve(arr, D);
        printf("Case #%d: %lld\n", i+1, ans);
    }
    return 0;
}