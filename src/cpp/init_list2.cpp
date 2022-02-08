#include <fmt/format.h>
#include <vector>
#include <initializer_list>

using namespace std;

class EvenSequence {
public:
	EvenSequence(initializer_list<double> args) {
		if(args.size() % 2 != 0) {
			throw invalid_argument{ "initializer_list should contain even number of elements." };
		}
		m_sequence.reserve(args.size());
		for(const auto& v : args) m_sequence.push_back(v);
	}

	void dump() const {
		for(const auto& v : m_sequence) 
			fmt::print("{}, ", v);
		fmt::print("\n");
	}

private:
	vector<double> m_sequence;
};
	
int main() {
	EvenSequence seq1 { 1., 2., 3., 4., 5., 6. };
	seq1.dump();

	try {
		EvenSequence seq2 { 7., 8., 9. };
	} catch(const invalid_argument& e) {
		fmt::print("{}\n", e.what());
	}
}

