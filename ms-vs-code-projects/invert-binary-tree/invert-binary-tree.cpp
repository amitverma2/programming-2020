#include<iostream>

struct Node {
  int val;
  Node * left;
  Node * right;
  Node() : val(0), left(nullptr), right(nullptr) { }
  Node(int _val) : val(_val), left(nullptr), right(nullptr) { }
  Node(int _val, Node* _left, Node* _right) : val(_val), left(_left), right(_right) { }
};

class MySolution {
  public:
    Node* invertTree(Node* root) {
      if (root == nullptr) return nullptr;
      
      Node* oldLeft = root->left;
      root->left = invertTree(root->right);
      root->right = invertTree(oldLeft);
      return root;
    }
};

class PrintTree {
  public:
    void preOrder(Node* root) {
      if (root == nullptr) return;
      std::cout << root->val << " ";
      preOrder(root->left);
      preOrder(root->right);
      return;
    }
};

int main() {
  // (1(2(4)(5))(3(6)(7))) pre-order
  Node* n4 = new Node(4);
  Node* n5 = new Node(5);
  Node* n2 = new Node(2, n4, n5);
  Node* n6 = new Node(6);
  Node* n7 = new Node(7);
  Node* n3 = new Node(3, n6, n7);
  Node* n1 = new Node(1, n2, n3);

  PrintTree* printObj = new PrintTree;

  std::cout << "Printing the current tree in pre-order\n";
  printObj->preOrder(n1);
  std::cout << std::endl;

  MySolution* obj = new MySolution;

  obj->invertTree(n1);

  std::cout << "Printing the inverted tree in pre-order\n";
  printObj->preOrder(n1);
  std::cout << std::endl;

  return 0;
}