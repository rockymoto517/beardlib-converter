#include <iostream>
#include <string>
#include "rapidjson/document.h"
#include "Converter.h"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cout << 
        "Please enter in the proper formatting:" << std::endl << 
        "Converter CustomOSTFolder NewOutputFolder" << std::endl << 
        "If your custom ost folder has spaces in it, please enter it using quotes, e.g. \"OST Folder\"" << std::endl;
    } else {
        char trackchar[] = "/track.txt";
        char locchar[] = "/loc/en.txt";
        char mxmlchar[] = "/main.xml";
        std::string folder(argv[1]);
        std::string output(argv[2]);
        std::string track(argv[1]);
        std::string loc(argv[2]);
        std::string mxml(argv[2]);
        track.append(trackchar);
        loc.append(locchar);
        mxml.append(mxmlchar);
        Converter converter(track, output);
        converter.copyDir();
        converter.locRewrite(loc);
        converter.altSoundsRewrite(mxml, converter.checkAlts());
        converter.copySongs(folder, output);
        std::cout << "Successfuly Converted." << std::endl <<
        "Press any key to exit...";
        std::cin.get();
    }
}
