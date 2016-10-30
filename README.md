# cppCollections
C++ collections, implemented for educational purposes

## linkedList

A LinkedList implementation using templates and safe pointers.

Run tests: ```make test```

Clear executables and object files: ```make clean```

#### Declaration:

```c_cpp
template<class T> class LinkedList;
```

#### Member functions:

```c_cpp
void addNode(T val);    // Appends value to the end of the list
void removeNode(T val); // Removes the first instance from the list
bool hasNode(T val);    // Returns true iff list contains this value
T first();              // Returns value of first node in the list
void print();           // Prints all values to standard output in format: 5->10->15
```

#### Non-member functions:

```c_cpp
// Returns a linked list in the reverse order of the input
// Effects: the input unique_ptr<LinkedList>* no longer points to a valid unique_ptr
// 
// Example of use:
// std::unique_ptr<LinkedList<int>> listPtr(new LinkedList<int>);
// for (int i=0; i<5; i++) { listPtr->addNode(i); }
// listPtr = LinkedList<int>::reverseInPlace(&listPtr);
static std::unique_ptr<LinkedList> reverseInPlace(std::unique_ptr<LinkedList>* headPtr);
```

#### Example of usage:

```c_cpp
void myFunction() {
  // Create a LinkedList of type int
  std::unique_ptr<LinkedList<int>> listPtr(new LinkedList<int>);
  for (int i=0; i<5; i++) {
    listPtr->addNode(i);
  }

  // Print contents to standard output
  listPtr->print(); // Prints "0->1->2->3->4"

  // Reverse the contents of the LinkedList
  listPtr = LinkedList<int>::reverseInPlace(&listPtr);
  listPtr->print(); // Prints "4->3->2->1->0"

  // Check that the list contains a given element
  assert(listPtr->hasNode(2) == true);
  assert(listPtr->hasNode(5) == false);
  assert(listPtr->first() == 4);
}
```
