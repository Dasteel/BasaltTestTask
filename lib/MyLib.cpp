//
// Created by denis on 31.08.23.
//

#include <sstream>
#include "MyLib.h"
#include "QtCore/QHash"
#include "QtCore/QRegExp"
#include "QtCore/QJsonObject"
#include "thread"
#include <rpm/rpmvercmp.h>
#include "QtCore/QtCoreVersion"








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


    path_archs_branch_1 = "archs_branch_1.json";
    path_archs_branch_2 = "archs_branch_2.json";
    path_binary_branch_1 = "binary_branch_1.json";
    path_binary_branch_2 = "binary_branch_2.json";



    WorkJson workJson;

    archs_branch_1 = workJson.getAllArchsBranch(branch_1,path_archs_branch_1);
    archs_branch_2 = workJson.getAllArchsBranch(branch_2,path_archs_branch_2);

    std::thread thread1(&MyLib::compare_branch_1,this);
    std::thread thread2(&MyLib::compare_branch_2, this);

    thread1.join();
    thread2.join();


    system(("rm -rf "+ (path_binary_branch_1+ QString("_1")).toStdString()).data());
    system(("rm -rf "+ (path_binary_branch_2+ QString("_1")).toStdString()).data());
    system(("rm -rf "+ (path_binary_branch_1+ QString("_2")).toStdString()).data());
    system(("rm -rf "+ (path_binary_branch_2+ QString("_2")).toStdString()).data());
    system(("rm -rf "+ (path_archs_branch_1).toStdString()).data());
    system(("rm -rf "+ (path_archs_branch_2).toStdString()).data());


}

/**
 * @brief MyLib::compare_version
 * Compares package version values in two binary branches
 */
void MyLib::compare_version() {
    path_archs_branch_1 = "archs_branch_1.json";
    path_archs_branch_2 = "archs_branch_2.json";
    path_binary_branch_1 = "binary_branch_1.json";
    path_binary_branch_2 = "binary_branch_2.json";

    WorkJson workJson;

    QHash<QString, QString> pkg_name_and_version_branch_1;
    QHash<QString, QString> pkg_name_and_version_branch_2;
    QHash<QString,QString> pkg_name_and_release_branch_1;
    QHash<QString,QString> pkg_name_and_release_branch_2;

    archs_branch_1 = workJson.getAllArchsBranch(branch_1, path_archs_branch_1);
    archs_branch_2 = workJson.getAllArchsBranch(branch_2, path_archs_branch_2);
    QJsonArray result_pkg_name_and_version;
    QList<QString> unique_pkg_name_2;





    for (const auto& arch: archs_branch_1) {
        if (archs_branch_2.contains(arch)) {

            pkg_name_and_version_branch_1 = workJson.getPkgNameAndVersion(branch_1, arch, path_binary_branch_1);
            pkg_name_and_version_branch_2 = workJson.getPkgNameAndVersion(branch_2, arch, path_binary_branch_2);
            pkg_name_and_release_branch_1 = workJson.get_pkg_name_and_release(branch_1, arch, path_binary_branch_1);
            pkg_name_and_release_branch_2 = workJson.get_pkg_name_and_release(branch_2, arch, path_binary_branch_2);
            QList<QString> pkg_name_branch_1 = pkg_name_and_version_branch_1.keys();
            QList<QString> pkg_name_branch_2 = pkg_name_and_version_branch_2.keys();

            int count =0;

            for (const auto& pkg_name: pkg_name_branch_1) {
                if (pkg_name_branch_2.contains(pkg_name)) {

                    QJsonObject jsonObject;



                    auto pkg_version_1 = pkg_name_and_version_branch_1[pkg_name];
                    auto pkg_version_2 = pkg_name_and_version_branch_2[pkg_name];
                    auto pkg_release_1 = pkg_name_and_release_branch_1[pkg_name];
                    auto pkg_release_2 = pkg_name_and_release_branch_2[pkg_name];


                    bool flag = false;

                    QString version_release_1 = pkg_version_1 + "-"+ pkg_release_1;
                    QString version_release_2 = pkg_version_2 + "-"+ pkg_release_2;

                    const char* version_release_1_Char = version_release_1.toStdString().c_str();
                    const char* version_release_2_Char = version_release_2.toStdString().c_str();

                    //int result = rpmvercmp(version_release_1_Char,version_release_2_Char);
                    int result = rpmvercmp(version_release_1_Char,version_release_2_Char);

                    //int result = 1;
                    if(result ==1)
                        flag = true;
                    else
                        flag =false;

                    if((!pkg_version_1.isEmpty() && !pkg_version_2.isEmpty()) && flag)
                    {
                        jsonObject["name"] = pkg_name;
                        jsonObject["version"] = pkg_version_1;
                        jsonObject["release"] = pkg_release_1;
                        result_pkg_name_and_version.append(jsonObject);
                        count++;
                    }

                }
            }


            workJson.writeToJsonFile(arch, outputFolderName + QString("/comp_version"), result_pkg_name_and_version,
                                     count);
            result_pkg_name_and_version = QJsonArray();
        }


    }

    system(("rm -rf "+ path_binary_branch_1.toStdString()).data());
    system(("rm -rf "+ path_binary_branch_2.toStdString()).data());
    system(("rm -rf "+ path_archs_branch_1.toStdString()).data());
    system(("rm -rf "+ path_archs_branch_2.toStdString()).data());

}

