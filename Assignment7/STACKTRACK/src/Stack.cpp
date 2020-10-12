#include "STACK/Stack.h"
#include <iostream>
#include <stdexcept>
#include <cstring>
using namespace std;

// The constructor is called every time an object is created.
// This insures that the object starts from a well defined state
// ... without requiring further initialization from the client.

// unimplemented!
Stack::Stack(){
  // ==> Insert code here:
  _count=0;
  std::cout << "HELLO from the default constructor." << std::endl;
}

// The push function increases the length of the stack by one element
// add the value to the end of the stack.  

Stack::Stack(const Stack & c)
{
  _count=c._count;
  std::memcpy(_data, c._data, _count * sizeof(int));
  std::cout << "HELLO from the copy constructor." << std::endl;
}

Stack::~Stack()
{
  std::cout << "GOOD-BYE from the destructor." << std::endl;
}

Stack& Stack::operator= (const Stack & c)
{
  _count = c._count;
  std::memcpy(_data, c._data, _count * sizeof(int));
  std::cout << "ASSIGN from the assignment operator" << std::endl;
  return *this;
}


// unimplemented!  
void Stack::push(int i) {
  // ==> insert code here
  if (_count>=STACK_MAX){
    throw std::range_error("attempt to push past the end of stack");
  }
  else{
    _data[_count] = i;
    _count++;
  }
}

// The pop function decreases the length of the stack by one element, 
// and returs the value that is popped off

// unimplemented!  
int Stack::pop(){
  //  ==> Change the following line to something sensible...
  _count--;
  return _data[_count];
  
}

// The size function returns the size of the stack. The stack does
// not change so this function is "const".

// unimplemented!  
unsigned int Stack::size() const {
  //  ==> Change the following line to something sensible...
  return _count;
}

// The print function dumps the entire stack to std::cout, in a 
// human-readable format.  The stack does not change, so this function
// is "const"

// unimplemented!  
void Stack::print() const {
  // ==> insert code here
  for (unsigned int j=0; j<_count;j++){
    std::cout<<_data[j]<<std::endl;
  } 
}

// The isEmpty() query function returns true or false, depending on 
// whether the stack is empty (length 0).  The stack does not change,
// so this function is "const"

// unimplemented!  
bool Stack::isEmpty() const {
  // Change the following line to something sensible
  return (_count==0);
}


