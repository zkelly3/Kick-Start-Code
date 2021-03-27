#include<cstdio>
#include<string>
#include<vector>
using namespace std;

char buf[2001];

struct Point {
    long long x;
    long long y;
    int index;
};

Point solve(string &str, int index) {
    int l = str.length();
    Point res;
    res.x = 0;
    res.y = 0;
    long long mod = 1000000000;
    int cnt = 1;
    while (index < l && str[index] !=')') {
        if (str[index] == 'N') res.y = (res.y - 1 + mod) % mod;
        else if (str[index] == 'S') res.y = (res.y + 1) % mod;
        else if (str[index] == 'W') res.x = (res.x - 1 + mod) % mod;
        else if (str[index] == 'E') res.x = (res.x + 1) % mod;
        else if (str[index] >= '0' && str[index] <= '9') {
            cnt = str[index] - '0';
        }
        else if (str[index] == '(') {
            Point new_res = solve(str, index+1);
            res.x = (res.x + new_res.x * cnt + mod) % mod;
            res.y = (res.y + new_res.y * cnt + mod) % mod;
            index = new_res.index + 1;
            cnt = 1;
            continue;
        }
        index++;
    }
    res.index = index;
    return res;
}

int main() {
    int T;
    scanf("%d", &T);
    for (int i=0; i<T; i++) {
        scanf("%s", buf);
        string str(buf);
        Point ans = solve(str, 0);
        printf("Case #%d: %lld %lld\n", i+1, ans.x+1, ans.y+1);
    }
    return 0;
}