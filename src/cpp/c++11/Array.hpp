#include <iostream>

template <typename T>
class Array
{
private:
    T* elements;
    size_t count;

public:
    explicit Array(size_t arraySize);    // Constructor
    Array(const Array& other);           // Copy Constructor
    Array(Array&& other);                // Move Constructor
    virtual ~Array();                    // Destructor
    T& operator[](size_t index);         // Subscript operator
    const T& operator[](size_t index) const;   // Subscript operator
    Array& operator=(const Array& rhs);  // Assignment operator
    Array& operator=(Array&& rhs);       // Move assignment operator
    size_t size() const { return count; }      // count accessor
};

template <typename T>
Array<T>::Array(size_t arraySize)
    try : elements {new T[arraySize]}
        , count{arraySize}
{}
catch(const std::exception& e) {
    std::cerr << "Memory allocation failure in Array constructor." << std::endl;
    throw e;
}


template <typename T>
inline Array<T>::Array(const Array& other)
    try : elements { new T[other.count]}
        , count{other.count}
{
    for(size_t i {}; i < count; ++i) {
        elements[i] = other.elements[i];
    }
}
catch(std::bad_alloc&) {
    std::cerr << "Memory allocation failed fro Array object copy." << std::endl;
}

template <typename T>
Array<T>::~Array()
{
    delete []elements;
}

template <typename T>
T& Array<T>::operator[](size_t index) {
    return elements[index];
}

template <typename T>
const T& Array<T>::operator[](size_t index) const {
    return elements[index];
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const Array<T>& arr)
{
    for(size_t i {}; i < arr.size(); ++i) {
        os << arr[i] << ' ';
    }
    return os;
}