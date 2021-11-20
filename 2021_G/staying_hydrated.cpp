#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;

struct Box {
	int s_x;
	int s_y;
	int b_x;
	int b_y;
};

struct Line {
	int x_y;
	bool is_down_left;
};

struct Point {
	int x;
	int y;
};

bool comp(Line &a, Line &b) {
	if (a.x_y < b.x_y) return true;
	if (a.x_y > b.x_y) return false;
	return a.is_down_left < b.is_down_left;
}

int min_pos(int K, vector<Line> &lines) {
	long long s_sum = 0;
	long long b_sum = 0;
	int pos_box = K;
	int neg_box = 0;
	for (Line &line : lines)
		if (line.is_down_left) s_sum += line.x_y;
	sort(lines.begin(), lines.end(), comp);
	
    int ans = lines[0].x_y;
	long long cur_sum = s_sum - (long long) pos_box * ans;
	
	
	for (int i = 0; i < 2 * K; i++) {
		Line &now = lines[i];
		if (now.is_down_left) {
			pos_box--;
			s_sum -= now.x_y;
		}
		else {
			neg_box++;
			b_sum += now.x_y;
		}
		long long tmp = s_sum - (long long) pos_box * now.x_y + (long long) neg_box * now.x_y - b_sum;
		if (tmp < cur_sum || (tmp == cur_sum && now.x_y < ans)) {
			cur_sum = tmp;
			ans = now.x_y;
		}
	}
	return ans;
}

Point solve(int K, vector<Box> &arr) {
    // ver: left to right, hor: down to top
	vector<Line> ver, hor;
	for (int i = 0; i < K; i++) {
		ver.push_back(Line{arr[i].s_x, true});
		ver.push_back(Line{arr[i].b_x, false});
		hor.push_back(Line{arr[i].s_y, true});
		hor.push_back(Line{arr[i].b_y, false});
	}
	return {min_pos(K, ver), min_pos(K, hor)};
}

int main() {
    int T;
    scanf("%d", &T);
    for (int i = 0; i < T; i++) {
        int K;
        scanf("%d", &K);
        
		vector<Box> arr(K);
		for (int j = 0; j < K; j++) {
			int a, b, c, d;
			scanf("%d %d %d %d", &a, &b, &c, &d);
			arr[j] = Box{a, b, c, d};
		}
        
        Point ans = solve(K, arr);
		printf("Case #%d: %d %d\n", i + 1, ans.x, ans.y);
    }
    return 0;
}