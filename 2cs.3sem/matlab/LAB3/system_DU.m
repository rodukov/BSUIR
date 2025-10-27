function f = system_DU(x, y)
f = [y(2) + sin(x);    % y₁' = y₂ + sin x
     -y(1) + x^2];     % y₂' = -y₁ + x²
end