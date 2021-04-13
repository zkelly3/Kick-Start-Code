#include<cstdio>
#include<utility>
#include<vector>
#include<queue>
using namespace std;

struct Toy {
    long long e;
    long long r;
};

class Comp {
    public:
        bool operator()(Toy a, Toy b) {
            return (a.e + a.r) < (b.e + b.r);
        }
};

pair<int, long long> solve(vector<Toy> arr) {
    int N = arr.size();
    long long sum = 0;
    for (int i=0; i<N; i++) {
        sum += arr[i].e;
    }
    
    long long best = sum;
    long long prev = 0;
    int best_r = 0;
    int cur_r = 0;
    priority_queue<Toy, vector<Toy>, Comp> q;
    for (int i=0; i<N; i++) {
        if (arr[i].e + arr[i].r <= sum) {
            if (best < sum + prev + arr[i].e) {
                best = sum + prev + arr[i].e;
                best_r = cur_r;
            }
            q.push(arr[i]);
            prev += arr[i].e;
        }
        else {
            sum -= arr[i].e;
            cur_r++;
            while (!q.empty() && (q.top().e + q.top().r > sum)) {
                Toy tmp = q.top();
                q.pop();
                prev -= tmp.e;
                sum -= tmp.e;
                cur_r++;
            }
        }
    }
    if (!q.empty()) {
        best = -1;
        best_r = cur_r;
    }
    return pair<int, long long>{best_r, best};
    
}

int main() {
    int T;
    scanf("%d", &T);
    for (int i=0; i<T; i++) {
        int N;
        scanf("%d", &N);
        
        vector<Toy> arr(N);
        for (int j=0; j<N; j++) {
            long long tmp1, tmp2;
            scanf("%lld %lld", &tmp1, &tmp2);
            arr[j] = Toy{tmp1, tmp2};
        }
        
        pair<int, long long> ans = solve(arr);
        
        printf("Case #%d: %d ", i+1, ans.first);
        if (ans.second == -1) printf("INDEFINITELY\n");
        else printf("%lld\n", ans.second);
    }
    return 0;
}