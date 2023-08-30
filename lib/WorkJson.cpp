//
// Created by denis on 30.08.23.
//

#include "WorkJson.h"
#include "Api_loader.h"
#include "QJsonArray"

#include "QJsonDocument"


/**
 * @brief WorkJson::getPkgNameAndVersion
 * Extracts package names and version data from a json file
 * @param branch
 * @param arch
 * @param path
 * @return a QHash containing the package name (key) and version (value).
 */

QHash<QString,QString> WorkJson::getPkgNameAndVersion(QString branch,QString arch,QString path)
{
    QHash<QString,QString> pkg_name_and_version;
    QJsonDocument document;
    Api_loader apiLoader;

    document = apiLoader.get_binary_branch_load(branch.toStdString(),arch.toStdString(),path.toStdString());

    auto packages_json_array =document[QString("packages")].toArray();
    for(auto it = packages_json_array.cbegin(); it!=packages_json_array.cend(); ++it)
    {
        auto pkg_name = QJsonValue(*it)["name"].toString();
        auto pkg_version = QJsonValue(*it)["version"].toString();
        pkg_name_and_version[pkg_name] = pkg_version;
    }

    return pkg_name_and_version;
}

/**
 * @brief WorkJson::getAllArchsBranch
 * Extracts data about branch architectures from a json file
 * @param branch
 * @param arch
 * @param path
 * @return a QList containing the architectures name .
 */
QList<QString> WorkJson::getAllArchsBranch(QString branch,QString path) {
    QList<QString> archs_list;
    QJsonDocument document;
    Api_loader apiLoader;

    document = apiLoader.get_all_arch_load(branch.toStdString(),path.toStdString());
    auto archs_branch_json_array = document[QString("archs")].toArray();
    for(auto it = archs_branch_json_array.cbegin();it!=archs_branch_json_array.cend(); ++it)
    {
        auto branch_arch = QJsonValue(*it)["arch"].toString();
        archs_list.push_back(branch_arch);
    }

    return archs_list;
}

