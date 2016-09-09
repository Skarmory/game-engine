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
			_observers[typeid(E)].push_back(new Callback<E>(std::bind(&Observer::receive, &o, std::placeholders::_1)));
		}

		template<typename E>
		void broadcast(const E& event)
		{
			for(auto callback : _observers[typeid(E)])
			{
				(*dynamic_cast<Callback<E>*>(callback))(event);
			}
		}

		template<typename E, typename ... Args>
		void broadcast(Args && ... args)
		{
			E event(forward<Args>(args) ...);
			broadcast(event);
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
			void operator()(const E& event) { callback(event); }
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
