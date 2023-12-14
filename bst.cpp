#include <bits/stdc++.h>

using namespace std;

struct node {
    int val;
    node *left, *right;
};

node* newNode(int num) {
    node* temp = new node;
    temp->val = num;
    temp->left = temp->right = NULL;
    return temp;
}

node* insert(int num, node* root) {
    if (!root) {
        return newNode(num);
    }

    if (num < root->val) {
        root->left = insert(num, root->left); 
    } else if (num > root->val) {
        root->right = insert(num, root->right);
    }
    return root;
}

//binary search
node* search(int num, node* root) {
    if (!root || root->val == num) {
        return root;
    } else if (num < root->val) {
        return search(num, root->left);
    } else {
        return search(num, root->right);
    }
}

node* del(int num, node* root) {
    if (!root){return root;}
    //find node to remove
    if (root->val > num){
        root->left = del(num, root->left);
        return root;
    } else if (root->val < num){
        root->right = del(num, root->right);
        return root;
    }

    //case 1 & 2: leaf node or only one child
    if (!root->left) {
        node* temp = root->right;
        delete root;
        return temp;
    } else if (!root->right) {
        node* temp = root->left;
        delete root;
        return temp;
    } else {
        //case 3: both children present
        node* swapNodeParent = root;
        node* swapNode = root->right;
        //go right once, then go all the way left to find successor
        while (swapNode->left) {
            swapNodeParent = swapNode;
            swapNode = swapNode->left;
        }

        if (swapNodeParent == root) {
            //subcase: depth of right->left subtree is 1
            swapNodeParent->right = swapNode->right;
        } else {
            swapNodeParent->left = swapNode->right;
        }

        //swap, delete, return
        root->val = swapNode->val;
        delete swapNode;
        return root;
    }
}

//dfs in order print
void inOrderPrint(node* root) {
    if (root) {
        inOrderPrint(root->left);
        cout << root->val << " ";
        inOrderPrint(root->right);
    }
}

int main(){
    node* root = NULL;
    root = insert(20, root);
    insert(40, root);
    insert(10, root);
    insert(20, root);
    insert(5, root);
    insert(80, root);
    inOrderPrint(root); cout << "\n";
    del(20, root);
    inOrderPrint(root); cout << "\n";
    insert(100, root);
    insert(20, root);
    insert(30, root);
    inOrderPrint(root); cout << "\n";
    del(5, root);
    insert(50, root);
    inOrderPrint(root); cout << "\n";
    search(80, root) ? cout << "exists!\n" : cout << "does not exist :(\n";
    search(70, root) ? cout << "exists!\n" : cout << "does not exist :(\n";
    return 0;
}

