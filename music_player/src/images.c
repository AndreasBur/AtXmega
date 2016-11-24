/**************************************************************************************
*   I N C L U D E
***************************************************************************************/
#include "images.h"


/**************************************************************************************
*
*   \fn BMP *init(const char *Image)
*
*   \brief open a bitmap image file
*
*   \return BMP pointer
*
***************************************************************************************/
BMP *init(const char *Image)
{
    BMP* Bmp;

    /* Read an image file */
    Bmp = BMP_ReadFile(Image);
    if (BMP_GetError() != BMP_OK) {
       /* Print error info */
        printf("An error has occurred: %s (code %d)\n", BMP_GetErrorDescription(), BMP_GetError() );
    }

    return Bmp;
}


/**************************************************************************************
*
*   \fn int getImageHeight(const char *Image)
*
*   \brief calculate the height of a bitmap image file
*
*   \return int height
*
***************************************************************************************/
int getImageHeight(image_t Image)
{
    BMP* Bmp;
    const char* ImagePath = getImagePath(Image);

    Bmp = init(ImagePath);
    if(Bmp != NULL) return BMP_GetHeight(Bmp);
    else return -1;
}


/**************************************************************************************
*
*   \fn int getImageWidth(const char *Image)
*
*   \brief calculate the width of a bitmap image file
*
*   \return int width
*
***************************************************************************************/
int getImageWidth(image_t Image)
{
    BMP* Bmp;
    const char* ImagePath = getImagePath(Image);

    Bmp = init(ImagePath);
    if(Bmp != NULL) return BMP_GetWidth(Bmp);
    else return -1;
}


/**************************************************************************************
*
*   \fn const char* getImagePath(image_t Image)
*
*   \brief get the path of a image
*
*   \return const char* image path
*
***************************************************************************************/
const char* getImagePath(image_t Image)
{
    static char path[MAX_PATH_LENGTH];
    const char* ImageFileName[] = { IMAGE_FILE_NAMES };

    strcpy(path, IMAGE_PATH);
    strcat(path, ImageFileName[Image]);
    strcat(path, IMAGE_ENDING);

    return path;
}
