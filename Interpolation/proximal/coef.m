function a = coef(f, x1, y1, x2, y2)
v1 = [1 x1 y1 x1*y1];
v2 = [1 x1 y2 x1*y2];
v3 = [1 x2 y1 x2*y1];
v4 = [1 x2 y2 x2*y2];
A = [v1; v2; v3; v4];
b = [f(y1, x1); f(y2, x1); f(y1, x2); f(y2, x2)];
a=A\b;
endfunction 