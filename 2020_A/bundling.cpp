#include<cstdio>
#include<string>
#include<vector>
using namespace std;

struct Node {
    int depth;
    char val;
    int cnt;
    vector<Node*> children;
};

int dfs(Node *root, int K, int &res) {
    int total = root->cnt;
    for (int i=0; i<root->children.size(); i++) {
        total += dfs(root->children[i], K, res);
    }
    res += root->depth * (total / K);
    return total % K;
}

int solve(vector<string> &arr, int K) {
    Node *root = new Node{0, '\0', 0, vector<Node*>()};
    for (int i=0; i<arr.size(); i++) {
        Node *tmp = root;
        for (int j=0; j<arr[i].length(); j++) {
            int idx = 0;
            while (idx < tmp->children.size()) {
                if (tmp->children[idx]->val == arr[i][j]) break;
                idx++;
            }
            if (idx == tmp->children.size()) {
                Node *child = new Node{tmp->depth+1, arr[i][j], 0, vector<Node*>()};
                tmp->children.push_back(child);
            }
            tmp = tmp->children[idx];
        }
        tmp->cnt++;
    }
    int res = 0;
    dfs(root, K, res);
    return res;
}

int main() {
    vector<char> buf(2000010);
    int T;
    scanf("%d", &T);
    for (int i=0; i<T; i++) {
        int N, K;
        scanf("%d %d", &N, &K);
        
        vector<string> arr;
        arr.reserve(N);
        for (int j=0; j<N; j++) {
            scanf("%s", buf.data());
            arr.emplace_back(buf.data());
        }
        int ans = solve(arr, K);
        printf("Case #%d: %d\n", i+1, ans);
    }
    return 0;
}