#include <iostream>
#include <string>
#include <filesystem>
#include <regex>
#include "rapidjson/document.h"
#include "Converter.h"

#ifdef _WIN32
#define SEPARATOR "\\"
#endif

#ifdef linux
#define SEPARATOR "/"
#endif

namespace fs = std::filesystem;

int main(int argc, char* argv[]) {
    if (argc == 1) {
        std::cout << "For help, use -h or -help." << std::endl;
        return 0;
    } 
    else if (std::strcmp(argv[1], "-r") == 0) {
        int result = 0;
        std::smatch m;
        fs::path parent(argv[2]);
        std::regex pattern("track.txt");
        for (auto& file: fs::recursive_directory_iterator(parent)) {
            std::string name = fs::path(file).make_preferred().string();
            if (!(std::string::npos != name.find('.'))) {
                std::string output(argv[3]);
                int backPos = name.find("\\");
                std::string folder = name.substr(backPos + 1);
                std::string _extension(SEPARATOR);
                _extension += "track.txt";
                const std::string track_extension(_extension);
                name.append(track_extension);
                output.append(SEPARATOR);
                output.append(folder);

                Converter*converter = new Converter(name, output, SEPARATOR);
                name = name.substr(0, name.size() - track_extension.size());
                if (result == 0) 
                    result += converter->callEdits(name, output, true);
                delete converter;
            }
        }
        return result;
    }
    else if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "-help") == 0) {
        std::cout << "To convert 1 folder: Converter input_folder output_folder." << std::endl <<
        "-r:    Recursive search and convert in folder." << std::endl;
        return 0;
    }
    else {
        std::string track = argv[1];
        std::string _extension(SEPARATOR);
        _extension += "track.txt";
        track.append(_extension);
        Converter*converter = new Converter(track, argv[2], SEPARATOR);
        int result = converter->callEdits(argv[1], argv[2], false);
        delete converter;
        return result;
    }
    return 1;
}
