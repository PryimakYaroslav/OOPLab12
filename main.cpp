#include <memory>
#include <vector>
#include <iostream>
#include <algorithm>

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

class SimpleDirectedGraph {
    private:
    int numVertices;
    std::vector<std::vector<int>> adjList;

    void DFSUtil(int vertex, std::vector<bool>& visited) {
        visited[vertex] = true;
        std::cout << vertex << " ";

        for (int neighbor: adjList[vertex]) {
            if (!visited[neighbor]) {
                DFSUtil(neighbor, visited);
            }
        }
    }

    bool hasPathUtil(int current, int target, std::vector<bool>& visited) {
        if (current == target) return true;

        visited[current] = true;

        for (int neighbor: adjList[current]) {
            if (!visited[neighbor]) {
                if (hasPathUtil(neighbor, target, visited)) {
                    return true;
                }
            }
        }
        return false;
    }

    public:
    explicit SimpleDirectedGraph(int vertices) {
        this->numVertices = vertices;
        adjList.resize(vertices);
    }

    void addEdge(int from, int to) {
        adjList[from].push_back(to);
    }

    void checkPath(int start, int target) {
        std::vector<bool> visited(numVertices, false);
        bool exist = hasPathUtil(start, target, visited);

        if (exist) {
            std::cout << "Path from " << start << " to " << target << " EXISTS.\n";
        } else {
            std::cout << "Path from " << start << " to " << target << " DOES NOT exist.\n";
        }
    }
};

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

    SimpleDirectedGraph graph(8);
    graph.addEdge(0, 1);
    graph.addEdge(0, 4);
    graph.addEdge(0, 6);
    graph.addEdge(1, 3);
    graph.addEdge(1, 4);
    graph.addEdge(3, 2);
    graph.addEdge(3, 6);
    graph.addEdge(5, 4);  
    graph.addEdge(6, 5);
    graph.addEdge(6, 7);
    graph.addEdge(7, 5); 
    
    graph.checkPath(0, 7);
    graph.checkPath(7, 4); 
    graph.checkPath(6, 2);
    graph.checkPath(5, 7);
    graph.checkPath(3, 7);
    return 0;
}