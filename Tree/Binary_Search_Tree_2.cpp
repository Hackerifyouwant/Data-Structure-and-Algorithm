#include<iostream>
#include<queue>
#include<string>

#define ll long long
#define endl '\n'

using namespace std;


class BST;
class TreeNode{
private:
    TreeNode *leftchild;
    TreeNode *rightchild;
    TreeNode *parent;
    int key;
    string element;
public:
    TreeNode():leftchild(0),rightchild(0),parent(0),key(0),element(""){};
    TreeNode(int a, string b):leftchild(0),rightchild(0),parent(0),key(a),element(b){};

    int GetKey(){return key;}              // 為了在main()要能夠檢視node是否正確
    string GetElement(){return element;}   // 才需要這兩個member function讀取private data

    // 其餘情況, 因為class BST是class TreeNode的friend class
    // 在class BST的member function中, 可以直接存取class TreeNode的private data

    friend class BST;   // 放在 private 或 public 都可以 
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
    void InorderPrint();        // 可以用來確認BST是否建立成功
    void Levelorder();          // 可以確認BST是否建立成功
    void DeleteBST(int key);
};

TreeNode* BST::Search(int key){
    TreeNode *current = root;
    while(current && key != current->key){
        if(current->key > key){
            current = current->leftchild;
        }else if(current->key < key){
            current = current->rightchild;
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
        }else if(insert_node->key < x->key){
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

TreeNode* BST::Leftmost(TreeNode *current){
    while(current->leftchild){
        current = current->leftchild;
    }
    return current;
}

TreeNode* BST::Successor(TreeNode *current){
    if(current->rightchild){
        return Leftmost(current->rightchild);
    }

    TreeNode *new_node = current->parent;

    while(new_node && current == new_node->rightchild){
        current = new_node;
        new_node = new_node->parent;
    }

    return new_node;
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
    queue <TreeNode*> q;
    
    q.push(this->root);

    TreeNode *current = new TreeNode;

    while(!q.empty()){
        current = q.front();

        q.pop();
        
        cout << current->element << "(" << current->key << ")" << " ";
        
        if(current->leftchild)q.push(current->leftchild);
        if(current->rightchild)q.push(current->rightchild);
    }

}

void BST::DeleteBST(int key){
    TreeNode *delete_node = Search(key);
    if(delete_node == NULL){
        cout << "data not found.\n";
        return;
    }
    TreeNode *x = 0;
    TreeNode *y = 0;

    if(delete_node->leftchild == NULL || delete_node->rightchild == NULL){
        y = delete_node;        
    }else{
        y = Successor(delete_node);
    }

    if(y->leftchild){
        x = y->leftchild;
    }else{
        x = y->rightchild;
    }

    if(x){
        x->parent = y->parent;
    }

    if(y->parent == NULL){
        this->root = x;
    }else if(y == y->parent->leftchild){
        y->parent->leftchild = x;
    }else{
        y->parent->rightchild = x;
    }

    if(y != delete_node){
        delete_node->key = y->key;
        delete_node->element = y->element;
    }

    delete y;
    y = 0;
}



int main(){
    BST T;

    T.InsertBST(8,"龜仙人");
    T.InsertBST(1000,"悟空");
    T.InsertBST(2,"克林");
    T.InsertBST(513,"比克");


    cout << "Inorder Traversal:\n";
    T.InorderPrint();
    cout << endl << endl;
    cout << "Level-order Traversal:\n";
    T.Levelorder();
    cout << endl << endl;

    T.DeleteBST(8);         // 刪除龜仙人(8), 確認比克(513)會成為新的root
    T.DeleteBST(513);

    cout << "Level-order Traversal:\n";
    T.Levelorder();
    cout << endl << endl;

    TreeNode *node = T.Search(1000);
    if(node != NULL){
        cout << "There is " << node->GetElement() << "(" << node->GetKey() << ")" << endl;
    }
    else {
        cout << "no element with Key(1000)" << endl;
    }

    node = T.Search(8);
    if(node != NULL){
        cout << "There is " << node->GetElement() << "(" << node->GetKey() << ")" << endl;
    }
    else {
        cout << "no element with Key(8)" << endl;
    }

    return 0;

    
}