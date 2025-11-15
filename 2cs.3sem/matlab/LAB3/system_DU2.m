function f = system_DU2(x, y)
f = [y(2);                    % y₁' = y₂
    y(1) + x*exp(x)];         % y₂' = y₁ + x·e^x
end