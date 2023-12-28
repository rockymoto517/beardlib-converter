#pragma once
#include "track.hpp"
#include <filesystem>

namespace fs = std::filesystem;

const fs::path create_dirs(const std::string &);
void create_loc(Track &, const std::string &);
void copy_files(const fs::path &, const fs::path &);
