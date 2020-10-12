#ifndef _Stack_h_
#define _Stack_h_
#define STACK_MAX 1024
#define STACK_INI_SIZE 1
class Stack {

 public:
  
  // Constructor:
  Stack();
  Stack(const Stack& c);

  ~Stack();
  Stack & operator= (const Stack & c);
  // Push:
  void push(int i);

  // Pop:
  int pop();

  // How big is the stack?
  unsigned int size() const;

  // Print (to std::cout) 
  void print() const;

  // Test if the stack is empty
  bool isEmpty() const;

 private:

  unsigned int       _count;            // Actual length of stack.
  unsigned int       _size;             // Size of memory allocated.
  int                *_data;  // An array to store data.
};
#endif
