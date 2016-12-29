#ifndef component_h
#define component_h

using namespace std;

class BaseComponent 
{
public:
	BaseComponent(void) : enabled(true) {}
	virtual ~BaseComponent(void) = default;
	virtual BaseComponent* clone(void) const = 0;

	bool enabled;
};

template<class DerivedComponent>
class Component : public BaseComponent
{
public:
	virtual BaseComponent* clone(void) const override
	{
		return new DerivedComponent(static_cast<const DerivedComponent&>(*this));
	}
};

#endif
