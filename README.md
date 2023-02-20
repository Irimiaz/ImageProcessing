# ImageProcessing

First, I declared a string called "command" that is read from the keyboard input until the word "quit" is read which stops the program and frees the memory. To operate with bmp pictures I need 3 structs: bmp_fileheader bmp_infoheader and image which I declared at the beginning and I use throughout the program.

Available Commands: 

  * save <path> : Save/overwrite the image from edit mode in path.
  * edit <path> : Loads the image into the application's memory for editing.
  * insert <path> y x : Inserts the image (full or cropped) from path over the one in edit mode.
  * set draw_color R G B : Sets a color that will be used either to draw or to fill an area.
  * set line_width x : Sets the dimensions of the pencil with which we will draw the lines.
  * draw line y1 x1 y2 x2 : Draws a line between two pixels.
  * draw rectangle y1 x1 width height : Draws a rectangle with a certain width and height starting at a given pixel.
  * draw triangle y1 x1 y2 x2 y3 x3 : Draws a triangle between three pixels. (It consists of three "Draw lines commands").
  * fill y x : Colors the given pixel and all the adjacent pixels which are the same color.
  * quit : Frees the memory and closes the program.
