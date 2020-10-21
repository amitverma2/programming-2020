#include<iostream>

struct SinglyLLNode {
  int val;
  SinglyLLNode* next;
  SinglyLLNode(int _val, SinglyLLNode* _next) : val(_val), next(_next) { }
};

class MySinglyLL {
  private:
    int count; // for quick size determination
    SinglyLLNode* head;
  public:
    MySinglyLL() : count(0), head(nullptr) { }
    int size(void) { return count; }
    int front(void) {
      if (head) {
        return head->val;
      } else {
        // C++ standard states that calling front on an empty container is undefined behaviour
        return -1;
      }
    }
    void push_front(SinglyLLNode* node) {
      if (node) {
        node->next = head;
        head = node;
        count++;
      }
    }
    void pop_front(void) {
      if (head) {
        SinglyLLNode* oldHead = head;
        head = head->next;
        delete oldHead;
        count--;
      }
    }
    void print(void) {
      if (count == 0) {
        std::cout << "Linked list is Empty\n";
      } else {
        std::cout << "Linked list has the following\n{ ";
        for(SinglyLLNode* ptr = head; ptr != nullptr; ptr = ptr->next) {
          std::cout << ptr->val << " ";
        }
        std::cout << "}\nelements\n";
      }
    }
};

int main() {
  MySinglyLL* ll = new MySinglyLL;
  ll->print();
  SinglyLLNode* n1 = new SinglyLLNode(1, nullptr);
  ll->push_front(n1);
  ll->print();
  SinglyLLNode* n2 = new SinglyLLNode(2, nullptr);
  ll->push_front(n2);
  ll->print();
  ll->pop_front();
  ll->print();
  ll->pop_front();
  ll->print();

  return 0;
}