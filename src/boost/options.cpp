#include <iostream>
#include <boost/program_options.hpp>

namespace po = boost::program_options;

int main(int ac, char *av[])
{
    po::options_description desc("allowed options");
    desc.add_options()("help", "--intesity: set intesity levels")("intensity", po::value<int>(), "set intensity level");
    po::variables_map vm;
    po::store(po::parse_command_line(ac, av, desc), vm);
    po::notify(vm);

    if (vm.count("help"))
    {
        std::cout << desc << "\n";
        return 1;
    }

    if (vm.count("intensity"))
    {
        std::cout << "intensity level set to "
                  << vm["intensity"].as<int>() << "\n";
    }
    else
    {
        std::cout << "intesity was not set\n";
    }

    return 0;
}