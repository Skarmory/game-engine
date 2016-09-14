#ifndef component_h
#define component_h

#include <string>

using namespace std;

class Component {
public:
	 Component() : enabled(true) {}
	 virtual ~Component(void) {}

	 bool enabled;
};

#endif
