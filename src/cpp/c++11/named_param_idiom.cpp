#include <iostream>
#include <fstream>
#include <string>

class File;

class OpenFile {
public:
    OpenFile(const std::string& filename);
    OpenFile& readonly();
    OpenFile& readwrite();
    OpenFile& createIfNotExist();
    OpenFile& blockSize(unsigned nbytes);

private:
    friend class File;
    std::string filename_;
    bool readonly_;
    bool createIfNotExist_;
    unsigned blockSize_;
};

inline OpenFile::OpenFile(const std::string& filename)
    : filename_ {filename}
    , readonly_ {false}
    , createIfNotExist_ {false}
    , blockSize_ {4096u}
{}

inline OpenFile& OpenFile::readonly() {
    readonly_ = true;
    return *this;
}

inline OpenFile& OpenFile::readwrite() {
    readonly_ = false;
    return *this;
}

inline OpenFile& OpenFile::createIfNotExist() {
    createIfNotExist_ = true;
    return *this;
}
inline OpenFile& OpenFile::blockSize(unsigned nbytes) {
    blockSize_ = nbytes;
    return *this;
}

class File {
public:
    File(const OpenFile& params);
};

File::File(const OpenFile& params) {
    std::cout << params.filename_ << " : " << params.readonly_ << " "
              << params.createIfNotExist_ << " "
              << params.createIfNotExist_ << std::endl;
}

int main() {
    File f = OpenFile("foo.txt")
                .readwrite()
                .createIfNotExist()
                .blockSize(1024u);
}