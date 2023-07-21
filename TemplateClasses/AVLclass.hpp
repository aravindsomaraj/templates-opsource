#ifndef AVLhpp
#define AVLhpp

#include<bits/stdc++.h>
// #include "AVLclass.hpp"
using namespace std;

template <typename T> struct TreeNode{                          
    int ht;
    T val;
    TreeNode *left, *right;
    TreeNode() : val(0), ht(1), left(nullptr), right(nullptr){}
    TreeNode(T x) : val(x), ht(1), left(nullptr), right(nullptr){}
};

template <typename T> class AVL {
private:
    static TreeNode<T>* rootptr;
    int UpdateH(TreeNode<T>*& root);
    void LeftRotate(TreeNode<T>*& root);
    void RightRotate(TreeNode<T>*& root);
    void AVLBalance(TreeNode<T>*& root);
 
public:
    TreeNode<T>* pop(TreeNode<T>*& root = rootptr);
    TreeNode<T>* Delete(T n, TreeNode<T>*& root = rootptr);
    TreeNode<T>* push(T n, TreeNode<T>*& root = rootptr);
    void Search(T n, TreeNode<T>*& root = rootptr);
    void print(TreeNode<T>* root = rootptr);

};
template <typename T> TreeNode<T>* AVL<T>::rootptr = nullptr;
template <typename T> int AVL<T>::UpdateH(TreeNode<T>*& root)
{
    int lh=0,rh=0;
    if(root->left)
        lh=root->left->ht;
    if(root->right)
        rh=root->right->ht;
    
    root->ht=max(lh,rh)+1;
    return lh-rh;
}
template <typename T> void AVL<T>::LeftRotate(TreeNode<T>*& root)
{
    TreeNode<T>* pivot = root->right;
    root->right=pivot->left;
    pivot->left=root;

    UpdateH(root);UpdateH(pivot);

    root=pivot;
}
template <typename T> void AVL<T>::RightRotate(TreeNode<T>*& root)
{
    TreeNode<T>* pivot = root->left;
    root->left=pivot->right;
    pivot->right=root;

    UpdateH(root);UpdateH(pivot);

    root=pivot;
}
template <typename T> void AVL<T>::AVLBalance(TreeNode<T>*& root)
{
    int bf=UpdateH(root);
    if(bf>1)
    {
        if(UpdateH(root->left)<0)
        {
            LeftRotate(root->left);
        }
        RightRotate(root);
    }
    else if(bf<-1)
    {
        if(UpdateH(root->right)>0)
        {
            RightRotate(root->right);
        }
        LeftRotate(root);
    }
}

/*
 *  This primitive search function is identical to a BST search functions
 *  because this is an AVL Tree.
 *  The return type may be modified as required to retrieve other attributes of searched key.
 * 
 */
template <typename T> void AVL<T>::Search(T n, TreeNode<T>*& root)
{
    if(root == nullptr)
    {
        cout << "Key does not exist" << endl;
        return;
    }
    if(root->val == n)
    {
        cout << "Key found" << endl;
    }
    else if(n>root->val)
        Search(n,root->right);
    else
        Search(n,root->left);    
}

/*
 *  Searches for the root, and deletes the node.
 *  Update: realized I can use Search function to get the node instead of
 *  writing the whole code again. Will remove this edit comment if I get
 *  to fixing it soon.
 * 
 */

template <typename T> TreeNode<T>* AVL<T>::Delete(T n, TreeNode<T>*& root)
{
    if(root==0)
        return 0;
    else if(n>root->val)
        root->right=Delete(n,root->right);
    else if(n<root->val)
        root->left=Delete(n,root->left);
    else
    {
        if(root->left == nullptr || root->right == nullptr)
        {
            TreeNode<T>* temp = root->left ? root->left : root->right;
            if(temp == nullptr)
            {
                temp = root;
                root = nullptr;
            }
            else
                *root = *temp;
            delete temp;
        }
        else
        {
            TreeNode<T>* temp = root->right;
            while(temp->left)
                temp = temp->left;
            root->val = temp->val;
            root->right = Delete(temp->val, root->right);
        }
    }

    if(root == nullptr)
        return root;
    UpdateH(root);
    AVLBalance(root);
    return root;
}

/*
 *  Deletes the root node of the AVL Tree
 *  Uses Delete function in tandem.
 *  Similar to pop in BST.
 */
template <typename T> TreeNode<T>* AVL<T>::pop(TreeNode<T>*& root)
{
    if(root == nullptr)
        return nullptr;
    if(root->left == nullptr)
    {
        TreeNode<T>* temp = root->right;
        delete root;
        root = temp;
    }
    else
    {
        TreeNode<T>* curr = root->left;
        while(curr->right)
            curr = curr->right;
        root->val = curr->val;
        root->left = Delete(curr->val, root->left);
    }
    if(root == nullptr)
        return root;
    UpdateH(root);
    AVLBalance(root);
    return root;
}


/*
 *  Push function. Self-explanatory.
 */
template <typename T> TreeNode<T>* AVL<T>::push(T n, TreeNode<T>*& root)
{
    if(root==0)
    {
        root=new TreeNode<T>(n);
        if(rootptr==0)
        {
            rootptr=root;
        }
        return root;
    }
    if(n>root->val)
        root->right=push(n,root->right);
    else
        root->left=push(n,root->left);
        
    
    AVLBalance(root);
    return root;
}

/*
 *  Print function.
 *  prints the tree in inorder fashion in a list manner, with corresponding heights.
 *  Feel free to change the traversal order or info to be printed, or etc.
 */
template <typename T> void AVL<T>::print(TreeNode<T>* root)
{
    if(root==0)
        return;
    
    print(root->left);
    cout << "Node: " << root->val << " - Height: " << root->ht << endl;
    print(root->right);
}

// int main()
// {
//     AVL<int> a;
//     a.push(1);
//     a.push(2);
//     a.print();
// }

#endif // AVLhpp