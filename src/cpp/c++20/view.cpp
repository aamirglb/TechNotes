#include <string>
#include <string_view>
#include "format"

class KeyValue {
public:
    KeyValue(std::string_view key, int value)
    : m_key {key}
    , m_value {value}
    {}

    const std::string& getKey() const { return m_key; }
    int getValue() const { return m_value; }

private:
    std::string m_key;
    int         m_value;
};


template<>
class fmt::formatter<KeyValue>
{
public:
    constexpr auto parse(auto& context) {
        auto iter { context.begin() };
        const auto end { context.end() };

        if(iter == end || *iter == '}') {
            m_outputType = OutputType::KeyAndValue;
            return iter;
        }

        switch(*iter) {
            case 'a':
                m_outputType = OutputType::KeyOnly;
                break;
            case 'b':
                m_outputType = OutputType::ValueOnly;
                break;
            case 'c':
                m_outputType = OutputType::KeyAndValue;
                break;
            default:
                throw fmt::format_error{ "Invalid KeyValue format specifier." };
                break;
        }

        ++iter;
        if(iter != end && *iter != '}') {
            throw fmt::format_error{ "Invalid KeyValue format specifier." };
        }
        return iter;
    }

    auto format(const KeyValue& kv, auto& context) {
        switch(m_outputType) {
            using enum OutputType;

            case KeyOnly:
                return fmt::format_to(context.out(), "{}", kv.getKey());
            case ValueOnly:
                return fmt::format_to(context.out(), "{}", kv.getValue());
            default:
                return fmt::format_to(context.out(), "{} - {}",
                    kv.getKey(), kv.getValue());
        }
    }
private:
    enum class OutputType {
        KeyOnly,
        ValueOnly,
        KeyAndValue,
    };
    OutputType m_outputType { OutputType::KeyAndValue };
};

std::string_view extractExtension(std::string_view filename) {
    return filename.substr(filename.rfind('.'));
}

class Simple
{
public:
    Simple() { fmt::print("Constructing simple!!\n"); }
    ~Simple() { fmt::print("Destructing simple!!\n"); }
};

int main() {
    std::string filename { R"(c:\temp\my file.ext)" };
    fmt::print("C++ string: {}\n", extractExtension(filename));

    const char* cStr { R"(c:\temp\my file.txt)" };
    fmt::print("C string: {}\n", extractExtension(cStr));

    fmt::print("Literal: {}\n", extractExtension(R"(c:\temp\my file.exe)"));

    const char* raw {"file.pdf"};
    size_t length {8};
    fmt::print("Raw: {}\n", extractExtension({raw, length}));
    fmt::print("Raw: {}\n", extractExtension(std::string_view{raw, length}));

    int i {42};
    fmt::print("|{:5}|\n", i);
    fmt::print("|{:{}}|\n", i, 7);
    fmt::print("|{:7}|\n", i);
    fmt::print("|{:<7}|\n", i);
    fmt::print("|{:_>7}|\n", i);
    fmt::print("|{:_^7}|\n", i);

    fmt::print("\n\n");
    i =  55;
    fmt::print("|{:<5}|\n", i);
    fmt::print("|{:<+5}|\n", i);
    fmt::print("|{:< 5}|\n", i);
    fmt::print("|{:< 5}|\n", -i);

    fmt::print("\n\n");

    KeyValue kv {"Key1", 11};
    fmt::print("{}\n", kv);
    fmt::print("{:a}\n", kv);
    fmt::print("{:b}\n", kv);
    fmt::print("{:c}\n", kv);
    // try {
    //     fmt::print("{:d}\n", kv);
    // } catch(const fmt::format_error& e) {
    //     fmt::print("{}\n", e.what());
    // }

    std::invoke([](){ fmt::print("Hello Lambda!!\n");});

    Simple *ptr = new Simple[4];
    // delete[] ptr;
    delete ptr;
}