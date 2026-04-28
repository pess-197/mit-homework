#include <iostream>
#include <vector>
using namespace std;

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
                vec.erase(find(vec.begin(), vec.end(), vec[i]));
                vec.insert(vec.begin()+jj, tmp);
            }
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

vector<int> timsort(vector<int> &vec) {
    int MinRun = 3;
    int isAscending = 0;
    vector<vector<int>> runs;
    vector<int> run;
    run.push_back(vec[0]);
    for (int i = 0; i < vec.size()-1; i++) {
        cout << vec[i] << " " << vec[i+1] <<  endl;
        run.push_back(vec[i+1]);
        if (isAscending == 0) {
            if (vec[i] <= vec[i+1]) {
                isAscending = 1;
            }
            else isAscending = -1;
        }
        
        else if (isAscending == 1) {
            if (vec[i] > vec[i+1]) {
                insertsort(run);
                runs.push_back(run);
                while (!run.empty()) {
                    run.pop_back();
                }
                i++;
                if (i < vec.size()) {
                    run.push_back(vec[i+1]);
                }
                isAscending = 0;
            }
        }
        else if (isAscending == -1) {
            if (vec[i] <= vec[i+1]) {
                insertsort(run);
                runs.push_back(run);
                while (!run.empty()) {
                    run.pop_back();
                }
                i++;
                if (i < vec.size()) {
                    run.push_back(vec[i+1]);
                }
                isAscending = 0;
            }
        }
    }
    if (!run.empty()) {
        runs.push_back(run);
    }
    insertsort(runs);
    for (auto &i : runs) {
        for (auto &j : i) {
            cout << j << " ";
        }
        cout << endl;
    }
    for (int i = 0; i < runs.size()-1; i++) {
        for (int j = 0; j < runs[i].size(); j++) {
            for (int k = 0; k < runs[i+1].size(); k++) {
                if (runs[i][j] < runs[i+1][k] || k == runs[i+1].size()-1) {
                    if (k > 0) {
                        runs[i+1].insert(runs[i+1].begin()+k, runs[i][j]);
                    }
                    else  runs[i+1].insert(runs[i+1].begin(), runs[i][j]);
                    for (auto &j : runs[i+1]) {
                        cout << j << " ";
                    }
                    cout << endl;
                    break;
                }
            }
        }
    }
    return runs[runs.size()-1];
}

int main() {
    vector<int> vec = {1, 3, 4,2 ,5, 3,52 , 0};
    vector<int> vec2 = {5, 3,52};
    insertsort(vec2);
    timsort(vec);
    for (auto &i : vec) {
        cout << i << " ";
    }
}