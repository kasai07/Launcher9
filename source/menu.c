#include "menu.h"
#include "draw.h"
#include "hid.h"
#include "fs.h"
#include "tga.h"
#include "payload.h"
#include "fatfs/ff.h"
#include "pathmenu.h"
#include "button.h"
#include "titre.h"

//int count
void DrawMenu(u32 count, u32 index, bool fullDraw)
{
    
	if (fullDraw) 
	{
        
		ClearScreenFull(true, true);
		loadtga(true,false,"Launcher9/bg/bg.tga",0,0);
		drawimage(titre, 140, 5,119, 19);
		DrawStringFColor(WHITE, TRANSPARENT, 200, SCREEN_HEIGHT - 30, true, "START:Poweroff");
		DrawStringFColor(WHITE, TRANSPARENT, 200, SCREEN_HEIGHT - 20, true, "SELECT:Reboot");
		DrawStringFColor(WHITE, TRANSPARENT, 200, SCREEN_HEIGHT - 10, true, "A : start Payload");
		if (CheckSD()) {
			DrawStringFColor(WHITE, TRANSPARENT, 5, SCREEN_HEIGHT - 30, true, "SD storage:  %lluMB", TotalStorageSpace() / (1024*1024));
			DrawStringFColor(WHITE, TRANSPARENT, 5, SCREEN_HEIGHT - 20, true, "      Used:  %lluMB", TotalStorageSpace() / (1024*1024) - RemainingStorageSpace() / (1024*1024));
			DrawStringFColor(WHITE, TRANSPARENT, 5, SCREEN_HEIGHT - 10, true, "      Free:  %lluMB", RemainingStorageSpace() / (1024*1024));
		} else {
			DrawStringFColor(RED  , TRANSPARENT, 5, SCREEN_HEIGHT - 20, true, "SD storage: unknown filesystem");
		}
	}
	
	ClearScreenFull(false, true);
	
	char pathtga[60];
	snprintf(pathtga, 60, "%s/%s%s", PATHLOGO, c[index], TGA);
	loadtga(false,true,pathtga,0,0);
	
	menupos.pos = 0;
	
	for (u32 i = 0; i < count; i++) 
	{
		drawimage(button, 80, 30 + (i*13),240, 11);
		if(i >= 12)break;
	}
		
	if(count >=13)
	if(index >= 12)menupos.pos = (index - 12);
		
	for (u32 i = 0; i < count; i++) 
	{
		if(menupos.pos != index)
		{
			if(compteur[menupos.pos] >= 32)
			{
				char name[33];
				snprintf(name, 32, "%s",c[menupos.pos]);
				DrawStringFColor(WHITE, TRANSPARENT, 200 - ((34 * 8) / 2), 30 + (i*13 + 2), true, "%s...", name);
			} else {
				DrawStringFColor(WHITE, TRANSPARENT, 200 - ((compteur[menupos.pos] * 8) / 2), 30 + (i*13 + 2), true, "%s", c[menupos.pos]);
			}
		}
		if(menupos.pos == index)
		{
			if(compteur[menupos.pos] >= 32)
			{
				char name[33];
				snprintf(name, 32, "%s",c[menupos.pos]);
				DrawStringFColor(SELECT, TRANSPARENT, 200 - ((34 * 8) / 2), 30 + (i*13 + 2), true, "%s...", name);
			} else {
				DrawStringFColor(SELECT, TRANSPARENT, 200 - ((compteur[menupos.pos] * 8) / 2), 30 + (i*13 + 2), true, "%s", c[menupos.pos]);
			}
		}
		menupos.pos++;
		if(i >= 12)break;
	}
}

u32 ProcessMenu()
{
    
	//Mise en memoire des noms des payload dans le "char c"
	//et retourne "count" le nombre de payload present
	
	u32 count = PathMenu();
    
	u32 index = 0;
    u32 result = MENU_EXIT_REBOOT;
	bool full_draw = false;
	
	int screenshot = 0;
	DrawMenu(count, index, true);
	
 // main processing loop
    while (true) 
	{
        
		u32 pad_state = InputWait();
		
		if (pad_state & BUTTON_A) {
            
			loadPayload(index);
			
		} else if (pad_state & BUTTON_DOWN) {
           
		   index = (index == count - 1) ? 0 : index + 1;
           
			
		} else if (pad_state & BUTTON_UP) {
            
			index = (index == 0) ? count - 1 : index - 1;
			
			
		} else if (pad_state & BUTTON_X) {
            
			Screenshot(NULL);
			
		}
		if (pad_state & BUTTON_START) {
           PowerOff();
        }
        if (pad_state & BUTTON_SELECT) {
           Reboot();
        }
		
		DrawMenu(count, index, full_draw);
        
    }
    
    return result;
}
