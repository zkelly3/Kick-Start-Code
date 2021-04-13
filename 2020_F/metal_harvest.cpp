#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;

struct Time {
    int begin;
    int end;
};

bool comp(Time a, Time b) {
    return a.begin < b.begin;
}

int solve(vector<Time> arr, int K) {
    int N = arr.size();
    sort(arr.begin(), arr.end(), comp);
    
    int res = 0;
    long long cur = 0;
    for (int i=0; i<N; i++) {
        if (cur >= arr[i].end) continue;
        else if (cur >= arr[i].begin) {
            int tmp = (arr[i].end - cur - 1) / K + 1;
            res += tmp;
            cur += tmp * K;
        }
        else {
            cur = arr[i].begin;
            int tmp = (arr[i].end - cur - 1) / K + 1;
            res += tmp;
            cur += tmp * K;
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
        
        vector<Time> arr(N);
        for (int j=0; j<N; j++) {
            int tmp1, tmp2;
            scanf("%d %d", &tmp1, &tmp2);
            arr[j] = Time{tmp1, tmp2};
        }
        
        int ans = solve(arr, K);
        printf("Case #%d: %d\n", i+1, ans);
    }
    return 0;
}