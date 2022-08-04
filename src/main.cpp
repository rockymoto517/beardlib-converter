#include <iostream>
#include <string>
#include <filesystem>
#include <regex>
#include <memory>
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
        const fs::path parent{argv[2]};
        std::regex pattern("track.txt");
        for (auto const& file: fs::directory_iterator{parent}) {
            std::string name = fs::path(file).make_preferred().string();            
            if (!(std::string::npos != name.find('.'))) {
                int backPos = name.find(SEPARATOR);
                std::string folder = name.substr(backPos + 1);
                std::string output(argv[3]);
                std::string _extension(SEPARATOR);
                            _extension += "track.txt";
                            name += _extension;
                            output += SEPARATOR;
                            output += folder;

                std::unique_ptr<Converter> converter = std::make_unique<Converter>(name, output, SEPARATOR);
                if (converter->trackExists()) {
                    name = name.substr(0, name.size() - _extension.size());
                    converter->callEdits(name, output, true);
                }
                else {
                    std::cout << "Error reading " << name << 
                                 ".\nPlease try validating the json file.\n\n";
                    return 1;
                }
            }
        }
        return 0;
    }
    else if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "-help") == 0) {
        std::cout << "To convert 1 folder: Converter input_folder output_folder.\n" <<
                     "-r:    Recursive search and convert in folder.\n";
        return 0;
    }
    else if (argc == 3) {
        std::string track = argv[1];
        std::string _extension(SEPARATOR);
                    _extension += "track.txt";
                    track += _extension;

        std::unique_ptr<Converter> converter = std::make_unique<Converter>(track, argv[2], SEPARATOR);
        if (converter->trackExists()) {
            converter->callEdits(argv[1], argv[2], false);
            return 0;
        }
        return 1;
    }
    std::cout << "Please enter a valid argument.\n" <<
                 "For help, use the - h flag.\n\n";
    return 1;
}
