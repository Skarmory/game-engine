#ifndef component_h
#define component_h

#include <string>

class Component {
public:
	 Component(std::string);
	 virtual ~Component(void);

 	 const std::string name(void) const { return _name; }

protected:
	 std::string _name;
};

#endif
