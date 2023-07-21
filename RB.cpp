#include <iostream>
#include <stdlib.h>
using namespace std;

// Structure to represent each
// node in a red-black tree
template <typename T> struct node {
    T val; // data
    int c; // 1-red, 0-black
    struct node* parent; // parent
    struct node* right; // right-child
    struct node* left; // left child
};
typedef struct node* Node;
// global root for the entire tree
Node global_root = NULL;

// function to perform BST insertion of a node
Node createNode(int n)
{
    Node root = new node();
    root->val = n;
    root->c = 1;
    root->parent = root->left = root->right = nullptr;
    return root;
}
Node Insert(Node trav, Node temp)
{
    if (trav == NULL)
        return temp;

    if (temp->val < trav->val)
    {
        trav->left = Insert(trav->left, temp);
        trav->left->parent = trav;
    }
    else if (temp->val > trav->val)
    {
        trav->right = Insert(trav->right, temp);
        trav->right->parent = trav;
    }

    return trav;
}

// Function performing right rotation
// of the passed node
void rightrotate(Node root)
{
    Node pivot = root->left;
    root->left = pivot->right;

    if(root->left) root->left->parent = root;

    pivot->parent = root->parent;
    if(!root->parent) global_root = pivot;
    else if(root == root->parent->left) root->parent->left = pivot;
    else root->parent->right = pivot;

    pivot->right = root;
    root->parent = pivot;
}

// Function performing left rotation
// of the passed node
void leftrotate(Node root)
{
    Node pivot = root->right;
    root->right = pivot->left;

    if(root->right)  root->right->parent = root;

    pivot->parent = root->parent;
    if(!root->parent) global_root = pivot;
    else if(root == root->parent->left) root->parent->left = pivot;
    else root->parent->right = pivot;

    pivot->left = root;
    root->parent = pivot;
}

// This function fixes violations
// caused by BST insertion
void RedBlack(Node global_root, Node pt)
{
    Node parent_pt = NULL;
    Node grand_parent_pt = NULL;

    while((pt != global_root) && (pt->c != 0) && (pt->parent->c == 1))
    {
        parent_pt = pt->parent;
        grand_parent_pt = pt->parent->parent;

        /*  Case : A
                Parent of pt is left child
                of Grand-parent of
            pt */
        if(parent_pt == grand_parent_pt->left)
        {

            Node uncle_pt = grand_parent_pt->right;

            /* Case : 1
                The uncle of pt is also red
                Only Recoloring required */
            if(uncle_pt != NULL && uncle_pt->c == 1)
            {
                grand_parent_pt->c = 1;
                parent_pt->c = 0;
                uncle_pt->c = 0;
                pt = grand_parent_pt;
            }

            else{

                /* Case : 2
                        pt is right child of its parent
                        Left-rotation required */
                if(pt == parent_pt->right) {
                    leftrotate(parent_pt);
                    pt = parent_pt;
                    parent_pt = pt->parent;
                }

                /* Case : 3
                        pt is left child of its parent
                        Right-rotation required */
                rightrotate(grand_parent_pt);
                int t = parent_pt->c;
                parent_pt->c = grand_parent_pt->c;
                grand_parent_pt->c = t;
                pt = parent_pt;
            }
        }

        /* Case : B
                Parent of pt is right
                child of Grand-parent of
            pt */
        else {
            Node uncle_pt = grand_parent_pt->left;

            /*  Case : 1
                The uncle of pt is also red
                Only Recoloring required */
            if((uncle_pt != NULL) && (uncle_pt->c == 1))
            {
                grand_parent_pt->c = 1;
                parent_pt->c = 0;
                uncle_pt->c = 0;
                pt = grand_parent_pt;
            }
            else {
                /* Case : 2
                    pt is left child of its parent
                    Right-rotation required */
                if(pt == parent_pt->left) {
                    rightrotate(parent_pt);
                    pt = parent_pt;
                    parent_pt = pt->parent;
                }

                /* Case : 3
                        pt is right child of its parent
                        Left-rotation required */
                leftrotate(grand_parent_pt);
                int t = parent_pt->c;
                parent_pt->c = grand_parent_pt->c;
                grand_parent_pt->c = t;
                pt = parent_pt;
            }
        }
    }
}

void push(int n)
{
    Node root = createNode(n);

    global_root = Insert(global_root, root);
    
    RedBlack(global_root, root);
        global_root->c = 0;
}
// Function to print inorder traversal
// of the fixated tree
void inorder(Node trav)
{
    if (trav == NULL)
        return;

    inorder(trav->left);
    cout << trav->val << " ";
    inorder(trav->right);
}

// driver code
int main()
{
int n = 7;
int a[7] = { 7, 6, 5, 4, 3, 2, 1 };

for (int i = 0; i < n; i++) {
    push(a[i]);
}

printf("Inorder Traversal of Created Tree\n");
inorder(global_root);

return 0;
}