#include <iostream>
#include <atomic>
#include <condition_variable>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>
#include <functional>

template <typename Input, typename Output>
class WorkQueue final
{
public:
    using ProcessFunction = std::function<Output(const Input &)>;

    WorkQueue(ProcessFunction func)
        : m_Process(std::move(func))
    {
    }

    ~WorkQueue()
    {
        Stop();
    }

    void Start()
    {
        Stop();
        m_Done = false;

        m_Thread = std::thread(
            [this]()
            {
                std::unique_lock<std::mutex> lock(m_Mutex);
                std::cout << "Starting the thread... " << std::this_thread::get_id() << std::endl;
                while (!m_Done)
                {
                    m_ImageReadyOrDone.wait(lock);
                    std::cout << "worker thread notified." << std::endl;
                    while (!m_Done && !m_InputQueue.empty())
                    {
                        const Input input = std::move(m_InputQueue.front());
                        m_InputQueue.pop();
                        lock.unlock();
                        Output output = m_Process(input);

                        lock.lock();
                        m_OutputQueue.emplace(output);
                    }
                }
            });
    }

    void Stop()
    {
        if (m_Thread.joinable())
        {
            std::unique_lock<std::mutex> lock(m_Mutex);
            m_Done = true;
            m_ImageReadyOrDone.notify_one();

            lock.unlock();
            m_Thread.join();
            lock.lock();

            while (!m_InputQueue.empty())
            {
                std::cout << "Enable to process input " << m_InputQueue.front() << std::endl;
                m_InputQueue.pop();
            }

            while (!m_OutputQueue.empty())
            {
                std::cout << "Enable to return output " << m_OutputQueue.front() << std::endl;
                m_OutputQueue.pop();
            }
        }
    }

    void Queue(Input &&input)
    {
        std::lock_guard<std::mutex> lock(m_Mutex);
        std::cout << "queuing " << input << " for processing. " << std::endl;
        m_InputQueue.emplace(std::forward<Input>(input));
        m_ImageReadyOrDone.notify_one();
    }

    void Queue(const Input &input)
    {
        std::lock_guard<std::mutex> lock(m_Mutex);
        std::cout << "queuing " << input << " for processing. " << std::endl;
        m_InputQueue.emplace(input);
        m_ImageReadyOrDone.notify_one();
    }

    std::vector<Output> GetResults()
    {
        std::lock_guard<std::mutex> lock(m_Mutex);
        std::vector<Output> output;
        while (!m_OutputQueue.empty())
        {
            std::cout << "placing " << m_OutputQueue.front() << " in output." << std::endl;
            output.emplace_back(std::move(m_OutputQueue.front()));
            m_OutputQueue.pop();
        }
        return output;
    }

private:
    ProcessFunction m_Process;

    std::thread m_Thread;
    std::mutex m_Mutex;
    std::condition_variable m_ImageReadyOrDone;
    std::atomic<bool> m_Done{false};

    std::queue<Input> m_InputQueue;
    std::queue<Output> m_OutputQueue;
};

int process_function(const int &x)
{
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(50ms);
    return x * x;
}

int main()
{
    using namespace std::chrono_literals;
    WorkQueue<int, int> wq(process_function);
    wq.Start();
    for (int i = 0; i < 10; ++i)
    {
        wq.Queue(i);
        if (i % 2 == 0)
            std::this_thread::sleep_for(100ms);
    }

    // std::this_thread::sleep_for(10s);

    auto results = wq.GetResults();
    wq.Stop();
    std::cout << "size of results: " << results.size() << std::endl;
    for (const auto &e : results)
    {
        std::cout << e << ' ';
    }
    std::cout << std::endl;

    wq.Start();
    for (int i = 10; i < 20; ++i)
    {
        wq.Queue(i);
        if (i % 2 == 0)
            std::this_thread::sleep_for(150ms);
    }
    results.clear();

    results = wq.GetResults();
    std::cout << "size of results: " << results.size() << std::endl;
    for (const auto &e : results)
    {
        std::cout << e << ' ';
    }
    std::cout << std::endl;
}