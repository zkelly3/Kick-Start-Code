#include<cstdio>
#include<string>
using namespace std;

char from_buf[100001];

int countMin(char from, char to) {
	return min((from + 26 - to) % 26, (to + 26 - from) % 26);
}

int solve(string from, string to) {
    int res = 0;
	for (int i = 0; i < from.length(); i++) {
		int cur = 26;
		for (int j = 0; j < to.length(); j++) {
			cur = min(cur, countMin(from[i], to[j]));
		}
		res += cur;
	}
	return res;
}

int main() {
    int T;
    scanf("%d", &T);
    for (int i = 0; i < T; i++) {
		char to_buf[27];
		scanf("%s", from_buf);
		scanf("%s", to_buf);
        string from(from_buf);
		string to(to_buf);
		int ans = solve(from, to);
        
		printf("Case #%d: %d\n", i + 1, ans);
    }
    return 0;
}