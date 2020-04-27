// C++ code
#include <iostream>
#include <string>

#define ll long long
#define endl '\n'

using namespace std;

/*-----------------------------
1. RBT中的每一個node不是黑色就是紅色。
2. root一定是黑色。
3. 每一個leaf node(也就是NIL)一定是黑色。
4. 如果某個node是紅色，那麼其兩個child必定是黑色，不能有兩個紅色node相連，如圖四中的node(17)、node(30)。
   若某個node為黑色，其child之顏色沒有限制，如圖四中的node(38)、node(26)、node(21)。
5. 站在任何一個node上，所有從該node走到其任意descendant leaf的path上之黑色node數必定相同。
   以圖四為例，站在node(14)上，所有從node(14)走向其descendant leaves(也就是NIL)的path上之黑色node數必為3：
   path1:14(b)-10(r)-7(b)-3(r)-NIL(b)；
   path2:14(b)-10(r)-7(b)-NIL(b)；
   path3:14(b)-10(r)-12(b)-NIL(b)；
   path4:14(b)-16(b)-15(r)-NIL(b)；
   path5:14(b)-16(b)-NIL(b)；

根據上述特徵的第四點與第五點，RBT中path可能的長度最小值一定是全部node皆為黑色(如圖四最右path)，而path可能的長度最大值並定是紅色-黑色相間(如圖四最左path)，如此便確保RBT擁有最長path(路徑)不會超過最短path的兩倍的特性。
color:r(0),b(1)
-------------------------------*/

class RBT;
class TreeNode{
private:
    TreeNode *leftchild;
    TreeNode *rightchild;
    TreeNode *parent;
    std::string element;
    int key;
    int color;         // 0: Red, 1: Black; using type:bool is ok
public:
    TreeNode():leftchild(0),rightchild(0),parent(0),element(""),key(0),color(0){};
    TreeNode(string str, int a):leftchild(0),rightchild(0),parent(0),element(str),key(a),color(0){};    
    
    friend RBT;
};
class RBT{
private:
    TreeNode *root;
    TreeNode *neel;    // 此即為NIL, 常被稱為sentinel
public:
    void LeftRotation(TreeNode *x);
    void RightRotation(TreeNode *x);
    void InsertRBT(int key, string element);
    void InsertFixedUpRBT(TreeNode *current);
    void DeleteRBT(int KEY);
    void DeleteFixedUpRBT(TreeNode *current);
    TreeNode* Leftmost(TreeNode *current);
    TreeNode* Successor(TreeNode *current);
    TreeNode* Search(int key);
};

TreeNode* RBT::Leftmost(TreeNode * current){
    while(current->leftchild){
        current = current->leftchild;
    }
    return current;
}

TreeNode* RBT::Successor(TreeNode *current){
    if(current->rightchild){
        return Leftmost(current->rightchild);
    }

    TreeNode* successor = current->parent;
        while(successor && successor->rightchild == current){
            current = successor;
            successor = successor->parent;
        }
        return successor;
}

TreeNode* RBT::Search(int KEY){
    TreeNode *current = root;
    while(current && current->key != KEY){
        if(KEY > current->key){
            current = current->rightchild; 
        }else if(KEY > current->key){
            current = current->leftchild;
        }
    }
    return current;
}
void RBT::DeleteRBT(int KEY){
    TreeNode *delete_node = Search(KEY);
    if(delete_node == NULL){
        cout << "data not found.\n";
        return;
    }

    TreeNode *x = 0;
    TreeNode *y = 0;

    if(delete_node->leftchild == neel || delete_node->rightchild == neel){
        y = delete_node;
    }else{
        y = Successor(delete_node);
    }
 
    if(y->leftchild != neel){
        x = y->leftchild;
    }else if(y->rightchild != neel){
        x = y->rightchild;
    }

    x->parent = y->parent;

    if(y->parent == neel){
        this -> root = x;
    }else if(y == y->parent->leftchild){
        y->parent->leftchild = x;
    }else{
        y->parent->rightchild = x;
    }

    if(y != delete_node){
        delete_node->key = y->key;
        delete_node->element = y->element;
    }

    if(y->color == 1){
        DeleteFixedUpRBT(x);
    }
}

