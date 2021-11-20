#include<cstdio>
#include<algorithm>
#include<string>
using namespace std;

char buf[10010];

bool solve(int N, int D, int C, int M, string line) {
    int mx = -1;
	for (int i = 0; i < N; i++) {
		if (line[i] == 'D') mx = i;
	}
	long long tmp_d = D;
	long long tmp_c = C;
	for (int i = 0; i < N; i++) {
		if (i > mx) break;
		if (line[i] == 'D') {
			if (tmp_d <= 0) return false;
			tmp_d--;
			tmp_c += M;
		}
		else {
			if (tmp_c <= 0) return false;
			tmp_c--;
		}
	}
	return true;
}

int main() {
    int T;
    scanf("%d", &T);
    for (int i=0; i<T; i++) {
        int N, D, C, M;
        scanf("%d %d %d %d", &N, &D, &C, &M);
        
		scanf("%s", buf);
		string line(buf);
        
        bool ans = solve(N, D, C, M, line);
		if (ans) printf("Case #%d: YES\n", i + 1);
		else printf("Case #%d: NO\n", i + 1);
    }
    return 0;
}