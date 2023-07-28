#include<iostream>
#include<cmath>
using namespace std;
 
// Acknowledgements: Made with help from samples on geeksforgeeks.com and https://www.tutorialspoint.com/cplusplus-program-to-implement-avl-tree

class AVL
{

// Nested Node class
//----------------------------------------------
class Node
{
    
public:

    int data;
    Node *left;
    Node *right;
    int height;

    Node(int data)
    {
        this->data = data;
        this->left = NULL;
        this->right = NULL;
        this->height = 0;
    }

    ~Node()
    {
        delete left;
        delete right;
    }
};

//----------------------------------------------


private:
    
    //---------------------------------------------- Variables
    Node *root;
    int count;
    Node* end;
    //----------------------------------------------
    // Private version of functions.
    //----------------------------------------------
    int getHeight(Node *root)
    {
        if(root == NULL)
        {
            return -1;
        }
        else
        {
            return root->height;
        }
    }
    
    //----------------------------------------------
    
    Node* getEnd(Node *root)
    {
        return end;
    }
    
    //----------------------------------------------

    Node* put(Node *root,int key)
    {
        if(root == NULL) //base case
        {
            Node *newNode = new Node(key); //Making a new node
            count++;
            return newNode;
        }

        if(key > root->data)
        {
            root->right = put(root->right,key); // putting to the right
        }
        else
        {
            root->left = put(root->left,key); //putting to the left
        }

        // updating root's height
        root->height = 1 + max(getHeight(root->left),getHeight(root->right));
        int bal = bf(root); // checking the balance factor of the root

        if(bal < -1 || bal > 1) // An if statement in case rotation is needed.
        {
            if(bal < -1) // RIGHT
            {
                if(key < root->right->data) // Right-Left case
                {
                    root->right = Right_Rotate(root->right);
                    return Left_Rotate(root);
                }
                else // Right-Right Case
                {
                    return Left_Rotate(root);
                }
            }
            else // LEFT
            {
                if(key < root->left->data) // Left-Left case
                {
                    return Right_Rotate(root);
                }
                else // Left-Right Case
                {
                    root->left = Left_Rotate(root->left);
                    return Right_Rotate(root);
                }
            }
        }
        
        return root; //returning if everything is OK!!

    }
    
    //----------------------------------------------

    int bf(Node *root) //  Stands for balance factor.
    {
        if(root == NULL) // I don't know what scenario this statement is actually going to be checked/true but it is important if it is ever the case.
        {
            return 0;
        }

        return getHeight(root->left) - getHeight(root->right);
    }
    
    //----------------------------------------------

    Node* Left_Rotate(Node * root) // A left rotation
    {
        Node *new_root = root->right;
        Node *ptr = new_root->left;

        root->right = ptr;
        new_root->left = root;

        root->height = 1 + max(getHeight(root->left),getHeight(root->right));
        new_root->height = 1 + max(getHeight(new_root->left),getHeight(new_root->right));

        return new_root;
    }
    
    //----------------------------------------------
    
    Node* Right_Rotate(Node *root) // A right rotation
    {
        Node *new_root = root->left;
        Node *ptr = new_root->right;

        root->left = ptr;
        new_root->right = root;

        root->height = 1 + max(getHeight(root->left),getHeight(root->right));
        new_root->height = 1 + max(getHeight(new_root->left),getHeight(new_root->right));

        return new_root;
    }

    //----------------------------------------------
    
