#include <iostream>

int32_t BinarySearch(int32_t *a, int32_t len, int32_t key)
{
    int32_t low{};
    int32_t high{len-1};

    while(low <= high)
    {
        int32_t mid = (low + high)/2;
        if(key == a[mid]) return mid;
        else if(key < a[mid]) high = mid - 1;
        else if(key > a[mid]) low = mid + 1;
    }
    return -1;
}

int32_t RecurBinarySearch(int32_t *a,
                        int32_t len,
                        int32_t low,
                        int32_t high,
                        int32_t key)
{
    int32_t mid;

    if(low <= high) {
        mid = (low+high) / 2;
        if(a[mid] == key) return mid;
        else if(key < a[mid])
            return RecurBinarySearch(a, len, low, mid - 1, key);
        else
            return RecurBinarySearch(a, len, mid+1, high, key);
    }
    return -1;
}
int main()
{
    int32_t a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int32_t key{10};
    // auto idx = BinarySearch(a, 10, key);
    auto idx = RecurBinarySearch(a, 10, 0, 10, key);
    if(idx != -1) {
        std::cout << "Element '" << key << "' found at: " << idx << std::endl;
    } else {
        std::cout << "Element '" << key << "' not present in array." << std::endl;
    }
}