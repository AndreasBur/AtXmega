#ifndef ITEM_item_menue_H
#define ITEM_item_menue_H

#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include "item.h"
#include "images.h"
#include "lcd.h"

#define DIST_ITEM_Y         4
#define DIST_ITEM_X         6
#define SCROLLBAR_WIDTH     7
#define SCROLLBAR_MIN_SIZE  10
#define DIST_ITEM_SCROLLBAR 5
#define DIST_IMAGE_X        3

class item_menue
{
    public:
        item_menue(int sWidth, int sHeight, font_t sFont, std::string sTitle="", color_t sBackgroundColor=COLOR_WHITE);
        ~item_menue();

		// item_menue get functions
        std::string getTitle() const { return Title; }
        int getWidth() const { return Width; }
        int getHeight() const { return Height; }
        font_t getFont() const { return Font; }
        int getSelectedItem() const { return SelectedItem; }
        color_t getSelectedItemColor() const { return SelectedItemColor; }
        color_t getSelectedItemBackgroundColor () const { return SelectedItemBackgroundColor; }
        int getChosenItem() const { return ChosenItem; }
        int getRefreshTimeout() const { return Timeout; }
		// item_menue set fuctions
		void setTitle(std::string sTitle, color_t sTitleColor=COLOR_WHITE);
		void setBorder(border_t sBorder, int sBorderWidth=1, color_t sBorderColor=COLOR_BLACK);
		void setWidth(int sWidth) { Width = sWidth; }
		void setHeight(int sHeight) { Height = sHeight; }
		void setFont(font_t sFont) { Font = sFont; }
		int setSelectedItem(int Id);
		void setSelectedItemColor(color_t sSelectedItemColor) { SelectedItemColor = sSelectedItemColor; }
		void setSelectedItemBackgroundColor(color_t sSelectedItemBackgroundColor) { SelectedItemBackgroundColor = sSelectedItemBackgroundColor; }
		int setChosenItem(int Id);
		void setItemLines() { ItemLines = true; }
        void clearItemLines() { ItemLines = false; }
        void setItemLines(bool sItemLines, color_t sItemLinesColor) { ItemLines = sItemLines; ItemLinesColor = sItemLinesColor; }
        void setItemLines(bool sItemLines) { ItemLines = sItemLines; }
        void setItemLinesColor(color_t sItemLinesColor) { ItemLinesColor = sItemLinesColor; }

		// Item methods
        int addItem(std::string sText, color_t sColor=COLOR_BLACK);
        int addItem(std::string sText, image_t sImage, int sImageWidth, int sImageHeight, color_t sColor=COLOR_BLACK);
        int swapItems(int Id1, int Id2);
        // Item methods set functions
        int setItem(int Id, item sItem);
		int setItemText(int Id, std::string sText);
		int setItemImage(int Id, image_t sImage, int sImageWidth, int sImageHeight);
		int setItemColor(int Id, color_t sColor);
		// Item methods get functions
		item getItem(int Id) const { return Items[Id]; }
        std::string getItemText(int Id) const { return Items[Id].getText(); }
        image_t getItemImage(int Id) const { return Items[Id].getImage(); }
        color_t getItemColor(int Id) const { return Items[Id].getColor(); }
		int getNumberOfItems() const { return Items.size(); }
		// Item methods
        bool ItemHasImage(int Id) const { return Items[Id].hasImage(); }

		// item_menue methods control functions
		void draw(int PosX, int PosY);
        void scroll(int Offset);
        void scrollTo(int position);
        void timeout();
    protected:

    private:
        void calcScrollbar();
        std::vector<item> Items;
        int Width;
        int Height;
        color_t BackgroundColor;
        border_t Border;
        int BorderWidth;
        color_t BorderColor;
        std::string Title;
        color_t TitleColor;
        font_t Font;
        int MaxItemsOnPage;
        int MaxTextLength;
        int MaxTextLengthWithImage;
        int SelectedItem;
        std::string SelectedItemText;
        color_t SelectedItemColor;
        color_t SelectedItemBackgroundColor;
        int TopItem;
        int ChosenItem;
        int ScrollSize;
        double ScrollStep;
        int Timeout;
        bool ItemLines;
        color_t ItemLinesColor;
        //bool item_menue_is_chosen;
};

#endif // item_menue_H

