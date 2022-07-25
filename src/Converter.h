#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include "rapidjson/document.h"

class Converter {
	private:
		const std::string SOURCE = "template";
		std::string original, destination, name, id;
		rapidjson::Document track;

	public:
		Converter(std::string ost, std::string dst);
		void copyDir(bool is_recursive);
		void readJson(std::string folder);
		void locRewrite(std::string file);
		//void soundsRewrite(std::string file, std::string trackpath, std::string mid);
		void altSoundsRewrite(std::string file, std::vector<bool> alts);
		std::vector<bool> checkAlts();
		void copySongs(std::string folder, std::string dst);
		int callEdits(std::string in, std::string out, bool is_recursive);
		void logMsg(std::string msg, int time, std::string relation);
};