#include <iostream>
#include <vector>

using namespace std;

struct tree {
    int val;
    tree* right;
    tree* left;
    tree* parent;
};

tree* newtree(int val) {
    tree* r = new tree;
    r->val = val;
    r->right = NULL;
    r->left = NULL;
    r->parent = NULL;
    return r;
}

void insert(tree*& tr, tree*& tmp, tree*& p) {
    if (!tr) {
        tr = p; 
        tr->parent = tmp;
    }
    else if (p->val >= tr->val) {
        insert(tr->right,tr,p);
    }
    else insert(tr->left,tr,p);
}

tree* find(tree*& tr, int pval) {
    if (!tr || tr->val == pval) {
        return tr;
    }
   if (pval >= tr->val) {
        return find(tr->right,pval);
   }
   else return find(tr->left,pval);
}
 
tree* min(tree* tr) {
    if (!tr->left) {
        return tr;
    }
    else return min(tr->left);
}

tree* next(tree*& tr, int pval) {
    tree* tmp = find(tr,pval);
    if (tmp->right) {
        return min(tmp->right);
    }
}
void del(tree*& tr, tree*& p) {
    if (!p->right && !p->left) {
        if (!p->parent) {
        tr = NULL;
    }
        else if(p->val >= p->parent->val) {
            p->parent->right = NULL;
        }
        else p->parent->left = NULL;
        delete p;
    }
    else if (!p->left) {
        if (!p->parent) {
        tr= p->right;
        p->right->parent =NULL;
    }
         else if(p->val >= p->parent->val) {
            p->parent->right = p->right;
            p->right->parent = p->parent;
        }
        else {p->parent->left = p->right;
             p->right->parent = p->parent;
        }
        delete p;
    }
    else if (!p->right) {
        if (!p->parent) {
        tr= p->left;
        p->left->parent = NULL;
    }
         else if(p->val >= p->parent->val) {
            p->parent->right = p->left;
             p->left->parent = p->parent;
        }
        else {p->parent->left = p->left;
             p->left->parent = p->parent;
        }
        delete p;
    }
    else {
        tree* nxt = next(tr,p->val);
        p->val = nxt->val;
        del(tr,nxt);
    }

}
void xpath(tree*& tr, tree*& x) {
    if (!tr || tr->val == x->val) {
        cout << tr->val << ".";
    }
    else if (x->val >= tr->val) {
        cout << tr->val << " ";
        xpath(tr->right,x);
    }
    else {
        cout << tr->val << " ";
        xpath(tr->left,x);
    }
}

int main() {
    vector<int> vec = {5, 3, 7, 1, 9, 4, 2, 8, 6, 0};
    tree* tr = NULL;
    tree* tmp = NULL;
    tree* val;
    for (auto &i : vec) {
        val = newtree(i);
        insert(tr,tmp,val);
    }
    tree* x = find(tr,0);
    xpath(tr,x);
}