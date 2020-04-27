#include<iostream>
#include<string.h>
#include<queue>

#define ll long long
#define endl '\n'

using namespace std;

class TreeNode{
private:
    TreeNode *leftchild;
    TreeNode *rightchild;
    TreeNode *parent;
    int key;
    string element;
public:
    TreeNode():leftchild(0),rightchild(0),parent(0),key(0),element(""){};
    TreeNode(int a,string b):leftchild(0),rightchild(0),parent(0),key(a),element(b){};

    int GetKey(){return key;}
    string GetElement(){return element;}

    friend class BST;
};

class BST{
private:
    TreeNode *root;
    TreeNode* Leftmost(TreeNode *current);
    TreeNode* Successor(TreeNode *current);
public:
    BST():root(0){};

    TreeNode* Search(int key);
    void InsertBST(int key, string element);
    void InorderPrint();
    void Levelorder();      
};

TreeNode* BST::Leftmost(TreeNode *current){
    while(current->leftchild){
        current = current->leftchild;
    }
    return current;
}

void BST::InorderPrint(){
    TreeNode *current = new TreeNode;
    current = Leftmost(root);
    while(current){
        cout << current->element << "(" << current->key << ")" << " ";
        current = Successor(current);
    }
}

void BST::Levelorder(){
    queue<TreeNode*> q;
    q.push(this->root);
    
    while(!q.empty()){
    
        TreeNode *current = q.front();
    
        q.pop();
    
        cout << current->element << "(" << current->key << ")" << " ";   
    
        if(current->leftchild)q.push(current->leftchild);
    
        if(current->rightchild)q.push(current->rightchild);
        
    }
}

TreeNode* BST::Successor(TreeNode *current){
    
    if(current->rightchild){
        return Leftmost(current->rightchild); 
    }

    TreeNode *successor = current->parent;

    while(successor && successor->rightchild == current){
        current = successor;
        successor = successor->parent;
    }

    return successor;
    
}

TreeNode* BST::Search(int KEY){

    TreeNode *current = root;
    
    while(current && KEY != current->key){
        
        if(KEY > current->key){
            current = current->rightchild;
        }else{
            current = current->leftchild;
        }
    }
    
    return current;
}

void BST::InsertBST(int key, string element){
    TreeNode *x = 0;
    TreeNode *y = 0;
    TreeNode *insert_node = new TreeNode(key, element);

    x = root;
    while(x){
        y = x;
        if(insert_node->key > x->key){
            x = x->rightchild;
        }else{
            x = x->leftchild;
        }
    }

    insert_node->parent = y;

    if(y == NULL){
        this->root = insert_node;
    }else if(insert_node->key > y->key){
        y->rightchild = insert_node;
    }else{
        y->leftchild = insert_node;
    }
}

int main(){
    BST T;

    T.InsertBST(8,"龜仙人");
    T.InsertBST(1000,"悟空");
    T.InsertBST(2,"克林");
    T.InsertBST(513,"比克");


    cout << "Inorder Traversal:" << endl;
    T.InorderPrint();
    cout << endl;
    cout << "Level-order Traversal:" << endl;
    T.Levelorder();
    cout << endl << endl;

    TreeNode *node = T.Search(1000);
    if(node != NULL){
        cout << "There is " << node->GetElement() << "(" << node->GetKey() << ")" << endl;
    }else {
        cout << "no element with Key(1000)" << endl;
    }

    node = T.Search(73);
    if(node != NULL){
        cout << "There is " << node->GetElement() << "(" << node->GetKey() << ")" << endl;
    }else {
        cout << "no element with Key(73)" << endl;
    }

    return 0; 
}