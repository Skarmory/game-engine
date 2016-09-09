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

template<typename E>
class Observer : public BaseObserver
{
	public:
		virtual ~Observer() {};
		virtual void receive(const E& e) = 0;

};

/*
template<typename E>
class Broadcaster
{
	typedef function<void(const Event&)> Connection;
	public:
		void connect(Connection&& connection)
		{
			_connections.push_back(move(connection));
		}

		void broadcast(const Event& event)
		{
			for(const auto& connection : _connections)
			{
				connection(event);
			}
		}

	private:
		vector<Connection> _connections;
}
*/


class EventManager
{
	struct BaseCallback;

	public:
		EventManager(void)  = default;
		~EventManager(void) = default;

		template<typename E, typename Observer>
		void subscribe(Observer& o)
		{
			//void(Observer<E>::*receive)(const E&) = &Observer::receive;
			_observers[typeid(E)].push_back(Callback<E>(&Observer::receive));
		}
	
		/*	
		template<typename E>
		void unsubscribe(BaseObserver& o)
		{
			vector<BaseObserver*>* v = &_observers[typeid(E)];
			v->erase(remove(v->begin(), v->end(), &o), v->end());
		}
		*/

		template<typename E>
		void broadcast(const E& event)
		{
			for(vector<BaseCallback>::iterator it = _observers[typeid(E)].begin(); it != _observers[typeid(E)].end(); it++)
			{
				dynamic_cast<Callback<E>>(*it)(event);
			}


			/*
			vector<BaseObserver*>* v = &_observers[typeid(E)];
			for(vector<BaseObserver*>::iterator it = v->begin(); it != v->end(); it++)
			{
				(*it)->receive(event);
			}
			*/
		}

		template<typename E, typename ... Args>
		void broadcast(Args && ... args)
		{
			E event(forward<Args>(args) ...);
			broadcast(&event);
		}

	private:
		map<type_index, vector<BaseCallback*>> _observers;
		//map<type_index, vector<BaseObserver*>> _observers;
		
		struct BaseCallback {
			virtual ~BaseCallback() {}
		};

		template<typename E>
		struct Callback : public BaseCallback 
		{ 
			Callback(function<void(const E&)> callback) : callback(callback) {}
			void operator()(const void* event) { callback(*(static_cast<const E*>(event))); }
			function<void(const E&)> callback;
		};
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
