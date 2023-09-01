//
// Created by denis on 31.08.23.
//

#include "MyLib.h"
#include "QHash"
#include "WorkJson.h"
#include "QJsonObject"


MyLib::MyLib(const QString branch1, const QString branch2, const QString outputfolderName) {
    this->branch_1 = branch1;
    this->branch_2 = branch2;
    this->outputFolderName = outputfolderName;
}

/**
 * @brief MyLib::compare_branches
 * Compares the values of package names in two binary branches
 */
void MyLib::compare_branches() {

    QString path_archs_branch_1 = "archs_branch_1.json";
    QString path_archs_branch_2 = "archs_branch_2.json";
    QString path_binary_branch_1 = "binary_branch_1.json";
    QString path_binary_branch_2 = "binary_branch_2.json";

    QHash<QString,QString> pkg_name_and_version_branch_1;
    QHash<QString,QString> pkg_name_and_version_branch_2;

    WorkJson workJson;

    QList<QString> archs_branch_1 = workJson.getAllArchsBranch(branch_1,path_archs_branch_1);
    QList<QString> archs_branch_2 = workJson.getAllArchsBranch(branch_2,path_archs_branch_2);
    QList<QString> unique_pkg_name_1;
    QJsonArray unique_pkg_name_json_1;
    QList<QString> unique_pkg_name_2;
    QJsonArray unique_pkg_name_json_2;

    for(auto arch : archs_branch_1)
    {
        if(archs_branch_2.contains(arch))
        {
            pkg_name_and_version_branch_1 = workJson.getPkgNameAndVersion(branch_1,arch,path_binary_branch_1);
            pkg_name_and_version_branch_2 = workJson.getPkgNameAndVersion(branch_2,arch,path_binary_branch_2);
            QList<QString> pkg_name_branch_1 = pkg_name_and_version_branch_1.keys();
            QList<QString> pkg_name_branch_2 = pkg_name_and_version_branch_2.keys();
            for(auto pkg_name : pkg_name_branch_1)
            {
                if(!pkg_name_branch_2.contains(pkg_name))
                {
                    //unique_pkg_name_1.append(pkg_name);
                    QJsonObject jsonObject;
                    jsonObject["name"] = pkg_name;
                    unique_pkg_name_json_1.append(jsonObject);


                }
            }


        }
        else{
            unique_pkg_name_1 =workJson.getPkgNameAndVersion(branch_1,arch,path_binary_branch_1).keys();
            for(auto pkg_name : unique_pkg_name_1) {
                QJsonObject jsonObject;
                jsonObject["name"] = pkg_name;
                unique_pkg_name_json_1.append(jsonObject);
            }

        }


        workJson.writeToJsonFile(arch, outputFolderName + QString("_branch_1"), unique_pkg_name_json_1,
                                 unique_pkg_name_json_1.size());

    }

    for(auto arch : archs_branch_2)
    {
        if(archs_branch_1.contains(arch))
        {
            pkg_name_and_version_branch_1 = workJson.getPkgNameAndVersion(branch_1,arch,path_binary_branch_1);
            pkg_name_and_version_branch_2 = workJson.getPkgNameAndVersion(branch_2,arch,path_binary_branch_2);
            QList<QString> pkg_name_branch_1 = pkg_name_and_version_branch_1.keys();
            QList<QString> pkg_name_branch_2 = pkg_name_and_version_branch_2.keys();
            for(auto pkg_name : pkg_name_branch_2)
            {
                if(!pkg_name_branch_1.contains(pkg_name))
                {

                    QJsonObject jsonObject;
                    jsonObject["name"] = pkg_name;
                    unique_pkg_name_json_2.append(jsonObject);


                }
            }


        }
        else{
            unique_pkg_name_2 =workJson.getPkgNameAndVersion(branch_2,arch,path_binary_branch_2).keys();
            for(auto pkg_name : unique_pkg_name_2) {
                QJsonObject jsonObject;
                jsonObject["name"] = pkg_name;
                unique_pkg_name_json_2.append(jsonObject);
            }

        }


        workJson.writeToJsonFile(arch, outputFolderName + QString("_branch_2"), unique_pkg_name_json_2,
                                 unique_pkg_name_json_2.size());

    }

    system(("rm -rf "+ path_binary_branch_1.toStdString()).data());
    system(("rm -rf "+ path_binary_branch_2.toStdString()).data());
    system(("rm -rf "+ path_archs_branch_1.toStdString()).data());
    system(("rm -rf "+ path_archs_branch_2.toStdString()).data());

    return;
}
