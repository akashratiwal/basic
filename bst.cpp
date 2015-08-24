#include <iostream>
#include <signal.h>
#include <cstdlib>
#include <unistd.h>

using namespace std;

extern "C" void sig_handler(int signal_number)
{
	char a[200];
	getlogin_r(a, 200);
	cout << "\nDo not end this way :D " << a << endl;
	exit(0);
}

struct node {
	int data;
	struct node *left;
	struct node *right;

	node() {
		data = 0;
		left = right = NULL;
	}
};

class BST {
	public:
		node *root;

		BST()
		{
			root = NULL;
		}

		BST(int a)
		{
			root = new node;
			root->data = a;
			root->left = root->right = NULL;
		}

		void insert(int a)
		{
			struct node *cur, *prev, *tmp;
			
			cur = root;
			prev = NULL;
			if (!root) {
				tmp = new node;
				tmp->data = a;
				tmp->right = tmp->left = NULL;
				root = tmp;
				return;
			}
			while (cur) {
				prev = cur;
				if (a < cur->data) {
					cur = cur->left;
				} else if (a > cur->data) {
					cur = cur->right;
				} else {
					return;
				}			
			}
			tmp = new node;
			tmp->data = a;
			tmp->right = tmp->left = NULL;			
			if (a > prev->data) {
				prev->right = tmp;
			} else {
				prev->left = tmp;
			}	
		}

		bool search(int a)
		{
			node * cur = root;

			while (cur) {
				if (a < cur->data) {
					cur = cur->left;
				} else if (a > cur->data) {
					cur = cur->right;
				} else {
					return true;
				}			
			}
			return false;
		}

		node * inorder_succesor(node * root)
		{
			if (root->left == NULL) {
				return NULL;
			}
		}

		void remove(int a)
		{
			if (search(a)) {
				if (root->data == a) {
					node *cur, *tmp, *prev, *parent;
					cur = root;
					//if no right child
					if (cur->right == NULL) {
						if (left) {
							root = cur->left;
							delete cur;
							return;
						} else {
							root = cur->left;
							delete cur;
							return;
						}
					}
					//No left child
					if (cur->left == NULL) {
						if (left) {
							root = cur->right;
							delete cur;
							return;
						} else {
							root = cur->right;
							delete cur;
							return;
						}
					}
					prev = cur;	
					cur = cur->left;
					tmp = cur;
					//No child of left child of removing node
					if (cur->right == NULL) {
						if (left) {
							cur->right = prev->right;
							root = root->left;
							delete tmp;
							return;
						} else {
							cur->right = prev->right;
							root = root->left;
							delete tmp;
							return;
						}
					}
					//Traverse until full successor
					while (cur->right) {
						prev = cur;
						cur = cur->right;
					}
					tmp = cur;
					prev->right = cur->left;
					if (left) {
						cur->left = root->left;
						cur->right = root->right;
						delete root;				
						root = cur;
						return;
					} else {
						cur->left = root->left;
						cur->right = root->right;
						delete root->right;
						root = cur;
						return;
					}
				}
				node *cur, *tmp, *prev, *parent;
				bool left;

				left = false;
				cur = root;
				parent = NULL;
				//Search for parent of removing node
				while (cur) {
					if (a < cur->data) {
						parent = cur;
						cur = cur->left;
					} else if (a > cur->data) {
						parent = cur;
						cur = cur->right;
					} else {
						break;
					}	
				}
				//Determine whether left or right
				left = (parent->data > a) ? true : false;
				//if no right child
				if (cur->right == NULL) {
					if (left) {
						parent->left = cur->left;
						delete cur;
						return;
					} else {
						parent->right = cur->left;
						delete cur;
						return;
					}
				}
				//No left child
				if (cur->left == NULL) {
					if (left) {
						parent->left = cur->right;
						delete cur;
						return;
					} else {
						parent->right = cur->right;
						delete cur;
						return;
					}
				}
				prev = cur;			
				cur = cur->left;
				tmp = cur;
				//No child of left child of removing node
				if (cur->right == NULL) {
					if (left) {
						cur->right = prev->right;
						parent->left = parent->left->left;
						delete tmp;
						return;
					} else {
						cur->right = prev->right;
						parent->right = parent->right->left;
						delete tmp;
						return;
					}
				}
				//Traverse until full successor
				while (cur->right) {
					prev = cur;
					cur = cur->right;
				}
				tmp = cur;
				prev->right = cur->left;
				if (left) {
					cur->left = parent->left->left;
					cur->right = parent->left->right;
					delete parent->left;				
					parent->left = cur;
					return;
				} else {
					cur->left = parent->right->left;
					cur->right = parent->right->right;
					delete parent->right;
					parent->right = cur;
					return;
				}
			}
		}
		
		void inorder(node *head)
		{
			if (head) {
				inorder(head->left);
				cout << head->data << " ";
				inorder(head->right);
			}
		}

		void delete_tree(node * root)
		{
			if (root) {
				delete_tree(root->left);
				delete_tree(root->right);
				delete root;
			}
		}
};

int main()
{
	signal(SIGABRT, &sig_handler);
	signal(SIGINT, &sig_handler);
	int tmp;
	BST bs;

	cout << "1. Insert\n2. Delete\n3. Search\n4. Inorder\n5. Exit" << endl;
	while (1) {
		cin >> tmp;
		switch(tmp) {
			case 1:
				cin >> tmp;
				bs.insert(tmp);
				break;
			case 2:
				cin >> tmp;
				bs.remove(tmp);
				break;
			case 3:
				cin >> tmp;
				cout << (bs.search(tmp) ? "Found" : "Not found") << endl;
				break;
			case 4:
				bs.inorder(bs.root);
				cout << endl;
				break;			
			case 5:
				bs.delete_tree(bs.root);
				return 0;
		}
	}
	
	return 0;	
}
