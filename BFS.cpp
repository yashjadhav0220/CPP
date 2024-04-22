#include <iostream>
#include <queue>
#include <omp.h>
class node
{
public:
    node *left;
    node *right;
    int data;
};
class Breadthfs
{
private:
    node *root;

public:
    Breadthfs() : root(nullptr) {} // Constructor to initialize root
    node *insert(int);
    void bfs();
};
node *Breadthfs::insert(int data)
{
    if (!root)
    {
        root = new node;
        root->left = nullptr;
        root->right = nullptr;
        root->data = data;
        return root;
    }
    std::queue<node *> q;
    q.push(root);
    while (!q.empty())
    {
        node *temp = q.front();
        q.pop();
        if (temp->left == nullptr)
        {
            temp->left = new node;
            temp->left->left = nullptr;
            temp->left->right = nullptr;
            temp->left->data = data;
            return root;
        }
        else
        {
            q.push(temp->left);
        }
        if (temp->right == nullptr)
        {
            temp->right = new node;
            temp->right->left = nullptr;
            temp->right->right = nullptr;
            temp->right->data = data;
            return root;
        }
        else
        {
            q.push(temp->right);
        }
    }
}
void Breadthfs::bfs()
{
    if (!root)
    {
        std::cout << "Tree is empty." << std::endl;
        return;
    }
    std::queue<node *> q;
    q.push(root);
    int qSize;
    while (!q.empty())
    {
        qSize = q.size();
#pragma omp parallel for
        for (int i = 0; i < qSize; i++)
        {
            node *currNode;
#pragma omp critical
            {
                currNode = q.front();
                q.pop();
                std::cout << "\t" << currNode->data;
            }
#pragma omp critical
            {
                if (currNode->left)
                    q.push(currNode->left);
                if (currNode->right)
                    q.push(currNode->right);
            }
        }
    }
}
int main()
{
    Breadthfs tree;
    int data;
    char ans;
    do
    {
        std::cout << "\nEnter data => ";
        std::cin >> data;
        tree.insert(data);
        std::cout << "Do you want to insert one more node? (y/n): ";
        std::cin >> ans;
    } while (ans == 'y' || ans == 'Y');
    tree.bfs();
    return 0;
}

/*
Run Commands:
1) g++ -fopenmp bfs.cpp –o bfs
2) ./bfs
*/