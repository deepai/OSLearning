#ifndef __FRAME_BUF_H
#define __FRAME_BUF_H

#define BLACK 0
#define BLUE 1
#define GREEN 2
#define CYAN 3
#define RED 4
#define MAGENTA 5
#define BROWN 6
#define LIGHT_GREY 7
#define DARK_GREY 8
#define LIGHT_BLUE 9
#define LIGHT_GREEN 10
#define LIGHT_CYAN 11
#define LIGHT_RED 12
#define LIGHT_MAGENTA 13
#define LIGHT_BROWN 14
#define WHITE 15

/**
 * This method is used to write a character in the frame buffer at the location
 * i. We pass a character which we wish to write alongwith fg and bg.
 */
void fb_write_cell(unsigned short i,char c,unsigned char fg,unsigned char bg);

#endif
