#include<cstdio>
#include<vector>
#include<algorithm>
#include<deque>
using namespace std;

long long solve(vector<long long> arr, int N) {
    int W = arr.size();
    sort(arr.begin(), arr.end());
    for (int i=0; i<W; i++) arr.push_back(arr[i] + N);
    long long res;
    int mid = (W-1) / 2;
    int head = 0;
    int tail = W - 1;
    int n_l = mid - head + 1;
    int n_r = tail - mid;
    
    long long left = 0;
    long long right = 0;
    for (int i=0; i<=mid; i++) left += arr[i];
    for(int i=mid+1; i<W; i++) right += arr[i];
    res = n_l * arr[mid] - left + right - n_r * arr[mid];
    
    for (int i=1; i<W; i++) {
        left -= arr[head];
        head++;
        mid++;
        left += arr[mid];
        
        right -= arr[mid];
        tail++;
        right += arr[tail];
        
        res = min(res, n_l * arr[mid] - left + right - n_r * arr[mid]);
    }
    
    return res;
}

int main() {
    int T;
    scanf("%d", &T);
    for (int i=0; i<T; i++) {
        int W, N;
        scanf("%d %d", &W, &N);
        
        vector<long long> arr(W);
        for (int j=0; j<W; j++) {
            scanf("%lld", &arr[j]);
            arr[j]--;
        }
        
        long long ans = solve(arr, N);
        printf("Case #%d: %lld\n", i+1, ans);
        
    }
    return 0;
} 