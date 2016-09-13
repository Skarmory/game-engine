#ifndef component_h
#define component_h

#include <string>

using namespace std;

class Component {
public:
	 Component() : _enabled(true) {}
	 virtual ~Component(void) {}

	 bool enabled(void) const { return _enabled; }

protected:
	 bool _enabled;
};

#endif
