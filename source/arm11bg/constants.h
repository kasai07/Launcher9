/* FILE and Folder names*/
#define ARM11COMMAND_ADDRESS 0x1FFF3000


#define ARM11_COMMANDS typedef struct { \
						    vu32 a11ControllValue; \
						    vu32 a11threadRunning; \
						    vu32 version; \
						    vu32 brightness; \
						    vu32 fbTopSelectedBuffer; \
						    vu32 fbTopLeft; \
						    vu32 fbTopLeft2; \
						    vu32 fbTopRigth; \
						    vu32 fbTopRigth2; \
						    vu32 fbBottomSelectedBuffer; \
						    vu32 fbBottom; \
						    vu32 fbBottom2; \
						    vu32 setBrightness; \
						    vu32 enableLCD; \
						    vu32 mode; \
						    vu32 changeMode; \
						} a11Commands;

#define MODE_MAIN 1
#define MODE_DRAW 2

#define ARM11_DONE 0
#define DISABLE_SCREEN 1
#define ENABLE_SCREEN 2
#define ENABLE_SCREEN_3D 3
