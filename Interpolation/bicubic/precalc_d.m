function [Ix, Iy, Ixy] = precalc_d(I)
    % =========================================================================
    % Prealculeaza matricile Ix, Iy si Ixy ce contin derivatele dx, dy, dxy ale 
    % imaginii I pentru fiecare pixel al acesteia.
    % =========================================================================
    
    % Obtinem dimensiunea imaginii.
    [m n nr_colors] = size(I);
    
    % TODO: Tranforma matricea I in double.
    I = double(I);

    % TODO: Calculeaza matricea cu derivate fata de x Ix.
    for i = 1 : m
      for j = 1: n
        Ix(i,j) = fx(I, j, i);
      endfor
    endfor

    % TODO: Calculeaza matricea cu derivate fata de y Iy.
    for i = 1 : m
      for j = 1 : n
        Iy(i,j) = fy(I, j, i);
      endfor
    endfor
    

    % TODO: Calculeaza matricea cu derivate fata de xy Ixy.

    for i = 1 : m
          for j = 1 : n
            Ixy(i, j) = fxy(I, j, i);
          endfor
        endfor
endfunction