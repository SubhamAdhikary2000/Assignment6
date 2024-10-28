#include <iostream>
using namespace std;

struct X {
    X() { cout << "default constructor\n"; }
    X(X&& x) { cout << "move constructor\n"; }
    X(const X& x) { cout << "copy constructor\n"; }
    constexpr X& operator=(const X&) {
        cout << "copy assignment\n";
        return *this;
    }
    ~X() { cout << "Destructor\n"; }
};

X foo(X x) {
    return x;
}

int main() {
    X obj;
    obj = foo(obj);
}

/*
___________________Detailed Output and Reasoning_________________
Creating obj:
    In main(), the statement X obj; calls the default constructor.
    Output so far: default constructor

Calling foo(obj):
    foo takes the argument obj by value. This means a copy of obj is created to pass it into the function.
    Therefore, the copy constructor is called when foo is invoked.
    Output so far: default constructor
                   copy constructor

Returning from foo():
    The return statement return x; in foo() tries to return the local object x.
    Since the function returns an object, the compiler will try to move the local x (if possible). Thus, the move constructor is called to return the object.
    Output so far: default constructor
                   copy constructor
                   move constructor

Assignment to obj:
    Back in main(), the result of foo(obj) is assigned to obj using the copy assignment operator.
    Output so far:  default constructor
                    copy constructor
                    move constructor
                    copy assignment

Destruction of Temporary Objects:
    After the assignment, the temporary objects created during the copy and move operations will be destroyed.
    The destructors will be called for:
        -The object x inside foo().
        -The temporary moved object returned by foo().
        Final Output: default constructor
                        copy constructor
                        move constructor
                        copy assignment
                        Destructor
                        Destructor


*/