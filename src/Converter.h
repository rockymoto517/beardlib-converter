#pragma once
#include <string>
#include <vector>
#include "rapidjson/document.h"

class Converter {
	private:
		const std::string SOURCE = "template";
		const std::string SOURCE_DIR = RESOURCE_DIRECTORY;
		std::string original, destination, name, id, SEPARATOR;
		rapidjson::Document track;

	public:
		Converter(const std::string ost, const std::string dst, const char* _SEPARATOR);
		void copyDir(const bool is_recursive);
		bool readJson(const std::string folder);
		void locRewrite(const std::string file);
		void altSoundsRewrite(const std::string file, const std::vector<bool> alts);
		std::vector<bool> checkAlts();
		void copySongs(const std::string folder, const std::string dst);
		void callEdits(const std::string in, const std::string out, const bool is_recursive);
		void logMsg(const std::string msg, const int time, const std::string relation);
		bool trackExists() {return track.IsObject();}
};
