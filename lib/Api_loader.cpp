//
// Created by denis on 30.08.23.
//

#include "Api_loader.h"
#include "QtCore/QFile"



/**
 * @brief Api_loader::get_all_arch
 * Method of getting a response containing a list of architectures of the transferred branch
 * @param branch
 * @param path
 * @return a QJsonDocument containing binary package archs list.
 */
QJsonDocument Api_loader::get_all_arch_load(std::string branch,  QString path) {
    QJsonDocument document;
    const std::string query = "curl -X 'GET' "
                              "  https://rdb.altlinux.org/api/site/all_pkgset_archs";
    std::string query_to_perform = query + "?branch=" + branch + " >" + path.toStdString();
    system(query_to_perform.data());

    QFile file(path);

    QByteArray buffer;

    if(file.open(QIODevice::ReadOnly))
    {
        qDebug()<<"File archs is open";
        buffer = file.readAll();
    }
    else
    {
        qDebug()<<"Error --> File archs is not open";
    }

    QJsonParseError parseError;

    document = QJsonDocument::fromJson(buffer,&parseError);
    if(parseError.errorString().toInt() != QJsonParseError::NoError)
    {
        qDebug()<<"Json document parse error";
        //document = NULL;
    }
    file.close();

    return document;
}

/**
 * @brief Api_loader::get_binary_branch_load
 * containing branch data for a specific architecture
 * @param branch
 * @param arch
 * @param path
 * @return a QJsonDocument containing branch data for a specific architecture.
 */

QJsonDocument Api_loader::get_binary_branch_load(std::string branch, std::string arch, QString path) {
    QJsonDocument document;
    const std::string query = "curl -X 'GET' "
                              "  https://rdb.altlinux.org/api/export/branch_binary_packages/";

    std::string query_to_perform = query + branch + "?arch=" + arch + " >" + path.toStdString();
    system(query_to_perform.data());
    QFile file(path) ;
    QByteArray buffer;
    if(file.open(QIODevice::ReadOnly))
    {
        qDebug()<<"File binary_branch is open";
        buffer = file.readAll();
    }
    else
    {
        qDebug()<<"Error --> File binary_branch is not open";
    }
    QJsonParseError parseError;

    document = QJsonDocument::fromJson(buffer,&parseError);
    if(parseError.errorString().toInt() != QJsonParseError::NoError)
    {
        qDebug()<<"Json document parse error";

    }

    file.close();

    return document;
}
