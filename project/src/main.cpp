#include <iostream>
#include <string>
#include "rapidjson/document.h"
#include "Converter.h"

int main() {
    std::string folder = "folder";
    std::string string = "inno_glitched";
    Converter converter("Ino_Glitch", folder);
    converter.copyDir();
    converter.locRewrite("folder/loc/en.txt", "string", "Innocence Glitched");
    converter.altSoundsRewrite("folder/main.xml", "Ino_Glitch/track.txt", string, converter.checkAlts("Ino_Glitch/track.txt"));
    converter.copySongs("Ino_Glitch", "Ino_Glitch/track.txt", folder);
}
