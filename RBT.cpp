#include <iostream>  // std::cout, std::cin
#include <algorithm>  // std::max
#include <utility>  // std::pair
#include <string>  // std::string
#include <vector>  // std::vector

struct Node {
    int pos;
    int value;
    int right;
    int left;
    int parent;
    bool color;

    Node() {
        this->pos = 0;
        this->value = 0;
        this->right = 0;
        this->left = 0;
        this->color = false;
    }

    Node(int pos, int value, int left, int right, bool color) {
        this->pos = pos;
        this->value = value;
        this->right = right;
        this->left = left;
        this->color = color;  // red - 1; black - 0;
    }
};

class RBT {
 private:
    std::vector<Node> tree_;
    int head_;
    int max_;

 public:
    RBT(std::vector<Node> tree, int head) {
        this->tree_ = tree;
        this->head_ = head;
        this->max_ = 0;
    }

    std::vector<Node> data() {
        return (tree_);
    }


    void insert(Node node) {
        tree_[node.pos] = node;
        max_ = std::max(max_, node.value);
    }

    bool checkRB(int pos) {
        if (pos == 0) {
            return true;
        }
        if (((tree_[pos].color) && (tree_[tree_[pos].right].color)) ||
            ((tree_[pos].color) && (tree_[tree_[pos].left].color))) {
                return false;
            } else {
                return (checkRB(tree_[pos].right) && checkRB(tree_[pos].left));
            }
    }

    int blackHelper(int pos) {
        if (pos == 0) {
            return 1;
        }
        if ((blackHelper(tree_[pos].right) == blackHelper(tree_[pos].left))
            && (blackHelper(tree_[pos].right) != 0)) {
            if (tree_[pos].color == 1) {
                return blackHelper(tree_[pos].right);
            } else {
                return blackHelper(tree_[pos].right) + 1;
            }
        } else {
            return 0;
        }
    }

    int maxSubTree(int pos) {
        if (pos == 0) {
            return 0;
        }
        return std::max(std::max(maxSubTree(tree_[pos].right),
            tree_[pos].value), std::max(maxSubTree(tree_[pos].left),
            tree_[pos].value));
    }

    int minSubTree(int pos) {
        if (pos == 0) {
            return this->max_;
        }
        return std::min(std::min(minSubTree(tree_[pos].right),
            tree_[pos].value), std::min(minSubTree(tree_[pos].left),
            tree_[pos].value));
    }

    void inOrder(int pos, std::vector<int>& ordered) {
        if (pos == 0) {
            return;
        } else {
            inOrder(tree_[pos].left, ordered);
            ordered.push_back(tree_[pos].value);
            inOrder(tree_[pos].right, ordered);
        }
    }

    bool checkTree(int pos) {
        return true;
    }
    /*bool checkTree(int pos) {
        if (pos == 0) {
            return true;
        }
        if ((((tree_[tree_[pos].right].value > tree_[pos].value)
            ||
            (tree_[pos].right == 0))
            &&
            ((tree_[pos].value < minSubTree(tree_[pos].right))
            ||
            (tree_[pos].right == 0)))
            &&
            (((tree_[tree_[pos].left].value < tree_[pos].value)
            ||
            (tree_[pos].left == 0))
            &&
            ((tree_[pos].value > maxSubTree(tree_[pos].left))))) {
            return (checkTree(tree_[pos].right) && (checkTree(tree_[pos].left)));
        } else {
            //  std::cout << pos << "\n";
            //  std::cout << maxSubTree(tree_[pos].left) << " "
            //  << minSubTree(tree_[pos].right) << "\n";
            return false;
        }
    }*/
};

int main() {
    int numberOfNodes;
    int head;
    std::cin >> numberOfNodes;
    if (numberOfNodes != 0) {
        std::cin >> head;
        std::vector<Node> vectorOfNodes(numberOfNodes + 1);
        RBT redBlack(vectorOfNodes, head);
        Node null(0, 0, 0, 0, 0);
        redBlack.insert(null);
        for (auto i = 0; i != numberOfNodes; i++) {
            int pos;
            int value;
            int left;
            int right;
            bool color;
            std::string rightString;
            std::string leftString;
            std::string colorString;
            std::cin >> pos >> value >> leftString
            >> rightString >> colorString;

            if (leftString == "null") {
                left = 0;
            } else {
                left = std::stoi(leftString);
            }
            if (rightString == "null") {
                right = 0;
            } else {
                right = std::stoi(rightString);
            }

            if (colorString == "R") {
                color = true;
            } else {
                color = false;
            }
            Node currNode(pos, value, left, right, color);
            redBlack.insert(currNode);
        }

        /*for (auto i = 0; i != numberOfNodes + 1; i++) {
            std::cout << ((redBlack.data())[i]).pos << " " <<
            ((redBlack.data())[i]).value << "\n";
        }*/

        bool checkRB = redBlack.checkRB(head);
        //std::cout << checkRB << "\n";
        bool checkNB = (redBlack.blackHelper(head) > 0);
        //std::cout << checkNB << "\n";
        bool checkTree = true;
        // std::cout << checkTree << "\n";
        bool checkHead = !((redBlack.data())[head].color);
        //std::cout << checkHead << "\n";
        std::vector<int> myVector;
        redBlack.inOrder(head, myVector);
        for (auto i = 0; i != myVector.size() - 1; i++) {
            if (myVector[i + 1] <= myVector[i]) {
                checkTree = false;
            }
        }
        bool conclusion = (checkRB && checkNB && checkHead && checkTree);
        if (conclusion) {
            std::cout << "YES\n";
        } else {
            std::cout << "NO\n";
        }
    } else {
        std::cout << "YES\n";
    }
}










