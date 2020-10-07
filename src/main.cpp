#include <iostream>
#include <vector>
#include <codecvt>
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

        FILE* byStartFile = fopen("out/byStart.txt", "w");
        sortByStart(lines);

        fprintf(byStartFile, "===================Sorted by start\n");
        for (auto& line : lines) {
            fwrite(line.start, sizeof(appChar), line.length(), byStartFile);
        }

        fclose(byStartFile);

        FILE* byEndFile = fopen("out/byEnd.txt", "w");
        sortByEnd(lines);

        fprintf(byEndFile, "===================Sorted by end\n");
        for (auto& line : lines) {
            fwrite(line.start, sizeof(appChar), line.length(), byEndFile);
        }

        fclose(byEndFile);

        FILE* originalFile = fopen("out/original.txt", "w");
        fprintf(originalFile, "===================Original\n");
        fwrite(data, sizeof(appChar), fileContentSize, originalFile);

        fclose(originalFile);

        munmap(data, fileContentSize);

        std::cout << "Done! You can find results in out/byStart.txt, out/byEnd.txt, out/original.txt" << "\n";
    }

    return 0;
}
