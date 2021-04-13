#include<cstdio>
#include<string>
#include<vector>
using namespace std;
char buf[100001];

struct Interval {
    int from;
    int to;
};

int solve(string str, vector<Interval> &arr) {
    int N = str.length();
    int Q = arr.size();
    
    vector<vector<int>> mp(N+1, vector<int>(26));
    for (int i=0; i<N; i++) {
        for (int j=0; j<26; j++) {
            if (str[i] - 'A' == j) {
                mp[i+1][j] = mp[i][j] + 1;
            }
            else {
                mp[i+1][j] = mp[i][j];
            }
        }
    }
    
    int res = 0;
    for (int i=0; i<Q; i++) {
        int cnt = 0;
        Interval tmp = arr[i];
        for (int j=0; j<26; j++) {
            if ((mp[tmp.to][j] - mp[tmp.from-1][j]) % 2 != 0) cnt ++;
        }
        if (cnt <= 1) res++;
    }
    return res;
}

int main() {
    int T;
    scanf("%d", &T);
    for (int i=0; i<T; i++) {
        int N, Q;
        scanf("%d %d", &N, &Q);
        
        string str;
        scanf("%s", buf);
        str = string(buf);
        
        vector<Interval> arr(Q);
        for (int j=0; j<Q; j++) {
            int tmp1, tmp2;
            scanf("%d %d", &tmp1, &tmp2);
            arr[j] = Interval{tmp1, tmp2};
        }
        int ans = solve(str, arr);
        printf("Case #%d: %d\n", i+1, ans);
    }
    return 0;
}