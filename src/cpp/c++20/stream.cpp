#include <iostream>
#include <iomanip>
#include <cstring>
#include <ctime>
#include <sstream>

#include "format"

void sumInput()
{
    std::cout << "Enter numbers on separate lines to add.\n"
              << "Use Ctrl+Z followed by Enter to finish (Ctrl+D on Unix/Linux).\n";

    int sum{};

    if(!std::cin.good()) {
        std::cerr << "Standard input is in bad state!!\n";
        return;
    }

    while(!std::cin.bad()) {
        int num;
        std::cin >> num;
        if(std::cin.good()) {
            sum += num;
        } else if(std::cin.eof()) {
            break;
        } else if(std::cin.fail()) {
            std::cin.clear();
            std::string badToken;
            std::cin >> badToken;
            std::cerr << "WARNING: Bad input encountered: " << badToken << std::endl;
        }
    }
    // std::cin.clear();
    std::cout << "The sum is " << sum << std::endl;
}

std::string readName(std::istream& stream)
{
    if(!stream.good()) {
        std::cerr << "stream is in bad state!!\n";
        stream.clear();
    }

    std::string name;
    std::cout << "\n\nEnter your name: ";

    char next;
    while(stream.get(next)) name += next;

    // while(stream) {
    //     int next { stream.get() };
    //     if(!stream || next == std::char_traits<char>::eof())
    //         break;
    //     name += static_cast<char>(next);
    // }
    return name;
}

void getReservationData()
{
    std::string guestName;
    int partySize {};

    char ch;
    std::cin >> std::noskipws;

    while(std::cin >> ch) {
        if(std::isdigit(ch)) {
            std::cin.unget(); // put back digit character into the input stream
            if(std::cin.fail()) {
                std::cout << "unget() failed" << std::endl;
            }
            break;
        }
        guestName += ch;
    }

    if(std::cin) {
        std::cin >> partySize;
    }

    if(!std::cin) {
        std::cerr << "Error getting party size." << std::endl;
        return;
    }

    std::cout << fmt::format("Guest: {}, party of {}.\n", guestName, partySize);
}

void readTokens()
{
    std::cout << "Enter tokens. (Ctrl-Z) followed by Enter to end.\n";
    std::ostringstream outStream;

    while(std::cin) {
        std::string nextToken;
        std::cout << "Next token: ";
        std::cin >> nextToken;
        if(!std::cin || nextToken == "done")
            break;
        outStream << nextToken << '\t';
    }
    std::cout << "End result is: " << outStream.str() << std::endl;
}

int main()
{
    for(int i {65}; i < 75; ++i) {
        std::cout.put(static_cast<char>(i));
    }
    std::cout << std::endl;

    const char* test {"hello\nworld"};
    std::cout.write(test, strlen(test));

    std::cout.imbue(std::locale{""});
    std::cout << "put_moeny: " << std::put_money("120000") << std::endl;

    time_t t_t { time(nullptr) };
    tm* t {localtime(&t_t)};
    std::cout << "time format: " << std::put_time(t, "%c") << std::endl;
    std::cout << std::quoted("Quoted string with \"embedded quotes\".") << std::endl;

    // std::cout << "\n\n";
    // sumInput();

    // std::cout << readName(std::cin) << std::endl;

    // getReservationData();
    readTokens();
}