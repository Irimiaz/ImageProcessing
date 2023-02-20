# ImageProcessing

First, I declared a string called "command" that is read from the keyboard input until the word "quit" is read which stops the program and frees the memory. To operate with bmp pictures I need 3 structs: bmp_fileheader bmp_infoheader and image which I declared at the beginning and I use throughout the program.

Available Commands: 

  save <path>
  
  edit <path>
  
  insert <path> y x
  
  set draw_color R G B
  
  set line_width x
  
  draw line y1 x1 y2 x2
  
  draw rectangle y1 x1 width height
  
  draw triangle y1 x1 y2 x2 y3 x3
  
  fill y x
  
  quit
  
  
Save: Save/overwrite the image from edit mode in path.
  
Edit: Loads the image into the application's memory for editing.
  
Insert: Inserts the image (full or cropped) from path over the one in edit mode.
  
Set draw_color: Sets a color that will be used either to draw or to fill an area.
  
Set line_width: Sets the dimensions of the pencil with which we will draw the lines.
  
Draw line: Draws a line between two pixels.
  
Draw rectangle: Draws a rectangle with a certain width and height starting at a given pixel.
  
Draw triangle: Draws a triangle between three pixels. (It consists of three "Draw lines commands").
  
Fill: Colors the given pixel and all the adjacent pixels which are the same color.
  
Quit: Frees the memory and closes the program.
  
