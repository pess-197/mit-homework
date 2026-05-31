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

tree* root(int x) {
    tree* r = new tree;
    r->color = 'b';
    r->val = x;
    r->left = NULL;
    r->right = NULL;
    r->parent = NULL;
    return r;
}

tree* node(tree* &tr, int x) {
    tree* r = new tree;
    r->color = 'r';
    r->val = x;
    r->left = NULL;
    r->right = NULL;
    r->parent = tr;
    return r;
}

tree* lturn(tree* &tr, tree* &x) {
    tree* y = x->right;
    x->right = y->left;
    if (y->left->left || y->left->right) {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent->left == x) {
        x->parent->left = y;
    }
    else x->parent->right = y;
    y->left = x;
    x->parent = y;
    if (!y->parent) {
        y->color = 'b';
        return y;
    }
    return tr;
}

tree* rturn(tree* &tr, tree* &x) {
    tree* y = x->left;
    x->left = y->right;
    if (y->right->right || y->right->left) {
        y->right->parent = x;
    }
    y->parent = x->parent;
    if (x->parent->left == x) {
        x->parent->left = y;
    }
    else x->parent->right = y;
    y->right = x;
    x->parent = y;
    if (!y->parent) {
        y->color = 'b';
        return y;
    }
    return tr;
}

tree* grprnt (tree* &x) {
    if (x && x->parent) {
        return x->parent->parent;
    }
    else return NULL;
}

tree* uncle(tree* &x) {
    tree* g = grprnt(x);
    if (!g) {
        return NULL;
    }
    else if (g->right == x->parent) {
        return g->left;
    }
    else return g->right;
}

tree* sblng (tree* &x) {
    if (x && x->parent) {
        if (x->parent->left == x) {
            return x->parent->right;
        }
        else return x->parent->left;
    }
    else return NULL;
}

tree* min(tree* tr) {
    if (!tr->left) {
        return tr;
    }
    else return min(tr->left);
}

tree* max(tree* tr) {
    if (!tr->right) {
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
    x->parent->color = 'b';
    g->color = 'r';
    if (x->parent->left == x && g->left == x->parent) {
        rturn(tr,g);
    }
    else lturn(tr,g);
}

void insert_case_4(tree* &tr, tree* &x) {
    tree* g = grprnt(x);
    if (x->parent->right == x && g->left == x->parent) {
        lturn(tr,x);
        x=x->left;
    }
    else {
        if (x->parent->left == x && g->right == x->parent) {
            rturn(tr,x);
            x=x->right;
        }
    }
    insert_case_5(tr,x);
}

void insert_case_3(tree* &tr, tree* &x) {
    tree* u = uncle(x);
    tree* g = grprnt(x);
    if (u && u->color == 'r' && x->parent->color == 'r') {
        x->parent->color = 'b';
        u->color = 'b';
        g->color = 'r';
        insert_case_1(tr,g);
    }
    else insert_case_4(tr,x);
}

void insert_case_2(tree* &tr, tree* &x) {
    if (x->color = 'r') {
        insert_case_3(tr,x);
    }
    else return;
}

void insert_case_1(tree* &tr, tree* &x) {
    if (!x->parent) {
        x->color = 'b';
    }
    else insert_case_2(tr,x);
}

void delete_case_1(tree* &tr, tree* &x) {
    if (!x->parent) {
        if (x->left) {
            tr = x->left;
        }
        else tr = x->right;
    }
    else delete_case_2(tr,x);
}

void delete_case_2(tree* &tr, tree* &x) {
    tree* s = sblng(x);
    if (s->color == 'r') {
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
    if (x->parent->color == 'b' && s->color == 'b' && (s->left->color == 'b' || (!s->left->left && !s->left->right)) && (s->right->color == 'b' || (!s->right->left && !s->right->right))) {
        s->color = 'r';
        delete_case_1(tr,x);
    }
    else delete_case_4(tr,x);
}

void delete_case_4(tree* &tr, tree* &x) {
    tree* s = sblng(x);
    if (x->parent->color == 'r' && s->color == 'b' && (s->left->color == 'b' || (!s->left->left && !s->left->right)) && (s->right->color == 'b' || (!s->right->left && !s->right->right))) {
        s->color = 'r';
        x->parent->color = 'r';
    }
    else delete_case_5(tr,x);
}

void delete_case_5(tree* &tr, tree* &x) {
    tree* s = sblng(x);
    if (x->parent->left == x && (s->left->color == 'r' && (s->left->left || s->left->right)) && (s->right->color == 'b' || (!s->right->left && !s->right->right))) {
        s->color = 'r';
        s->left->color = 'b';
        lturn(tr,s);
    }
    else if (x->parent->right == x && (s->right->color == 'r' && (s->right->left || s->right->right)) && (s->left->color == 'b' || (!s->left->left && !s->left->right))) {
        s->color = 'r';
        s->right->color = 'b';
        rturn(tr,s);
    }
    delete_case_6(tr,x);
}

void delete_case_6(tree* &tr, tree* &x) {
    tree* s = sblng(x);
    s->color=s->parent->color;
    s->parent->color = 'b';
    if (x->parent->left == x) {
        s->right->color = 'b';
        lturn(tr,x->parent);
    }
    else {
        s->left->color = 'b';
        rturn(tr,x->parent);
    }
}

void insert(tree* &tr, tree* &pr, int x) {
    if (x < pr->val && !pr->left) {
        pr->left = node(pr,x);
        insert_case_1(tr,pr->left);
    }
    else {
        if (x > pr->val && !pr->right) {
            pr->right = node(pr,x);
            insert_case_1(tr,pr->right);
        }
        else {
            if (x < pr->val && pr->left) {
                insert(tr,pr->left,x);
            }
            if (x > pr->val && pr->right) {
                insert(tr,pr->right,x);
            }
        }
    }
}

void replace(tree* &tr, tree* &x) {
    if (x->left) {
        tree* ch = x->left;
        ch->parent = x->parent;
        if (x->parent) {
            if (x->parent->left == x) {
                x->left = ch;
            }
            else x->right = ch;
        }
    }
    else {
        tree* ch = x->right;
        ch->parent = x->parent;
        if (x->parent) {
            if (x->parent->right == x) {
                x->right = ch;
            }
            else x->left = ch;
        }
    }
}

void del(tree* &tr, tree*&x) {
    tree* tmp;
    tree* t;
    if (x->left && x->right) {
        if (x->val <= tr->val) {
            tmp = max(x);
        }
        else tmp = min(x);
        t->val = x->val;
        x->val = tmp->val;
        tmp->val = t->val;
        x = tmp;
    }
    if (x->left || x->right) {
        if (x->left && !x->right) {
            t= x->left;
        }
        if (x->right && !x->left) {
            t= x->right;
        }
        replace(tr,x);
        if (x->color == 'b') {
            if (t->color == 'r') {
                t->color = 'b';
            }
            else delete_case_1(tr,x);
        }
    }
    else {
        if (x->color == 'b') {
            delete_case_1(tr,x);
        }
        else {
            if (x->parent->left == x) {
                x->parent->left = NULL;
            }
            else x->parent->right = NULL;
        }
    }
    delete x;
}