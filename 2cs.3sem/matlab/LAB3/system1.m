function rez = system1(x)
a = x(1)*sqrt(x(2)) - 100;
b = x(1).^2+x(2).^2 - 1000;
rez = [a; b];