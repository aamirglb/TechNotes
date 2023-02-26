#include "Poco/MD5Engine.h"
#include "Poco/DigestStream.h"
#include "fmt/core.h"

#include <iostream>

int main(int argc, char *argv[])
{
    Poco::MD5Engine md5;
    Poco::DigestOutputStream ds(md5);
    ds << "abcdefghijklmnopqrstuvwxyz";
    ds.close();

    std::cout << "Computing md5 checksum..." << std::endl;
    std::cout << Poco::DigestEngine::digestToHex(md5.digest()) << std::endl;
    // std::cout << fmt::format("Digest = {}", Poco::DigestEngine::digestToHex(md5.digest())) << std::endl;
    return 0;
}