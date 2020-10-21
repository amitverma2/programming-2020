#include<iostream>

struct Node {
  int val;
  Node* next;
  Node* prev;
  Node(int _val) : val(_val), next(nullptr), prev(nullptr) { }
};

class MyDLL {
  private:
    int count;
    Node* head;
    Node* tail;
  public:
    MyDLL() : count(0), head(nullptr), tail(nullptr) { }
    int size(void) { return count; }
    void push_front(Node* node) {
      if (node) {
        std::cout << "push_front " << node->val << "\n";
        node->next = head;
        node->prev = nullptr;
        if (head) {
          head->prev = node;
        }
        head = node;
        if (tail == nullptr) {
          tail = node; // the list was previously empty
        }
        count++;
      }
    }
    int front(void) {
      if (head) {
        return head->val;
      }
      return -1; // as per standard empty container front access is undefined
    }
    int back(void) {
      if(tail) {
        return tail->val;
      }
      return -1; // as per standard emtry container access is undefined.
    }
    void pop_front(void) {
      if (head) {
        std::cout << "pop_front\n";
        Node* oldHead = head;
        head = head->next;
        if (head) {
          head->prev = nullptr;
        }
        if (tail == oldHead) {
          tail = nullptr;
        }
        // OCD of mine
        oldHead->next = oldHead->prev = nullptr;
        delete oldHead;
        count--;
      }
    }
    void pop_back(void) {
      if (tail) {
        std::cout << "pop_back\n";
        Node* oldTail = tail;
        tail = tail->prev;
        if (tail) {
          tail->next = nullptr;
        }
        if (head == oldTail) {
          head = nullptr;
        }
        // my OCD
        oldTail->next = oldTail->prev = nullptr;
        delete oldTail;
        count--;
      }
    }
    void print(void) {
      if (head == nullptr) {
        std::cout << "DLL is empty\n";
      } else {
        std::cout << "{ ";
        for(Node* ptr = head; ptr != nullptr; ptr = ptr->next) {
          std::cout << ptr->val << " ";
        }
        std::cout << "}\n";
      }
    }
    void printReverse(void) {
      if(tail == nullptr) {
        std::cout << "DLL is empty\n";
      } else {
        std::cout << "DLL in reverse order\n{ ";
        for(Node* ptr = tail; ptr != nullptr; ptr = ptr->prev) {
          std::cout << ptr->val << " ";
        }
        std::cout << "}\nelements\n";
      }
    }
};

int main() {
  MyDLL* myDLL = new MyDLL;
  std::cout << "DLL has size " << myDLL->size() << std::endl;
  myDLL->print();

  Node* n1 = new Node(1);
  myDLL->push_front(n1);
  std::cout << "DLL has size " << myDLL->size() << std::endl;
  myDLL->print();

  Node* n2 = new Node(2);
  myDLL->push_front(n2);
  std::cout << "DLL has size " << myDLL->size() << std::endl;
  myDLL->print();

  Node* n3 = new Node(3);
  myDLL->push_front(n3);
  std::cout << "DLL has size " << myDLL->size() << std::endl;
  myDLL->print();

  myDLL->pop_front();
  std::cout << "DLL has size " << myDLL->size() << std::endl;
  myDLL->print();

  myDLL->pop_back();
  std::cout << "DLL has size " << myDLL->size() << std::endl;
  myDLL->print();

  myDLL->pop_back();
  std::cout << "DLL has size " << myDLL->size() << std::endl;
  myDLL->print();

  Node* n5 = new Node(5);
  myDLL->push_front(n5);
  myDLL->print();

  return 0;
}