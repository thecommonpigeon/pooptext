#include "poopchar.h"

PoopChar::PoopChar(QObject *parent) : QObject(parent)
{
    font = QFont("Times", 12, 50, false);  //family, size, weight, italic
}                                          //weight 50 is normal, 80 is bold

void PoopChar::setChar(QString str){
    value = str[0];
    if(str == "[space]"){
        value = ' ';
    }
    if(str == "[newline]"){
        value = '\n';
    }
    charChanged(QString(value));
}

void PoopChar::setFamily(QString fam){
    font.setFamily(fam);
    fontChanged(font.family());
    charChanged(QString(value));        //char is not actually changed, this just updates the preview
}

void PoopChar::setSize(int size){
    font.setPointSize(size);
    sizeChanged(font.pointSizeF());
    charChanged(QString(value));
}

void PoopChar::setItalic(bool italic){
    font.setItalic(italic);
    italicChanged(italic);
    charChanged(QString(value));
}

void PoopChar::setBold(bool bold){
    if(bold){
        font.setWeight(80);
    } else {
        font.setWeight(50);
    }
    boldChanged(font.weight());
    charChanged(QString(value));
}
