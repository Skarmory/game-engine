#ifndef entity_h
#define entity_h

#include <stdlib.h>
#include <memory>
#include <map>
#include <vector>
#include <string>
#include <assert.h>
#include <typeindex>
#include "component.h"

using namespace std;

class Entity {
public:
	Entity(int _id);
	~Entity(void);

	// Add component to the entity
	void add_component(const shared_ptr<Component> c)
	{
		_components[typeid(*c)].push_back(c);
	}

	// Remove component from entity
	template<class T>
	void remove_component(void)
	{
		_components.erase(typeid(T));
	}

	// Return pointer to component
	template<class T>
	shared_ptr<T> get_component(void)
	{
		if(has_component<T>())
			return static_pointer_cast<T>(_components.at(typeid(T)).at(0));
		
		return nullptr;
	}

	// Return const pointer to const component
	template<class T>
	const shared_ptr<const T> get_component(void) const
	{
		if(has_component<T>())
			return static_pointer_cast<const T>(_components.at(typeid(T)).at(0));

		return nullptr;
	}
	
	// Return iterator to list of componetns of type T
	template<class T>
	pair<typename vector<T>::iterator, typename vector<T>::iterator>
	get_components(void) 
	{
		return make_pair(
			_components[typeid(T)].begin(),
			_components[typeid(T)].end()
		);
	}
	
	// Return const iterator to the list of componetns of type T
	template<class T>
	pair<typename vector<T>::const_iterator, typename vector<T>::const_iterator>
	get_components(void) 
    const
	{
		return make_pair(
			_components.at(typeid(T)).cbegin(),
			_components.at(typeid(T)).cend()
		);
	}
	
	// Check to see whether the entity has component T
	template<class T>
	bool has_component(void)
	const
	{
		if(_components.find(typeid(T)) != _components.end() && _components.at(typeid(T)).size() > 0)
			return true;
		return false;
	}

private:

	int _id;
	map<type_index, vector<shared_ptr<Component>>> _components;
};

#endif
