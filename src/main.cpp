#include <iostream>
#include <fstream>
#include <vector>
#include <codecvt>
#include "app_common.h"
#include "PoemSorter.h"

int main() {

    std::cout << "Input file path:\n";

    std::string path;
    std::cin >> path;

    std::ifstream fileStream(path);
    if (!fileStream.is_open()) {
        std::cout << "Bad filepath\n";
    } else {

        const std::locale utf8_locale = std::locale(std::locale(), new std::codecvt_utf8<wchar_t>());

        std::basic_ifstream<appChar> ifs(path, std::ios::ate);
        ifs.imbue(utf8_locale);
        auto pos = ifs.tellg();

        appChar* data = new appChar[pos];

        ifs.seekg(0, std::ios::beg);
        ifs.read(data, pos);

        std::wcout.imbue(utf8_locale);

        std::wcout << data ;

        const appChar* sortedByStart = sortByStart(data);
        const appChar* sortedByEnd = sortByEnd(data);

        std::basic_ofstream<appChar> out("res.txt");
        out.imbue(utf8_locale);


        out << sortedByStart << "\n===================\n" << sortedByEnd << "\n===================\n" << data;
        out.close();
    }

    std::cout << isblank('\t') << "\n";


    return 0;
}
