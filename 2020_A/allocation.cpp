#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;

int solve(vector<int> &arr, int B) {
    sort(arr.begin(), arr.end());
    int tmp = 0;
    int res = 0;
    for (int i=0; i<arr.size(); i++) {
        tmp += arr[i];
        if (tmp <= B) res++;
        else break;
    }
    return res;
}

int main() {
    int T;
    scanf("%d", &T);
    for (int i=0; i<T; i++) {
        int N, B;
        scanf("%d %d", &N, &B);
        
        vector<int> arr(N);
        for (int j=0; j<N; j++) {
            scanf("%d", &arr[j]);
        }
        int ans = solve(arr, B);
        printf("Case #%d: %d\n", i+1, ans);
    }
    return 0;
}