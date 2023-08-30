//
// Created by denis on 30.08.23.
//

#include "Api_loader.h"
#include "QFile"


/**
 * @brief Api_loader::get_all_arch
 * Method of getting a response containing a list of architectures of the transferred branch
 * @param branch
 * @param path
 * @return a QJsonDocument containing binary package archs list.
 */
QJsonDocument Api_loader::get_all_arch_load(std::string branch,  std::string path) {
    QJsonDocument document;
    const std::string query = "curl -X 'GET' "
                              "  https://rdb.altlinux.org/api/site/all_pkgset_archs?branch=p10/";
    std::string query_to_perform = query + "?branch=" + branch + " >" + path;
    system(query_to_perform.data());
    QFile file("path") ;
    QByteArray buffer;
    if(file.isOpen())
    {
        qDebug()<<"File archs is open";
        buffer = file.readAll();
    }

    QJsonParseError parseError;

    document = QJsonDocument::fromJson(buffer,&parseError);
    if(parseError.errorString().toInt() != QJsonParseError::NoError)
    {
        qDebug()<<"Json document parse error";
        //document = NULL;
    }

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

QJsonDocument Api_loader::get_binary_branch_load(std::string branch, std::string arch, std::string path) {
    QJsonDocument document;
    const std::string query = "curl -X 'GET' "
                              "  https://rdb.altlinux.org/api/export/branch_binary_packages/";

    std::string query_to_perform = query + branch + "?arch=" + arch + " >" + path;
    system(query_to_perform.data());
    QFile file("path") ;
    QByteArray buffer;
    if(file.isOpen())
    {
        qDebug()<<"File binary_branch is open";
        buffer = file.readAll();
    }
    QJsonParseError parseError;

    document = QJsonDocument::fromJson(buffer,&parseError);
    if(parseError.errorString().toInt() != QJsonParseError::NoError)
    {
        qDebug()<<"Json document parse error";
        //document = QJsonDocument(nullptr);
    }

    return document;
}
