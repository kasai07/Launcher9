#include "common.h"
#include "draw.h"
#include "fs.h"
#include "menu.h"
#include "payload.h"





int main()
{
    
	ClearScreenFull(true, true);
	DebugClear();
	InitFS();
	RemainingStorageSpace();
	
	u32 menu_exit = ProcessMenu();
    
    DeinitFS();
    (menu_exit == MENU_EXIT_REBOOT) ? Reboot() : PowerOff();
    return 0;
}
