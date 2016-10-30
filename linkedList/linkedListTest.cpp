#include <cassert>   //Use for assert
#include <iostream>  //Use for printf
#include <memory>    //Use for smart pointers
#include <stdexcept> //Use for runtime_error
#include "linkedList.h"

void testCanAddNodes() {
  LinkedList<int> list;
  assert(!list.hasNode(5));
  list.addNode(5);
  list.addNode(10);
  list.addNode(15);
  assert(list.hasNode(10));
  assert(list.hasNode(5));
  assert(list.hasNode(15));
  assert(!list.hasNode(20));
}

void testCanAddStringNodes() {
  LinkedList<const char*> list;
  list.addNode("hello, i'm alice");
  list.addNode("hello, i'm bob");
  list.addNode("hello, i'm trudy");
  assert(list.hasNode("hello, i'm alice"));
  assert(list.hasNode("hello, i'm bob"));
  assert(list.hasNode("hello, i'm trudy"));
}

void testCanRemoveFirstNode() {
  LinkedList<int> list;
  for (int i=1;i<=3;i++) {
    list.addNode(5*i);
  }
  list.removeNode(5);
  assert(!list.hasNode(5));
  assert(list.hasNode(10));
  assert(list.hasNode(15));
}

void testCanRemoveMiddleNode() {
  LinkedList<int> list;
  for (int i=1;i<=3;i++) {
    list.addNode(5*i);
  }
  list.removeNode(10);
  assert(!list.hasNode(10));
  assert(list.hasNode(5));
  assert(list.hasNode(15));
}

void testCanRemoveAllNodes() {
  LinkedList<int> list;
  for (int i=1;i<=3;i++) {
    list.addNode(5*i);
  }
  list.removeNode(10);
  list.removeNode(5);
  assert(!list.hasNode(5));
  assert(!list.hasNode(10));
  assert(list.hasNode(15));

  list.removeNode(15);
  assert(!list.hasNode(15));
}

void testCanRemoveNodeNotInList() {
  LinkedList<int> list;
  list.addNode(5);
  list.addNode(10);
  list.removeNode(15);
  assert(list.hasNode(5));
  assert(list.hasNode(10));
}

void testCanRemoveNodes() {
  testCanRemoveFirstNode();
  testCanRemoveMiddleNode();
  testCanRemoveAllNodes();
  testCanRemoveNodeNotInList();
}

void testCanGetValue() {
  std::unique_ptr<LinkedList<int>> listPtr(new LinkedList<int>);
  try {
    int val = listPtr->first();
    assert(1 == 0); // Fail, should throw runtime_error
  } catch (std::runtime_error err) {
  }
  for (int i=0; i<5; i++) {
    listPtr->addNode(i);
  }
  for (int i=0; i<5; i++) {
    assert(listPtr->first() == i);
    listPtr = std::move(listPtr->next);
  }
}

void testCanReverseLinkedList_Empty() {
  std::unique_ptr<LinkedList<int>> listPtr(new LinkedList<int>);
  assert(listPtr != nullptr);
  std::unique_ptr<LinkedList<int>> newListPtr = LinkedList<int>::reverseInPlace(&listPtr);
  assert(newListPtr != nullptr);
}

void testCanReverseLinkedList_SingleElement() {
  std::unique_ptr<LinkedList<int>> listPtr(new LinkedList<int>);
  int val = 10;
  listPtr->addNode(val);
  assert(listPtr->hasNode(val));
  listPtr = LinkedList<int>::reverseInPlace(&listPtr);
  assert(listPtr->hasNode(val));
}

void testCanReverseLinkedList_MultipleElements() {
  std::unique_ptr<LinkedList<int>> listPtr(new LinkedList<int>);
  for (int i=0; i<5; i++) {
    listPtr->addNode(i);
  }
  listPtr = LinkedList<int>::reverseInPlace(&listPtr);
  for (int i=4; i>=0; i--) {
    assert(listPtr->first() == i);
    listPtr = std::move(listPtr->next);
  }
}

void testCanReverseLinkedList() {
  testCanReverseLinkedList_Empty();
  testCanReverseLinkedList_SingleElement();
  testCanReverseLinkedList_MultipleElements();
}

void testCanPrintLinkedList() {
  LinkedList<int> list;
  list.print();
  for (int i=0; i<3; i++) {
    list.addNode(5*i);
    list.print();
  }
}

int main() {
  testCanAddNodes();
  testCanAddStringNodes();
  testCanRemoveNodes();
  testCanGetValue();
  testCanReverseLinkedList();
  testCanPrintLinkedList();
  printf("All tests passed!\n");
  return 0;
}