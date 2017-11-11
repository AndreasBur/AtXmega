#ifndef GITEMMENUE_H
#define GITEMMENUE_H

#include <vector>
#include "gItem.h"
#include "gAnyMenue.h"


#define SCROLLBAR_WIDTH         7
#define SCROLLBAR_MIN_SIZE      10
#define DIST_ITEM_SCROLLBAR     5
#define MARGIN_SCROLLBAR        5


class gItemMenue : public gAnyMenue
{
    public:
        gItemMenue(gObject* Parent, int sPosX, int sPosY, int sWidth, int sHeight, font_t sFont, std::string sTitle="", color_t sBackgroundColor=COLOR_WHITE);
        virtual ~gItemMenue();

        // gItemMenue methods get functions
        std::vector<gItem> getItems() const { return Items; }
        std::vector<gItem>& getrItems() { return Items; }
        color_t getBackgroundColor() const { return BackgroundColor; }
        font_t getFont() const { return Font; }
        std::string getTitle() const { return Title; }
        color_t getTitleColor() const { return TitleColor; }
        int getItemMargin() const { return ItemMargin; }
        int getSelectedItem() const { return SelectedItem; }
        //color_t getSelectedItemColor() const { return SelectedItemColor; }
        color_t getSelectedItemBackgroundColor () const { return SelectedItemBackgroundColor; }
        bool getItemLines() const { return ItemLines; }
        color_t getItemLinesColor() const { return ItemLinesColor; }
        bool getTimeout() const { return Timeout; }

        // gItemMenue methods set fuctions
        void setItems(std::vector<gItem> sItems) { Items = sItems; }
		void setTitle(std::string sTitle, color_t sTitleColor=COLOR_WHITE);
		void setBackgroundColor(color_t sBackgroundColor) { BackgroundColor = sBackgroundColor; }
		void setFont(font_t sFont);
		void setItemMargin(int sItemMargin);
		int setSelectedItem(int Id);
		//void setSelectedItemColor(color_t sSelectedItemColor) { SelectedItemColor = sSelectedItemColor; }
		void setSelectedItemBackgroundColor(color_t sSelectedItemBackgroundColor) { SelectedItemBackgroundColor = sSelectedItemBackgroundColor; }
		void setItemLines() { ItemLines = true; }
        void clearItemLines() { ItemLines = false; }
        void setItemLines(bool sItemLines, color_t sItemLinesColor) { ItemLines = sItemLines; ItemLinesColor = sItemLinesColor; }
        void setItemLines(bool sItemLines) { ItemLines = sItemLines; }
        void setItemLinesColor(color_t sItemLinesColor) { ItemLinesColor = sItemLinesColor; }

        // Item methods get functions
        gItem getItem(int Id) const { return Items[Id]; }
        gItem& getrItem(int Id) { return Items[Id]; }
        int getNumberOfItems() const { return Items.size(); }
        // Item methods set functions
        int setItem(int Id, gItem sItem);

		// Item methods
		int addItem(gItem Item);
        int addItem(std::string Text, color_t TextColor=COLOR_BLACK, oF_int EventFunction=NULL);
        int addItem(std::string Text, image_t Image, int ImageWidth, int ImageHeight, int ImageMarginRight, int ImageMarginLeft, color_t TextColor=COLOR_BLACK, oF_int EventFunction=NULL);

		// gItemMenue methods control functions
        void scroll(int Offset);
        void scrollTo(int Position);
        void timeout();
        virtual void draw();
        virtual void event(event_t Event);

    protected:

    private:
        void calcPage();
        void calcScrollbar();
        std::vector<gItem> Items;
        color_t BackgroundColor;
        font_t Font;
        std::string Title;
        color_t TitleColor;
        int ItemMargin;
        int SelectedItem;
        color_t SelectedItemBackgroundColor;
        bool ItemLines;
        color_t ItemLinesColor;
        int PageHeight;
        int MaxItemsOnPage;
        int TopItem;
        int ScrollSize;
        double ScrollStep;
        bool Timeout;
};

#endif // GITEMMENUE_H
