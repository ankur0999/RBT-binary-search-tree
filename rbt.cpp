#include<iostream>
#include<queue>
using namespace std;

class Node{
	public:
		int data;
        int color;
		Node* left;
		Node* right;
        Node* parent;
		Node(int data){
			this->data = data;
			this->left = new Node();
			this->right = new Node();
            this->parent = NULL;
            this->color = 0;
        }
        Node(){
            this->data = -1;
            this->left = NULL;
            this->right = NULL;
            this->parent = NULL;
            this->color = 0;
        }
        };

class BST{
    protected:
    Node* root;
    
    public:
    BST(){
        root = NULL;
        
       
    }

    
    void insertData(){
        insertData(root);
    }
    void insertData(Node*& root){
    cout<<"insert Element: "<<endl;
	int data;
	cin>>data;
	while(data != -1){
        Node* child = new Node(data);
	    BST_insertion(root, child);
	    cin >> data;
	}
    }
    void BST_insertion(Node*& p, Node*& c);
    void getMax(){
        getMax(root);
    }
    Node* getMax(Node* p);
    void getMin(){
        getMin(root);
    }
    Node* getMin(Node* p);
    Node* searchData(Node* root, int data);
    void deleteData(int data){
        Node* d = searchData(root, data);
        if(d != NULL)
        deleteData(root, d);
    }
    void deleteData(Node*& p, Node*& data);
    void preorder(){
        preorder(root);
    }
    void preorder(Node* p);
    void postorder(){
        postorder(root);
    }
    void postorder(Node* p);
    void inorder(){
        inorder(root);
    }
    void inorder(Node* p);
    void levelorder(){
        cout<<"level order traversal is "<<endl;
        levelorder(root);
        
    }
    void levelorder(Node* p);
    
    void Transplant(Node*& root, Node*& u, Node*& v);
    ~BST(){
        postorderDeletion(root);
    }
    void postorderDeletion(Node* root);
    

};

