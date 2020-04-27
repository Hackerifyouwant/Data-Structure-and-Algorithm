#include<iostream>
#include<string>
#include<queue>

#define ll long long
#define endl '\n'

using namespace std;

/*---------------------------
parent <--> child：以pointer說明，被指向者(pointed)為child，指向者(point to)為parent。

siblings：擁有相同parent的node們，互相稱兄道弟。

descendant(子嗣)：圖四中，站在A，所有能夠以「parent指向child」的方式找到的node，皆稱為A的descendant，因此整棵樹除了A以外皆為A的descendant。

ancestor(祖先)：圖四中，站在K，所有能夠以「尋找parent」的方式找到的node，皆稱為K的ancestor，因此，E、B、A皆為K的ancestor。

path(路徑)：由descendant與ancestor關係連結成的edge，例如A-B-E-K、A-C-F-N。

level：定義root的level為1，其餘node的level為其parent的level加一。

height of node：某一node與其最長path上之descendant leaf node之間的edge數。

height of tree：樹的height即為root的height。

depth：某一node與root之間的edge數。
-----------------------------*/
class BinaryTree;
class TreeNode{
public:
    TreeNode *leftchild;
    TreeNode *rightchild;
    TreeNode *parent;
    string str;

    TreeNode():leftchild(0),rightchild(0),parent(0),str(""){};
    TreeNode(string s):leftchild(0),rightchild(0),parent(0),str(s){};
    
    friend class Tree;
};

class BinaryTree{
public:
    TreeNode *root;
    BinaryTree():root(0){};
    BinaryTree(TreeNode *node):root(node){};

    void Preorder(TreeNode *currrent);
    void Inorder(TreeNode *current);
    void Postorder(TreeNode *current);
    void Levelorder();

    TreeNode* leftmost(TreeNode *current);
    TreeNode* rightmost(TreeNode *current);

    TreeNode* InorderSuccessor(TreeNode *current);
    TreeNode* InorderPredecessor(TreeNode *current);

    void Inorder_by_parent(TreeNode *root);
    void Inorder_Reverse(TreeNode *root);
};

void BinaryTree::Preorder(TreeNode *current){
    if(current){
        cout << current->str << " ";
        Preorder(current->leftchild);
        Preorder(current->rightchild);
    }
}

void BinaryTree::Inorder(TreeNode *current){
    if(current){
        Inorder(current->leftchild);
        cout << current->str << " ";
        Inorder(current->rightchild);
    }
}

void BinaryTree::Postorder(TreeNode *current){
    if(current){
        Postorder(current->leftchild);
        Postorder(current->rightchild);
        cout << current->str << " ";
    }
}

void BinaryTree::Levelorder(){
    queue <TreeNode*> q;
    q.push(this->root);
    while(!q.empty()){
        TreeNode *current = q.front();
        q.pop();
        cout << current->str << " " ;
        if(current->leftchild){
            q.push(current->leftchild);
        }
        if(current->rightchild){
            q.push(current->rightchild);
        }
    }
}

TreeNode* BinaryTree::leftmost(TreeNode *current){
    while(current->leftchild){
        current = current->leftchild;
    }
    return current;
}

TreeNode* BinaryTree::rightmost(TreeNode *current){
    while(current->rightchild){
        current = current->rightchild;
    }
    return current;
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

void BinaryTree::Inorder_by_parent(TreeNode *root){
    TreeNode *current = new TreeNode;
    current = leftmost(root);

    while(current){
        cout << current->str << " ";
        current = InorderSuccessor(current); 
    }
}

TreeNode* BinaryTree::InorderPredecessor(TreeNode *current){
    if(current->leftchild){
        return rightmost(current->leftchild);
    }

    TreeNode *predecessor = current->parent;

    while(predecessor && predecessor->leftchild == current){
        current = predecessor;
        predecessor = predecessor->parent;
    }

    return predecessor;
}

void BinaryTree::Inorder_Reverse(TreeNode *root){
    TreeNode *current = new TreeNode;
    current = rightmost(root);

    while(current){
        cout << current->str << " ";
        current = InorderPredecessor(current);
    }
}


int main(){
    TreeNode *nodeA = new TreeNode("A"); 
    TreeNode *nodeB = new TreeNode("B"); 
    TreeNode *nodeC = new TreeNode("C"); 
    TreeNode *nodeD = new TreeNode("D"); 
    TreeNode *nodeE = new TreeNode("E"); 
    TreeNode *nodeF = new TreeNode("F"); 
    TreeNode *nodeG = new TreeNode("G"); 
    TreeNode *nodeH = new TreeNode("H"); 
    TreeNode *nodeI = new TreeNode("I"); 

    nodeA->rightchild = nodeC;
    nodeA->leftchild = nodeB;
    nodeB->rightchild = nodeE;
    nodeB->leftchild = nodeD;
    nodeC->leftchild = nodeF;
    nodeE->rightchild = nodeH;
    nodeE->leftchild = nodeG;
    nodeF->rightchild = nodeI;

    nodeB->parent = nodeA; 
    nodeC->parent = nodeA;
    nodeD->parent = nodeB; 
    nodeE->parent = nodeB;
    nodeG->parent = nodeE; 
    nodeH->parent = nodeE;
    nodeF->parent = nodeC; 
    nodeI->parent = nodeF;

    BinaryTree T(nodeA);

    cout << "Preorder" << endl ;
    T.Preorder(T.root);
    cout << endl ;
    cout << "Inorder" << endl ;
    T.Inorder(T.root);
    cout << endl ;
    cout << "Postorder" << endl ;
    T.Postorder(T.root);
    cout << endl ;
    cout << "Levelorder" << endl ;
    T.Levelorder();
    cout<<endl;
    cout << "Inorder_by_Parent" << endl ;    
    T.Inorder_by_parent(T.root);
    cout<<endl;
    cout << "Inorder_Reverse" << endl ;    
    T.Inorder_Reverse(T.root);
    cout<<endl;

    return 0;
}