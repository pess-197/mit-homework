#include <iostream>
#include <vector>
#include <set>
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

// set<vector<int>> cycle_search(vector<vector<int>> gr,int a) {
//     vector<int> used(gr.size(),0);
//     set<vector<int>> sett;    
//     used[a] = 2;
//     stack* h = NULL;
// 	stack* pr = NULL;
// 	stack* pr2 = NULL;
// 	int prpr = a;
//     int ii = 0;
//     int fl = 0;
//     push(h, a);
// 	push(pr,a);
// 	push(pr2,a);
//     while (h) {
//         a = h->val;
// 		//cout << a << ", " << pr->val << ", " << pr2->val << " ";
// 		cout << a << " ";
// 		fl = 0;
//         for (int i = 0; i < gr[a].size(); i++) {
// 			if (used[gr[a][i]] == 0) {
// 				used[gr[a][i]] = 2;
//                 ii = i;
//                 fl = 1;
// 				push(pr2,a);
// 				break;
// 			}
// 			if (used[gr[a][i]] == 1 && gr[a][i] != pr->val && gr[a][i] != pr2->val) {
// 				used[gr[a][i]] = 2;
//                 ii = i;
//                 fl = 1;
// 				push(pr2,a);
// 				break;
// 			}
// 			else if (used[gr[a][i]] == 1 &&  (gr[a][i] == pr->val || gr[a][i] == pr2->val) && used[a] < 3) {
// 				fl = 2;
// 				break;
// 			}
//             // if (gr[a][i] != pr->val && gr[a][i] != pr2->val  && used[gr[a][i]] == 2) {
//             //     stack* tmp = 0;
// 			// 	cout << prpr << " ";
// 			// 	while (h) {
// 			// 		push(tmp,h->val);
// 			// 		cout << h->val << " ";
// 			// 		pop(h);
// 			// 	}
// 			// 	cout << '\n';
// 			// 	reverse(tmp);
// 			// 	h = tmp;
//             // }
// 		}
// 		push(pr,a);
//         if (fl == 1) {
// 			push(h, gr[a][ii]);
// 		}
// 		else if (fl == 0) {
//             pop(h);
// 			pop(pr2);
//             used[a] = 1;
//         }
// 		else {
// 			pop(h);
// 			pop(pr2);
//             used[a] = 3;
// 		}
//     }
// 	cout << '\n';
// 	for (auto &i : used) {
// 		cout << i << " ";
// 	}
//     return sett;
// }

void insertsort(vector<int>& vec) {
    if(vec[0] > vec[1]) {
        swap(vec[0], vec[1]);
    }
    if (vec.size() > 2) {
        int jj, tmp;
        for (int i = 2; i < vec.size(); i++) {
            jj = i;
            for (int j = 0; j < i; j++) {
                if (vec[i] < vec[j]) {
                    jj = j;
                    break;
                }
            }
            if (jj != i) {
                tmp = vec[i];
                vec.erase(vec.begin()+i);
                vec.insert(vec.begin()+jj, tmp);
            }
        }
    }
}


void add_cycle(int sv, int fv) {
	int curv = fv;
	vector<int> tmp;
	while (curv != sv) {
		tmp.push_back(curv);
		curv = pr[curv];
	}
	tmp.push_back(sv);
	insertsort(tmp);
	cycles_sort.insert(tmp);
}

void cycle_search(int x,vector<vector<int>> gr) {
	used[x] = 1;
	for (int i = 0; i < gr[x].size(); i++) {
		if (pr[x] == gr[x][i]) {
			continue;
		}
		if (used[gr[x][i]] == 0) {
			pr[gr[x][i]] = x;
			cycle_search(gr[x][i], gr);
		}
		else {
			add_cycle(gr[x][i],x);
		}
	}
	used[x] =0;
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

int main() {
    int cnt = 0;
	vector<vector<int>> gr = { {1,2,4,5}, {0,3},{0,5},{1},{0,6},{0,2,6}, {4,5} };
    vector<vector<int>> ribs = { {0,1}, {0,2}, {0,4},{0,5}, {1,3}, {2,5}, {4,6}, {5,6}};
    gr= l_Adj(gr.size(), ribs, false);
	pr.resize(gr.size());
	used.resize(gr.size());
	for (int i = 0; i <gr.size(); i++) {
		pr[i] = -1;
		used[i] = 0;
	}
	cycle_search(0,gr);
    for (auto &i : cycles_sort) {
        for (int j = 0; j < i.size(); j++) {
            cout << i[j] << " ";
        }
        cout << '\n';
    }
}
