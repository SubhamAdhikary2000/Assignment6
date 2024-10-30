#include <iostream>
using namespace std;

class myvector
{
    int* p;                   // pointer to the base address of vector
    unsigned int size;         // Size of the vector
    bool shallow;              // Indicates if this is a shallow copy
    int count=1;

public:
    // Default constructor: Creates an empty vector
    myvector() : p(nullptr), size(0), shallow(false) {}

    // Parameterized Constructor: Creates a vector of given size, initialized to 0
    myvector(unsigned int n) : size(n), shallow(false)
    {
        p = new int[size]{0};  // Initialize all elements to 0
    }

    // Copy constructor: Supports both shallow and deep copy
    myvector(myvector& v, bool shallow = true) : size(v.size), shallow(shallow)
    {
        if (shallow)
        {
            // shallow copy: Copy only the pointer
            v.count++;
            p = v.p;
        }
        else
        {
            // deep copy: Allocate new memory and copy elements
            p = new int[size];
            for (unsigned int i = 0; i < size; ++i) {
                p[i] = v.p[i];
            }
        }
    }
    // Return the base pointer to the vector
    int* get_ptr() const
    {
        return p;
    }

    // Return the size of the vector
    constexpr unsigned int get_size() const
    {
        return size;
    }

    // Return the shallow flag
    bool is_shallow() const
    {
        return shallow;
    }
     // Update the element at index i with val
    void update(unsigned int i, int val)
    {
        if (i < size)
        {
            p[i] = val;
        }
    }
    // Return the element at index i
    constexpr int get(unsigned int i) const
    {
        return (i < size) ? p[i] : 0;
    }

    // Print the vector contents
    void print() const
    {
        for (unsigned int i = 0; i < size; ++i)
        {
            cout << p[i] << " ";
        }
        cout << endl;
    }

    // Expand the vector and insert a new value at the end
    void push_back(int val)
    {
        int* new_p = new int[size + 1];  // Allocate new memory for expanded vector
        for (unsigned int i = 0; i < size; ++i)
        {
            new_p[i] = p[i];             // Copy existing elements
        }
        new_p[size] = val;               // Add the new element
        if (!shallow)
        {
            delete[] p;  // Free old memory only if it's a deep copy
        }
        p = new_p;
        ++size;
    }

    // Destructor:
    ~myvector() {
        //Releases memory for deep copied objects
        if (!shallow && p != nullptr)
        {
            delete[] p;  // Free the allocated memory
        }
        else
        {
            //shallow copies is released only when no shallow copies exist in the scope i.e  if number of instances sharing the same memory is zero then we need to free the memory
            if (--count == 0)
            {
                delete[] p;
            }
        }
    }


};

int main() {
    // Create a vector of size 7 initialized to 0
    myvector x(7);
    for (unsigned int i = 0; i < 7; ++i)
    {
        x.update(i, 10 + 5 * i);
    }

    // Perform shallow copy of x
    myvector v{x};
    v.update(1, 100);
    v.print();  // Output: 10 100 20 25 30 35 40

    // Verify that x is also modified (shallow copy effect)
    x.print();  // Output: 10 100 20 25 30 35 40

    // Perform deep copy of x
    myvector y{x, false};
    y.update(1, 200);
    y.print();  // Output: 10 200 20 25 30 35 40

    // Verify that x is NOT modified (deep copy effect)
    x.print();  // Output: 10 100 20 25 30 35 40

    // Add 500 to the end of y and verify
    y.push_back(500);
    y.print();  // Output: 10 200 20 25 30 35 40 500

    return 0;
}
