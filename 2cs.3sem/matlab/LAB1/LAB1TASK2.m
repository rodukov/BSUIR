x = 0.1:0.01:5;     % область определения
y = myfunc1(x);

plot(x, y);
xlabel('x');
ylabel('y');
title('y = 2lg(x) - (x-2)^2');
grid on;
