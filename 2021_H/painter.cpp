#include<cstdio>
#include<vector>
#include<string>
using namespace std;

char buf[100001];

int solve(string s, int l) {
    vector<int> arr(l);
	for (int i = 0; i < l; i++) {
		if (s[i] == 'U') arr[i] = 0;
		else if (s[i] == 'R') arr[i] = 1;
		else if (s[i] == 'B') arr[i] = 2;
		else if (s[i] == 'Y') arr[i] = 4;
		else if (s[i] == 'P') arr[i] = 3;
		else if (s[i] == 'O') arr[i] = 5;
		else if (s[i] == 'G') arr[i] = 6;
		else if (s[i] == 'A') arr[i] = 7;
	}
	
	int res = 0;
	for (int i = 0; i < l;) {
		if (arr[i] == 0) {
			i++;
			continue;
		}
		res++;
		int color = 1;
		while ((arr[i] & color) == 0) color *= 2;
		for (int j = i; j < l && (arr[j] & color) != 0; j++) {
			arr[j] -= color;
		}
	}
	return res;
}

int main() {
    int T;
    scanf("%d", &T);
    for (int i = 0; i < T; i++) {
		int l;
		scanf("%d", &l);
		scanf("%s", buf);
        string s(buf);
		int ans = solve(s, l);
        
		printf("Case #%d: %d\n", i + 1, ans);
    }
    return 0;
}