#include<iostream>
#include<queue>

using namespace std;

class Node {
public:
    int data;
    Node *left;
    Node *right;
    Node* parent;
    Node() :left(nullptr), right(nullptr),parent(nullptr) {};
    Node(int x):data(x), left(nullptr), right(nullptr),parent(nullptr) {};
};

class heap
{
public:
    Node* root;
    vector<Node*> nodes;
    heap() :root(nullptr) {};
    ~heap()
    {
        deleteall(root);
    }
    void deleteall(Node *root)
    {
        if (!root) return;
        deleteall(root->left);
        deleteall(root->right);
        delete root;
    }
    void heapify(Node* node);
    void bubble_down(Node* node);
    void insert_node(int val);
    void pop_heap();
    inline int top();
};

void printheap(ostream& str, Node* root)
{
    if (!root) return;
    str << root->data<<" ";
    printheap(str, root->left);
    printheap(str, root->right);
}

ostream& operator<<(ostream& str, Node* root)
{
    printheap(str,root);
    return str;
}

void heap::heapify(Node* node)
{
    if (!node->parent) return;
    if (node->data < node->parent->data)
    {
        int temp = node->data;
        node->data = node->parent->data;
        node->parent->data = temp;
    }
    heapify(node->parent);
}

void heap::bubble_down(Node* root)
{
    if (!root->left && !root->right) return;
    Node* min_node=root;
    if (root->left && root->right)
    {
        if (root->left->data < root->right->data)
            min_node = root->left;
        else if (root->left->data >= root->right->data)
            min_node = root->right;
    }
    else if (root->left) min_node = root->left;
    else if (root->right) min_node = root->right;
    if (root->data > min_node->data)
    {
        int temp = root->data;
        root->data = min_node->data;
        min_node->data = temp;
        bubble_down(min_node);
    }
}

void heap::insert_node(int val)
{
    if (!root) root = new Node(val);
    else
    {
        queue<Node*> bfs;
        bfs.push(root);
        char done = 'N';
        while (done!='D')
        {
            Node* top = bfs.front();
            bfs.pop();
            if (!top->left)
            {
                Node* new_node = new Node(val);
                top->left = new_node;
                new_node->parent = top;
                done = 'D';
                nodes.emplace_back(new_node);
                heapify(new_node);
                break;
            }
            else if (!top->right)
            {
                Node* new_node = new Node(val);
                top->right = new_node;
                new_node->parent = top;
                done = 'D';
                nodes.emplace_back(new_node);
                heapify(new_node);
                break;
            }
            else
            {
                bfs.push(top->left);
                bfs.push(top->right);
            }
        }
    }

}

void heap::pop_heap()
{
    if (nodes.size() == 0)
    {
        cout << "Heap is already empty";
        return;
    }
    if (nodes.back()==root)
    {
        delete root;
        root = nullptr;
        nodes.pop_back();
    }
    else
    {
        root->data = nodes.back()->data;
        Node* p = nodes.back()->parent;
        if (p->left == nodes.back())
        {
            Node* del_node = p->left;
            p->left = nullptr;
            delete del_node;
        }
        if (p->right == nodes.back())
        {
            Node* del_node = p->right;
            p->right = nullptr;
            delete del_node;
        }
        nodes.pop_back();
        bubble_down(root);
    }
}

inline int heap::top()
{
    return root->data;
}

int main()
{
    heap new_heap;
    new_heap.insert_node(4);
    new_heap.insert_node(5);
    new_heap.insert_node(1);
    new_heap.insert_node(2);
    new_heap.insert_node(6);
    new_heap.insert_node(8);
    new_heap.insert_node(0);
    cout << new_heap.root<<endl;
    cout << new_heap.top() << endl;
    new_heap.pop_heap();
    cout << new_heap.root << endl;
    return 0;
}