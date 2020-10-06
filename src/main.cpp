#include <iostream>
#include <vector>
#include <codecvt>
#include <chrono>
#include <sys/mman.h>
#include <fcntl.h>
#include <libnet.h>
#include "app_common.h"
#include "poem_sorter.h"

appChar* read(const char* path, size_t& size) {
    int descriptor = open(path, O_RDONLY);

    struct stat fileStat{};
    if (fstat(descriptor, &fileStat) == -1) return nullptr;

    auto* data = (appChar*) mmap(nullptr, fileStat.st_size, PROT_READ, MAP_PRIVATE, descriptor, 0);
    if (data == MAP_FAILED) return nullptr;

    close(descriptor);

    size = fileStat.st_size;

    return data;
}

int main(int argc, char* argv[]) {
    appChar* data;
    size_t fileContentSize = 0;
    const std::locale utf8_locale = std::locale(std::locale(), new std::codecvt_utf8<wchar_t>());

    if (argc > 1) {
        data = read(argv[1], fileContentSize);
    } else {
        std::cout << "Input file path:\n";

        appString str;
        std::cin >> str;

        data = read(str.data(), fileContentSize);
    }

    if (data == nullptr) {
        std::cout << "Bad filepath\n";
    } else {
        std::vector<LineData> lines;
        fromCString(data, fileContentSize, lines);

        FILE* outFile = fopen("out/res.txt", "w");


        sortByStart(lines);

        fprintf(outFile, "===================Sorted by start\n");
        for (auto& line : lines) {
            fwrite(line.start, sizeof(appChar), line.length() + 1, outFile);
        }


        sortByEnd(lines);

        fprintf(outFile, "===================Sorted by end\n");
        for (auto& line : lines) {
            fwrite(line.start, sizeof(appChar), line.length() + 1, outFile);
        }


        fprintf(outFile, "===================Original\n");
        fwrite(data, sizeof(appChar), fileContentSize, outFile);

        fclose(outFile);
        munmap(data, fileContentSize);

        std::cout << "Done! You can find result in out/res.txt" << "\n";
    }

    return 0;
}
