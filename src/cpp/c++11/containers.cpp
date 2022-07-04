#include <iostream>
#include <deque>
#include <fstream>
#include <string>
#include <vector>
#include <array>
#include <list>
#include <unordered_set>
#include <unordered_map>

enum class Modes
{
    eFM_INVALID,
    eFM_VECTOR,
    eFM_DEQUE,
};

class CVectorDequeTest
{
public:
    CVectorDequeTest();

    void ReadTestFile(const std::string& szFile, Modes mode)
    {
        char buff[0xFFFF] = {0};
        std::ifstream inFile;
        inFile.open(szFile);

        while(inFile.getline(buff, sizeof(buff))) {
            if(mode == Modes::eFM_VECTOR) {
                m_vData.push_back(buff);
            } else if(mode == Modes::eFM_DEQUE) {
                m_dData.push_back(buff);
            }
        }
        inFile.close();
    }

    virtual ~CVectorDequeTest();

protected:
    std::vector<std::string> m_vData;
    std::deque<std::string> m_dData;
};

int main()
{
    std::deque<float> coll;
    for(int32_t i = 1; i <= 6; ++i) {
        coll.push_front(i * 1.1);
    }

    for(const auto& e : coll) {
        std::cout << e << ' ';
    }
    std::cout << std::endl;

    std::array<int32_t, 5> arr;
    for(size_t i = 0; i < arr.size(); ++i) {
        std::cout << i << ": " << arr[i] << std::endl;
    }

    std::list<char> clist;
    for(char c='a'; c<='z'; ++c) clist.push_back(c);
    for(const auto& c : clist) std::cout << c << ", ";
    std::cout << std::endl;

    for(auto& c : clist) c -= 32;

    for(const auto& c : clist) std::cout << c << ", ";
    std::cout << std::endl;

    /*std::unordered_set<std::string>*/ std::unordered_multiset<std::string> cities {
        "Dubai", "Abu Dhabi", "Sharja", "Ajman", "RAK",
    };

    for(const auto& e : cities) std::cout << e << ' ';
    std::cout << std::endl;

    cities.insert({"London", "Munich", "New York", "Dubai", "RAK"});
    for(const auto& e : cities) std::cout << e << ' ';
    std::cout << std::endl;

    std::unordered_map<std::string, double> uno_map {
        {"tim", 9.9},
        {"struppi", 11.77},
    };

    for(std::pair<const std::string, double>& e : uno_map) {
        e.second *= e.second;
    }

    for(const auto& e : uno_map)
        std::cout << e.first << ": " << e.second << std::endl;
}
