clc; clear;

% Решение системы ДУ
[x, y] = ode45('system_DU2', [0, 10], [5, 12]);

% Построение графика y(x)
plot(x, y(:,1))
grid on
title('y(x)')
xlabel('x')
ylabel('y')

% Проверка y(0) = 5
y(1,1)  % Должно быть 5

% Нахождение y(2)
y_2 = interp1(x, y(:,1), 2)