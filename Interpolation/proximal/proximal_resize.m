function R = proximal_resize(I, p, q)
    % =========================================================================
    % Se scaleaza imaginea folosind algoritmul de Interpolare Proximala.
    % Transforma imaginea I din dimensiune m x n în dimensiune p x q.
    % =========================================================================
    [m n nr_colors] = size(I);

    % Se converteste imaginea de intrare la alb-negru, daca este cazul.
    if nr_colors > 1
        R = -1;
        return
    endif

    % TODO: Initializeaza matricea finala drept o matrice nula.
    out=zeros(p,q);
    % Obs:
    % Atunci când se aplica o scalare, punctul (0, 0) al imaginii nu se va deplasa.
    % În Octave, pixelii imaginilor sunt indexati de la 1 la n.
    % Daca se lucreaza cu indici de la 1 la n si se înmultesc x si y cu s_x respectiv s_y,
    % atunci originea imaginii se va deplasa de la (1, 1) la (sx, sy)!
    % De aceea, trebuie lucrat cu indici în intervalul [0, n - 1].

    % TODO: Calculeaza factorii de scalare.
    sx=(q-1)/(n-1);
    sy=(p-1)/(m-1);
    
    % TODO: Defineste matricea de transformare pentru redimensionare.
    T=diag([sx,sy]);
    % TODO: Inverseaza matricea de transformare, FARA a folosi functii predefinite!
    for i=1:2
      for j=1:2
        if(i==j)
        
           Tinv(i,j)=1/T(i,j);
        endif
      endfor
    endfor
   
    
    % Se parcurge fiecare pixel din imagine.
    for y = 0 : p - 1
        for x = 0 : q - 1
            % TODO: Aplica transformarea inversa asupra (x, y) si calculeaza x_p si y_p
            % din spatiul imaginii initiale.
            v=[x;y];
            v=Tinv*v;
            xp=v(1)+1;
            yp=v(2)+1;
            % TODO: Trece (xp, yp) din sistemul de coordonate [0, n - 1] in
            % sistemul de coordonate [1, n] pentru a aplica interpolarea.
            
            % TODO: Calculeaza cel mai apropiat pixel.
            xp=round(xp);
            yp=round(yp);
            % TODO: Calculeaza valoarea pixelului din imaginea finala.
            R(y+1,x+1)=I(yp,xp);
        endfor
    endfor
  R = uint8(R);
    % TODO: Transforma matricea rezultata în uint8 pentru a fi o imagine valida.
    
endfunction
