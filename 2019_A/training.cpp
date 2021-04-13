#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;

int solve(vector<int> &arr, int P) {
    int N = arr.size();
    sort(arr.begin(), arr.end());

    int tmp = 0;
    for (int i=P-2; i>=0; i--) tmp += arr[P-1] - arr[i];
    int res = tmp;
    
    for (int i=1; i+P-1<N; i++) {
        tmp += (P-1)*(arr[i+P-1]-arr[i+P-2]) - (arr[i+P-2] - arr[i-1]);
        res = min(res, tmp);
    }
    return res;
}

int main() {
    int T;
    scanf("%d", &T);
    for (int i=0; i<T; i++) {
        int N, P;
        scanf("%d %d", &N, &P);
        
        vector<int> arr(N);
        for (int j=0; j<N; j++) {
            scanf("%d", &arr[j]);
        }
        int ans = solve(arr, P);
        printf("Case #%d: %d\n", i+1, ans);
    }
    return 0;
}