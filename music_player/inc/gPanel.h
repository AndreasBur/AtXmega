#ifndef GPANEL_H
#define GPANEL_H

#include <vector>
#include "event.h"
#include "gObject.h"


class gPanel : public gObject
{
    public:
        gPanel(int sPosX=0, int sPosY=0, int sWidth=GLCD_WIDTH, int sHeight=GLCD_HEIGHT);
        ~gPanel();

        // gPanel methods get functions
        std::vector<gObject*> getObjects() { return pObjects; }
        int getSelectedObject() const { return SelectedObject; }
        // gPanel methods set functions
        void setpObjects(std::vector<gObject*> spObjects) { pObjects = spObjects; }
        void setSelectedObject(int Id) { SelectedObject = Id; pObjects[Id]->setIsSelected(); }

        // gObject methods get functions
        gObject* getpObject(int Id) { return pObjects.at(Id); }
        int getNumberOfpObjects() const { return pObjects.size(); }
        // gObject methods set functions
        int setObject(int Id, gObject* pObject);

        // gPanel methods control functions
        int addObject(gObject* pObject);
        void free(int Id);
        void freeAll();
        void scroll(int Offset);
        void scrollTo(int Position);
        virtual void draw();
        virtual void event(event_t event);

    protected:

    private:
        std::vector<gObject*> pObjects;
        int SelectedObject;
};

#endif // GPANEL_H
