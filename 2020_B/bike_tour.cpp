#include<cstdio>
#include<vector>
using namespace std;

int solve(vector<int> &arr) {
    int N = arr.size();
    int res = 0;
    for (int i=1; i<N-1; i++) {
        if (arr[i] > arr[i-1] && arr[i] > arr[i+1]) res++;
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
        printf("Case #%d: %d\n", i+1, ans);
    }
    return 0;
}