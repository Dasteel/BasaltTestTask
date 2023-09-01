//
// Created by denis on 31.08.23.
//

#ifndef UNTITLED4_MYLIB_H
#define UNTITLED4_MYLIB_H

#include "QString"
#include "QList"


class MyLib {

    void compare();

public:
    explicit MyLib(const QString branch1,const QString branch2,const QString outputfolderName);
    void compare_branches();
    void compare_version(QString arch);

private:
    QString branch_1;
    QString branch_2;
    QString outputFolderName;
    QList<QString> archs_branch_1;
    QList<QString> archs_branch_2;





};


#endif //UNTITLED4_MYLIB_H
