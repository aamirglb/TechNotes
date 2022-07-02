#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>

class Person {
public:
    std::string name;
    std::shared_ptr<Person> mother;
    std::shared_ptr<Person> father;
    // std::vector<std::shared_ptr<Person>> kids;
    std::vector<std::weak_ptr<Person>> kids;

    Person(const std::string& n,
           std::shared_ptr<Person> m = nullptr,
           std::shared_ptr<Person> f = nullptr)
        : name{n}
        , mother{m}
        , father{f}
    {}

    ~Person() {
        std::cout << "delete " << name << std::endl;
    }
};

std::shared_ptr<Person> initFamily(const std::string& name)
{
    std::shared_ptr<Person> mom(new Person(name + "'s mom"));
    std::shared_ptr<Person> dad(new Person(name + "'s dad"));
    std::shared_ptr<Person> kid(new Person(name, mom, dad));
    mom->kids.push_back(kid);
    dad->kids.push_back(kid);
    return kid;
}

int main()
{
    std::shared_ptr<Person> p = initFamily("aamir");

    std::cout << "aamir's family exists" << std::endl;
    std::cout << " - aamir is shared " << p.use_count() << " times." << std::endl;
    // std::cout << " - name of 1st kid of aamir's mom: "
    //           << p->mother->kids[0]->name << std::endl;
    std::cout << " - name of 1st kid of aamir's mom: "
              << p->mother->kids[0].lock()->name << std::endl;

    p = initFamily("mohd");
    std::cout << "mohd's family exists" << std::endl;

    std::string s {"abcd"};

    do {
        std::cout << s << std::endl;
    } while(std::next_permutation(s.begin(), s.end()));

}