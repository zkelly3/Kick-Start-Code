#include<cstdio>
#include<string>
using namespace std;

char buf[100010];


int solve(string s) {
    int N = s.length();
    int res = 0;
    
    string k_tgt = "KICK";
    int k_begin = 0;
    int k_cnt = 0;
    bool in_k = false;
    
    string s_tgt = "START";
    int s_begin = 0;
    int s_cnt = 0;
    bool in_s = false;
    
    for (int i=0; i<N; i++) {
        if (in_s && s[i] != s_tgt[i-s_begin]) in_s = false;
        if (in_s && i-s_begin == 4) {
            s_cnt++;
            in_s = false;
            res += k_cnt;
        }
        if (!in_s && s[i] == s_tgt[0]) {
            s_begin = i;
            in_s = true;
        }
        
        if (in_k && s[i] != k_tgt[i-k_begin]) in_k = false;
        if (in_k && i-k_begin == 3) {
            k_cnt++;
            in_k = false;
        }
        if (!in_k && s[i] == k_tgt[0]) {
            k_begin = i;
            in_k = true;
        }
    }
    return res;
}

int main() {
    int T;
    scanf("%d", &T);
    for (int i=0; i<T; i++) {
        scanf("%s", buf);
        string s(buf);
        int ans = solve(s);
        printf("Case #%d: %d\n", i+1, ans);
    }
    return 0;
}