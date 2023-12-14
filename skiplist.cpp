#include <bits/stdc++.h>

using namespace std;

struct node {
    int val;
    node *right, *down;
    node(int v, node* r = nullptr, node* d = nullptr) : val(v), right(r), down(d) {} //constructor syntax
};

class Skiplist {
    private:
        node* head;
        int maxLevel;

        node* newNode(int num, node* next, node* down) {
            return new node(num, next, down); 
        }

        int flipCoin() {
            int coin = rand() % 2;
            //cout << coin << "\n";
            return coin;
        }

    public:
        //set max level to log base 2 of number of elements (E[number of elements on one level] = half of prev level)
        Skiplist(int max = 3) : head(nullptr), maxLevel(max) {
            head = newNode(INT_MIN, nullptr, nullptr);
            for (int i = 1; i < maxLevel; i++) {
                //make maxLevel - 1 levels, head should point to top level
                node* newHead = newNode(INT_MIN, nullptr, head);
                head = newHead;
            }
        }

        void printSkiplist() {
            node* curr = head;
            while (curr) {
                node* express = curr;
                while (express) {
                    cout << express->val << " ";
                    express = express->right;
                }
                cout << "\n";
                curr = curr->down;
            }
        }

        //from here, functions are similar to bst functions
        node* search(int val) {
            node* curr = head;

            while(curr) {
                if (curr->val == val) {
                    break;
                } else if (curr->right && curr->right->val <= val) {
                    curr = curr->right;
                } else {
                    curr = curr->down;
                }
        }
            return curr;
    }

        void insert(int val) {
            //utilize stack, keep track of previous nodes
            stack<node*> s;
            node* curr = head;

            while (curr) {
                if (curr->val == val) {
                    //if value already exists, return
                    return;
                } else if (curr->right && curr->right->val <= val) {
                    curr = curr->right;
                } else {
                    //store prev node before going down
                    s.push(curr);
                    curr = curr->down;
                }
            }

            //curr should point to the node at the bottom level before the value inserted
            node* downNode = nullptr;
            bool insertUp = true;

            while (!s.empty() && insertUp) {
                node* newVal = newNode(val, s.top()->right, downNode);
                s.top()->right = newVal;
                downNode = newVal;
                s.pop();

                insertUp = flipCoin() == 0 ? false : true;
            }
            return;
        }

        void del(int val) {
            node* curr = head;
            stack<node*> s;

            while (curr) {
                if (curr->right && curr->right->val == val) {
                    //store previous nodes in stack
                    s.push(curr);
                    curr = curr->down;
                } else if (curr->right && curr->right->val < val) {
                    curr = curr->right;
                } else {
                    curr = curr->down;
                }
            }

            while (!s.empty()) {
                node* temp = s.top()->right;
                s.top()->right = s.top()->right->right;
                delete temp;
                s.pop();
            }
            return;
        }

        void insert20(int val, int counter) {
            //utilize stack, keep track of previous nodes
            stack<node*> s;
            node* curr = head;

            while (curr) {
                if (curr->val == val) {
                    //if value already exists, return
                    return;
                } else if (curr->right && curr->right->val <= val) {
                    curr = curr->right;
                } else {
                    //store prev node before going down
                    s.push(curr);
                    curr = curr->down;
                }
            }

            //curr should point to the node at the bottom level before the value inserted
            node* downNode = nullptr;

            for (int i = 0; i <= counter; i++) {
                node* newVal = newNode(val, s.top()->right, downNode);
                s.top()->right = newVal;
                downNode = newVal;
                s.pop();
            }
            return;
        }
};

int main(){
    srand(time(nullptr));
    Skiplist sl;
    sl.insert20(20, 2);
    sl.insert(40);
    sl.insert(10);
    sl.insert(20);
    sl.insert(5);
    sl.insert(80);
    sl.printSkiplist();
    sl.del(20);
    sl.printSkiplist();
    sl.insert(100);
    sl.insert20(20, 1);
    sl.insert(30);
    sl.printSkiplist();
    sl.del(5);
    sl.insert(50);
    sl.printSkiplist();
    sl.search(80) ? cout << "found!\n" : cout << "DNE!\n";
    sl.search(70) ? cout << "found!\n" : cout << "DNE!\n";
}

