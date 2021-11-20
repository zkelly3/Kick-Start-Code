#include<cstdio>
#include<string>
#include<set>
#include<vector>
using namespace std;

struct Node {
	char val;
	Node* prev;
	Node* next;
};

char buf[500001];

void deleteNode(Node* root) {
	if (root == nullptr) return;
	deleteNode(root->next);
	delete root;
}

string solve(string str, int l) {
	Node* fake_head = new Node{' ', nullptr, nullptr};
	Node* head = fake_head;
	for (int i = 0; i < l; i++) {
		Node* cur = new Node{str[i], head, nullptr};
		head->next = cur;
		head = head->next;
	}
	
	vector<set<Node*>> arr(10);
	head = fake_head->next;
	while (head != nullptr && head->next != nullptr) {
		if (head->val == '9' && head->next->val == '0') arr[9].insert(head);
		else if (head->val + 1 == head->next->val) arr[head->val - '0'].insert(head);
		head = head->next;
	}

	bool finished = false;
	while (!finished) {
		finished = true;
		for (int i = 0; i < 10; i++) {
			for (auto it = arr[i].begin(); it != arr[i].end(); it++) {
				finished = false;
				Node* cur = *it;
				Node* cur_prev = cur->prev;
				Node* cur_next = cur->next;
				Node* new_prev = cur_prev;
				Node* new_next = cur_next->next;
				Node* tmp = new Node{'0' + (i + 2) % 10, new_prev, new_next};
				new_prev->next = tmp;
				if (new_next != nullptr) new_next->prev = tmp;
				
				if (cur_prev != fake_head && cur_prev->val == '9' && cur->val == '0') arr[9].erase(arr[9].find(cur_prev));
				else if (cur_prev != fake_head && cur_prev->val + 1 == cur->val) arr[cur_prev->val - '0'].erase(arr[cur_prev->val - '0'].find(cur_prev));
				if (new_next != nullptr && cur_next->val == '9' && new_next->val == '0') arr[9].erase(arr[9].find(cur_next));
				else if (new_next != nullptr && cur_next->val + 1 == new_next->val) arr[cur_next->val - '0'].erase(arr[cur_next->val - '0'].find(cur_next));
				
				if (new_prev != fake_head && new_prev->val == '9' && tmp->val == '0') arr[9].insert(new_prev);
				else if (new_prev != fake_head && new_prev->val + 1 == tmp->val) arr[new_prev->val - '0'].insert(new_prev);
				if (new_next != nullptr && tmp->val == '9' && new_next->val == '0') arr[9].insert(tmp);
				else if (new_next != nullptr && tmp->val + 1 == new_next->val) arr[tmp->val - '0'].insert(tmp);
				
				delete cur;
				delete cur_next;
			}
			arr[i].clear();
		}
	}
	
	string res;
	head = fake_head->next;
	while (head != nullptr) {
		res.push_back(head->val);
		head = head->next;
	}
	deleteNode(fake_head);
	
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
		string ans = solve(s, l);
        
		printf("Case #%d: %s\n", i + 1, ans.c_str());
    }
    return 0;
}