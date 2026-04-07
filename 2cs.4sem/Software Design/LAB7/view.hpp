#ifndef VIEW_HPP
#define VIEW_HPP

#include "observer.hpp"
#include "model.hpp"
#include <cstdio>   // для printf
#include <cstdlib>  // для system

// Консольное представление – наблюдатель модели
class ConsoleView : public Observer {
public:
    ConsoleView(CubeRootModel* model)
        : _model(model)
    {
        _model->addObserver(this);
    }

    virtual void update() override {
        system("clear");   // очистка экрана (для Windows). Для Linux/macOS: system("clear");
        printf("Current number: %.6f\n", _model->getValue());
        printf("Cube root:      %.6f\n", _model->getCubeRoot());
        printf("\nEnter a real number (or 'q' to quit): ");
    }

private:
    CubeRootModel* _model;
};

#endif