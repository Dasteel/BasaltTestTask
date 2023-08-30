#include <QCoreApplication>
#include <QDebug>



int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);
    const std::string query = "curl -X 'GET' "
                              "  https://rdb.altlinux.org/api/export/branch_binary_packages/";
    std::string branch_1 = "p10";
    std::string arch = "aarch64";
    std::string path = "request1.json";
    std::string query_to_perform = query + branch_1 + "?arch=" + arch + " >" + path;
    system(query_to_perform.data());
    return QCoreApplication::exec();
}
