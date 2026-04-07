#include "model.hpp"
#include "view.hpp"
#include "controller.hpp"

int main() {
    // Создаём модель с начальным значением 0
    CubeRootModel model(0.0);

    // Создаём представление и подписываем его на модель
    ConsoleView view(&model);

    // Создаём контроллер и передаём ему модель
    Controller controller(&model);

    // Первое отображение данных
    view.update();

    // Запускаем цикл обработки ввода
    controller.run();

    return 0;
}