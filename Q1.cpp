#include <iostream>
#include <stdexcept> // For exception handling

class myvector {
    int* p;                   // Base pointer to the vector's data
    unsigned int size;         // Size of the vector
    bool shallow;              // Indicates if this is a shallow copy

public:
    // Default constructor: Creates an empty vector
    myvector() : p(nullptr), size(0), shallow(false) {}

    // Constructor: Creates a vector of given size, initialized to 0
    myvector(unsigned int n) : size(n), shallow(false) {
        p = new int[size]{0};  // Initialize all elements to 0
    }

    // Copy constructor: Supports both shallow and deep copy
    myvector(myvector& v, bool shallow = true) : size(v.size), shallow(shallow) {
        if (shallow) {
            // Perform shallow copy: Copy only the pointer
            p = v.p;
        } else {
            // Perform deep copy: Allocate new memory and copy the data
            p = new int[size];
            for (unsigned int i = 0; i < size; ++i) {
                p[i] = v.p[i];
            }
        }
    }

    // Destructor: Releases memory only for deep copied objects
    ~myvector() {
        if (!shallow && p != nullptr) {
            delete[] p;  // Free the allocated memory
        }
    }

    // Return the base pointer to the vector
    int* get_ptr() const {
        return p;
    }

    // Return the size of the vector
    constexpr unsigned int get_size() const {
        return size;
    }

    // Return the shallow flag
    bool is_shallow() const {
        return shallow;
    }

    // Update the element at index i with value val
    void update(unsigned int i, int val) {
        if (i >= size) {
            throw std::out_of_range("Index out of bounds");
        }
        p[i] = val;
    }

    // Return the element at index i
    constexpr int get(unsigned int i) const {
        if (i >= size) {
            throw std::out_of_range("Index out of bounds");
        }
        return p[i];
    }

    // Print the vector contents to the console
    void print() const {
        for (unsigned int i = 0; i < size; ++i) {
            std::cout << p[i] << " ";
        }
        std::cout << std::endl;
    }

    // Expand the vector and insert a new value at the end
    void push_back(int val) {
        int* new_p = new int[size + 1];  // Allocate new memory for expanded vector
        for (unsigned int i = 0; i < size; ++i) {
            new_p[i] = p[i];             // Copy existing elements
        }
        new_p[size] = val;               // Add the new element
        if (!shallow) {
            delete[] p;  // Free old memory only if it's a deep copy
        }
        p = new_p;
        ++size;
    }
};

int main() {
    // Create a vector of size 7 initialized to 0
    myvector x(7);
    for (unsigned int i = 0; i < 7; ++i) {
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

/*
Class Members:
    p: A pointer to dynamically allocated memory storing the vector’s elements.
    size: The size of the vector.
    shallow: A flag to track whether the vector is a shallow copy.

Constructors:
    Default Constructor: Initializes an empty vector.
    Parameterized Constructor: Creates a vector of size n with all elements set to 0.
    Copy Constructor: Can perform both shallow and deep copy based on the shallow flag.
    
Destructor: Releases memory only if the vector is not a shallow copy.

push_back Method: Expands the vector by 1 element and inserts a new value at the end
*/