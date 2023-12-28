#include "files.hpp"
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

const fs::path create_dirs(const std::string &out) {
    const fs::path outDir(out);
    const fs::path soundsDir(out + "/sounds");
    const fs::path locDir(out + "/loc");
    try {
        fs::create_directory(outDir);
        fs::create_directory(soundsDir);
        fs::create_directory(locDir);
    } catch (std::exception &e) {
        printf("Error creating one or more directories. Please check if the "
               "output directory specified already exists or not.\n\n\n%s",
               e.what());
    }

    return soundsDir;
}

void create_loc(Track &track, const std::string &output) {
    std::string jukeboxId = "menu_jukebox_" + track.get_id();
    std::string screenId = "menu_jukebox_screen_" + track.get_id();
    json loc = {{jukeboxId, track.get_name()}, {screenId, track.get_name()}};

    std::ofstream jsonOut(output + "/loc/en.txt");
    jsonOut << std::setw(4) << loc << std::endl;
    jsonOut.close();
}

void copy_files(const fs::path &inDir, const fs::path &soundsDir) {
    for (const auto &file : fs::directory_iterator(inDir)) {
        if (file.path().string().find("track.txt") == std::string::npos)
            [[unlikely]] {
            fs::copy_file(file,
                          soundsDir /
                              file.path().string().substr(
                                  file.path().string().find_last_of("/") + 1));
        }
    }
}
