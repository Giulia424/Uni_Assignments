function out = proximal_2x2_RGB(img, STEP = 0.1)
    % ==============================================================================================
    % Aplica Interpolare Proximala pe imaginea 2 x 2 definita img cu puncte intermediare echidistante.
    % img este o imagine colorata RGB -Red, Green, Blue.
    % =============================================================================================

    
         
      redChannel = img(:,:,1); % Red channel
      greenChannel = img(:,:,2); % Green channel
      blueChannel = img(:,:,3); % Blue channel
      red=proximal_2x2(redChannel,STEP);
      green=proximal_2x2(greenChannel,STEP);
      blue=proximal_2x2(blueChannel,STEP);
      out= cat(3, red, green, blue);
    
    % TODO: Aplic? functia proximal pe cele 3 canale ale imaginii.
    
    % TODO: Formeaza imaginea finala concatenând cele 3 canale de culori.
    
endfunction
