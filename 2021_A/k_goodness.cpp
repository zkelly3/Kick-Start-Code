#include<cstdio>
#include<vector>
#include<cmath>
using namespace std;

int solve(vector<char> &arr, int K) {
    int N = arr.size()-1;
    int cnt = 0;
    for (int i=0; i<(N/2); i++) {
        int j = N - i - 1;
        if (arr[i] != arr[j]) cnt++;
    }
    return abs(K - cnt);
}

int main() {
    int T;
    scanf("%d", &T);
    for (int i=0; i<T; i++) {
        int N, K;
        scanf("%d %d", &N, &K);
        
        vector<char> arr(N+1);
        scanf("%s", arr.data());
        int ans = solve(arr, K);
        printf("Case #%d: %d\n", i+1, ans);
    }
    return 0;
}