#include "item_menue.h"


item_menue::item_menue(int sWidth, int sHeight, font_t sFont, std::string sTitle, color_t sBackgroundColor)
{
    BackgroundColor = sBackgroundColor;
    Title = sTitle;
    TitleColor = COLOR_WHITE;
    Width = sWidth;
    Height = sHeight;
    Font = sFont;
    if(sTitle.empty() == false) Height -=  GetFontHeight(sFont) + DIST_ITEM_Y;
    MaxItemsOnPage = (int)(sHeight / (GetFontHeight(sFont) + DIST_ITEM_Y));
    MaxTextLength = (sWidth-DIST_ITEM_X-DIST_ITEM_SCROLLBAR) / GetFontWidth(sFont);
    MaxTextLengthWithImage = (sWidth-DIST_ITEM_X-DIST_ITEM_SCROLLBAR-DIST_IMAGE_X-GetFontHeight(sFont)) / GetFontWidth(sFont);
    SelectedItem = 0;
    SelectedItemColor = COLOR_WHITE;
    SelectedItemBackgroundColor = COLOR_BLACK;
    TopItem = 0;
    Timeout = 0;
    Border = BORDER_NORMAL;
    BorderColor = COLOR_BLACK;
    BorderWidth = 1;
    ItemLines = false;
    ItemLinesColor = COLOR_NONE;
}

item_menue::~item_menue()
{

}

void item_menue::setTitle(std::string sTitle, color_t sTitleColor)
{
    if(sTitle.empty() == false) Height -=  GetFontHeight(Font) + DIST_ITEM_Y;
    Title = sTitle;
    TitleColor = sTitleColor;
}

void item_menue::setBorder(border_t sBorder, int sBorderWidth, color_t sBorderColor)
{
    Border = sBorder;
    BorderWidth = sBorderWidth;
    BorderColor = sBorderColor;
}

int item_menue::setSelectedItem(int Id)
{
    if(Id < (int)Items.size()) {
        SelectedItem = Id;
        return Id;
    }
    return -1;
}

int item_menue::setChosenItem(int Id)
{
    if(Id < (int)Items.size()) ChosenItem = Id;
    return Id;
}

int item_menue::addItem(std::string sText, color_t sColor)
{
    Items.push_back(item(sText, sColor));
    // check if scrollbar is needed
	if((int)Items.size() > MaxItemsOnPage) calcScrollbar();
    return Items.size();
}

int item_menue::addItem(std::string sText, image_t sImage, int sImageWidth, int sImageHeight, color_t sColor)
{
    Items.push_back(item(sText, sImage, sImageWidth, sImageHeight, sColor));
    if((int)Items.size() > MaxItemsOnPage) calcScrollbar();
    return Items.size();
}

int item_menue::swapItems(int Id1, int Id2)
{
    item Tmp;
    Tmp = Items[Id1];
    Items[Id1] = Items[Id2];
    Items[Id2] = Tmp;
    return 1;
}

int item_menue::setItem(int Id, item sItem)
{
    if(Id < (int)Items.size()) {
        Items[Id] = sItem;
        return Id;
    }
    return -1;
}

int item_menue::setItemText(int Id, std::string sText)
{
    if(Id < (int)Items.size()) {
        Items[Id].setText(sText);
        return Id;
    }
    return -1;
}

int item_menue::setItemImage(int Id, image_t sImage, int sImageWidth, int sImageHeight)
{
    if(Id < (int)Items.size()) {
        Items[Id].setImage(sImage, sImageWidth, sImageHeight);
        return Id;
    }
    return -1;
}

int item_menue::setItemColor(int Id, color_t sColor)
{
    if(Id < (int)Items.size()) {
        Items[Id].setColor(sColor);
        return Id;
    }
    return -1;
}

