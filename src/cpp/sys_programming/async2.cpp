#include <iostream>
#include <future>

void asyncProducer(std::promise<int> &prom);
void asyncConsumer(std::future<int> &f);

int main()
{
    std::promise<int> prom;
    std::future<int> f = prom.get_future();

    std::async(asyncProducer, std::ref(prom));
    std::async(asyncConsumer, std::ref(f));
}

void asyncProducer(std::promise<int>& prom)
{
    std::cout << "sending 5 to consumer...\n";
    prom.set_value(5);
}

void asyncConsumer(std::future<int> &f)
{
    std::cout << "Got " << f.get() << " from producer...\n";
}