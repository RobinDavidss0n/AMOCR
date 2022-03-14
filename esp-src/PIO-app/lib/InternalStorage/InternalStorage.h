#include <Preferences.h>

#ifndef INTERNALSTORGAE_H
#define INTERNALSTORAGE_H

class InternalStorage{

private:
    Preferences m_preferences;
    int m_currentImageNumber;
    const char m_nameSpace[12] = "ImageNumber";
    
    
public:
    InternalStorage();
    ~InternalStorage();

    bool updateImageNumber();
    bool resetImageNumber();
    int getImageNumber();

};

#endif