#ifndef observer_h
#define observer_h

#include <vector>
#include <map>
#include <typeindex>
#include <memory>
#include <algorithm>
#include <functional>

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
			for(auto& callback : _observers[typeid(E)])
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

#endif
