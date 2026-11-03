#include<iostream>
using namespace std;

struct Node{
    int data;
    Node* left;
    Node* right;

    Node(int val){
        data = val;
        left =  nullptr;
        right = nullptr;
    }
};

void inOrder(Node* root){
    if(root == NULL) return ;

    inOrder(root->left);
    cout<<root->data <<"  "; 
    inOrder(root->right);
}

void changeRootData(Node* root){
    if(root == NULL) return ;

    root = new Node(89);
    return ;
}


Node* mirrorTree(Node* root, Node* mirror){
    if(root == NULL) return nullptr;

    mirror = new Node(root->data);

    mirror->left = mirrorTree(root->right, mirror->left);
    mirror->right = mirrorTree(root->left , mirror->right);
    return mirror;
}

void mirrorInSameTree(Node* root){
    if(root == NULL) return ;

    Node* temp = root->left;
    root->left = root->right;
    root->right = temp;

    if(root->left) mirrorInSameTree(root->left);
    if(root->right) mirrorInSameTree(root->right); 
}

int main() {
    
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);
    root->right->left = new Node(6);
    root->right->right = new Node(7);

    // changeRootData(root);


    inOrder(root);
    cout<<"\n\n\n";
    // Mirror the binary tree
    Node* mirror = mirrorTree(root , mirror);   //making other mirror tree
    inOrder(mirror);
    cout<<"\n\n\n";

    //now making the mirror in the same tree
    mirrorInSameTree(root);
    inOrder(root);  
    return 0;
}

