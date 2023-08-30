//
// Created by denis on 30.08.23.
//

#ifndef UNTITLED4_WORKJSON_H
#define UNTITLED4_WORKJSON_H

#include "QHash"
#include "QList"


class WorkJson {

public:

    QHash<QString,QString> getPkgNameAndVersion(QString branch,QString arch,QString path);
    QList<QString> getAllArchsBranch(QString branch,QString path);
    void WriteToJsonFile(); //допилить, нужно придумать, что будет параметрами функции


};


#endif //UNTITLED4_WORKJSON_H