void RBT::DeleteFixedUpRBT(TreeNode *current){
    while(current != root && current->color == 1){
        if(current == current->parent->leftchild){
            TreeNode *sibiling = current->parent->rightchild;
            //Case 1
            if(sibiling->color == 0){
                sibiling->color = 1;
                current->parent = 0;
                LeftRotation(current->parent);
                sibiling = current->parent->rightchild;
            }
            //Case 2,3,4:經過case1已經確保sibiling都為黑色
            //Case 2
            if(sibiling->rightchild->color == 1 && sibiling->leftchild->color == 1){
                sibiling->color = 0;
                current = current->parent;
            }else{
                //Case 3
                if(sibiling->rightchild->color == 1){
                    sibiling->leftchild->color = 1;
                    sibiling->color = 0;
                    RightRotation(sibiling);
                    sibiling = current->parent->rightchild;
                }
                //Case 3之後必定會變成Case 4
                //Case 4
                sibiling->color = current->parent->color;
                current->parent->color = 1;
                sibiling->rightchild->color = 1;
                LeftRotation(current->parent);
                current = root;
            }
        }
        else{
            TreeNode *sibiling = current->parent->leftchild;
            //Case 1
            if(sibiling->color == 0){
                sibiling->color = 1;
                current->parent->color = 0;
                RightRotation(current->parent);
                sibiling = current->parent->leftchild;
            }
            //Case 2,3,4
            //Case 2
            if(sibiling->rightchild->color == 1 && sibiling->leftchild->color == 1){
                sibiling->color = 0;
                current = current->parent;
            }else{
                if(sibiling->leftchild->color == 1){
                    sibiling->rightchild->color = 1;
                    sibiling->color = 0;
                    LeftRotation(sibiling);
                    sibiling = current->parent->leftchild;
                }
                sibiling->color = current->parent->color;
                current->parent->color = 1;
                sibiling->leftchild->color = 1;
                RightRotation(current->parent);
                current = root;
            }
        }        
    }
    current->color = 1;
}
    

void RBT::InsertRBT(int key, string str){
    TreeNode *x = root;
    TreeNode *y = neel;

    TreeNode *insert_node = new TreeNode(str, key);

    while(x != neel){
        y = x;
        if(x->key > insert_node->key){
            x = x->leftchild;
        }else if(x->key < insert_node->key){
            x = x->rightchild;
        }
    }

    if(y == neel){
        this->root = insert_node;
    }else if(y->key > insert_node->key){
        y->leftchild = insert_node;
    }else{
        y->rightchild = insert_node;
    }

    insert_node->leftchild = neel;
    insert_node->rightchild = neel;

    InsertFixedUpRBT(insert_node); 
}

void RBT::InsertFixedUpRBT(TreeNode *current){
    while(current->parent->color == 0){
        if(current->parent == current->parent->parent->leftchild){
            TreeNode *uncle = current->parent->parent->rightchild;

            if(uncle->color == 0){
                //case 1
                current->parent->color = 1;
                uncle->color = 1;
                current->parent->parent->color = 0;
                current = current->parent->parent;
            }else {
                if(current == current->parent->rightchild){
                    //case 2
                    current = current->parent;
                    LeftRotation(current);
                }
                //case 3
                current->parent->color = 1;
                current->parent->parent->color = 0;
                RightRotation(current->parent->parent);
            }
        
        }else{
            TreeNode *uncle = current->parent->parent->leftchild;

            if(uncle->color == 0){
                //case 1
                current->parent->color = 1;
                uncle->color = 1;
                current->parent->parent->color = 0;
                current = current->parent->parent;
            }else {
                if(current == current->parent->rightchild){
                    //case 2
                    current = current->parent;
                    RightRotation(current);
                }
                //case 3
                current->parent->color = 1;
                current->parent->parent->color = 0;
                LeftRotation(current->parent->parent);
            }
        }
    }
    root->color = 1;
}

void RBT::LeftRotation(TreeNode *x){
    TreeNode *y = x->rightchild;
   
    x->rightchild = y->leftchild;
    
    if(y->leftchild){
        y->leftchild->parent = x;
    }

    y->parent = x->parent;

    if(x->parent == neel){
        root = y;
    }else if(x == x->parent->leftchild){
        x->parent->leftchild = y;
    }else {
        x->parent->rightchild = y;
    }

    y->leftchild = x;
    x->parent = y;

}

void RBT::RightRotation(TreeNode *y){    
    TreeNode *x = y->leftchild;
   
    y->leftchild = x->rightchild;
    
    if(x->rightchild){
        x->rightchild->parent = y;
    }

    x->parent = y->parent;

    if(y->parent == neel){
        root = x;
    }else if(y == y->parent->leftchild){
        y->parent->leftchild = x;
    }else {
        y->parent->rightchild = x;
    }

    x->rightchild = y;
    y->parent = x;

   
}

int main(){
    


    return 0;
}