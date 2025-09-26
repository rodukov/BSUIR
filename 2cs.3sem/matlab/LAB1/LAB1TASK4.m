[x, y] = meshgrid(-3:0.1:3, -3:0.1:3);  
% создаём сетку точек (матрицы X и Y) в диапазоне -3…3 с шагом 0.1

z1 = myfunc2_1(x, y);

mesh(x, y, z1);  
% строим трёхмерный график поверхности с помощью функции mesh

xlabel('x'); ylabel('y'); zlabel('z1');  
title('mesh: z1(x,y)');

meshc(x, y, z1);  
% строим трёхмерный график поверхности с добавленными проекциями контуров (contour)

xlabel('x'); ylabel('y'); zlabel('z1');  
title('meshc: z1(x,y)');  