void item_menue::draw(int PosX, int PosY)
{
    int LineHeight = Height / MaxItemsOnPage;
    std::string Buffer;
    // draw title tag
    if(Title.empty() == false) {
        LCD_DrawBox(PosX, PosY, PosX+Width, PosY+LineHeight, BorderColor, BORDER_NORMAL, BorderWidth, BorderColor);
        LCD_Text(GetCenterTextX(Title.c_str(), Font, Width, PosX), PosY+BorderWidth, Title.c_str(), TitleColor, COLOR_NONE, Font);
        PosY = PosY + LineHeight;
    }
    // draw scrollbar
	if((int)Items.size() > MaxItemsOnPage) {
		int ScrollbarX = PosX + Width - 5 - SCROLLBAR_WIDTH;
		int ScrollbarY = PosY + 3;
		int ScrollbarH = Height - 5;
        LCD_DrawBox(ScrollbarX, ScrollbarY + 1, ScrollbarX + SCROLLBAR_WIDTH, ScrollbarY + ScrollbarH - 2, COLOR_NONE, BORDER_NORMAL, 2, BorderColor);
		// scroll position
		int ScrollY = (int)((TopItem * ScrollStep) + 0.5);
        LCD_DrawBox(ScrollbarX, ScrollbarY + ScrollY + 1, ScrollbarX + SCROLLBAR_WIDTH, ScrollbarY + ScrollY + ScrollSize-3, BorderColor, BORDER_NORMAL, 1, BorderColor);
        if(Border == BORDER_ROUNDED) {
            LCD_SetPoint(ScrollbarX, ScrollbarY + 1, COLOR_WHITE);
            LCD_SetPoint(ScrollbarX, ScrollbarY + ScrollbarH - 2, COLOR_WHITE);
            LCD_SetPoint(ScrollbarX + SCROLLBAR_WIDTH, ScrollbarY + 1, COLOR_WHITE);
            LCD_SetPoint(ScrollbarX + SCROLLBAR_WIDTH, ScrollbarY + ScrollbarH - 2, COLOR_WHITE);
        }
	}
    // draw items
    for(int i=0; i < MaxItemsOnPage; i++)
    {
		int ItemIndex = i + TopItem;
		bool HasImage = ItemHasImage(ItemIndex);
		if(ItemIndex >= (int)Items.size() || ItemIndex < 0) continue;
        // calculate line height
		int LineY = PosY + DIST_ITEM_Y + i * LineHeight;
		// draw item text
		if(ItemIndex == SelectedItem) {
            // change style if selected
            if(SelectedItemText.length() == 0) {
                SelectedItemText = getItemText(SelectedItem);
                scroll(0); // do dummy scroll
            }
            // check if item has image
            if(HasImage) {
                Buffer = SelectedItemText.substr(0, MaxTextLengthWithImage);
                LCD_PutImage(PosX+DIST_ITEM_X, LineY, "pfad");
                LCD_Text(PosX+DIST_ITEM_X+GetFontHeight(Font)+DIST_IMAGE_X, LineY, Buffer.c_str(), SelectedItemColor, SelectedItemBackgroundColor, Font);
            } else {
                Buffer = SelectedItemText.substr(0, MaxTextLength);
                LCD_Text(PosX+DIST_ITEM_X, LineY, Buffer.c_str(), SelectedItemColor, SelectedItemBackgroundColor, Font);
            }
		}
		else {
            // check if item has image
            if(HasImage) {
                Buffer = SelectedItemText.substr(0, MaxTextLengthWithImage);
                LCD_PutImage(PosX+DIST_ITEM_X, LineY, "pfad");
                LCD_Text(PosX+DIST_ITEM_X+GetFontHeight(Font)+DIST_IMAGE_X, LineY, Buffer.c_str(), getItemColor(ItemIndex), COLOR_NONE, Font);
            } else {
                Buffer = getItemText(ItemIndex).substr(0, MaxTextLength);
                LCD_Text(PosX+DIST_ITEM_X, LineY, Buffer.c_str(), getItemColor(ItemIndex), COLOR_NONE, Font);
            }
        }
	}
    // draw border
    if(Border == BORDER_NORMAL) LCD_DrawBox(PosX, PosY, PosX + Width, PosY + Height, COLOR_NONE, BORDER_NORMAL, BorderWidth, BorderColor);
    if(Border == BORDER_ROUNDED) {
        LCD_DrawBox(PosX, PosY, PosX + Width, PosY + Height, COLOR_NONE, BORDER_NORMAL, BorderWidth, BorderColor);
        LCD_SetPoint(PosX, PosY + Height, COLOR_WHITE);
        LCD_SetPoint(PosX + Width, PosY + Height, COLOR_WHITE);
        if(Title.empty()) {
            LCD_SetPoint(PosX, PosY, COLOR_WHITE);
            LCD_SetPoint(PosX + Width, PosY, COLOR_WHITE);
        } else {
            LCD_SetPoint(PosX, PosY-LineHeight, COLOR_WHITE);
            LCD_SetPoint(PosX + Width, PosY-LineHeight, COLOR_WHITE);
        }
    }
}

void item_menue::scroll(int Offset)
{
    bool HasImage = getItemImage(SelectedItem);

    // calculate selected item
	SelectedItem += Offset;
	if(SelectedItem < 0) SelectedItem = 0;
    if(SelectedItem >= (int)Items.size()) SelectedItem = Items.size() - 1;
    // copy selected item text to string variable
    SelectedItemText = getItemText(SelectedItem);
    // if selected item text too long set timeout
    if((HasImage == false && (int)SelectedItemText.length() > MaxTextLength) || (HasImage == true && (int)SelectedItemText.length() > MaxTextLengthWithImage)) {
        SelectedItemText.append(" - ");
        Timeout = 1;
    } else Timeout = 0;
	// check if item is visible
	// selected item is too far at the bottom
	if(SelectedItem - TopItem >= MaxItemsOnPage) TopItem = SelectedItem - MaxItemsOnPage + 1;
	// selected item is too far at the top
	if(TopItem - SelectedItem > 0) TopItem = SelectedItem;
}

void item_menue::scrollTo(int Position)
{
    if(Position >= (int)Items.size() || Position < 0) return;
	TopItem = Position;
}

void item_menue::timeout()
{
    int Length = getItemText(SelectedItem).length();
    bool HasImage = ItemHasImage(SelectedItem);

    if((HasImage == false && Length > MaxTextLength) || (HasImage == true && Length > MaxTextLengthWithImage)) {
        // if item text is too long than rotate text
        std::rotate(SelectedItemText.begin(), SelectedItemText.begin()+1, SelectedItemText.end());
    }
}

void item_menue::calcScrollbar()
{   // resize max text length
    MaxTextLength = (Width-DIST_ITEM_X-SCROLLBAR_WIDTH-DIST_ITEM_SCROLLBAR) / GetFontWidth(Font);
    MaxTextLengthWithImage = (Width-DIST_ITEM_X-SCROLLBAR_WIDTH-DIST_ITEM_SCROLLBAR-DIST_IMAGE_X-GetFontHeight(Font)) / GetFontWidth(Font);
    // calculate scrollbar step and size
    ScrollSize = Height / (Items.size() - MaxItemsOnPage);
    if(ScrollSize <= 10) ScrollSize = SCROLLBAR_MIN_SIZE+6;
    ScrollStep = (double)(Height - 6 - ScrollSize) / (double)(Items.size() - MaxItemsOnPage);
}

