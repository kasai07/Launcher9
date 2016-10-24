#include "draw.h"

#define SET_PIXEL(buffer, x, y, rgb)\
{\
	u32 offset = (SCREEN_HEIGHT * x + SCREEN_HEIGHT - y ) * BYTES_PER_PIXEL;\
	*((u8*)buffer + offset++) = rgb >> 16;\
	*((u8*)buffer + offset++) = rgb >> 8;\
	*((u8*)buffer + offset++) = rgb & 0xFF;;\
}

#define PATHLOGO			"/Launcher9/logo"


typedef struct
{
	uchar id_lenght;
	uchar colormap_type;
	uchar image_type;
	uchar cm_first1;
	uchar cm_first2;
	uchar cm_lenght1;
	uchar cm_lenght2;
	uchar cm_size;
	uchar x_origin1;
	uchar x_origin2;
	uchar y_origin1;
	uchar y_origin2;
	uchar width1;
	uchar width2;
	uchar height1;
	uchar height2;
	uchar pixel_depth;
	uchar image_descriptor;
	char data[288000];//400 * 240 * 3 = 288000
}tga_header_t;

tga_header_t data;




u32 loadtga(bool top_screen, bool bot_screen, char* path, int poswidth, int posheight);

u32 Readtga(void *dest, const char *path);

u32 drawtga_top(int posX, int posY);
u32 drawtga_bot(int posX, int posY);
