#include<iostream>

using namespace std;

class Node
{
public:
    int val;
    int height;
    Node* left;
    Node* right;
    Node* root;
    Node() :root(nullptr) {};
    Node(int x):val(x), left(nullptr), right(nullptr) {};
};
Node* root=nullptr;

int height_node(Node* track)
{
    if (!track) return 0;
    int hl = 1 + height_node(track->left);
    int hr = 1 + height_node(track->right);
    return hl < hr ? hr : hl;
}

Node* LLRotation(Node* track)
{
    Node* l_child = track->left;
    track->left = l_child->right;
    l_child->right = track;
    l_child->height = height_node(l_child);
    track->height = height_node(track);
    if (root == track) root = l_child;
    return l_child;
}

Node* LRRotation(Node* track)
{
    Node* l_child = track->left;
    Node* r_child = track->left->right;
    l_child->right = r_child->left;
    track->left = r_child->right;
    r_child->left = l_child;
    r_child->right = track;
    r_child->height = height_node(r_child);
    track->height = height_node(track);
    l_child->height = height_node(l_child);
    if (root == track) root = r_child;
    return r_child;
}


Node* insert(Node* track, int key)
{
    if (track == nullptr)
    {
        Node* new_node = new Node(key);
        track = new_node;
    }
    else if (key < track->val)
        track->left = insert(track->left, key);
    else
        track->right = insert(track->right, key);
    track->height = height_node(track);
    int hl = 0, hr = 0;
    if (track->left) hl = track->left->height;
    if (track->right) hr = track->right->height;
    if (hl - hr == abs(2));
    int diff = hl - hr;
    hl = 0;
    hr = 0;
    if (diff == 2)
    {
        if (track->left->left) hl = track->left->left->height;
        if (track->left->right) hr = track->left->right->height;
        if (hl - hr == 1)
            LLRotation(track);
        else if (hl - hr == -1)
            LRRotation(track);
    }
    return track;
}
void inorder(Node* track)
{
    if (!track) return;
    inorder(track->left);
    cout << "{"<<track->val<<","<<track->height<<"}"<<" ";
    inorder(track->right);
}

int main()
{
    root = insert(root, 5);
    insert(root, 2);
    insert(root, 9);
    insert(root, 1);
    insert(root, 4);
    insert(root, 3);
    cout << root->val;
    inorder(root);
    return 0;
}