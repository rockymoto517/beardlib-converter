#include "files.hpp"
#include "xml.hpp"
#include <filesystem>

int main(int argc, char *argv[]) {
    if (argc == 3) {
        std::string inDir = argv[1];
        Track track(inDir + "/track.txt");

        std::string outDir = argv[2];
        const fs::path soundDir = create_dirs(outDir);
        XML xml(track, outDir);
        xml.write_file();
        create_loc(track, outDir);

        copy_files(inDir, soundDir);
    } else {
        printf("Usage: Converter <CustomOST Directory> <Output Directory>\n");
    }
}
