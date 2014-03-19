#include "base_entity.h"
#include <QTextStream>

void BaseEntity::save(QFile *file){
    QString data(QString::fromStdString(this->stringify()));
    QTextStream out(file);
    out << data << endl;
    return;
}

void BaseEntity::load(string &line)
{
    int pos = line.find(",");
    string Eid = line.substr(0, pos);
    BaseEntity::id = stoi(Eid);
    line.erase(0,pos + 1);
    string owner = line.substr(0, pos = line.find(","));
    this->owner = owner;
    line.erase(0,pos + 1);
    string sx = line.substr(0, pos = line.find(","));
    x = stoi(sx);
    line.erase(0,pos + 1);
    string sy = line.substr(0, pos = line.find(","));
    y = stoi(sy);
    line.erase(0,pos + 1);
    string sImage = line.substr(0, pos = line.find(","));
    image = sImage;
    line.erase(0,pos + 1);
    return;

}

