function out = proximal_resize_RGB(img, p, q)
    % =========================================================================
    % Redimensioneaza imaginea img astfel încât aceasta save fie de dimensiune p x q.
    % Imaginea img este colorata.
    % =========================================================================

    % TODO: Extrage canalul rosu al imaginii.
    
    % TODO: Extrage canalul verde al imaginii.
    
    % TODO: Extrage canalul albastru al imaginii.
      redChannel = img(:,:,1); % Red channel
      greenChannel = img(:,:,2); % Green channel
      blueChannel = img(:,:,3); % Blue channel
    % TODO: Aplica functia proximal pe cele 3 canale ale imaginii.
    red= proximal_resize(redChannel, p, q);
    blue = proximal_resize(blueChannel, p, q);
    green = proximal_resize(greenChannel, p, q);
    % TODO: Formeaza imaginea finala concatenând cele 3 canale de culori.
    out= cat(3, red, green, blue);

endfunction
