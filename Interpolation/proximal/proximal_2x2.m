function out = proximal_2x2(f, STEP = 0.1)
    % ===================================================================================
    % Aplica Interpolare Proximala pe imaginea 2 x 2 f cu puncte intermediare echidistante.
    % f are valori cunoscute în punctele (1, 1), (1, 2), (2, 1) ?i (2, 2).
    % Parametrii:
    % - f = imaginea ce se va interpola;
    % - STEP = distan?a dintre dou? puncte succesive.
    % ===================================================================================
    
    % TODO: Defineste coordonatele x si y ale punctelor intermediare.

    % Se afl? num?rul de puncte.

    % TODO: Cele 4 puncte încadratoare vor fi aceleasi pentru toate punctele din interior.
    
    x_int=1:STEP:2;
    n = length(x_int);

  % TODO: Initializeaza rezultatul cu o matrice nula n x n.
    out=zeros(n,n);
    % Se parcurge fiecare pixel din imaginea finala.
    for i = 1 : n
        for j = 1 : n
            x = round(x_int(i));
            y = round(x_int(j));
            out(i,j)=f(x, y);
        end
    end 
endfunction