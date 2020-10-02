#include <iostream>
#include <fstream>
#include <vector>
#include <codecvt>
#include "app_common.h"
#include "poem_sorter.h"

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

        auto* data = new appChar[pos];

        ifs.seekg(0, std::ios::beg);
        ifs.read(data, pos);

        const appChar* sortedByStart = sortByStart(data);
        const appChar* sortedByEnd = sortByEnd(data);

        std::basic_ofstream<appChar> out("out/res.txt");
        out.imbue(utf8_locale);


        out << sortedByStart << "\n===================\n" << sortedByEnd << "\n===================\n" << data;
        out.close();

        std::cout << "Done! You can find result in out/res.txt" << "\n";
    }

    return 0;
}
