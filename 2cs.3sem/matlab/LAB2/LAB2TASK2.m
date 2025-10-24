%% Лабораторная работа №2
% Задание: Найти все точки экстремума и корни функции
% y = 5 - 2/x - x^2 + 10*sin(x), при x ∈ [-10, 10]

clc; clear; close all;

% === 1. Задаем диапазон ===
x = linspace(-10, 10, 2000);   % много точек для точного графика

yfun = @(x) 5 - 2./x - x.^2 + 10*sin(x);
yfunr = @(x) -(5 - 2./x - x.^2 + 10*sin(x));
y = yfunr(x);

% === 2. Построение графика ===
figure;
plot(x, y, 'LineWidth', 1.5);
grid on;
xlabel('x');
ylabel('y');
title('График функции y = 5 - 2/x - x^2 + 10 sin(x)');
hold on;

[x2, y2, k2] = fminsearch(yfun, 0.001)
[x1, y1, k1] = fminsearch(yfunr, -0.001)
