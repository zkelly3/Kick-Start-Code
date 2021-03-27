#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;

bool canCut(vector<int> &arr, int K, int tgt) {
    int cut = 0;
    for (int i=1; i<arr.size(); i++) {
        int tmp = arr[i] - arr[i-1];
        while (tmp > tgt) {
            cut++;
            tmp -= tgt;
        }
    }
    return cut <= K;
}

int solve(vector<int> &arr, int K) {
    int tail = 1;
    for (int i=1; i<arr.size(); i++) tail = max(tail+1, arr[i] - arr[i-1]+1);
    int head = 0;
    while (tail - head > 1) {
        int middle = (head + tail) / 2;
        if (canCut(arr, K, middle)) tail = middle;
        else head = middle;
    }
    return tail;
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