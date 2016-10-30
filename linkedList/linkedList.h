#include <memory>    //Use for smart pointers
#include <iostream>  //Use for printf
#include <stdexcept> //Use for runtime_error

template<class T>
struct Node {
   T val;
   Node(T val_) : val(val_) {};
};

template<class T>
class LinkedList {
private:
   std::unique_ptr<Node<T>> node;
public:
   std::unique_ptr<LinkedList<T>> next;
   // Appends a node with this value to the end of the list
   void addNode(T val) {
      if (node == nullptr) {
         node = std::make_unique<Node<T>>(val);
         node->val = val;
      } else if (next == nullptr) {
         next = std::make_unique<LinkedList<T>>();
         next->node = std::make_unique<Node<T>>(val);
      } else {
         next->addNode(val);
      }
   }
   // Removes the first instance of the given value
   void removeNode(T val) {
      if (node == nullptr) return;
      if (node->val == val) {
         if (next != nullptr) {
            node = std::move(next->node);
            next = std::move(next->next);
         } else {
            node.reset(nullptr);
         }
      } else if (next != nullptr) {
         next->removeNode(val);
      }
   }
   // Returns true iff list contains this value
   bool hasNode(T val) {
      if (node == nullptr) {
         return false;
      }
      if (node->val == val) {
         return true;
      }
      if (next == nullptr) {
         return false;
      }
      return next->hasNode(val);
   }
   // Returns value of head node
   T first() {
      if (node == nullptr) {
         throw std::runtime_error("Head is empty, cannot return value");
      }
      return node->val;
   }
   // Prints all values to standard output
   void print() {
      if (node == nullptr) {
         printf("(empty)\n");
      } else if (next == nullptr) {
         printf("%d\n", node->val);
      } else {
         printf("%d->", node->val);
         next->print();
      }
   }
   // Returns a linked list in the reverse order of the input
   // Effects: the input unique_ptr<LinkedList>* no longer points to a valid unique_ptr
   // 
   // Example of use:
   // std::unique_ptr<LinkedList<int>> listPtr(new LinkedList<int>);
   // for (int i=0; i<5; i++) { listPtr->addNode(i); }
   // listPtr = LinkedList<int>::reverseInPlace(&listPtr);
   static std::unique_ptr<LinkedList> reverseInPlace(std::unique_ptr<LinkedList>* headPtr) {
      if (headPtr == nullptr || *headPtr == nullptr) return nullptr;
      if ((*headPtr)->next == nullptr) return std::move(*headPtr);

      std::unique_ptr<LinkedList> newHead = nullptr;
      std::unique_ptr<LinkedList> list = std::move(*headPtr);
      std::unique_ptr<LinkedList> next = nullptr;
      //a->b->c->... : newHead=null, list=&a
      while (list != nullptr) {
         next = (list->next == nullptr) ? nullptr : std::move(list->next);
         //a  b->c->... : list=&a, next=&b
         list->next = std::move(newHead);
         newHead = std::move(list);
         //a  b->c->... : newHead=&a, next=&b
         list = (next == nullptr) ? nullptr : std::move(next);
         //a  b->c->... : newHead=&a, list=&b, next=&b
      }
      return newHead;
   }
};
