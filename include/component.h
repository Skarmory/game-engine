#ifndef component_h
#define component_h

#include <string>

using namespace std;

class Component {
public:
	 Component(string name) : _name(name), _enabled(true) {}
	 virtual ~Component(void) {}

 	 const string name(void) const { return _name; }
	 bool enabled(void) const { return _enabled; }

protected:
	 string _name;
	 bool _enabled;
};

#endif