    Node* erase(Node *root, int key) // Erasing a node.
    {
        if(root == NULL) //base case
        {
            return NULL;
        }
    
        if(key > root->data)
        {
            root->right = erase(root->right,key);
        }
        else
        {
            if(key < root->data)
            {
                root->left = erase(root->left,key);
            }
            
            else //Reaching here means root is the node that has to be deleted and that creates 3 more cases that need to be accounted for.
            {
                if(root->left == NULL && root->right == NULL) // Case 1: Root is a leaf Node
                {
                    delete root;
                    return NULL;
                }
                    
                else // Case 2: Root has 1 child only
                {
                    if(root->left == NULL)
                    {
                        Node *temp = root->right;
                        root->right = NULL; // we need to make the right of root NULL first because if we don't and call simply delete root, that will lead to deletion of the whole tree along with root.
                        delete root;
                        root = temp;
                    }
                    else
                    {
                        if(root->right == NULL)
                        {
                            Node *temp = root->left;
                            root->left = NULL; // we need to make the right of root NULL first because if we don't and call simply delete root, that will lead to deletion of the whole tree along with root.
                            delete root;
                            root = temp;
                        }
                        else // Case 3: Root has both children. So after the deletion of root, we need to make the minimum(leftmost) value of right subtree as the new root.
                        {
                            Node *temp = root->right;
                            while(temp->left != NULL)
                            {
                                temp = temp->left;
                            }
    
                            root->data = temp->data; //Updating roots data
                            root->right = erase(root->right,temp->data); // deleting the leftmost node of the right subtree
                        }
                    }
                }
                        
                root->height = 1 + max(getHeight(root->left),getHeight(root->right));
                int bal = bf(root);
    
                if(bal < -1 || bal > 1) //checking if deletion has caused imbalances in the root
                {
                    if(bal < -1)
                    {
                        if(bf(root->right) > 0) //Right Left Case
                        {
                            root->right = Right_Rotate(root->right);
                            return Left_Rotate(root);
                        }
                        else //Right Right Case
                        {
                            return Left_Rotate(root);
                        }
    
                    }
                    
                    else
                    {
                        if(bf(root->left) > 0) //Left Left Case
                        {
                            return Right_Rotate(root);
                        }
                        else //Left Right Case
                        {
                            root->left = Left_Rotate(root->left);
                            return Right_Rotate(root);
                        }
                    }
                }
            }
        }   
        count--; // Lower size.
        return root; //return if everything is fine
    }
    
    //----------------------------------------------

    void print(Node *root,string indent) // Simple print function to print tree in the format given in the criteria.
    {
        if(root == NULL)
        {
            return;
        }
        if(root->height ==0)
        {
            cout<<indent<<"L"<<' '<<'('<<root->height<<')'<<endl;
            return;
        }
        else
        {
            cout<<indent<<root->data<<' '<<'('<<root->height<<')'<<endl;
        }
    
        print(root->left,indent+" ");
        print(root->right,indent+" ");
    }
    
    //----------------------------------------------
    
    Node* find(Node *root,int key) // Recursive function to find a key, if not found returns end.
    {
        if(root == NULL) // Base case
        {
            return end;
        }
    
        if(root->data == key)
        {
            return root;
        }
    
        if(key > root->data)
        {
            return find(root->right,key);
        }
        
        else
        {
            return find(root->left,key);
        }
    };
    
    //----------------------------------------------

//----------------------------------------------

public:

    // Public functions called in main file. All have the requested return type and parameters but they use the private functions to generate a requested action. For example put takes only key as parameter but calls
    // the private put function with root as an additional parameter. Therefore simplfying the process and obeying the criteria.
    //----------------------------------------------
    // Constructor and Destructor
    //----------------------------------------------
    
    AVL()
    {
        root = NULL;
        count = 0;
        Node* end_node = new Node(-1);
        end = end_node;
    }
    
    ~AVL()
    {
        delete root;
        delete end;
    }
    
    //----------------------------------------------
    // put, erase, find and print.
    //----------------------------------------------
    Node* put(int k)
    {
        root = put(root,k);
        return find(root,k);
    }

    void print()
    {
        print(root,"");
    }

    void erase(int k)
    {
        root = erase(root,k);
    }

    Node* find(int k)
    {
        return find(root,k);
    }
    
    //----------------------------------------------
    // Size and empty.
    //----------------------------------------------
    int size()
    {
        return count;
    }

    bool empty()
    {
        return count == 0;
    }
    
    //----------------------------------------------
    // getEnd
    //----------------------------------------------
    
    Node* getEnd()
    {
        return getEnd(root);
    }

};