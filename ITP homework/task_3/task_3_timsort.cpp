#include <iostream>
#include <vector>
using namespace std;

void insertsort(vector<int>& vec) {
    if(vec[0] > vec[1]) {
        swap(vec[0], vec[1]);
    }
    int jj, tmp;
    for (int i = 2; i < vec.size(); i++) {
        jj = i;
        for (int j = 0; j < i; j++) {
            if (vec[i] < vec[j]) {
                jj = j;
                break;
            }
        }
        tmp = vec[i];
        vec.erase(find(vec.begin(), vec.end(), vec[i]));
        vec.insert(vec.begin()+jj, tmp);
    }
}

int main() {
    vector<int> vec = {1, 3, 4,2 ,5, 3,52 , 0};
    insertsort(vec);
    for (auto &i : vec) {
        cout << i << " ";
    }
}