#include "gPanel.h"

gPanel::gPanel(int sPosX, int sPosY, int sWidth, int sHeight)
{
    setPosX(sPosX);
    setPosY(sPosY);
    setWidth(sWidth);
    setHeight(sHeight);
    SelectedObject = 0;
    setIsChosen();
    setIsSelected();
}

gPanel::~gPanel()
{

}

int gPanel::setObject(int Id, gObject *pObject)
{
    if(Id < (int)pObjects.size()) {
        pObjects[Id] = pObject;
        return Id;
    }
    return -1;
}

int gPanel::addObject(gObject *pObject)
{
    pObjects.push_back(pObject);
    return pObjects.size() - 1;
}

void gPanel::free(int Id)
{
    if(pObjects.size() == 0) return;

    if(Id < (int)pObjects.size()) {
        if(pObjects[Id] != NULL) {
            delete pObjects[Id];
            pObjects[Id] = NULL;
            pObjects.erase(pObjects.begin()+Id);
        }
    }
}

void gPanel::freeAll()
{
    if(pObjects.size() == 0) return;
    // ERGÄNZEN
}


void gPanel::scroll(int Offset)
{
    if(pObjects.size() == 0) return;
    // clear selection old object
    pObjects[SelectedObject]->clearIsSelected();
    // calculate selected item
	SelectedObject += Offset;
	if(SelectedObject < 0) SelectedObject = 0;
    if(SelectedObject >= (int)pObjects.size()) SelectedObject = pObjects.size() - 1;
    // set selection new object
    pObjects[SelectedObject]->setIsSelected();
}

void gPanel::event(event_t Event)
{
    // check if pObjects in vector
    if(pObjects.size() == 0) return;
    // check if event function exists
    if(getEventFunction() != NULL) {
        getEventFunction()(Event);
        return;
    }
    // no event function exists so use default
    if(pObjects[SelectedObject]->getIsChosen() == false) {
        if(Event == EVENT_ROTATION_R) scroll(1);
        if(Event == EVENT_ROTATION_L) scroll(-1);
        //if(Event == EVENT_BUTTON1) pObjects[SelectedObject]->setIsChosen();
        if(Event == EVENT_BUTTON1) pObjects[SelectedObject]->event(Event);
    } else {
        pObjects[SelectedObject]->event(Event);
    }
}

void gPanel::draw()
{
    if(pObjects.size() == 0) return;
    for (std::vector<gObject*>::const_iterator it = pObjects.begin(); it != pObjects.end(); it++) {
        (*it)->draw();
    }
}
