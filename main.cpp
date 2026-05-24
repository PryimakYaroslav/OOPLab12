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

BinaryNode* searchBST(const std::unique_ptr<BinaryNode>& root, int val, int& comparsions) {
    if (!root) return nullptr;

    comparsions++;
    if (root->data == val){
        return root.get();
    }

    comparsions++;    
    if (val < root->data) {
        return searchBST(root->left, val, comparsions);
    } else {
        return searchBST(root->right, val, comparsions);        
    }
}

void findAndPrint(const std::unique_ptr<BinaryNode>& root, int val) {
    int compr = 0;
    BinaryNode* result = searchBST(root, val, compr);

    if (result) {
        std::cout << "Element " << val << " has been found." << " Comparsions: " << compr << "\n";
    } else {
        std::cout << "Element " << val << " not found." << " Comparsions: " << compr << "\n";        
    }
}

int main() {
    std::unique_ptr<BinaryNode> bstRoot = nullptr;

    std::vector<int> data = {70, 20, 50, 30, 80, 60, 40};
    for (int x : data) {
        insertBST(bstRoot, x);
    }

    findAndPrint(bstRoot, 30);
    findAndPrint(bstRoot, 40);
    findAndPrint(bstRoot, 65);  
    findAndPrint(bstRoot, 80);
    findAndPrint(bstRoot, 50); 
    return 0;
}