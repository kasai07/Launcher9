#include "tga.h"
#include "draw.h"
#include "fatfs/ff.h"

static FIL file;

u32 Readtga(void *dest, const char *path)
{
    
   

    if(f_open(&file, path, FA_READ) == FR_OK)
    {
	
		f_lseek(&file, 0);
		f_sync(&file);
		uint fsize = f_size(&file);
		
		uint bytes_read;
       
		f_read(&file, dest, fsize, &bytes_read);
        
		f_close(&file);
    }
    else return 1;

    return 0;
}



u32 loadtga(bool top_screen, bool bot_screen, char* path, int poswidth, int posheight)
{	
	int point0 = 0;
	int r, g, b, a = 1;
	int dir = 0;
						
	
	if(Readtga(&data, path) == 0)
	{
		
		int width  = data.width2 * 256 + data.width1;					
		int height = data.height2 * 256 + data.height1;
	
	
		for(int i = height; point0 < i; i--)
		{	 
			for(int j = 0; j < width; j++)	
			{
				if(data.pixel_depth == 24)//24bit
				{
					b = (data.data[dir++]);
					g = (data.data[dir++]);
					r = (data.data[dir++]);
					
					
				}	
				if(data.pixel_depth == 32)//32bit
				{
					
					b = (data.data[dir++]);
					g = (data.data[dir++]);
					r = (data.data[dir++]);
					a = (data.data[dir++]);
					
					
				}
				
				if(top_screen)//0 top screen
				{
					if(a == 0)
					{
						u32 passe = (SCREEN_HEIGHT * poswidth+j + SCREEN_HEIGHT - posheight+i ) * BYTES_PER_PIXEL;
						*((u8*)TOP_SCREEN0 + passe++);
						*((u8*)TOP_SCREEN0 + passe++);
						*((u8*)TOP_SCREEN0 + passe++);
						
						
					}else
					{
						SET_PIXEL(TOP_SCREEN0, (poswidth+j), (posheight+i), RGB(r,g,b));
					}
				}
				if(bot_screen)//0 bot scrren
				{
					
					if(a == 0)
					{
						u32 passe = (SCREEN_HEIGHT * poswidth+j + SCREEN_HEIGHT - posheight+i ) * BYTES_PER_PIXEL;
						*((u8*)BOT_SCREEN0 + passe++);
						*((u8*)BOT_SCREEN0 + passe++);
						*((u8*)BOT_SCREEN0 + passe++);
						
						
					}else
					{
						SET_PIXEL(BOT_SCREEN0, (poswidth+j), (posheight+i), RGB(r,g,b));
					}
				}
				
				
			}			
		}
		
		
	} else return 1;
	
	return 0;
}

u32 drawtga_top(int posX, int posY)
{
	u8 r, g, b, a = 1;
	int dir = 0;
	int width  = data.width2 * 256 + data.width1;					
	int height = data.height2 * 256 + data.height1;
	
	for(int i = height; 0 < i; i--)
	{	 
		
		for(int j = 0; j < width; j++)	
		{
			
			if(data.pixel_depth == 24)//24bit
				{
					b = (data.data[dir++]);
					g = (data.data[dir++]);
					r = (data.data[dir++]);
					
					
				}	
				if(data.pixel_depth == 32)//32bit
				{
					
					b = (data.data[dir++]);
					g = (data.data[dir++]);
					r = (data.data[dir++]);
					a = (data.data[dir++]);
					
					
				}
			
			if(a == 0x00)
			{
				u32 passe = (240 * posX+j + 240 - posY+i ) * 3;
				*((u8*)TOP_SCREEN0 + passe++);
				*((u8*)TOP_SCREEN0 + passe++);
				*((u8*)TOP_SCREEN0 + passe++);
				
			}else
			{
				SET_PIXEL(TOP_SCREEN0, (posX+j), (posY+i), RGB(r,g,b));
			}
		}			
	}
}

u32 drawtga_bot(int posX, int posY)
{
	u8 r, g, b, a = 1;
	int dir = 0;
	int width  = data.width2 * 256 + data.width1;					
	int height = data.height2 * 256 + data.height1;
	
	for(int i = height; 0 < i; i--)
	{	 
		
		for(int j = 0; j < width; j++)	
		{
			
			if(data.pixel_depth == 24)//24bit
				{
					b = (data.data[dir++]);
					g = (data.data[dir++]);
					r = (data.data[dir++]);
					
					
				}	
				if(data.pixel_depth == 32)//32bit
				{
					
					b = (data.data[dir++]);
					g = (data.data[dir++]);
					r = (data.data[dir++]);
					a = (data.data[dir++]);
					
					
				}
			
			if(a == 0x00)
			{
				u32 passe = (240 * posX+j + 240 - posY+i ) * 3;
				*((u8*)BOT_SCREEN0 + passe++);
				*((u8*)BOT_SCREEN0 + passe++);
				*((u8*)BOT_SCREEN0 + passe++);
				
			}else
			{
				SET_PIXEL(BOT_SCREEN0, (posX+j), (posY+i), RGB(r,g,b));
			}
		}			
	}
}

