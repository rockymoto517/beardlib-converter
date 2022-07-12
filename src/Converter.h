#include <string>
#include <fstream>
#include <vector>
#include "rapidjson/document.h"

class Converter {
	private:
		const std::string SOURCE = "template";
		std::string destination, original, name, id;
		rapidjson::Document track;

	public:
		Converter(std::string ost, std::string dst);
		void copyDir();
		void readJson(std::string folder);
		void locRewrite(std::string file);
		//void soundsRewrite(std::string file, std::string trackpath, std::string mid);
		void altSoundsRewrite(std::string file, std::vector<bool> alts);
		std::vector<bool> checkAlts();
		void copySongs(std::string folder, std::string dst);
		void callEdits(std::vector<std::string> folder);
		void logMsg(std::string msg, int time, std::string relation);
};