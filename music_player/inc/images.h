#ifndef IMAGES_H
#define IMAGES_H

#include "qdbmp.h"
#include <string.h>

#ifdef __cplusplus
	extern "C" {
#endif


/**************************************************************************************
*   D E F I N E
***************************************************************************************/
#define IMAGE_PATH                  "../../img/"
#define IMAGE_ENDING                ".bmp"
#define MAX_PATH_LENGTH             100

#define IMAGE_FILE_NAMES            "",                                 \
                                    "settings",                         \
                                    "play_button",                      \
                                    "stop_button",                      \
                                    "repeat_button",                    \
                                    "repeat_button_pushed",             \
                                    "repeat_button_selected",           \
                                    "repeat_button_pushed_selected",    \
                                    "music_icon"


/**************************************************************************************
*   T Y P E D E F
***************************************************************************************/
typedef enum {
	IMAGE_NONE,
	IMAGE_SETTINGS,
	IMAGE_PLAYMUSIC,
	IMAGE_STOP,
	IMAGE_REPEAT,
	IMAGE_REPEAT_PUSHED,
	IMAGE_REPEAT_SELECTED,
	IMAGE_REPEAT_PUSHED_SELECTED,
	IMAGE_MUSIC
} image_t;


/**************************************************************************************
*   P R O T O T Y P E S
***************************************************************************************/
BMP *init(const char *Image);
int getImageHeight(image_t Image);
int getImageWidth(image_t Image);
const char* getImagePath(image_t Image);


#ifdef __cplusplus
        }
#endif
#endif // IMAGES_H
