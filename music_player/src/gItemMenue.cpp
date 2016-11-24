#include "gItemMenue.h"

gItemMenue::gItemMenue(gObject* Parent, int sPosX, int sPosY, int sWidth, int sHeight, font_t sFont, std::string sTitle, color_t sBackgroundColor)
    //: gObject(BORDER_RECT, 3, COLOR_BLUE2, BORDER_RECT, 3, COLOR_RED)
{
    setParent(Parent);
    setPosX(sPosX);
    setPosY(sPosY);
    setWidth(sWidth);
    setHeight(sHeight);
    Font = sFont;
    BackgroundColor = sBackgroundColor;
    Title = sTitle;
    TitleColor = COLOR_WHITE;
    ItemMargin = 3;
    calcPage();
    SelectedItem = 0;
    SelectedItemBackgroundColor = COLOR_YELLOW;
    TopItem = 0;
    ItemLines = false;
    ItemLinesColor = COLOR_BLACK;
    Timeout = 0;
}

gItemMenue::~gItemMenue()
{

}

void gItemMenue::setTitle(std::string sTitle, color_t sTitleColor)
{
    Title = sTitle;
    TitleColor = sTitleColor;
    calcPage();
}

void gItemMenue::setFont(font_t sFont)
{
    Font = sFont;
    calcPage();
}

void gItemMenue::setItemMargin(int sItemMargin)
{
    ItemMargin = sItemMargin;
    calcPage();
}

int gItemMenue::setSelectedItem(int Id)
{
    if(Id < (int)Items.size()) {
        SelectedItem = Id;
        return Id;
    }
    return -1;
}

int gItemMenue::setItem(int Id, gItem sItem)
{
    if(Id < (int)Items.size()) {
        Items[Id] = sItem;
        return Id;
    }
    return -1;
}

int gItemMenue::addItem(gItem Item)
{
    Items.push_back(Item);
	calcScrollbar();
    return Items.size();
}

int gItemMenue::addItem(std::string Text, color_t TextColor, oF_int EventFunction)
{
    gItem Item(this, 0, -1, getWidth(), GetFontHeight(Font));
    Item.setText(Text, Font, TextColor);
    Items.push_back(Item);
	calcScrollbar();
    return Items.size();
}

int gItemMenue::addItem(std::string Text, image_t Image, int ImageWidth, int ImageHeight, int ImageMarginRight, int ImageMarginLeft, color_t TextColor, oF_int sEventFunction)
{
    gItem Item(this, 0, -1, getWidth(), GetFontHeight(Font));
    Item.setText(Text, Font, TextColor);
    Item.setImage(Image, ImageWidth, ImageHeight, ImageMarginRight, ImageMarginLeft);
    Items.push_back(Item);
	calcScrollbar();
	return Items.size();
}

void gItemMenue::scroll(int Offset)
{
    if(Items.size() == 0) return;
    // clear selection of old item
    Items[SelectedItem].clearIsSelected();
    Items[SelectedItem].setBackgroundColor(COLOR_NONE);
    // calculate selected item
	SelectedItem += Offset;
	if(SelectedItem < 0) SelectedItem = 0;
    if(SelectedItem >= (int)Items.size()) SelectedItem = Items.size() - 1;
    // check if Item has timeout
    Timeout = Items[SelectedItem].getTimeout();
    // set selection of new item
    Items[SelectedItem].setIsSelected();
    Items[SelectedItem].setBackgroundColor(SelectedItemBackgroundColor);
	// check if item is visible
	// selected item is too far at the bottom
	if(SelectedItem - TopItem >= MaxItemsOnPage) TopItem = SelectedItem - MaxItemsOnPage + 1;
	// selected item is too far at the top
	if(TopItem - SelectedItem > 0) TopItem = SelectedItem;
}

void gItemMenue::scrollTo(int Position)
{
    if(Position >= (int)Items.size() || Position < 0) return;
	TopItem = Position;
}

void gItemMenue::timeout()
{
    Items[SelectedItem].timeout();
}

