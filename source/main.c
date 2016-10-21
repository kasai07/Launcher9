#include "common.h"
#include "draw.h"
#include "fs.h"
#include "menu.h"
#include "screen.h"




int main()
{
    screenInit();
	ClearScreenFull(true, true);
	DebugClear();
	InitFS();

	Menu_Launcher();
	
	return 0;
}
