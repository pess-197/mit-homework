#include <iostream>
using namespace std;

struct tree{
    int val;
    int height;
    tree* right;
    tree* left;
    tree* parent;
};

tree* nil;

void init_nil() {
    nil = new tree;
    nil->height = 0;
    nil->left = nil->right = nil->parent = nil;
}

inline int get_height(tree* &tr) {
    return tr->height;
}

void heighup (tree* &tr) {
    if (tr != nil) {
        tr->height = 1 + max(get_height(tr->left), get_height(tr->right));
    }
}

int balance_fac(tree* &tr) {
    if (tr == nil) {
        return 0;
    }
    return get_height(tr->left) - get_height(tr->right);
}

tree* root(int x) {
    tree* r = new tree;
    r->height = 1;
    r->val = x;
    r->left = nil; 
    r->right = nil;
    r->parent = nil;
    return r;
}

tree* node(tree* &tr, int x) {
    tree* r = new tree;
    r->height = 1;
    r->val = x;
    r->left = nil;
    r->right = nil;
    r->parent = tr;
    return r;
}

tree* lturn(tree* &tr, tree* &x) {
    tree* y = x->right;
    x->right = y->left;
    if (y->left != nil) {               
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nil) {
        tr = y;
    }
    else if (x == x->parent->left) {
        x->parent->left = y;
    }
    else x->parent->right = y;
    y->left = x;
    x->parent = y;
    heighup(x);
    heighup(y);
    return tr; 
}

tree* rturn(tree* &tr, tree* &x) {
    tree* y = x->left;
    x->left = y->right;
    if (y->right != nil) {               
        y->right->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nil) {
        tr = y;
    }
    else if (x == x->parent->right) {
        x->parent->right = y;
    }
    else x->parent->left = y;
    y->right = x;
    x->parent = y;
    heighup(x);
    heighup(y);
    return tr; 
}

void preorder(tree* &tr);

void balance(tree* &tr, tree* &x) {
    int bf = balance_fac(x);
    if (bf > 1) { 
        preorder(tr);
        cout << endl;                       
        if (balance_fac(x->left) < 0) {
            preorder(tr);
    cout << endl;
            lturn(tr, x->left);
        }
        
        rturn(tr, x);
        
    }
    else if (bf < -1) {                  
        if (balance_fac(x->right) > 0) {
            rturn(tr, x->right);
        }
        lturn(tr, x);
    }
}

tree* grprnt (tree* &x) {
    if (x != nil && x->parent != nil) {
        return x->parent->parent;
    }
    else return nil;
}

tree* uncle(tree* &x) {
    tree* g = grprnt(x);
    if (g == nil) {
        return nil;
    }
    else if (g->right == x->parent) {
        return g->left;
    }
    else return g->right;
}

tree* sblng (tree* &x) {
    if (x != nil && x->parent != nil) {
        if (x->parent->left == x) {
            return x->parent->right;
        }
        else return x->parent->left;
    }
    else return nil;
}

tree* min(tree* tr) {
    if (tr->left == nil) {
        return tr;
    }
    else return min(tr->left);
}

tree* max(tree* tr) {
    if (tr->right == nil) {
        return tr;
    }
    else return max(tr->right);
}



void insert(tree* &tr, tree* &pr, int x) {
    if (x < pr->val && pr->left == nil) {
        pr->left = node(pr, x);
    }
    else if (x > pr->val && pr->right == nil) {
        pr->right = node(pr, x);
    }
    else {
        if (x < pr->val && pr->left != nil) {
            insert(tr, pr->left, x);
            return;
        }
        if (x > pr->val && pr->right != nil) {
            insert(tr, pr->right, x);
            return;
        }
    }
    preorder(tr);
    cout << endl;
    heighup(pr);
    balance(tr, pr);
}

// *** FIX 1: Changed v from reference to plain pointer ***
void replace(tree* &tr, tree* u, tree* v) {
    if (u->parent == nil)
        tr = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;
    if (v != nil)
        v->parent = u->parent;
}

void avl_delete(tree* &tr, tree* start) {
    tree* p = start;
    while (p != nil) {
        heighup(p);
        balance(tr, p);
        p = p->parent;
    }
}

void del(tree* &tr, tree*&x) {
    if (x == nil) return;                   
    tree* y = x;
    tree* child;
    tree* fix_start = x->parent;

    if (x->left == nil) {
        child = x->right;
        replace(tr, x, x->right);
    }
    else if (x->right == nil) {
        child = x->left;
        replace(tr, x, x->left);
    }
    else {
        y = max(x->left);
        if (y->parent == x) {
            fix_start = y;
        }
        else fix_start = y->parent;

        child = y->left;                   
        if (y->parent == x) {
            if (child != nil) child->parent = y;             
        }
        else {
            replace(tr, y, y->left);
            y->left = x->left;
            y->left->parent = y;
        }
        replace(tr, x, y);
        y->right = x->right;
        y->right->parent = y;
        y->height = x->height;
    }

    delete x;
    x = nil;

    // *** FIX 2: Call AVL rebalancing after deletion ***
    avl_delete(tr, fix_start);
}

void preorder(tree* &tr) {
    if (tr != nil) {
        cout << tr->val <<  ", ";
        preorder(tr->left);
        preorder(tr->right);
    }
}

void inorder(tree* &tr) {
    if (tr != nil) {
        inorder(tr->left);
        cout << tr->val <<  ", ";
        inorder(tr->right);
    }
}

void del_odd(tree* &tr, tree* &x) {
    if (x == nil) return;
    del_odd(tr, x->left);
    del_odd(tr, x->right);
    if (x->val % 2 != 0) {
        tree* tmp = x;
        del(tr, tmp);
    }
}

int main() {
    init_nil();
       
    int n;
    cout << "enter n:";
    cin >> n;
    tree* tr;
    int val;
    cin >> val;
    tr = root(val);
    for (int i = 1; i < n; i++) {
        cin >> val;
        insert(tr, tr, val);
        
    }
    preorder(tr);
    cout << endl;
    del_odd(tr, tr);
    preorder(tr);
    delete nil;
}