void gItemMenue::draw()
{
    int LineHeight = PageHeight / MaxItemsOnPage;
    int X = getPosXabs();
    int Y = getPosYabs();
    // draw backgroundcolor
    if(BackgroundColor != COLOR_NONE)
        LCD_DrawBox(getPosXabs(), getPosYabs(), getPosXabs()+getWidth()-1, getPosYabs()+getHeight()-1, BackgroundColor, BORDER_NONE, 0, COLOR_NONE);
    // draw title tag
    if(Title.empty() == false) {
        LCD_DrawBox(X, Y, X+getWidth()-1, Y+LineHeight-1, getBorderColor(), getBorder(), getBorderWidth(), getBorderColor());
        LCD_Text(GetCenterTextX(Title.c_str(), Font, getWidth(), X), GetCenterTextY(Font, LineHeight, Y), Title.c_str(), TitleColor, COLOR_NONE, Font);
        Y += LineHeight;
    }

    if(Items.size() == 0) return;

    // draw scrollbar
	if((int)Items.size() > MaxItemsOnPage) {
		int ScrollbarX = X + getWidth() - 7 - SCROLLBAR_WIDTH;
		int ScrollbarY;
		if(Title.empty()) ScrollbarY = Y + 5;
		else ScrollbarY = Y + 2;
		int ScrollbarH = PageHeight - 2*MARGIN_SCROLLBAR;
        LCD_DrawBox(ScrollbarX, ScrollbarY, ScrollbarX + SCROLLBAR_WIDTH, ScrollbarY + ScrollbarH, COLOR_NONE, BORDER_RECT, 2, getBorderColor());
		// scroll position
		int ScrollY = (int)((TopItem * ScrollStep) + 0.5);
        LCD_DrawBox(ScrollbarX, ScrollbarY + ScrollY, ScrollbarX + SCROLLBAR_WIDTH, ScrollbarY + ScrollY + ScrollSize, getBorderColor(), BORDER_RECT, 1, getBorderColor());

        if(getBorder() == BORDER_RECT_ROUNDED) {
            LCD_SetPoint(ScrollbarX, ScrollbarY, COLOR_WHITE);
            LCD_SetPoint(ScrollbarX, ScrollbarY + ScrollbarH, COLOR_WHITE);
            LCD_SetPoint(ScrollbarX + SCROLLBAR_WIDTH, ScrollbarY, COLOR_WHITE);
            LCD_SetPoint(ScrollbarX + SCROLLBAR_WIDTH, ScrollbarY + ScrollbarH, COLOR_WHITE);
        }
	}
    // draw items
    for(int i=0; i < MaxItemsOnPage; i++)
    {
		int ItemIndex = i + TopItem;
		if(ItemIndex >= (int)Items.size() || ItemIndex < 0) continue;
        // calculate line position
        int LineY;
        if(Title.empty() == false) LineY = ItemMargin + (i+1) * LineHeight;
		else LineY = ItemMargin + i * LineHeight;
		int ItemY = getPosYabs()+LineY+Items[ItemIndex].getHeight();
		if(ItemLines) LCD_DrawLine(getPosX(), ItemY, getPosX()+Items[ItemIndex].getWidth()-5, ItemY, ItemLinesColor);
        Items[ItemIndex].setPosY(LineY);
        Items[ItemIndex].draw();
	}
	drawBorder();
}

void gItemMenue::event(event_t Event)
{
    if(Event == EVENT_ROTATION_R) scroll(1);
    if(Event == EVENT_ROTATION_L) scroll(-1);
    if(Event == EVENT_BUTTON1) {
        if(getIsChosen() == false) setIsChosen(true);
        else Items[SelectedItem].event(Event);
    }
    if(Event == EVENT_BUTTON2) clearIsChosen();
}

void gItemMenue::calcPage()
{
    if(Title.empty() == false) PageHeight = getHeight() - (GetFontHeight(Font) + ItemMargin);
    else PageHeight = getHeight();
    MaxItemsOnPage = (int)(PageHeight / (GetFontHeight(Font) + ItemMargin));
}

void gItemMenue::calcScrollbar()
{
    // check if scrollbar is needed
    if((int)Items.size() > MaxItemsOnPage) {
        // calculate scrollbar step and size
        ScrollSize = (PageHeight-2*MARGIN_SCROLLBAR) / (Items.size() - MaxItemsOnPage);
        if(ScrollSize <= 10) ScrollSize = SCROLLBAR_MIN_SIZE;
        ScrollStep = (double)((PageHeight-2*MARGIN_SCROLLBAR) - ScrollSize) / (double)(Items.size() - MaxItemsOnPage);
        // set item width
        for(int i=0; i < (int)Items.size(); i++)
        {
            Items[i].setWidth(getWidth()-SCROLLBAR_WIDTH-2*DIST_ITEM_SCROLLBAR);
        }
    }
}
