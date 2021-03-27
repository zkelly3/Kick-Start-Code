#include<cstdio>
#include<vector>
#include<deque>
using namespace std;

struct TreeNode {
    vector<TreeNode*> children;
    double prob_a;
    double prob_b;
};

deque<double> dfs(TreeNode* root, double base, int cnt, bool is_a) {
    if (root->children.empty()) {
        deque<double> res;
        res.push_back(base);
        if (is_a) root->prob_a = base;
        else root->prob_b = base;
        return res;
    }
    vector<deque<double>> ch_res(root->children.size());
    int size = -1;
    int index = -1;
    for (int i=0; i<ch_res.size(); i++) {
        ch_res[i] = dfs(root->children[i], base, cnt, is_a);
        if ((int)(ch_res[i].size()) > size) {
            index = i;
            size = ch_res[i].size();
        }
    }
    for (int i=0; i<ch_res.size(); i++) {
        if (i != index) {
            for (int j=0; j<ch_res[i].size(); j++) {
                ch_res[index][j] += ch_res[i][j];
            }
        }
    }
    ch_res[index].push_front(base);
    if (cnt < ch_res[index].size()) ch_res[index][0] += ch_res[index][cnt];
    if (is_a) root->prob_a = ch_res[index][0];
    else root->prob_b = ch_res[index][0];
    return std::move(ch_res[index]);
}


double solve(vector<int> &arr, int A, int B) {
    int N = arr.size() + 1;
    vector<TreeNode*> nodes(N);
    nodes[0] = new TreeNode{vector<TreeNode*>(), 0, 0};
    for (int i=1; i<N; i++) {
        nodes[i] = new TreeNode{vector<TreeNode*>(), 0, 0};
        nodes[arr[i-1]-1]->children.push_back(nodes[i]);
    }

    dfs(nodes[0], 1.0/N, A, true);
    dfs(nodes[0], 1.0/N, B, false);
    
    double res = 0;
    for(int i=0; i<N; i++) {
        res += nodes[i]->prob_a + nodes[i]->prob_b - (nodes[i]->prob_a * nodes[i]->prob_b);
    }
    
    return res;
}

int main() {
    int T;
    scanf("%d", &T);
    for (int i=0; i<T; i++) {
        int N, A, B;
        scanf("%d %d %d", &N, &A, &B);
        
        vector<int> arr(N-1);
        for (int j=0; j<N-1; j++) {
            scanf("%d", &arr[j]);
        }
        double ans = solve(arr, A, B);
        printf("Case #%d: %f\n", i+1, ans);
    }
    return 0;
}