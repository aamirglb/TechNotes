#include <iostream>
#include <string>
#include <vector>
#include <memory>

int main()
{
    std::shared_ptr<std::string> p1(new std::string("aamir"));
    std::shared_ptr<std::string> p2(new std::string("mohd"));

    (*p1)[0] = 'A';
    p2->replace(0, 1, "M");

    std::vector<std::shared_ptr<std::string>> coll;
    coll.push_back(p2);
    coll.push_back(p2);
    coll.push_back(p1);
    coll.push_back(p2);
    coll.push_back(p1);

    for(const auto ptr : coll) std::cout << *ptr << " ";
    std::cout << std::endl;

    *p1 = "Ali";

    for(const auto ptr : coll) std::cout << *ptr << " ";
    std::cout << std::endl;

    std::cout << "use_count: " << coll[0].use_count() << std::endl;
}