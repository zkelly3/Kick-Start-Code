#include<cstdio>
#include<vector>
using namespace std;

int solve(vector<int> &arr, int K) {
    int N = arr.size();
    int res = 0;
    bool rec = false;
    int start = -1;
    for (int i=0; i<N; i++) {
        if (rec && arr[i] != (K - i + start)) rec = false;
        if (rec && arr[i] == 1) {
            res ++;
            rec = false;
        }
        if (arr[i] == K) {
            rec = true;
            start = i;
        }
    }
    return res;
}

int main() {
    int T;
    scanf("%d", &T);
    for (int i=0; i<T; i++) {
        int N, K;
        scanf("%d %d", &N, &K);
        
        vector<int> arr(N);
        for (int j=0; j<N; j++) {
            scanf("%d", &arr[j]);
        }
        int ans = solve(arr, K);
        printf("Case #%d: %d\n", i+1, ans);
    }
    return 0;
}