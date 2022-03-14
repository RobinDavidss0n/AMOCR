#include "InternalStorage.h"

InternalStorage::InternalStorage(){
    m_preferences.begin(m_nameSpace, false);
    m_currentImageNumber = m_preferences.getInt(m_nameSpace, 0);
    
}

InternalStorage::~InternalStorage(){
    
}

bool InternalStorage::updateImageNumber(){
    if(!m_preferences.putInt(m_nameSpace, getImageNumber() + 1)){
        return true;
    }else{
        return false;
    }
}

bool InternalStorage::resetImageNumber(){
    return m_preferences.clear();
}

int InternalStorage::getImageNumber(){
    return m_currentImageNumber;
}