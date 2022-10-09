function R = proximal_rotate(I, rotation_angle)
    % =========================================================================
    % Roteste imaginea alb-negru I de dimensiune m x n cu unghiul rotation_angle,
    % aplicând Interpolare Proximala.
    % rotation_angle este exprimat în radiani.
    % =========================================================================
    [m n nr_colors] = size(I);
     I = double(I);
    % Se converteste imaginea de intrare la alb-negru, daca este cazul.
    if nr_colors > 1
        R = -1;
        return
    endif

    % Obs:
    % Atunci când se aplica o scalare, punctul (0, 0) al imaginii nu se va deplasa.
    % În Octave, pixelii imaginilor sunt indexati de la 1 la n.
    % Daca se lucreaza în indici de la 1 la n si se inmultesc x si y cu s_x respectiv s_y,
    % atunci originea imaginii se va deplasa de la (1, 1) la (sx, sy)!
    % De aceea, trebuie lucrat cu indici în intervalul [0, n - 1].

    % TODO: Calculeaza cosinus si sinus de rotation_angle.
    cosinus=cos(rotation_angle);
    sinus=sin(rotation_angle);

    % TODO: Initializeaza matricea finala.
    R=zeros(m,n);

    % TODO: Calculeaza matricea de transformare.
    T = [cosinus, - sinus; sinus, cosinus];
    % TODO: Inverseaza matricea de transformare, FOLOSIND doar functii predefinite!
    T_inv=inv(T);
    % Se parcurge fiecare pixel din imagine.
    for y = 0 : m - 1
        for x = 0 : n - 1
            % TODO: Aplica transformarea inversa asupra (x, y) si calculeaza x_p si y_p
            % din spatiul imaginii initiale.
    A = T_inv * [x; y];
    x_p = A(1, 1);
    y_p = A(2, 1);
    % TODO: Trece (xp, yp) din sistemul de coordonate [0, n - 1] în
    % sistemul de coordonate [1, n] pentru a aplica interpolarea.
    x_p=x_p+1;
    y_p=y_p+1;
    % TODO: Daca xp sau yp se afla în exteriorul imaginii,
    % se pune un pixel negru si se trece mai departe.
    if x_p < 1 || x_p > n || y_p < 1 || y_p > m
       R(y + 1, x + 1) = 0;
       continue;
    endif
    % TODO: Afla punctele ce înconjoara(xp, yp).
     x1 = floor(x_p);
     y1 = floor(y_p);
     x2 = ceil(x_p);
     y2 = ceil(y_p);
     if x1 == x2 && y1 == y2
        R(y+1, x+1) = I(y_p, x_p);
        continue;
     endif       
     if x1 == x2
        R(y+1, x+1) = (y2 - y_p) / (y2 - y1) * I(y1, x1) + (y_p - y1) / (y2 - y1) * I(y2, x1);
        continue;
     endif
     if y1 == y2
        R(y+1, x+1) = (x2 - x_p) / (x2 - x1) * I(y1, x1) + (x_p - x1) / (x2 - x1) * I(y1, x2);
        continue;
     endif
    
    % TODO: Calculeaza coeficientii de interpolare notati cu a
    % Obs: Se poate folosi o functie auxiliara în care sau se calculeze coeficientii,
    % conform formulei.
    a = coef(I, x1, y1, x2, y2);
    % TODO: Calculeaza valoarea interpolata a pixelului (x, y).
     R(y+1, x+1) = a(1) + a(3) * y_p + a(2) * x_p + a(4) * x_p * y_p;
        endfor
    endfor

    % TODO: Transforma matricea rezultata în uint8 pentru a fi o imagine valida.
    R = uint8(R);
endfunction
