#include<cstdio>
#include<vector>
#include<stack>
using namespace std;

struct TreeNode {
    int cnt;
    int idx;
    vector<TreeNode*> prevs;
    vector<TreeNode*> chs;
};

int makeTree(TreeNode* root) {
    root->cnt = 1;
    
    int prev = 0;
    if (root->prevs[prev] != nullptr) {
        while (prev < root->prevs[prev]->prevs.size() && root->prevs[prev]->prevs[prev] != nullptr) {
            root->prevs.push_back(root->prevs[prev]->prevs[prev]);
            prev++;
        }
    }
    for (int i=0; i<root->chs.size(); i++) root->cnt += makeTree(root->chs[i]);
    return root->cnt;
}

int dfs(int place, TreeNode* from, TreeNode* root, int k) {
    if (root->cnt >= k) {
        if (from == nullptr) {
            if (place == root->idx) return place + k;
            else return place - k;
        }
        else {
            if (place <= root->idx) return root->idx + (k - from->cnt);
            else return root->idx + 1 - (k - from->cnt);
        }
    }
    TreeNode* prev = root;
    for (int i = root->prevs.size() - 1; i >= 0; --i) {
        i = min(i, (int)(prev->prevs.size()) - 1);
        if (i < 0) break;
        if (prev->prevs[i]->cnt < k) prev = prev->prevs[i];
    }
    return dfs(place, prev, prev->prevs[0], k);
}


vector<int> solve(vector<int> &arr, vector<vector<int>> &qs) {
    int d = arr.size();
    vector<TreeNode*> doors(d);
    vector<int> l_l(d);
    vector<int> r_l(d);
    stack<int> l_s;
    stack<int> r_s;
    for (int i=0; i<d; i++) {
        doors[i] = new TreeNode{0, i, vector<TreeNode*>(1), vector<TreeNode*>()};
    }
    for (int i=0; i<d; i++) {
        while (!l_s.empty() && arr[l_s.top()] < arr[i]) l_s.pop();
        if (l_s.empty()) l_l[i] = -1;
        else l_l[i] = l_s.top();
        l_s.push(i);
    }
    for (int i=d-1; i>=0; i--) {
        while (!r_s.empty() && arr[r_s.top()] < arr[i]) r_s.pop();
        if (r_s.empty()) r_l[i] = -1;
        else r_l[i] = r_s.top();
        r_s.push(i);
    }
    
    for (int i=0; i<d; i++) {
        int l_largest = l_l[i];
        int r_largest = r_l[i];
        
        if (l_largest == -1 && r_largest == -1) continue;
        else if (l_largest == -1) {
            doors[i]->prevs[0] = doors[r_largest];
            doors[r_largest]->chs.push_back(doors[i]);
        }
        else if (r_largest == -1) {
            doors[i]->prevs[0] = doors[l_largest];
            doors[l_largest]->chs.push_back(doors[i]);
        }
        else {
            if (arr[r_largest] > arr[l_largest]) {
                doors[i]->prevs[0] = doors[l_largest];
                doors[l_largest]->chs.push_back(doors[i]);
            }
            else {
                doors[i]->prevs[0] = doors[r_largest];
                doors[r_largest]->chs.push_back(doors[i]);
            }
        }
    }

    TreeNode* root = nullptr;
    for (int i=0; i<d; i++) {
        if (doors[i]->prevs[0] == nullptr) {
            root = doors[i];
            break;
        }
    }
    makeTree(root);
    
    vector<int> res(qs.size());
    for (int i=0; i<qs.size(); i++) {
        if (qs[i][0]-1 == 0) res[i] = dfs(qs[i][0]-1, nullptr, doors[qs[i][0]-1], qs[i][1]-1);
        else if (qs[i][0]-1 == d) res[i] = dfs(qs[i][0]-1, nullptr, doors[qs[i][0]-2], qs[i][1]-1);
        else if (arr[qs[i][0]-2] > arr[qs[i][0]-1]) res[i] = dfs(qs[i][0]-1, nullptr, doors[qs[i][0]-1], qs[i][1]-1);
        else res[i] = dfs(qs[i][0]-1, nullptr, doors[qs[i][0]-2], qs[i][1]-1);
    }
    return res;
}

int main() {
    int T;
    scanf("%d", &T);
    for (int i=0; i<T; i++) {
        int N, Q;
        scanf("%d %d", &N, &Q);
        
        vector<int> arr(N-1);
        for (int j=0; j<N-1; j++) {
            scanf("%d", &arr[j]);
        }
        vector<vector<int>> qs(Q, vector<int>(2));
        for (int j=0; j<Q; j++) {
            scanf("%d %d", &qs[j][0], &qs[j][1]);
        }
        vector<int> ans = solve(arr, qs);
        
        printf("Case #%d:", i+1);
        for (int i=0; i<ans.size(); i++) printf(" %d", ans[i]+1);
        printf("\n");
    }
    return 0;
}