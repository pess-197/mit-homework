#include <iostream>
#include <vector>
#include <set>
#include <cstdlib>
#include <algorithm>
using namespace std;

vector<int> used;
vector<int> pr;
set<vector<int>> cycles_sort;

struct stack {
	int val;
	stack* next;
};

void push(stack*& h, int i) {
	stack* r = new stack;
	r->val = i;
	r->next = h;
	h = r;
} 

int pop(stack*& h) {
	int i = h->val;
	stack* r = h;
	h = h->next;
	delete r;
	return i;
}

void reverse(stack*& h) {
	stack* h1 = NULL;
	while (h) {
		int i = pop(h);
		push(h1, i);
	}
	h = h1;
}

struct queue {
	int val;
	queue *next;
};

void push(queue *&h, queue *&t, int i) {
	queue* r = new queue;
	r->val = i;
	r->next = NULL;
	if (!h && !t) {
		h = t = r;
	}
	else {
		t->next = r;
		t = r;
	}
}

int pop(queue *&h, queue *&t) {
	queue *r = h;
	int i = h->val;
	h = h->next;
	if (!h) {
		t = NULL;
	}
	delete r;
	return i;
}

void bfs(vector<vector<vector<int>>> gr, vector<int> &a, int x) {
	int ii;
    vector<int> b(a.size(), 0);
    vector<vector<int>> routes(a.size());
	a[x] = 0;
    for (int i = 0; i < a.size(); i++) {
        routes[i].push_back(i);
    }
    int minn;
    int minv;
	queue* h = NULL;
	queue* t = NULL;
	push(h,t, x);
	while (h) {
		x = pop(h, t);
        b[x] = 1;
		for (int i = 0; i < gr[x].size(); i++) {
			if (a[x]+gr[x][i][1] < a[gr[x][i][0]]) {
                a[gr[x][i][0]] = a[x]+gr[x][i][1];
                routes[gr[x][i][0]] = routes[x];                 
                routes[gr[x][i][0]].push_back(gr[x][i][0]); 
            }
		}
        minn = INT_MAX;
        for (int i = 0; i < a.size(); i++) {
            if (a[i] < minn && b[i] == 0) {
                minn = a[i];
                minv = i;
            }
        }
        if (minn < INT_MAX) push(h,t,minv);
	}
    for (auto &i : routes) {
        //reverse(i.begin(), i.end());
        for (auto &j : i) {
            cout << j << " ";
        }
        cout << endl;
    }
}

int main() {
    int n;
	cout << "Enter n:";
	cin >> n;
	int nd;
	int ndcnt = 0;
	int prndcnt = n;
	vector<vector<vector<int>>> gr;
	gr.resize(n);
	vector<int> tmp = {0, 0};
    vector<int> a(gr.size(),INT_MAX);
	for (int i = 0; i < n; i++) {
		cout << i <<  " --- Enter the number of adjacent nodes:";
		cin >> ndcnt;
		for (int j = 0; j <ndcnt; j++) {
			cin >> nd >> tmp[1];
            tmp[0]=nd;
			gr[i].push_back(tmp);
		}
	}
    int x;
    cin >> x;
    bfs (gr,a,x);
    for (auto &i : a) {
        cout << i << " ";
    }
}