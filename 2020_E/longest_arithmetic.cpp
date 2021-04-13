#include<cstdio>
#include<vector>
using namespace std;

int solve(vector<int> &arr) {
    int N = arr.size();
    int cnt = 1;
    int cur = arr[1] - arr[0];
    int res = cnt;
    for (int i=2; i<arr.size(); i++) {
        if (arr[i] - arr[i-1] != cur) {
            cnt = 1;
            cur = arr[i] - arr[i-1];
        }
        else {
            cnt++;
        }
        
        res = max(res, cnt);
    }
    return res;
}

int main() {
    int T;
    scanf("%d", &T);
    for (int i=0; i<T; i++) {
        int N;
        scanf("%d", &N);
        
        vector<int> arr(N);
        for (int j=0; j<N; j++) {
            scanf("%d", &arr[j]);
        }
        int ans = solve(arr);
        printf("Case #%d: %d\n", i+1, ans+1);
    }
    return 0;
}