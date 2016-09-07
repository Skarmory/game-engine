#ifndef observer_h
#define observer_h

#include <vector>
#include <map>
#include <typeindex>
#include <memory>
#include <algorithm>

using namespace std;

class Event
{
	public:
		virtual ~Event(void) {}
};

class BaseObserver
{
	public:
		virtual ~BaseObserver(void) {}
};

template<typename EventType>
class Observer : public BaseObserver
{
	public:
		virtual ~Observer() {}
		virtual void receive(const EventType& e) {} 
};

class EventManager
{
	public:
		EventManager(void)  = default;
		~EventManager(void) = default;

		template<typename EventType>
		void subscribe(BaseObserver& o)
		{
			_observers[typeid(EventType)].push_back(&o);
		}
		
		template<typename EventType>
		void unsubscribe(BaseObserver& o)
		{
			vector<BaseObserver*>* v = &_observers[typeid(EventType)];
			v->erase(remove(v->begin(), v->end(), &o), v->end());
		}

		template<typename EventType>
		void broadcast(const EventType& event)
		{
			vector<BaseObserver*>* v = &_observers[typeid(EventType)];
			for(vector<BaseObserver*>::iterator it = v->begin(); it != v->end(); it++)
			{
				static_cast<Observer<EventType>*>(*it)->receive(event);
			}
		}

		template<typename EventType, typename ... Args>
		void broadcast(Args && ... args)
		{
			EventType event(forward<Args>(args) ...);
			broadcast(&event);
		}

	private:
		map<type_index, vector<BaseObserver*>> _observers;
};

/*
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
*/

#endif
