#ifndef component_h
#define component_h

#include <string>

using namespace std;

class Component {
public:
	 Component(void) : enabled(true) {}
	 virtual ~Component(void) = default;

	 bool enabled;
};

#endif
