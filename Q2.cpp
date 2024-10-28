/*Expected Output of the program:

foo()
val.i=5
~foo()
val.i=5
However, this output is logically incorrect and indicates undefined behavior. Let's analyze why.

___________Explanation of the Error________________
What happens when o is deleted?
    -When delete o is called, the destructor of obj is invoked, which triggers the destructor of my_foo.
    -Thus, "~foo()" is printed, and the memory associated with my_foo is released.
    -After the delete o call, val still holds a reference to my_foo, which no longer exists.
    -Accessing val.i after the deletion of o results in undefined behavior, since val points to deallocated memory.


_____________Corrected Program____________________
Avoid Using a Reference
    -Instead of returning a reference to my_foo, return a copy. This way, even if o is deleted, the copy will remain valid*/

#include <iostream>
#include <stdexcept>

struct foo {
    foo() { std::cout << "foo()\n"; } 
    ~foo() { std::cout << "~foo()\n"; }
    int i{5};
};

struct obj {
    foo getFoo() { return my_foo; }
    foo my_foo; 
};

int main() {
    obj* o = new obj();
    foo val = o->getFoo();
    std::cout << "val.i=" << val.i << std::endl;
    delete o;
    std::cout << "val.i=" << val.i << std::endl;

    return 0;
}
