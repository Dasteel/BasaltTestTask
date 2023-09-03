#include <QCoreApplication>
#include <iostream>

#include "MyLib.h"
#include "stdio.h"
#include "version.h"
#include <getopt.h>

#define BUFSIZE 32

void printHelp()
{
    std::cout << "DESCRIPTION\n" <<
              "\tThe program compares two branches passed to it as input, "
              "obtained using '/export/branch_binary_packages/"
              "{branch}' method REST API 'https://rdb.altlinux.org/api' "
              "1)Searches for unique packages of branch 1 that are not in branch 2."
              "2)Search for unique packages of branch 2 that are not in branch 1. "
              "3)Search for packages whose version is in branch 1\n"
              "more versions of branch 2 packages. "
              "At the end, the program writes the result to json files with the name\n"
              " of the architecture to which the listed packages belong "
              << std::endl;
    std::cout << "\nPARAMS\n" <<
              "\t-h, --help        - information about the program\n" <<
              "\t-v, --version     - the current version of the program\n" <<
              "\t-b1 <branch name> - the name of the first branch\n" <<
              "\t-b2 <branch name> - the name of the second branch\n" <<
              "\t-o, --output      - path to the folder where the result \n";
}


int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    char branch_name_1[BUFSIZE+1];
    char branch_name_2[BUFSIZE+1];
    char output_folder[BUFSIZE+1];

    struct option opts[] = {
            {"help",    no_argument,	   0, 'h'},
            {"version", no_argument, 	   0, 'v'},
            {"output",  required_argument, 0, 'o'}
    };
    int branch_cnt = 0;
    int opchar     = 0;
    while( -1 != (opchar = getopt_long(argc, argv, "hvbo:1:2:", opts, nullptr)) )
    {
        switch(opchar)
        {
            case 'h':
                printHelp();
                return EXIT_SUCCESS;
            case 'v':
                std::cout << "Current program version: " << cur_version << std::endl;
                return EXIT_SUCCESS;
            case 'b':
                break;
            case '1':
                if (branch_cnt != 2)
                { sprintf(branch_name_1, "%s", optarg); ++branch_cnt; }
                break;
            case '2':
                if (branch_cnt != 2)
                { sprintf(branch_name_2, "%s", optarg); ++branch_cnt; }
                break;
            case 'o':
                sprintf(output_folder, "%s", optarg);
                break;
            default:
                std::cout << "Invalid parameters passed!" << std::endl;
        }
    }

    if (opterr)
    {
        if (branch_cnt < 2)
        {
            std::cout << "Specify names for both branches." << std::endl;
        } else
        {
            MyLib myLib(QString::fromUtf8(branch_name_1), QString::fromUtf8(branch_name_2), QString::fromUtf8(output_folder));
            myLib.compare_branches();
            myLib.compare_version();
        }
    }


    exit(1);


    return a.exec();
}
