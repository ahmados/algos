#include <iostream>  // std::cout, std::cin
#include <algorithm>  // std::max
#include <utility>  // std::pair

struct Node {
    int value;
    int freq;
    Node* right;
    Node* left;
    Node* parent;

    explicit Node(std::pair<int, int> valkey) {
        this->value = valkey.first;
        this->freq = valkey.second;
        this->right = nullptr;
        this->left = nullptr;
        this->parent = nullptr;
    }

    Node(std::pair<int, int> valkey, Node* right, Node* left) {
        this->value = valkey.first;
        this->freq = valkey.second;
        this->right = right;
        this->left = left;
        this->parent = nullptr;
    }
};

class SearchTree {
 private:
    Node* head_;

 public:
    explicit SearchTree(Node* head) {
        this->head_ = head;
    }

    Node* getHead() {
        return head_;
    }
    void insertHelper(Node* node, int val) {
        if (node->value == val) {
            (node->freq)++;
            return;
        }
        if (node->value > val) {
            if (!node->left) {
                auto pair = std::make_pair(val, 1);
                node->left = new Node(pair);
                (node->left)->parent = node;
            } else if (node->value == val) {
                return;
            } else {
                insertHelper(node->left, val);
            }
        } else {
            if (!node->right) {
                auto pair = std::make_pair(val, 1);
                node->right = new Node(pair);
                (node->right)->parent = node;
            } else if (node->value == val) {
                return;
            } else {
                insertHelper(node->right, val);
            }
        }
    }
    void insert(int val) {
        if (head_) {
            if (head_->value == val) {
                (head_->freq)++;
                return;
            }
            this->insertHelper(head_, val);
        } else {
            auto pair = std::make_pair(val, 1);
            head_ = new Node(pair);
        }
    }

    int heightHelper(Node* node) {
        if (!node) {
            return 0;
        } else {
            return (1 + std::max(heightHelper(node->left), heightHelper(node->right)));
        }
    }

    Node* largest(Node* node) {
        if (!node->right) {
            return node;
        } else {
            return largest(node->right);
        }
    }

    void print(Node* node) {
        if ((!node->right) && (!node->left)) {
            std::cout << node->value << " " << node->freq << "\n";
        } else {
            if (node->left) {
                print(node->left);
            }
            std::cout << node->value << " " << node->freq << "\n";
            if (node->right) {
                print(node->right);
            }
        }
    }

    bool checkAVL(Node* node) {
        if ((node->left) && (node->right)) {
            if (std::abs(this->heightHelper(node->left)-
                this->heightHelper(node->right)) <= 1) {
                return ((checkAVL(node->left)) && (checkAVL(node->right)));
            } else {
                return false;
            }
        } else if (node->left) {
            if (this->heightHelper(node->left) <= 1) {
                return true;
            } else {
                return false;
            }
        } else if (node->right) {
            if (this->heightHelper(node->right) <= 1) {
                return true;
            } else {
                return false;
            }
        } else {
            return true;
        }
    }
};

int main() {
    SearchTree tree(nullptr);
    int number = -1;
    while (number != 0) {
        std::cin >> number;
        if (number != 0) {
            tree.insert(number);
        }
    }
    Node* head = tree.getHead();
    tree.print(head);
}

