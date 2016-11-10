#include <iostream>

using namespace std;

template<class T>
class bstnode{
public:
    T item;
    bstnode<T> *left,*right,*parent;
    bstnode();
    bstnode(T);
};

template<class T>
class bst{
private:
    bstnode<T> *root;
public:
    bst();
    ~bst();
    void insert(T); 
    int remove(T);
    int search(T);
    void display(bstnode<T>*);
};

template<class T>
bst<T>::bst(){
    root = NULL;
}
template<class T>
bst<T>::~bst(){
    while(root!=NULL){
        remove(root->item);
    }
}
template<class T>
void bst<T>::insert(T item){
    bstnode<T> *tmp = new bstnode<T>(item);
    if(root == NULL){
        root = tmp;
    }else{
        bstnode<T> *tmp2 = root , *prev;
        while(tmp2!=NULL){
            prev = tmp2;
            if(tmp->item < tmp2->item){
                tmp2 = tmp2->left;
            }else{
                tmp2 = tmp2->right;
            }    
        }
        if(tmp->item < prev->item){
            prev->left = tmp;
            tmp->parent = prev;
        }else{ 
            prev->right = tmp;
            tmp->parent = prev;
        } 
        
    }
}
template <class T>
void bst<T>::display(bstnode<T> *root){
    if(root!=NULL){
        cout<<root->item<<" ";
        display(root->left);
        display(root->right);    
    }
    
}
template <class T>
int bst<T>::remove(T x){
    bstnode<T> *del = root , *prev;
    int ctr = 1;
    if(root == NULL){
        return -ctr;
    }else if(x == del->item){
        if(del->left == NULL && del->right == NULL){
            root = NULL;
        }else if(del->left!=NULL && del->right!=NULL){
             bstnode<T> *tmp = del->right;
                while(tmp->left!=NULL){
                    tmp = tmp->left;
                }
                int temp = tmp->item;
                remove(temp);
                root->item = temp;
        }else if(del->right == NULL){
            root = del->left;
            delete(del);
        }else{
            root = del->right;
            delete(del);
        }
        return ctr;
    } else {
        while(del->item!=x){
            prev = del;
            if(x < del->item){
                del = del->left;
            }else{
                del = del->right;
            }
            if(del == NULL){
                return -ctr;
            }
            ctr++;
        }
        if(del->left==NULL && del->right==NULL){
            if(del->item > prev->item){
                prev->right = NULL;
            }else{
                prev->left = NULL;
            }
            //display(root);
            delete(del);
            return ctr;
        }else{
            if(del->left == NULL){ //naa siyay right child
                prev->right = del->right;
                bstnode<T> *tmp = del->right;
                tmp->parent = prev;
                //display(root);
                delete(del);
                return ctr;
            }else if(del->right == NULL){
                prev->left = del->left;
                bstnode<T> *tmp = del->left;
                tmp->parent = prev;
                //display(root);
                delete(del);
                return ctr;
            }else{
                bstnode<T> *tmp = del->right;
                while(tmp->left!=NULL){
                    tmp = tmp->left;
                }
                int temp = tmp->item;
                remove(temp);
                del->item = temp;
                //display(root);
                return ctr;
            }
        }
        return -ctr;
    }
    
}

template <class T>
int bst<T>::search(T i){
    bstnode<T> *tmp = root;
    int x = 1;
    while(tmp!=NULL &&tmp->item!=i){
        if(i < tmp->item){
            tmp = tmp->left;
        }else{
            tmp = tmp->right;
        }
        x++;
    }
    if(tmp == NULL)
       return -x+1;
    return x;
}

int main() {
    int n,m,i,x;
    cin>>n;
    for(;n>0;n--){
        bst<int> b;
        cin>>m;
        for(;m>0;m--){
            cin>>i;
            b.insert(i);
        }
        cin>>x;
        int s = b.remove(x);
        if(s<0){
            cout<<s*-1<<" !FOUND"<<endl;
        }else{
            cout<<s<<" DELETED"<<endl;
        }
        
    }
    return 0;
}

template<class T>
bstnode<T>::bstnode(){
    left = right = parent = NULL;
}
template<class T>
bstnode<T>::bstnode(T item){
    this->item = item;
    left = right = parent = NULL;
}
