#include <iostream>
#include <vector>
using namespace std;

struct tree{
    int val;
    char color;
    tree* right;
    tree* left;
    tree* parent;
};

tree* nil;

void init_nil() {
    nil = new tree;
    nil->color = 'b';
    nil->left = nil->right = nil->parent = nil;
}


tree* root(int x) {
    tree* r = new tree;
    r->color = 'b';
    r->val = x;
    r->left = nil; 
    r->right = nil;
    r->parent = nil;
    return r;
}

tree* node(tree* &tr, int x) {
    tree* r = new tree;
    r->color = 'r';
    r->val = x;
    r->left = nil;
    r->right = nil;
    r->parent = tr;
    return r;
}

tree* lturn(tree* &tr, tree* &x) {
    if (x == nil) return tr;
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
    return tr; 
}

tree* rturn(tree* &tr, tree* &x) {
    if (x == nil) return tr;
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
    return tr; 
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

void insert_case_1(tree* &tr, tree* &x);
void insert_case_2(tree* &tr, tree* &x);
void insert_case_3(tree* &tr, tree* &x);
void insert_case_4(tree* &tr, tree* &x);
void insert_case_5(tree* &tr, tree* &x);
void delete_case_1(tree* &tr, tree* &x);
void delete_case_2(tree* &tr, tree* &x);
void delete_case_3(tree* &tr, tree* &x);
void delete_case_4(tree* &tr, tree* &x);
void delete_case_5(tree* &tr, tree* &x);
void delete_case_6(tree* &tr, tree* &x);

void insert_case_5(tree* &tr, tree* &x) {
    tree* g = grprnt(x);
    if (x != nil && x->parent != nil && g != nil) {
        x->parent->color = 'b';
        g->color = 'r';
        if (x->parent->left == x && g->left == x->parent) {
            rturn(tr,g);
        }
        else if (x->parent->right == x && g->right == x->parent) lturn(tr,g);
    }
}

void insert_case_4(tree* &tr, tree* &x) {
    tree* g = grprnt(x);
    if (g == nil) return;
    if (x->parent->right == x && g->left == x->parent) {
        lturn(tr,x->parent);
        x=x->left;
    }
    else {
        if (x->parent->left == x && g->right == x->parent) {
            rturn(tr,x->parent);
            x=x->right;
        }
    }
    insert_case_5(tr,x);
}

void insert_case_3(tree* &tr, tree* &x) {
    tree* u = uncle(x);
    tree* g = grprnt(x);
    if (g !=nil) {
        if (u != nil && u->color == 'r' && x->parent->color == 'r') {
            x->parent->color = 'b';
            u->color = 'b';
            g->color = 'r';
            insert_case_1(tr,g);
        }
        else insert_case_4(tr,x);
    }
}

void insert_case_2(tree* &tr, tree* &x) {
    if (x->parent->color == 'r') {
        insert_case_3(tr,x);
    }
    else {
        return;
    }
}

void insert_case_1(tree* &tr, tree* &x) {
    if (x->parent == nil) {
        x->color = 'b';
    }
    else insert_case_2(tr,x);
}

void delete_case_1(tree* &tr, tree* &x) {
    if ( x != nil && x->parent == nil) {
        return;
    }
    else delete_case_2(tr,x);
}

void delete_case_2(tree* &tr, tree* &x) {
    tree* s = sblng(x);
    if (s !=nil && s->color == 'r') {
        x->parent->color = 'r';
        s->color = 'b';
        if (x->parent->left == x) {
            lturn(tr,x->parent);
        }
        else rturn(tr,x->parent);
    }
    delete_case_3(tr,x);
}

void delete_case_3(tree* &tr, tree* &x) {
    tree* s = sblng(x);
    if (x != nil && x->parent != nil && s != nil && x->parent->color == 'b' && s->color == 'b' && s->right && s->left != nil && s->left->color == 'b' && s->right->color == 'b') {
        s->color = 'r';
        delete_case_1(tr,x);
    }
    else delete_case_4(tr,x);
}

void delete_case_4(tree* &tr, tree* &x) {
    tree* s = sblng(x);
    if (x != nil && x->parent != nil && x->parent->color == 'r' && s != nil && s->color == 'b' && s->right && s->left != nil && s->left->color == 'b' && s->right->color == 'b') {
        s->color = 'r';
        x->parent->color = 'r';
    }
    else delete_case_5(tr,x);
}

void delete_case_5(tree* &tr, tree* &x) {
    tree* s = sblng(x);
    if (s == nil) {
        delete_case_6(tr, x);
        return;
    }
    if (x != nil && x->parent->left == x && s->right && s->left != nil && s->right->color == 'b' && s->left->color == 'r') {
        s->color = 'r';
        s->left->color = 'b';
        rturn(tr, s);
    } 
    else if (x != nil && x->parent->right == x && s->left != nil && s->right != nil && s->left->color == 'b' && s->right->color == 'r') {
        s->color = 'r';
        s->right->color = 'b';
        lturn(tr, s);
    }
    delete_case_6(tr, x);
}

void delete_case_6(tree* &tr, tree* &x) {
    tree* s = sblng(x);
    if (s != nil) {
        s->color=s->parent->color;
        s->parent->color = 'b';
    }
    if (x != nil && x->parent->left == x) {
        if (s->right != nil) s->right->color = 'b';
        lturn(tr,x->parent);
    }
    else {
        if (x != nil && s->left != nil) s->left->color = 'b';
        rturn(tr,x->parent);
    }
}

void insert(tree* &tr, tree* &pr, int x) {
    if (x < pr->val && pr->left == nil) {
        pr->left = node(pr, x);
        insert_case_1(tr, pr->left);
    }
    else if (x > pr->val && pr->right == nil) {
        pr->right = node(pr, x);
        insert_case_1(tr, pr->right);
    }
    else {
        if (x < pr->val && pr->left != nil) {
            insert(tr, pr->left, x);
        }
        if (x > pr->val && pr->right != nil) {
            insert(tr, pr->right, x);
        }
    }
}

void replace(tree* &tr, tree* &u, tree* &v) {
    if (u->parent == nil)
        tr = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;
    if (v != nil)
        v->parent = u->parent;
}

void del(tree* &tr, tree*&x) {
    if (x == nil) return;                   
    tree* y = x;
    tree* child;
    char y_original_color = y->color;
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
        y_original_color = y->color;
        child = y->left;                   
        if (y->parent == x) {
            child->parent = y;             
        }
        else {
            replace(tr, y, y->left);
            y->left = x->left;
            y->left->parent = y;
        }
        replace(tr, x, y);
        y->right = x->right;
        y->right->parent = y;
        y->color = x->color;
    }

    if (y_original_color == 'b') {
        if ( child != nil && child->color == 'r') child->color = 'b';
        else {
            delete_case_1(tr, child);
        }
    }
    delete x;
    x = nil;                              
}

void inorder(tree* &tr) {
    if (tr != nil) {
        inorder(tr->left);
        cout << tr->val <<tr->color <<  ", ";
        // if (tr->left) cout << tr->left->val<<tr->left->color  << ", ";
        // if (tr->right) cout << tr->right->val<<tr->right->color  << ", ";
        //cout << endl;
        inorder(tr->right);
    }
}

void del_odd(tree* &tr, tree* &x) {
    if (x == nil) return;
    del_odd(tr, x->left);
    del_odd(tr,x->right);
    if (x->val % 2 != 0) {
        tree* tmp = x;
        del(tr, tmp);
    }
}

int main() { //task #12
    init_nil();
       
    int n;
    cout << "enter n:";
    cin >> n;
    tree* tr;
    int val;
    cin >> val;
    tr = root(val);
    for (int i = 1; i <n; i++) {
        cin >> val;
        insert(tr,tr,val);
    }
    inorder(tr);
    cout << endl;
    del_odd(tr,tr);
    inorder(tr);
}