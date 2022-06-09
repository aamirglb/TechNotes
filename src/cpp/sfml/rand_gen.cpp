#include <iostream>
#include <mutex>
#include <random>
// #include <SFML/System/Mutex.hpp>
// #include <SFML/System/Lock.hpp>
#include <SFML/Config.hpp>

class RandomGenerator {
public:
    RandomGenerator() : m_engine(m_device()) {}

    int Generate(int _min, int _max) {
        std::lock_guard<std::mutex> guard(m_mutex);

        if(_min > _max) { std::swap(_min, _max); }

        if(_min != m_intDistribution.min() ||
            _max != m_intDistribution.max()) {
            m_intDistribution = std::uniform_int_distribution<int>(_min, _max);
        }
        return m_intDistribution(m_engine);
    }

    float Generate(float _min, float _max) {
        std::lock_guard<std::mutex> guard(m_mutex);

        if(_min > _max) { std::swap(_min, _max); }

        if(_min != m_floatDistribution.min() ||
            _max != m_floatDistribution.max()) {
            m_floatDistribution = std::uniform_real_distribution<float>(_min, _max);
        }
        return m_floatDistribution(m_engine);
    }


    float operator()(float _min, float _max) {
        return Generate(_min, _max);
    }
    int operator()(int _min, int _max) {
        return Generate(_min, _max);
    }
private:
    std::random_device m_device;
    std::mt19937       m_engine;
    std::uniform_int_distribution<int> m_intDistribution;
    std::uniform_real_distribution<float> m_floatDistribution;
    std::mutex m_mutex;
};

int main()
{
    std::cout << "Using SFML version: "
              << SFML_VERSION_MAJOR << "."
              << SFML_VERSION_MINOR << "."
              << SFML_VERSION_PATCH << std::endl;

    RandomGenerator randGen;
    for(auto i{0}; i < 20; ++i) {
        std::cout << randGen(0, 100) << " ";
    }
    std::cout << std::endl;
    for(auto i{0}; i < 20; ++i) {
        std::cout << randGen(0.f, 1.0f) << " ";
    }
    std::cout << std::endl;
}

