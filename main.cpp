#include <memory>
#include <vector>
#include <iostream>

struct BinaryNode {
    int data;
    std::unique_ptr<BinaryNode> left = nullptr;
    std::unique_ptr<BinaryNode> right = nullptr;
    BinaryNode(int val) : data(val) {}
};

void insertBST(std::unique_ptr<BinaryNode>& root, int val){
    if (!root) {
        root = std::make_unique<BinaryNode>(val);
        return;
    }

    if (val < root->data) {
        insertBST(root->left, val);
    } else if (val > root->data) {
        insertBST(root->right, val);
    }
}

int main() {
    std::unique_ptr<BinaryNode> bstRoot = nullptr;

    std::vector<int> data = {70, 20, 50, 30, 80, 60, 40};
    for (int x : data) {
        insertBST(bstRoot, x);
    }

    return 0;
}