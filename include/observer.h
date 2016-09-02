#ifndef observer_h
#define observer_h

#include <vector>
#include <memory>
#include <algorithm>

using namespace std;

enum Event
{
	ENTITY_CREATED = 0,
	ENTITY_COLLISION = 1
};

class Observer
{
	public:
		virtual ~Observer() {}
		virtual void on_notify(const shared_ptr<Entity>&, Event) = 0;
};


class Observable
{
	public:
		void add_observer(const shared_ptr<Observer>& observer)
		{
			_observers.push_back(observer);
		}

		void remove_observer(const shared_ptr<Observer>& observer)
		{
			remove_if(_observers.begin(), _observers.end(),  [&](shared_ptr<Observer>& sp)->bool { return &(*sp) == &(*observer); });
		}

	protected:
		void notify(const shared_ptr<Entity>& entity, Event event)
		{
			for(vector<shared_ptr<Observer>>::iterator it = _observers.begin(); it != _observers.end(); it++)
			{
				(*it)->on_notify(entity, event);
			}
		}

	private:
		vector<shared_ptr<Observer>> _observers;
};

#endif
