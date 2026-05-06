#include <iostream>
#include <vector>

using namespace std;

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


void dfs(vector<vector<int>> gr, vector<int> a, int x) {
	int ii;
	a[0] = 1;
	bool fl = false;
	cout << x << " ";
	stack* h = NULL;
	push(h, x);
	while (h) {
		x = h->val;
		fl = false;
		for (int i = 0; i < gr[x].size(); i++) {
			cout << "/" << a[gr[x][i]] << "/ ";
			if (a[gr[x][i]] == 0) {
				fl = true;
				ii = i;
				break;
			}
		}
		if (fl == true) {
			a[gr[x][ii]] = 1;
			cout << gr[x][ii] << " ";
			push(h, gr[x][ii]);
		}
		else pop(h);
	}
	bool fl2 = false;
	for (int i = 0; i < a.size(); i++) {
		if (a[i] == 0) {
			fl2 = true;
			ii = i;
			break;
		}
	}
	if (fl2 == true) {
		x = ii;
		dfs(gr, a, x);
	}

}
void bfs(vector<vector<int>> gr, vector<int> a, int x) {
	int ii;
	a[0] = 1;
	cout << x << " ";
	queue* h = NULL;
	queue* t = NULL;
	push(h,t, x);
	while (h) {
		x = pop(h, t);
		for (int i = 0; i < gr[x].size(); i++) {
			cout << "/" << a[gr[x][i]] << "/ ";
			if (a[gr[x][i]] == 0) {
				a[gr[x][i]] = 1;
				push(h, t, gr[x][i]);
				cout << gr[x][i] << " ";
			}
		}
	}
	bool fl2 = false;
	for (int i = 0; i < a.size(); i++) {
		if (a[i] == 0) {
			fl2 = true;
			ii = i;
			break;
		}
	}
	if (fl2 == true) {
		x = ii;
		bfs(gr, a, x);
	}
}

vector<vector<int>> l_Adj(int n, int m, vector<int> ribs) {
    
}


int main() {
	int n = 7;
	vector<vector<int>> gr = { {1,2,4,5}, {0,3},{0,5},{1},{0,6},{0,2,6}, {4,5} };
	vector<int> a(n, 0);
	dfs(gr, a,0);
	cout << '\n';
	bfs(gr, a, 0);
}
