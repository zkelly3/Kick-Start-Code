#include<cstdio>
#include<vector>
using namespace std;

long long get(vector<long long> &bit, int i) {
    long long res = 0;
    while (i > 0) {
        res += bit[i];
        i -= (i & -i);
    }
    return res;
}

void update(vector<long long> &bit, int i, long long dlt) {
    int N = bit.size() - 1;
    while (i <= N) {
        bit[i] += dlt;
        i += (i & -i);
    }
    return;
}

long long solve(vector<int> &arr, vector<char> &w, vector<vector<int>> &cmd) {
    int N = arr.size();
    int Q = w.size();
    vector<long long> bit1(N+1);
    vector<long long> bit2(N+1);
    for (int i=0; i<N; i++) {
        int minus = ((i+1) % 2 == 1) ? 1 : -1;
        update(bit1, i+1, arr[i]*(i+1)*minus); 
    }
    for (int i=0; i<N; i++) {
        int minus = ((i+1) % 2 == 1) ? 1 : -1;
        update(bit2, i+1, arr[i]*minus); 
    }
    
    long long res = 0;
    for (int i=0; i<Q; i++) {
        if (w[i] == 'U') {
            int index = cmd[i][0];
            int minus = (index % 2 == 1) ? 1 : -1;
            long long delta = (cmd[i][1] - arr[index-1]) * minus;
            update(bit2, index, delta);
            delta *= index;
            update(bit1, index, delta);
            arr[index-1] = cmd[i][1];
        }
        else {
            int left = cmd[i][0];
            int right = cmd[i][1];
            long long ans1 = get(bit1, right) - get(bit1, left-1);
            long long ans2 = get(bit2, right) - get(bit2, left-1);
            int minus = (left % 2 == 1) ? 1 : -1;
            res += minus * (ans1 - (left-1) * ans2);
        }
    }
    return res;
}

int main() {
    int T;
    scanf("%d", &T);
    for (int i=0; i<T; i++) {
        int N, Q;
        scanf("%d %d", &N, &Q);
        
        vector<int> arr(N);
        for (int j=0; j<N; j++) {
            scanf("%d", &arr[j]);
        }
        vector<char> w(Q);
        vector<vector<int>> cmd(Q, vector<int>(2));
        char buf[3];
        for (int j=0; j<Q; j++) {
            scanf("%s %d %d", buf, &cmd[j][0], &cmd[j][1]);
            w[j] = buf[0];
        }
        
        long long ans = solve(arr, w, cmd);
        printf("Case #%d: %lld\n", i+1, ans);
    }
    return 0;
}