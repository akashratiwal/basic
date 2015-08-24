#include <iostream>
#include <cstring>

#define TS 26
#define MAX 100

using namespace std;

struct node {
	struct node *a[TS];
	bool ar[TS];	
	
	//Constructor for node
	/*node() {
		for (int i = 0; i < TS; i++) {
			a[i] = NULL;
			ar[i] = false;
		}
	}*/
};

class Trie {
	public:
		struct node *root;
		
		Trie()
		{
			root = new node();
		}

		void insert(char *input, int size)
		{
			struct node *h;
			int i;
		
			h = root;
			for (i = 0; i < size; i++) {
				if (i == size - 1) {
					h->ar[input[i] - 'a'] = true;
					break;
				}
				if (!h->a[input[i] - 'a']) {
					h->a[input[i] - 'a'] = new node();
				}
				h = h->a[input[i] - 'a'];
			}
		}

		bool search(char *input, int size)
		{
			struct node *h;
			struct node *prev;
			int i;
		
			h = root;
			prev = NULL;
			if (root == NULL) {
				return false;
			}
			for (int i = 0; i < size; i++) {
				if (i == size - 1) {
					return (h->ar[input[i] - 'a']) ? true : false;
				}			
				if (h->a[input[i] - 'a']) {
					h = h->a[input[i] - 'a'];
				} else {
					return false;
				}
			}
		}
		
		void delete_tree(struct node *head)
		{
			if (!head) {
				return;
			}
			for (int i = 0; i < TS; i++) {
				delete_tree(head->a[i]);
			}
			delete head;
		}

		node *remove(node *t, char *input, int size)
		{
			if (size == 1) {
				t->ar[input[0] - 'a'] = false;
				bool flag = false;
				for (int i = 0; i < TS; i++) {
					if (t->ar[i] || t->a[i]) {
						flag = true;					
					}
				}
				if (flag) {
					return	t;
				} else {
					delete t;
					return NULL;
				}
			}
			t->a[input[0] - 'a'] = remove(t->a[input[0] - 'a'], input + 1, size - 1);
			bool flag = false;
			for (int i = 0; i < TS; i++) {
				if (t->ar[i] || t->a[i]) {
					flag = true;					
				}
			}
			if (flag) {
				return t;
			} else {
				delete t;
				return NULL;
			}
		}
};


int main()
{
	Trie t;
	int tmp;
	char st[MAX];

	cout << "1. Insert\n2. Search\n3. Remove\n4. Exit" << endl;
	while (1) {
		cin >> tmp;
		switch (tmp) {
			case 1:
				cin >> st;
				t.insert(st, strlen(st));
				break;
			case 2:
				cin >> st;
				cout << (t.search(st, strlen(st)) ? "Found" : "Not found") << endl;
				break;
			case 3:
				cin >> st;
				if (t.search(st, strlen(st))) {
					t.root = t.remove(t.root, st, strlen(st));
				}
				break;
			case 4:
				t.delete_tree(t.root);
				return 0;
		}
	}

	return 0;
}
