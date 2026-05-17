#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include <map>

using namespace std;

ifstream in("in.txt");
ofstream out("output.txt");

struct date {
	int dd, mm, yy;
};

struct people {
	string lastname;
	string position;
	date bd;
	int exp=1;
	int wage=1;
};

date strtodate(string s) {
	date x;
	string cttr = s.substr(0, 2);
	x.dd = atoi(cttr.c_str());
	cttr = s.substr(3, 2);
	x.mm = atoi(cttr.c_str());
	cttr = s.substr(6, 4);
	x.yy = atoi(cttr.c_str());
	return x;
}
vector<people> input() {
	vector<people> x;
	people p;
	while (in.peek() != EOF) {
		in >> p.lastname;
		in >> p.position;
		string bds;
		in >> bds;
		p.bd = strtodate(bds);
		in >> bds;
		p.exp = atoi(bds.c_str());
		in >> bds;
		p.wage = atoi(bds.c_str());
		x.push_back(p);
	}
	return x;
}

void output(people x) {
	out << setw(10) << left << x.lastname;
	out << setw(10) << left << x.position;
	if (x.bd.dd < 10) out << left << '0' << x.bd.dd << '.';
	else out <<left << x.bd.dd << '.';
	if (x.bd.mm < 10) out << '0' << x.bd.mm << '.';
	else out << x.bd.mm << '.';
	out << setw(6) << x.bd.yy;
	out << setw(6) << left << x.exp;
	out << setw(7) << left << x.wage;
}

struct list {
	people val;
	list* next;
	list* prev;
};

void push(list*& h, list*& t, people i) {
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
		std::cout << p->val.bd.dd << " " << p->val.exp << " " << p->val.lastname << " " << p->val.position << " " << p->val.wage << "; ";
		p = p->next;
	}
}

list* find(people i, list* h, list* t) {
	list* p = h;
	while (!p) {
		if (p->val.lastname == i.lastname) {
			break;
		}
		p = p->next;
	}
	return p;
}

// void insert(people i, list*& h, list*& t, list* b) {
// 	list* p = new list;
// 	if (b == t) {
// 		b->next = p;
// 		p->next = NULL;
// 		p->prev = b;
// 		p->val = i;
// 		t = p;
// 	}
// 	else {
// 		p->next = b->next;
// 		b->next->prev = p;
// 		p->prev = b;
// 		p->val = i;
// 		b->next = p;
// 	}
// }

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



// void insertsort(list*& h, list*& t) {
// 	list* fl = h->next;
// 	list* p = h;
// 	list* tmp = fl;
// 	list* tmp1 = fl;
// 	int a, b = 0;
// 	bool fll = false;
// 	if (fl->val < p->val) {
// 		a = p->val;
// 		b = fl->val;
// 		insert(b, h, t, p);
// 		insert(a, h, t, fl);
// 		pop(h, t, h);
// 		pop(h, t, h->next);
// 	}
// 	fl = h->next->next;
// 	while (fl) {
// 		p = h;
// 		while (fl->val > p->val) {
// 			p = p->next;
// 		}
// 		if (p->prev) {
// 			insert(fl->val, h, t, p->prev);
// 		}
// 		else {
// 			list* r = new list;
// 			r->val = fl->val;
// 			r->next = h;
// 			r->prev = NULL;
// 			h = r;
// 			h->next->prev = r;
// 		}
// 		tmp = fl;
// 		fl = fl->next;
// 		//cout << tmp->next->prev->val << '\n';
// 		pop(h, t, tmp);
// 	}
//}

vector<vector<list*>> hashing(vector<people> res) {
	int m = res.size() / 4;
    int h;
    vector<vector<list*>> hash(m, {NULL, NULL});
    for (int i = 0; i <res.size(); i++) {
        h = res[i].wage % m;
        push(hash[h][0], hash[h][1], res[i]);
    }
	return hash;
}

void delette(vector<vector<list*>>& hash, people x,int m) {
	int h = x.wage % m;
	list* i = hash[h][0];
	while (i) {
		if (i->val.lastname == x.lastname) {
			//cout << x.lastname << " ";
			pop(hash[h][0], hash[h][1], i);
			break;
		}
		i = i->next;
	}
}

void findd(vector<vector<list*>> &hash, people x,int m) {
	int h = x.wage % m;
	list* i = hash[h][0];
	while (i) {
		if (i->val.lastname == x.lastname) {
			std::cout << i->val.bd.dd << " " << i->val.exp << " " << i->val.lastname << " " << i->val.position << " " << i->val.wage << endl;
			break;
		}
		i = i->next;
	}
	
}

void insert(vector<vector<list*>> &hash, people x,int m) {
	int h = x.wage % m;
	push(hash[h][0], hash[h][1], x);
}

int main() {
   	vector<people> res = input();
    int m = res.size() / 4;
    int h;
	people x;
	cout << "Enter subject's birthday: ";
	cin >> x.bd.dd;
	cout << "Enter subject's birtmonth: ";
	cin >> x.bd.mm;
	cout << "Enter subject's birtyear: ";
	cin >> x.bd.yy;
	cout << "Enter subject's lastname: ";
	cin >> x.lastname;
	cout << "Enter subject's experience: ";
	cin >> x.exp;
	cout << "Enter subject's position: ";
	cin >> x.position;
	cout << "Enter subject's wage: ";
	cin >> x.wage;
    vector<vector<list*>> hash = hashing(res);
	for (auto &i : hash) {
		print(i[0], i[1]);
		std::cout << endl;
	}
	cout << endl;
	insert(hash,x,m);
	for (auto &i : hash) {
		print(i[0], i[1]);
		std::cout << endl;
	}
	cout << endl;
	findd(hash,x,m);
	delette(hash,x,m);
	for (auto &i : hash) {
		print(i[0], i[1]);
		std::cout << endl;
	}
	cout << endl;
	
}