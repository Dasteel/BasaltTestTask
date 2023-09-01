//
// Created by denis on 30.08.23.
//

#ifndef UNTITLED4_WORKJSON_H
#define UNTITLED4_WORKJSON_H

#include "QHash"
#include "QList"
#include "QJsonArray"


class WorkJson {

public:


    QHash<QString,QString> getPkgNameAndVersion(QString branch,QString arch,QString path);
    QList<QString> getAllArchsBranch(QString branch,QString path);
    void writeToJsonFile(const QString& arch, const QString& folderName, QJsonArray data_to_write, qint32 count_of_unique_pkg_name);

};


#endif //UNTITLED4_WORKJSON_H
