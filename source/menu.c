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

void DrawMenu(u32 count, u32 index, bool fullDraw);

u32 Menu_Launcher()
{
    
	
	u32 count = PathMenu();
    
	u32 index = 0;
	bool full_draw = false;
	
	DrawMenu(count, index, true);
	u8 boot = 1;
    while (true) 
	{
        
		if (boot == 1)
		{
			if(WaitBootInput(3) == 1)
			{
				loadPayload(777);
			
			} else {	
				boot = 0;
			}
		}
		u32 pad_state = InputWait();
		
		if (pad_state & BUTTON_A) {
            
			loadPayload(index);
			
		} else if (pad_state & BUTTON_DOWN) {
           
		   index = (index == count - 1) ? 0 : index + 1;
           
			
		} else if (pad_state & BUTTON_UP) {
            
			index = (index == 0) ? count - 1 : index - 1;
			
			
		} else if (pad_state & BUTTON_LEFT) {
           
		    index = (index <= 0) ? count - 1 : index - 1;
           
			
		} else if (pad_state & BUTTON_RIGHT) {
            
			index = ((index + 1) % count);
			
		} else if (pad_state & BUTTON_X) {
            
			Screenshot(NULL);
			
		} else if (pad_state & BUTTON_POWER) {
		   
		   PowerOff();
			
		} else if (pad_state & BUTTON_HOME) {
		   
		   Reboot();  
			
		} else {
			full_draw = false;
		}
		
		DrawMenu(count, index, full_draw);
        
    }
    
}

void DrawMenu(u32 count, u32 index, bool fullDraw)
{
    
	if (fullDraw) 
	{
        
		ClearScreenFull(true, true);
		loadtga(true,false,"Launcher9/bg/bg.tga",0,0);
		
		drawimage(titre, 140, 5,119, 19);
		
		DrawStringFColor(WHITE, TRANSPARENT, 10, 230, true, "A: Boot Payload");
		DrawStringFColor(WHITE, TRANSPARENT, 150, 230, true, "POWER: Power off");
		DrawStringFColor(WHITE, TRANSPARENT, 290, 230, true, "HOME: Reboot");
	}
	
	
	char pathtga[60];
	snprintf(pathtga, 60, "/Launcher9/logo/%s.tga",c[index]);
	if(loadtga(false,true,pathtga,0,0) != 0)
	{
		ClearScreenFull(false, true);
		DrawStringFColor(WHITE, TRANSPARENT, 160 - ((9 * 8) / 2), 120, false, "No Logo !");
	}
	//--------------
	if(Readtga(&data, "/Launcher9/bg/barre.tga") == 0)
	{
		int width  = data.width2 * 256 + data.width1;
		for (u32 i = 0; i < count; i++) 
		{
			drawtga_top(200 - (width / 2), 30 + (i*13));
			if(i >= 12)break;
		}
		
	}else{
		
		for (u32 i = 0; i < count; i++) 
		{
			drawimage(button, 80, 30 + (i*13),240, 11);
			if(i >= 12)break;
		}
	}
	//---------------
	
	
	if(index == 0)menupos.pos2 = 0;	
	if(count > 12)
	{
		if((menupos.pos2 + 12) < index)menupos.pos2++;
		if(menupos.pos2 > index)menupos.pos2--;
		if(index == count - 1)menupos.pos2 = count - 13;
	}
	menupos.pos = menupos.pos2;
	
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
