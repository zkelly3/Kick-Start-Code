#include<cstdio>
#include<vector>
#include<string>
#include<unordered_map>
using namespace std;

struct Point {
    int r;
    int p;
};

int dp(unordered_map<string, int> &mp, string state) {
    int S = state[0] - '0';
    int total = S * S;
    int pass = total + 1;
    Point a{state[pass]-'0', state[pass+1]-'0'};
    Point b{state[pass+2]-'0', state[pass+3]-'0'};
    pass += 4;
    
    char turn = state[pass];
    if (turn == 'A') state[pass] = 'B';
    else state[pass] = 'A';
    pass ++;
    
    int score = 0;
    for (int i=0; i<10; i++) {
        score *= 10;
        score += state[pass+1+i] - '0';
    }
    if (state[pass] == '-') score = -score;
    
    Point &now = (turn == 'A') ? a : b;
    Point &next = (turn == 'A') ? b : a;
    
    pass = 1;
    vector<Point> test_now;
    if (now.p > 0 && state[pass+now.r*now.r+now.p-1] == '1') test_now.push_back(Point{now.r, now.p-1});
    if (now.p < now.r*2 && state[pass+now.r*now.r+now.p+1] == '1') test_now.push_back(Point{now.r, now.p+1});
    if (now.p % 2 == 0 && now.r < S-1 && state[pass+(now.r+1)*(now.r+1)+now.p+1] == '1') test_now.push_back(Point{now.r+1, now.p+1});
    if (now.p % 2 == 1 && now.r > 0 && state[pass+(now.r-1)*(now.r-1)+now.p-1] == '1') test_now.push_back(Point{now.r-1, now.p-1});
    
    vector<Point> test_next;
    if (next.p > 0 && state[pass+next.r*next.r+next.p-1] == '1') test_next.push_back(Point{next.r, next.p-1});
    if (next.p < next.r*2 && state[pass+next.r*next.r+next.p+1] == '1') test_next.push_back(Point{next.r, next.p+1});
    if (next.p % 2 == 0 && next.r < S-1 && state[pass+(next.r+1)*(next.r+1)+next.p+1] == '1') test_next.push_back(Point{next.r+1, next.p+1});
    if (next.p % 2 == 1 && next.r > 0 && state[pass+(next.r-1)*(next.r-1)+next.p-1] == '1') test_next.push_back(Point{next.r-1, next.p-1});
    
    if (test_now.empty() && test_next.empty()) return score;
    else if (test_now.empty()) {
        unordered_map<string, int>::iterator it = mp.find(state);
        if (it != mp.end()) return it->second;
        int res = dp(mp, state);
        mp[state] = res;
        return res;
    }
    else {
        if (turn == 'A') score ++;
        else score --;
        pass = 1 + total + 4 + 1;
        if (score >= 0) state[pass] = ' ';
        else state[pass] = '-';
        pass ++;
        
        int tmp = (score >= 0) ? score : -score;
        for (int i=9; i>=0; i--) {
            state[pass+i] = tmp % 10 + '0';
            tmp /= 10;
        }
        
        pass = 1;
        int best;
        for (int i=0; i<test_now.size(); i++) {
            state[pass+test_now[i].r*test_now[i].r+test_now[i].p] = '0';
            if (turn == 'A') {
                state[1+total] = test_now[i].r + '0';
                state[1+total+1] = test_now[i].p + '0';
            }
            else {
                state[1+total+2] = test_now[i].r + '0';
                state[1+total+3] = test_now[i].p + '0';
            }
            
            int tmp;
            unordered_map<string, int>::iterator it = mp.find(state);
            if (it != mp.end()) tmp = it->second;
            else {
                tmp = dp(mp, state);
                mp[state] = tmp;
            }
            
            if (i == 0 || (turn == 'A' && best < tmp) || (turn == 'B' && best > tmp)) best = tmp;
            state[pass+test_now[i].r*test_now[i].r+test_now[i].p] = '1';
        }
        return best;
    }
}


int solve(int S, Point a, Point b, vector<Point> arr) {
    int total = S * S;
    int C = arr.size();
    int pass = 0;
    // S [S*S 0or1s] RA PA RB PB Turn score
    
    string state;
    state.push_back(S + '0');
    pass++;
    
    for (int i=0; i<total; i++) state.push_back('1');
    for (int i=0; i<C; i++) state[pass+arr[i].r*arr[i].r+arr[i].p] = '0';
    state[pass+a.r*a.r+a.p] = '0';
    state[pass+b.r*b.r+b.p] = '0';
    
    pass += total;
    state.push_back(a.r + '0');
    state.push_back(a.p + '0');
    state.push_back(b.r + '0');
    state.push_back(b.p + '0');
    state.push_back('A');
    state.push_back(' ');
    for (int i=0; i<10; i++) state.push_back('0');
    
    unordered_map<string, int> mp;
    int res = dp(mp, state);
    return res;
}

int main() {
    int T;
    scanf("%d", &T);
    for (int i=0; i<T; i++) {
        int S, RA, PA, RB, PB, C;
        scanf("%d %d %d %d %d %d", &S, &RA, &PA, &RB, &PB, &C);
        Point a{RA-1, PA-1};
        Point b{RB-1, PB-1};
        
        vector<Point> arr(C);
        for (int j=0; j<C; j++) {
            int R, P;
            scanf("%d %d", &R, &P);
            arr[j] = Point{R-1, P-1};
        }
        
        int ans = solve(S, a, b, arr);
        printf("Case #%d: %d\n", i+1, ans);
        
    }
    return 0;
}