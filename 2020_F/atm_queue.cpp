#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;

struct ATM {
    int index;
    int val;
    int x;
};

bool comp(ATM a, ATM b) {
    if (((a.val-1) / a.x) > ((b.val-1) / b.x)) return false;
    else if (((a.val-1) / a.x) < ((b.val-1) / b.x)) return true;
    else if (a.index > b.index) return false;
    else return true;
}

vector<int> solve(vector<ATM> arr) {
    int N = arr.size();
    vector<int> res(N);
    sort(arr.begin(), arr.end(), comp);
    for(int i=0; i<N; i++) res[i] = arr[i].index;
    return res;
}

int main() {
    int T;
    scanf("%d", &T);
    for (int i=0; i<T; i++) {
        int N, X;
        scanf("%d %d", &N, &X);
        
        vector<ATM> arr(N);
        for (int j=0; j<N; j++) {
            int tmp;
            scanf("%d", &tmp);
            arr[j] = ATM{j+1, tmp, X};
        }
        
        vector<int> ans = solve(arr);
        
        printf("Case #%d:", i+1);
        for (int i=0; i<ans.size(); i++) printf(" %d", ans[i]);
        printf("\n");
    }
    return 0;
}