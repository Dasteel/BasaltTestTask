//
// Created by denis on 30.08.23.
//

#ifndef UNTITLED4_API_LOADER_H
#define UNTITLED4_API_LOADER_H

#include "QJsonDocument"


class Api_loader {
public:

    QJsonDocument get_binary_branch_load(std::string branch, std::string arch, QString path);

    QJsonDocument get_all_arch_load(std::string branch, QString path);
private:



};


#endif //UNTITLED4_API_LOADER_H
