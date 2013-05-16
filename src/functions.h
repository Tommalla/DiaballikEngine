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
	
	inline int sgn(const int x) {
		return (x == 0) ? 0 : ((x < 0) ? -1 : 1);
	}
}

#endif