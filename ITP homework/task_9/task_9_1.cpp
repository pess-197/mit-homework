#include <iostream>

using namespace std;

struct list {
	int val;
	list* next;
	list* prev;
};

void push(list*& h, list*& t, int i) {
	list* p = new list;
	p->val = i;
	p->next = NULL;
	if (!h && !t) {
		p->prev = NULL;
		h = p;
	}
	else {
		t->next = p;
		p->prev = t;
	}
	t = p;
}

void print(list* h, list* t) {
	list* p = h;
	while (p) {
		std::cout << p->val << " ";
		p = p->next;
	}
}

list* find(int i, list* h, list* t) {
	list* p = h;
	while (!p) {
		if (p->val == i) {
			break;
		}
		p = p->next;
	}
	return p;
}

void insert(int i, list*& h, list*& t, list* b) {
	list* p = new list;
	if (b == t) {
		b->next = p;
		p->next = NULL;
		p->prev = b;
		p->val = i;
		t = p;
	}
	else {
		p->next = b->next;
		b->next->prev = p;
		p->prev = b;
		p->val = i;
		b->next = p;
	}
}

void pop(list*& h, list*& t, list* b) {
	list* p = b;
	if (b == t && b == h) {
		h = t = NULL;
	}
	else if (b == h) {
		h = h->next;
		h->next->prev = h;
		h->prev = NULL;
	}
	else if (b == t) {
		t = t->prev;
		t->next = NULL;
	}
	else {
		b->prev->next = b->next;
		b->next->prev = b->prev;
	}
	delete p;
}


void del(list*& h, list*& t) {
	while (h) {
		list* p = h;
		h = h->next;
		delete p;
	}
}



void insertsort(list*& h, list*& t) {
	list* fl = h->next;
	list* p = h;
	list* tmp = fl;
	list* tmp1 = fl;
	int a, b = 0;
	bool fll = false;
	if (fl->val < p->val) {
		a = p->val;
		b = fl->val;
		insert(b, h, t, p);
		insert(a, h, t, fl);
		pop(h, t, h);
		pop(h, t, h->next);
	}
	fl = h->next->next;
	while (fl) {
		p = h;
		while (fl->val > p->val) {
			p = p->next;
		}
		if (p->prev) {
			insert(fl->val, h, t, p->prev);
		}
		else {
			list* r = new list;
			r->val = fl->val;
			r->next = h;
			r->prev = NULL;
			h = r;
			h->next->prev = r;
		}
		tmp = fl;
		fl = fl->next;
		//cout << tmp->next->prev->val << '\n';
		pop(h, t, tmp);
	}

}
