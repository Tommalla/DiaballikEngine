#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <string>

using namespace std;

namespace engine {
	inline void printDebug(const string& str) {
		#ifndef NDEBUG
		puts(("dbg: " + str).c_str());
		#endif
	}
}

#endif