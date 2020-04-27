#include<iostream>
#include<sstream>
#include<queue>

#define ll long long
#define endl '\n'

using namespace std;

class BinaryTree;
class TreeNode{
private:
    TreeNode *leftchild;
    TreeNode *rightchild;
    TreeNode *parent;
    char data;
public:
    TreeNode():leftchild(0),rightchild(0),parent(0),data('x'){};
    TreeNode(char s):leftchild(0),rightchild(0),parent(0),data(s){};

    friend class BinaryTree;
};

class BinaryTree{
private:
    TreeNode *root;
public:
    BinaryTree():root(0){};
    BinaryTree(const char* str);

    void LevelorderConstruct(stringstream &ss);
    void InsertLevelorder(char data);

    TreeNode* leftmost(TreeNode *current);
    TreeNode* InorderSuccessor(TreeNode *current);
    void Inorder_by_parent();
};

TreeNode* BinaryTree::leftmost(TreeNode *current){
    while(current->leftchild){
        current = current->leftchild;
    }
    return current;
}

void BinaryTree::Inorder_by_parent(){
    TreeNode *current = new TreeNode;
    current = leftmost(root);

    while(current){
        cout << current->data << " ";
        current = InorderSuccessor(current); 
    }
}

TreeNode* BinaryTree::InorderSuccessor(TreeNode *current){
    if(current->rightchild){
        return leftmost(current->rightchild);
    }

    TreeNode *successor = current->parent;
    while(successor && current == successor->rightchild){
        current = successor;
        successor = successor->parent;
    }
    return successor;
}

BinaryTree::BinaryTree(const char* str){
    stringstream ss;
    ss << str;

    root = new TreeNode;
    ss >> root->data;

    LevelorderConstruct(ss);
}

void BinaryTree::LevelorderConstruct(stringstream &ss){
    queue<TreeNode*> q;
    TreeNode *current = root;
    char data = 'x';

    while(ss >> data){
        if(data >= 65 && data <= 90){
            TreeNode *new_node = new TreeNode(data);
            new_node->parent = current;
            current->leftchild = new_node;
            q.push(new_node);
        }
        if(!(ss >> data))break;
        if(data >= 65 && data <= 90){
            TreeNode *new_node = new TreeNode(data);
            new_node->parent = current;
            current->rightchild = new_node;
            q.push(new_node);
        }
        current = q.front();
        q.pop();
    }
}

void BinaryTree::InsertLevelorder(char data){
    queue<TreeNode*> q;
    TreeNode *current = root;

    while(current){
        if(current->leftchild){
            q.push(current->leftchild);
        }else{
            TreeNode *new_node = new TreeNode(data);
            new_node->parent = current;
            current->leftchild = new_node;
            break;
        }
        if(current->rightchild){
            q.push(current->rightchild);
        }else{
            TreeNode *new_node = new TreeNode(data);
            new_node->parent = current;
            current->rightchild = new_node;
            break;
        }
        current = q.front();
        q.pop();
    }
}


int main(){
    const char *a = "A B C D E F x x x G H x I";
    BinaryTree T(a);
    T.Inorder_by_parent();

    cout<<endl;
    
    T.InsertLevelorder('K');
    T.InsertLevelorder('L');
    T.InsertLevelorder('M');
    T.InsertLevelorder('N');
    T.Inorder_by_parent();
    cout << endl;

    cout << endl;


    return 0;
}