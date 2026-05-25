#include <iostream>
#include <vector>
#include <set>
#include <cstdlib>
using namespace std;

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

// void dfs(vector<vector<int>> gr, vector<vector<int>> ribs, vector<int> a, int x,bool isT) {
// 	int ii;
//     int xx = x;
//     int count = 1;
// 	a[x] = 1;
// 	bool fl = false;
// 	cout << x << " ";
// 	stack* h = NULL;
// 	push(h, x);
// 	while (h) {
// 		x = h->val;
// 		fl = false;
// 		for (int i = 0; i < gr[x].size(); i++) {
// 			if (a[gr[x][i]] == 0) {
// 				fl = true;
// 				ii = i;
// 				break;
// 			}
// 		}
// 		if (fl == true) {
// 			a[gr[x][ii]] = 1;
// 			cout << gr[x][ii] << " ";
//             count++;
// 			push(h, gr[x][ii]);
// 		}
// 		else pop(h);
// 	}
//     cout << '\n';
//     if (count == gr.size() && isT == false) {
//         system("cls");
//         vector<vector<int>> grT = l_AdjT(gr.size(), ribs);
//         for (int i = 0; i <a.size(); i++) {
//             a[i] = 0;
//         }
//         dfs(grT, ribs, a, xx,true);
//     }
//     else {
//         bool fl2 = false;
// 	    for (int i = 0; i < a.size(); i++) {
// 		    if (a[i] == 0) {
// 			    fl2 = true;
// 			    ii = i;
// 			    break;
// 		    }
// 	    }
// 	    if (fl2 == true) {
// 		    x = ii;
// 		    dfs(gr, ribs, a, x,false);
// 	    }
//     }
// }


void bfs(vector<vector<int>> gr, vector<int> a, int x) {
	int ii;
	a[x] = 1;
	cout << x << " ";
	queue* h = NULL;
	queue* t = NULL;
	push(h,t, x);
	while (h) {
		x = pop(h, t);
		for (int i = 0; i < gr[x].size(); i++) {
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


void euler_traverse(vector<vector<int>> gr) {
    vector<vector<vector<int>>> a(gr.size());
	int oddcnt = 0;
	int asize = 0;
	 int isVisited = 0;
	for (int i = 0; i < gr.size(); i++) {
		a[i].resize(gr[i].back()+1);
		asize+=gr[i].size();
		if (gr[i].size() % 2 != 0) {
			oddcnt+=1;
			if (oddcnt > 2) {
				isVisited = 1;
				break;
			}
		}
		for (int j = 0; j < gr[i].back()+1; j++) {
			a[i][j].push_back(0);
		}
	}
	if (oddcnt == 1) {
		isVisited = 1;
	}
	int acnt = 0;
    stack* h = NULL;
    push(h,0);
    oddcnt = 0;
	if (isVisited == 1) {
		acnt = asize;
		cout << endl << "Euler traverse is impossible" << endl;
	}
    while (acnt < asize) {
        isVisited = 0;
        for (int i = 0; i < gr[h->val].size(); i++) {
            if (a[h->val][gr[h->val][i]][0] == 0) {
                a[h->val][gr[h->val][i]][0] = 1;
				a[gr[h->val][i]][h->val][0] = 1;
                acnt+=2;
                cout << h->val << "---" << gr[h->val][i] << " ";
                push(h, gr[h->val][i]);
                isVisited = 1;
                break;
            }
        }
        if (isVisited == 0) {
            system("cls");
			for (int i = 0; i < gr.size(); i++) {
				for (int j = 0; j < gr[i].back()+1; j++) {
					a[i][j][0] = 0;
				}
			}
			oddcnt++;
			if (oddcnt >= gr.size()) {
				cout << endl << "Euler traverse is impossible" << endl;
				break;
			}
			acnt = 0;
			h->val= (h->val+1)%gr.size();
			cout << endl;
        }
        else if (isVisited == 2) {
            break;
        }
    }
}

void insertsort(vector<vector<int>>& vec) {
    if(vec[0].size() > vec[1].size()) {
        swap(vec[0], vec[1]);
    }
    if (vec.size() > 2) {
        int jj;
        vector<int> tmp;
        for (int i = 2; i < vec.size(); i++) {
            jj = i;
            for (int j = 0; j < i; j++) {
                if (vec[i].size() < vec[j].size()) {
                    jj = j;
                    break;
                }
            }
            tmp = vec[i];
            vec.erase(find(vec.begin(), vec.end(), vec[i]));
            vec.insert(vec.begin()+jj, tmp);
        }
    }
}

int main() {
    int n;
	cout << "Enter q n:";
	cin >> n;
	int nd;
	int ndcnt = 0;
	int prndcnt = n;
    bool isRib = false;
	vector<vector<int>> gr;
	gr.resize(n);
	vector<vector<int>> ribs;
	vector<int> tmp = {0, 0};
	cout << '\n';
	for (int i = 0; i < n; i++) {
		cout << i <<  " --- Enter the number of adjacent nodes:";
		cin >> ndcnt;
		for (int j = 0; j <ndcnt; j++) {
			cin >> nd;
			gr[i].push_back(nd);
		}
	}
    euler_traverse(gr);
}
