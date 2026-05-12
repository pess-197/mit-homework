#include <iostream>
#include <vector>
#include <set>
#include <cstdlib>
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

vector<vector<int>> l_Adj(int n, vector<vector<int>> ribs, bool orient) {
    vector<vector<int>> gr;
    gr.resize(n);
    for (int i = 0; i < ribs.size(); i++) {
        if (ribs[i][0] > n || ribs[i][1] > n) {
            continue;
        }
        else {
            if (orient) gr[ribs[i][0]].push_back(ribs[i][1]);
            else {
                gr[ribs[i][0]].push_back(ribs[i][1]);
                gr[ribs[i][1]].push_back(ribs[i][0]);
            }
        }
    }
	return gr;
}

vector<vector<int>> l_AdjT(int n, vector<vector<int>> ribs) {
    vector<vector<int>> gr;
    gr.resize(n);
    for (int i = 0; i < ribs.size(); i++) {
        if (ribs[i][0] > n || ribs[i][1] > n) {
            continue;
        }
        else {
            gr[ribs[i][1]].push_back(ribs[i][0]);
        }
    }
	return gr;
}

void dfs(vector<vector<int>> gr, vector<vector<int>> ribs, vector<int> a, int x) {
	int ii;
    int xx = x;
    int count = 1;
	a[x] = 1;
	bool fl = false;
	cout << x << " ";
	stack* h = NULL;
	push(h, x);
	while (h) {
		x = h->val;
		fl = false;
		for (int i = 0; i < gr[x].size(); i++) {
			if (a[gr[x][i]] == 0) {
				fl = true;
				ii = i;
				break;
			}
		}
		if (fl == true) {
			a[gr[x][ii]] = 1;
			cout << gr[x][ii] << " ";
            count++;
			push(h, gr[x][ii]);
		}
		else pop(h);
	}
    cout << '\n';
    if (count == gr.size()) {
        system("cls");
        vector<vector<int>> grT = l_AdjT(gr.size(), ribs);
        for (int i = 0; i <a.size(); i++) {
            a[i] = 0;
        }
        dfs(grT, ribs, a, xx);
    }
    else {
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
		    dfs(gr, ribs, a, x);
	    }
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



int main() {
    int cnt = 0;
    vector<vector<int>> ribs = { {0,1}, {1,2}, {1,5}, {1,4}, {2,3}, {3,2}, {3,7}, {7,3}, {7,6}, {5,6}, {6,5}, {4,5}, {4,0}};
    vector<int> a(8,0);
    vector<vector<int>> gr= l_Adj(8, ribs, false);
    dfs(gr,ribs,a,0);
}