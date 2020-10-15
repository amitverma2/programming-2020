#include<iostream>

struct Node {
  Node * left;
  Node * right;
};

class checkBBT {
private:
  static int checkHeight(Node *node) {
    if (node == nullptr)
      return 0;

    int lh = checkHeight(node->left);
    if (lh == -1) return -1;

    int rh = checkHeight(node->right);
    if (rh == -1) return -1;

    int diff = lh - rh;
    if (diff < 0) diff *= -1;

    if (diff > 1) {
      return -1;
    } else {
      return ((lh > rh)?lh:rh) + 1;
    }
  }
public:
  static int isBalanced(Node *node) {
    return checkHeight(node);
  }
};

int main(int argc, char *argv[]) {
  Node *root = new Node;
  root->left = new Node;
  root->right = new Node;
  root->left->left = new Node;
  root->left->right = new Node;
  root->right->left = new Node;
  root->left->left->left = new Node;

  std::cout << std::hex << "Root: " << root << " Left: " << root->left << " Right: " << root->right << std::endl;

  int height = checkBBT::isBalanced(root);
  if (height != -1) {
    std::cout << "Is balanced BBT of height " << height << std::endl;
  } else {
    std::cout << "Is not a balanced BBT\n";
  }
  return 0;
}