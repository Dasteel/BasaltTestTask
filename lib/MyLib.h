//
// Created by denis on 31.08.23.
//

#ifndef UNTITLED4_MYLIB_H
#define UNTITLED4_MYLIB_H

#include "QtCore/QHash"
#include "QtCore/QList"
#include "QtCore/QString"
#include "QtCore/QJsonArray"
#include "WorkJson.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>



class MyLib {



public:
    explicit MyLib(const QString branch1,const QString branch2,const QString outputfolderName);
    void compare_branches();
    void compare_version();
    void compare_branch_1();
    void  compare_branch_2();




private:

    QString branch_1;
    QString branch_2;
    QString outputFolderName;
    QHash<QString,QString> pkg_name_and_version_branch_1_1;
    QHash<QString,QString> pkg_name_and_version_branch_1_2;
    QHash<QString,QString> pkg_name_and_version_branch_2_1;
    QHash<QString,QString> pkg_name_and_version_branch_2_2;
    QList<QString> archs_branch_1;
    QList<QString> archs_branch_2;
    QJsonArray unique_pkg_name_json_1;
    QJsonArray unique_pkg_name_json_2;
    QString arch1;
    QString arch2;
    QString path_archs_branch_1;
    QString path_archs_branch_2;
    QString path_binary_branch_1;
    QString path_binary_branch_2;








};


#endif //UNTITLED4_MYLIB_H
