#include <cstdlib>

[[noreturn]] void forceProgramTermination() {
	std::exit(1);
}

[[deprecated("Unsafe method, please use isUsbAvailable")]]
bool isDongleAvailable() {
	bool isAvailable {};
	return isAvailable;
}

// gcc: warning: control reaches end of non-void function [-Wreturn-type]
bool isFeatureLicensed(int featureId) {
	if( !isDongleAvailable()) {
		forceProgramTermination();
	} else {
		bool isLicensed { featureId == 42 };
		return isLicensed;
	}
}

int main() {
	[[maybe_unused]] bool isLicensed { isFeatureLicensed(42)};
}
	
