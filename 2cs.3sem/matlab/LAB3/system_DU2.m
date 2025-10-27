function f = system_DU2(x, y)
f = [y(2);                          % y₁' = y₂
     y(1) + x*exp(x)/(x^2 - 1)];    % y₂' = y₁ + x·e^x/(x²-1)
end