// https://www.careercup.com/question?id=5140810577215488
// https://massivealgorithms.blogspot.com/2015/11/longest-increasing-path-in-n-ary-tree.html

#include <iostream>
#include <vector>
#include <queue>
#include <climits>

class Tree
{
private:
    class Node
    {
    public:
        int key;
        Node* left;
        Node* right;

        Node(int k) : key {k}, left{nullptr}, right{nullptr} { }
    };

    Node* root;
    using Path = std::vector<Node *>;

    void constructTree(std::vector<int>& keys)
    {
        std::queue<Node*> nodeQueue;
        if (root == nullptr) {
            root = new Node(keys[0]);
        }
        nodeQueue.push(root);

        int keyIndex = 1;
        while (nodeQueue.size() != 0) {
            Node* current = nodeQueue.front();
            nodeQueue.pop();

            if (keyIndex < keys.size() && keys[keyIndex] != INT_MIN) {
                current->left = new Node(keys[keyIndex]);
                nodeQueue.push(current->left);
            }
            keyIndex++;

            if (keyIndex < keys.size() && keys[keyIndex] != INT_MIN) {
                current->right = new Node(keys[keyIndex]);
                nodeQueue.push(current->right);
            }
            keyIndex++;
        }
    }

    void preorder(Node*& node, std::vector<Node*>& path) {
        if (node == nullptr) {
            return;
        }
        path.push_back(node);
        preorder(node->left, path);
        preorder(node->right, path);
    }

    void print(std::vector<Node*>& path)
    {
        for (auto node : path) {
            std::cout << node->key << " ";
        }
        std::cout << "\n";
    }

    void longestIncreasingPath(Node* node, int currentLength, int expected, int& maxLength,
        Path& longestPath, Path currentPath)
    {
        if (node == nullptr) {
            return;
        }

        if (node->key >= expected) {
            currentLength++;
        } else {
            currentLength = 1;
            currentPath.clear();
        }

        if (currentLength > maxLength) {
            longestPath = currentPath;
        }
        currentPath.push_back(node);

        maxLength = std::max(currentLength, maxLength);

        longestIncreasingPath(node->left, currentLength, node->key + 1, maxLength, longestPath, currentPath);
        longestIncreasingPath(node->right, currentLength, node->key + 1, maxLength, longestPath, currentPath);
    }

public:
    Tree() : root{nullptr} { }

    Tree(std::vector<int>& keys) : root{nullptr}
    {
        if (keys.size() == 0) {
            return;
        }
        constructTree(keys);
    }

    void preorder()
    {
        std::vector<Node*> path;
        preorder(root, path);
        print(path);
    }

    int longestConsecutivePath()
    {
        if (root == nullptr) {
            return 0;
        }

        int length = 0;
        Path longestPath {};
        Path currentPath {};

        longestIncreasingPath(root, 0, root->key, length, longestPath, currentPath);
        print(longestPath);
        return length;
    }
};

int main()
{
    std::vector<int> keys {1, 2, 3, 4, 5, 6, INT_MIN, 7, INT_MIN, 8, 9, INT_MIN, 10, 11};
    Tree tree(keys);

    std::cout << "Inorder traversal: ";
    tree.preorder();

    std::cout << "Longest path length: ";
    tree.longestConsecutivePath();
    // std::cout << "\n";

    return 0;
}