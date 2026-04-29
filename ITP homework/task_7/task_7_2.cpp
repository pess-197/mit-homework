// #include <iostream>
// #include <vector>

// using namespace std;

// struct tree {
//     int val;
//     tree* right;
//     tree* left;
//     tree* parent;
// };

// tree* newtree(int val) {
//     tree* r = new tree;
//     r->val = val;
//     r->right = NULL;
//     r->left = NULL;
//     r->parent = NULL;
//     return r;
// }

// void insert(tree*& tr, tree*& tmp, tree*& p) {
//     if (!tr) {
//         tr = p; 
//         tr->parent = tmp;
//     }
//     else if (p->val >= tr->val) {
//         insert(tr->right,tr,p);
//     }
//     else insert(tr->left,tr,p);
// }

// tree* find(tree*& tr, int pval) {
//     if (!tr || tr->val == pval) {
//         return tr;
//     }
//    if (pval >= tr->val) {
//         return find(tr->right,pval);
//    }
//    else return find(tr->left,pval);
// }
 
// tree* min(tree* tr) {
//     if (!tr->left) {
//         return tr;
//     }
//     else return min(tr->left);
// }

// tree* next(tree*& tr, int pval) {
//     tree* tmp = find(tr,pval);
//     if (tmp->right) {
//         return min(tmp->right);
//     }
// }
// void del(tree*& tr, tree*& p) {
//     if (!p->right && !p->left) {
//         if (!p->parent) {
//         tr = NULL;
//     }
//         else if(p->val >= p->parent->val) {
//             p->parent->right = NULL;
//         }
//         else p->parent->left = NULL;
//         delete p;
//     }
//     else if (!p->left) {
//         if (!p->parent) {
//         tr= p->right;
//         p->right->parent =NULL;
//     }
//          else if(p->val >= p->parent->val) {
//             p->parent->right = p->right;
//             p->right->parent = p->parent;
//         }
//         else {p->parent->left = p->right;
//              p->right->parent = p->parent;
//         }
//         delete p;
//     }
//     else if (!p->right) {
//         if (!p->parent) {
//         tr= p->left;
//         p->left->parent = NULL;
//     }
//          else if(p->val >= p->parent->val) {
//             p->parent->right = p->left;
//              p->left->parent = p->parent;
//         }
//         else {p->parent->left = p->left;
//              p->left->parent = p->parent;
//         }
//         delete p;
//     }
//     else {
//         tree* nxt = next(tr,p->val);
//         p->val = nxt->val;
//         del(tr,nxt);
//     }

// }

// int incount(tree*& tr,int sum) {
//     if (tr->right || tr->left) {
//         if (tr->right && tr->left) {
//             return incount(tr->right, sum) + incount(tr->left, tr->val);
//         }
//         else if (tr->right) {
//             return incount(tr->right, sum+tr->val);
//         }
//         else if (tr->left) {
//             return incount(tr->left, sum+tr->val);
//         }
//     }
//     return sum;
// }

// void inorder(tree *tr, int sum){
//     if(tr) {
//         inorder ( tr->left,sum+tr->val);
//         cout << sum << " ";
//         inorder ( tr->right,sum+tr->val);
//     }
// }


// int main() {
//     vector<int> vec = {5, 3, 7, 1, 9, 4, 2, 8, 6, 0};
//      vector<int> vec2 = {10,5,2,15,20};
//     tree* tr = NULL;
//     tree* tmp = NULL;
//     tree* val;
//     int sum = 0;
//     for (auto &i : vec2) {
//         sum+=i;
//         val = newtree(i);
//         insert(tr,tmp,val);
//     }
//     cout << endl;
//     cout <<incount(tr,0);
// }