/**
 * @brief MyLib::compare_branches
 * Compares the values of package names in the first binary branch with the second
 */
void MyLib::compare_branch_1() {
    WorkJson workJson;
    QList<QString> unique_pkg_name_1;
    for(const auto& arch : archs_branch_1)
    {
        if(archs_branch_2.contains(arch))
        {
            pkg_name_and_version_branch_1_1 = workJson.getPkgNameAndVersion(branch_1,arch,path_binary_branch_1+QString("_1"));
            pkg_name_and_version_branch_2_1 = workJson.getPkgNameAndVersion(branch_2,arch,path_binary_branch_2+QString("_1"));
            QList<QString> pkg_name_branch_1 = pkg_name_and_version_branch_1_1.keys();
            QList<QString> pkg_name_branch_2 = pkg_name_and_version_branch_2_1.keys();
            for(const auto& pkg_name : pkg_name_branch_1)
            {
                if(!pkg_name_branch_2.contains(pkg_name))
                {
                    QJsonObject jsonObject;
                    jsonObject["name"] = pkg_name;
                    unique_pkg_name_json_1.append(jsonObject);


                }
            }


        }
        else{
            unique_pkg_name_1 =workJson.getPkgNameAndVersion(branch_1,arch,path_binary_branch_1).keys();
            for(const auto& pkg_name : unique_pkg_name_1) {
                QJsonObject jsonObject;
                jsonObject["name"] = pkg_name;
                unique_pkg_name_json_1.append(jsonObject);
            }

        }


        workJson.writeToJsonFile(arch, outputFolderName + QString("/branch_1"), unique_pkg_name_json_1,
                                 unique_pkg_name_json_1.size());
        unique_pkg_name_json_1 = QJsonArray();

    }

}

/**
 * @brief MyLib::compare_branches
 * Compares the values of package names in the second binary branch with the first
 */
void  MyLib::compare_branch_2() {
    WorkJson workJson;
    QList<QString> unique_pkg_name_2;

    for(const auto& arch : archs_branch_2)
    {
        if(archs_branch_1.contains(arch))
        {
            pkg_name_and_version_branch_1_2 = workJson.getPkgNameAndVersion(branch_1,arch,path_binary_branch_1+QString("_2"));
            pkg_name_and_version_branch_2_2 = workJson.getPkgNameAndVersion(branch_2,arch,path_binary_branch_2+QString("_2"));
            QList<QString> pkg_name_branch_1 = pkg_name_and_version_branch_1_2.keys();
            QList<QString> pkg_name_branch_2 = pkg_name_and_version_branch_2_2.keys();
            for(const auto& pkg_name : pkg_name_branch_2)
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
            for(const auto& pkg_name : unique_pkg_name_2) {
                QJsonObject jsonObject;
                jsonObject["name"] = pkg_name;
                unique_pkg_name_json_2.append(jsonObject);
            }

        }


        workJson.writeToJsonFile(arch, outputFolderName+QString("/branch_2"), unique_pkg_name_json_2,
                                 unique_pkg_name_json_2.size());
        unique_pkg_name_json_2 = QJsonArray();

    }

}





