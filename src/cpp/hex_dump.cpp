#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <array>
#include <algorithm>

class BinaryReader{
private:
	std::ifstream  f;
	std::string    filename;
	std::streampos fileSize;

public:
    void open(std::string fname) {
		filename = fname;
        f.open(filename, std::ios::binary);

        f.seekg(0, std::ios::end);
        fileSize = f.tellg();
        f.seekg(0, std::ios::beg);

	}

	// hex dump binary file
	void hex_dump() {
		uint8_t ch;
		uint32_t count{};
		const uint32_t max{16};
		std::array<int8_t, max> row;
        uint32_t offset{};

		std::cout << "File Name: " << filename << std::endl;
		if(fileSize > 1024) {
			double fsize = fileSize / 1024.;
		    std::cout << "File Size: " << std::fixed << std::setprecision(2) << fsize << " kb" << std::endl;
		} else {
			std::cout << "File Size: " << fileSize << " bytes" << std::endl;
		}

		while(f >> ch) {
			if(!count || count % max == 0) std::cout << std::hex << std::setw(8) << std::setfill('0') << offset << ":\t";
			std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<uint32_t>(ch) << " ";
			//++count;
			row[count++ % max] = ch;
			if(count % max == 0) {
				std::cout << '\t';
				for(const auto& c : row) {
					if(isprint(c)) std::cout << c;
					else std::cout << '.';
				}
				std::fill(row.begin(), row.end(), 0);
				std::cout << std::endl;
				offset += max;
			}
		}
		std::cout << std::endl;
    }

    void close(){
        f.close();
    }
};


int main(int argc, char* argv[]) 
{

	if(argc < 2) {
		std::cerr << "./hex_dump <binary-file>\n";
		return -1;
	}
    BinaryReader b;
    b.open(argv[1]);
	b.hex_dump();
    b.close();
}

