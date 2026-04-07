#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include "model.hpp"
#include <iostream>
#include <string>
#include <cstdlib>

class Controller {
public:
    Controller(CubeRootModel* model)
        : _model(model)
    {}

    void run() {
        std::string input;
        while (true) {
            // Приглашение выводится View, но чтение делает контроллер
            std::getline(std::cin, input);
            if (input == "q" || input == "Q") {
                break;
            }
            double value;
            try {
                value = std::stod(input);
                _model->setValue(value);
            } catch (...) {
                // Если ввод некорректен, показываем сообщение
                system("cls");
                printf("Invalid input! Please enter a number.\n");
                printf("\nEnter a real number (or 'q' to quit): ");
                // Обновление не вызываем, просто ждём новый ввод
            }
        }
    }

private:
    CubeRootModel* _model;
};

#endif