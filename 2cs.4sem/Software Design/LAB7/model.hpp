#ifndef MODEL_HPP
#define MODEL_HPP

#include "observer.hpp"
#include <cmath>   // для std::cbrt

// Модель: хранит число и умеет вычислять кубический корень
class CubeRootModel : public Observable {
public:
    CubeRootModel(double initialValue = 0.0)
        : _value(initialValue) {}

    double getValue() const {
        return _value;
    }

    double getCubeRoot() const {
        return std::cbrt(_value);   // кубический корень (работает и с отрицательными)
    }

    void setValue(double newValue) {
        _value = newValue;
        notifyUpdate();   // оповещаем все представления об изменении
    }

private:
    double _value;
};

#endif