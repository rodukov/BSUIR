#ifndef OBSERVER_HPP
#define OBSERVER_HPP

#include <vector>

// Наблюдатель (интерфейс)
class Observer {
public:
    virtual void update() = 0;
    virtual ~Observer() = default;
};

// Наблюдаемый объект
class Observable {
public:
    void addObserver(Observer* observer) {
        _observers.push_back(observer);
    }

    void notifyUpdate() {
        for (auto* obs : _observers) {
            obs->update();
        }
    }

private:
    std::vector<Observer*> _observers;
};

#endif