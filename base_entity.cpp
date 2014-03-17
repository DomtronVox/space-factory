#include "base_entity.h"
#include <QTextStream>

void BaseEntity::save(QFile *file){
    QString data(QString::fromStdString(this->stringify()));
    QTextStream out(file);
    out << data << endl;
    return;
}

string BaseEntity::load(string line)
{
    int pos;
    string Eid = line.substr(0, pos = line.find(","));
    this->id = stoi(Eid);
    line.erase(0,pos + 1);
    string x = line.substr(0, pos = line.find(","));
    this->x = stoi(x);
    line.erase(0,pos + 1);
    string y = line.substr(0, pos = line.find(","));
    this->y = stoi(y);
    line.erase(0,pos + 1);
    string image = line.substr(0, pos = line.find(","));
    this->image = image;
    line.erase(0,pos + 1);
    return line;

}

