#include <map>
#include <string>
#include <mutex>
#include <shared_mutex>
#include <vector>
#include <chrono>
#include <iostream>
#include <cstdlib>

class dns_entry
{
public:
    dns_entry() = default;
    dns_entry(std::string entry) : dns{entry}
    {
    }
    dns_entry(const dns_entry &) = default;
    dns_entry &operator=(const dns_entry &) = default;

private:
    std::string dns{};
};

class dns_cache
{
    std::map<std::string, dns_entry> entries;
    mutable std::shared_mutex entry_mutex;

public:
    dns_entry find_entry(const std::string &domain) const
    {
        std::shared_lock<std::shared_mutex> lock{entry_mutex};
        const std::map<std::string, dns_entry>::const_iterator itr = entries.find(domain);
        return (itr == entries.end()) ? dns_entry() : itr->second;
    }

    void update_or_add_entry(const std::string &domain, const dns_entry &dns_details)
    {
        std::lock_guard<std::shared_mutex> lock{entry_mutex};
        entries[domain] = dns_details;
    }
};

std::vector<std::pair<std::string, std::string>> dns{
    std::make_pair("127.0.0.1", "localhost"),
    std::make_pair("8.8.8.8", "google"),
    std::make_pair("1.1.1.1", "mircosoft"),
    std::make_pair("2.2.2.2", "yahoo"),
    std::make_pair("3.3.3.3", "amazon"),
    std::make_pair("4.4.4.4", "oracle"),
};

void add_entries(dns_cache &cache)
{
    srand(time(nullptr));

    static int idx{};
    while (idx < dns.size())
    {
        std::cout << "adding entry " << dns[idx].first << " -> " << dns[idx].second << " to database." << std::endl;
        cache.update_or_add_entry(dns[idx].first, dns_entry(dns[idx].second));
        std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 1000));
        ++idx;
    }
}

int main()
{
    dns_cache cache;
    std::thread t1(add_entries, std::ref(cache));

    t1.join();
}