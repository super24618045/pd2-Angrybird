#ifndef CONTACTCOUNT_H
#define CONTACTCOUNT_H
#include "rectangle.h"
#include <QList>
#include<iostream>
class ContactCount:public b2ContactListener
{
public:
    void BeginContact(b2Contact *contact);
private:
    float damage;

};


#endif // CONTACTCOUNT_H
