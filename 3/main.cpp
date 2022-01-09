#include "linked_list.h"
#include <iostream>

int main() {
    LinkedList<int> list = {1, 2, 3, 4, 5};
    LinkedList<int> list1 = {5, 4, 3, 2, 1};
    list.reverse();
    for(const auto& v : list) {
        std::cout << v << std::endl;
    }

    std::cout << "Hello, World!";
    return 0;
}
