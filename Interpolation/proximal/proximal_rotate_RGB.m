function out = proximal_rotate_RGB(img, rotation_angle)
    % =========================================================================
    % Aplica Interpolarea Proximala pentru a roti o imagine RGB cu un unghi dat.
    % =========================================================================
    
        
      redChannel = img(:,:,1); % Red channel
      greenChannel = img(:,:,2); % Green channel
      blueChannel = img(:,:,3); % Blue channel
     
    
    
    
    % TODO: Aplica rotatia pe fiecare canal al imaginii.
      red=proximal_rotate(redChannel,rotation_angle);
      green=proximal_rotate(greenChannel,rotation_angle);
      blue=proximal_rotate(blueChannel,rotation_angle);
    % TODO: Formeaza imaginea finala concatenând cele 3 canale de culori.
      out= cat(3, red, green, blue);
endfunction