// Create a heap inplace

#include <iostream>
#include <array>

constexpr int32_t heapSize {8};

using heap_t = std::array<int32_t, heapSize>;

void insert(heap_t &arr, int n) {
    int32_t tmp {arr[n]};
    int32_t i {n};

    while(i > 1 && tmp > arr[ i/2 ]) {
        arr[i] = arr[i/2];
        i /= 2;
    }
    std::cout << i << " " << arr[i] << " " << tmp << std::endl;
    arr[i] = tmp;
}

int32_t deleteHeap(heap_t &arr, int32_t n) {
    int32_t i{}, j{}, x{};

    int32_t delVal = arr[1];
    // element to be deleted
    x = arr[n];

    // last element to be adjuested in the heap,
    // initially it will take root's place
    arr[1] = arr[n];
    arr[n] = delVal;

    i = 1;
    j = i*2; // left child of i

    while(j < n-1) {
        // compare left child with right child is greater
        if(arr[j+1] > arr[j]) j++;

        // check if parent is less then the child
        if(arr[i] < arr[j]) {
            std::swap(arr[i], arr[j]);
            i = j;
            j = 2*j; // move to left child
        } else {
            break;
        }
    }
    return delVal;
}

void createHeap() {
    heap_t a {0, 10, 20, 30, 25, 5, 40, 35};
    // heap_t b {0, 2, 5, 8, 9, 4, 10, 7};

    std::cout << "Before heap creation: " << std::endl;
    for(const auto& e : a) std::cout << e << ' ';
    std::cout << std::endl;

    for(int32_t i = 2; i < heapSize; ++i)
        insert(a, i);

    std::cout << "After heap creation: " << std::endl;
    for(const auto& e : a) std::cout << e << ' ';
    std::cout << std::endl;

    for(int32_t i = heapSize - 1; i > 1; --i) {
        std::cout << "Deleted element: " << deleteHeap(a, i) << std::endl;
    }
    // std::cout << "Deleted element: " << deleteHeap(a, 6) << std::endl;

    for(const auto& e : a) std::cout << e << ' ';
    std::cout << std::endl;
}

int main()
{
    createHeap();
}