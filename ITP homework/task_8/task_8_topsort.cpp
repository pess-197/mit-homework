#include <iostream>
#include <vector>
#include <set>
#include <cstdlib>
#include "task_8_euler.cpp" //on your PC, you can add insertsort there as well as comment main() and dfs().
// I included it in order to not copypaste all the functions here again
using namespace std;

vector<vector<int>> dfs(vector<vector<int>>& gr, vector<vector<int>>& ribs, vector<int>& a, int x,bool isT,vector<vector<int>> &ress) {
	int ii;
    int xx = x;
    int count = 1;
	a[x] = 1;
	int fl = 0;
	vector<int> res;
	stack* h = NULL;
	push(h, x);
	while (h) {
		x = h->val;
		fl = 0;
		for (int i = 0; i < gr[x].size(); i++) {
			if (a[gr[x][i]] == 0) {
				fl =1;
				ii = i;
				break;
			}
			else if (a[gr[x][i]] == 1) {
				fl = 2;
			}
		}
		if (fl == 1) {
			a[gr[x][ii]] = 1;
			res.push_back(gr[x][ii]);
            count++;
			push(h, gr[x][ii]);
		}
		else if (fl == 2) {
			pop(h);
		}
		else {
			a[h->val] = 2;
			pop(h);
			break;
		}
	}
	if (count == gr.size() && isT == false) {
        vector<vector<int>> grT = l_AdjT(gr.size(), ribs);
        for (int i = 0; i <a.size(); i++) {
			if (a[i] == 1) {
            	a[i] = 0;
			}
        }
        dfs(grT, ribs, a, xx,true,ress);
    }
	else if (fl == 0 && count > 1) {
		for (int i = 0; i <a.size(); i++) {
			if (a[i] == 1) {
            	a[i] = 0;
			}
        }
		dfs(gr,ribs,a,xx,false,ress);
	}
   
    else if (fl != 0 || (fl == 0 && count == 1)) {
		if (res.size() > 0) {
			res.push_back(xx);
			ress.push_back(res);
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
		    dfs(gr, ribs, a, x,false,ress);
	    }
    }
	return ress;
}

bool topsort(vector<vector<int>> gr,vector<vector<int>> ribs, vector<int> a,vector<vector<int>> countt) {
	vector<int> res;
	vector<vector<int>> ress;
	vector<int> tmp(gr.size());
	for (int i = 0; i < gr.size(); i++) {
		tmp[i] = i;
	}
	ress = dfs(gr,ribs,a,0,false,ress);
	if (ress.size() > 0) {
		cout << "Topological sorting is impossible" << endl;
		return false;
	}

	insertsort(countt);
	for (auto &i: countt) {
		cout << i[1] << " -- " << i[0] << endl;
	}
	int i = 0;
	while (countt[i][0] == 0) {
		cout << countt[i][1] << " ";
		res.push_back(countt[i][1]);
		tmp.erase(find(tmp.begin(),tmp.end(), countt[i][1]));
		i++;
	}
	int j = 0;
	bool isLnkdtse = false;
	while (res.size() < gr.size()) {
		for (int i = 0; i < gr[res[j]].size(); i++) {
			isLnkdtse = false;
			for (int b = 0; b < tmp.size(); b++) {
				for (int p = 0; p < gr[tmp[b]].size(); p++) {
					if (gr[tmp[b]][p] == gr[res[j]][i]) {
						isLnkdtse = true;
						break;
					}
				}
				if (isLnkdtse) break;
			}
			if (!isLnkdtse) {
				cout << gr[res[j]][i] << " ";
				res.push_back(gr[res[j]][i]);
				tmp.erase(find(tmp.begin(),tmp.end(), gr[res[j]][i]));
			}
		}
		j++;
	}
}

int main() {
    int n;
	cout << "Enter n:";
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
			tmp[0]=i;
			tmp[1]=nd;
			ribs.push_back(tmp);
		}
	}
	vector<vector<int>> countt(gr.size(), {0, 0});
	for (int i = 0; i < countt.size(); i++) {
		countt[i][1] = i;
	}
	for (int i = 0; i <gr.size(); i++) {
		 cout << i << " --- ";
		for (auto &j : gr[i]) {
           countt[j][0]++;
		   cout << j << " ";
		}
		cout << '\n';
	}
	vector<int> a(gr.size(),0);
    topsort(gr,ribs,a,countt);
}