void BST:: postorderDeletion(Node* root){
    if(root == NULL) return;
    postorderDeletion(root->left);
    postorderDeletion(root->right);
    delete[] root;
}
Node* BST:: searchData(Node* root, int data){
    Node* x = root;
    while(x != NULL){
        if(x->data == data) return x;
        else if(x->data < data)
            x = x->right;
        else
            x = x->left;
    }
    return x;
}
Node* BST:: getMin(Node* root){
    if(root == NULL)
		return NULL;
	Node* tmp = root;
	while(tmp->left != NULL)
            tmp = tmp->left;
	return tmp;
}
Node* BST:: getMax(Node* root){
    if(root == NULL)
		return NULL;
	Node* tmp = root;
	while(tmp->right != NULL)
		tmp = tmp->right;
	return tmp;
}
void BST:: BST_insertion(Node*& root, Node*& child){
        Node* y = NULL;
        Node* x = root;
        if(root == NULL){
            root = child;
            root->color = 0;
        }
        else{
            while(x->data != -1){
            y = x;
            if(child->data < x->data)
                x = x->left;
            else
                x = x->right;
        }
        child->parent = y;
        
        
        
        if(child->data < y->data){
            Node* tmp = y->left;
            delete[] tmp;
            y->left = child;
}
        else{
            Node* tmp = y->right;
            delete[] tmp;
            y->right = child;
        }}    
}
void BST:: deleteData(Node*& root, Node*& d){
	if(d->left == NULL)
        Transplant(root, d, d->right);
    else if(d->right == NULL)
        Transplant(root, d, d->left);
    else{
        Node* mini = getMin(d->right);
        if(mini->parent != d){
            Transplant(root, mini, mini->right);
            mini->right = d->right;
            mini->right->parent = mini;
        }
        Transplant(root, d, mini);
        mini->left = d->left;
        mini->left->parent = mini;
    }
}
void BST:: Transplant(Node*& root, Node*& u, Node*& v){
    if(u->parent == NULL)
        root = v;
    else if(u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;
    if(v != NULL){
        v->parent = u->parent;
    }
}
void BST:: preorder(Node* root){
	if(root == NULL)
		return;
	cout<< root->data << " ";
	preorder(root->left);
	preorder(root->right);
}
void BST:: inorder(Node* root){

	if(root == NULL)
		return;
	inorder(root->left);
	cout << root->data <<" ";
	inorder(root->right);
}
void BST:: postorder(Node* root){
	if(root == NULL)
		return;
	postorder(root->left);
	postorder(root->right);
	cout<<root->data<<" ";
}
void BST:: levelorder(Node* root){
    
    if(root == NULL)
		return;
    int h = -1;
	queue<Node*> q;
	q.push(root);
	q.push(NULL);
	while(!q.empty()){
		Node* front = q.front();
        q.pop();
        
		if(front == NULL){
            h++;
			cout<<endl;
			if(!q.empty())
				q.push(NULL);
		}
		else{
            if(front->data != -1)
                cout<<front->data<<" ";
			if(front->left)
				q.push(front->left);
			if(front->right)
				q.push(front->right);
		}}
        
}

class RBT : public BST{


    public:
    
    void insertData(){
        insertData(root);
    }
    void insertData(Node*& root);
    void RB_insert_fixup(Node*& root, Node* z);
    
    void leftRotate(Node*& root, Node*& z);
    void rightRotate(Node*& root, Node*& z);
};        
void RBT:: insertData(Node*& root){
    cout<<"Insert Element"<<endl;
    int x;
    cin>>x;
    while(x != -1){
        Node* child = new Node(x);
        child->color = 1;
        BST_insertion(root, child);
        
        RB_insert_fixup(root, child);
        
        cin>>x;
    }
}

void RBT:: RB_insert_fixup(Node*& root, Node* z){
    
    if(z->parent){
    while(z->parent->color == 1){
        if(z->parent == z->parent->parent->left){
            Node* y = z->parent->parent->right;
            if(y->color == 1){
                z->parent->color = 0;
                y->color = 0;
                z->parent->parent->color = 1;
                z = z->parent->parent;
            }
            else{
                if(z == z->parent->right){
                    z = z->parent;
                    leftRotate(root, z);
                    
                }
                z->parent->color = 0;
                z->parent->parent->color = 1;
                rightRotate(root, z->parent->parent);
            }
            
        }
        else{
            Node* y = z->parent->parent->left;
            if(y->color == 1){
                z->parent->color = 0;
                y->color = 0;
                z->parent->parent->color = 1;
                z = z->parent->parent;
            }
            else{
                if(z == z->parent->left){
                    z = z->parent;
                    rightRotate(root, z);
                }
                z->parent->color = 0;
                z->parent->parent->color = 1;
                leftRotate(root, z->parent->parent);
            }
        }
        if(!z->parent)
            break;
    }
    root->color = 0;
    
}


}
void RBT:: leftRotate(Node*& root, Node*& x){
    
   Node* y = x->right;
   x->right = y->left;
   if(y->left)
       y->left->parent = x;
   if(x->parent == NULL){
    root = y;
   }
   else if(x == x->parent->left){
       x->parent->left = y;
       y->parent = x->parent;}
    else
        {
            x->parent->right = y;
            y->parent = x->parent;
        }
    
    y->left = x;
    x->parent = y;
                                           

}
void RBT:: rightRotate(Node*& root, Node*& y){
    
    Node* x = y->left;
    
    y->left = x->right;
    
    if(x->right)
        x->right->parent = y;
    
    if(y->parent == NULL){
        
        root = x;}
    else if(y == y->parent->left){
        
        y->parent->left = x;
        x->parent = y->parent;
        }
    else {
        
        y->parent->right = x;
        x->parent = y->parent;
        }
    x->right = y;
    y->parent = x;
   
    
}

int main(){
    RBT a;
    a.insertData();
    a.levelorder();
}
