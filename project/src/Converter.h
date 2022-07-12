#include <string>
#include <fstream>
#include <vector>
#include "rapidjson/document.h"

class Converter {
	protected:
		std::string destination, original;

	public:
		Converter(std::string ost, std::string dst);
		void copyDir();
		rapidjson::Document readJson(std::string folder);
		void locRewrite(std::string file, std::string mid, std::string name);
		//void soundsRewrite(std::string file, std::string trackpath, std::string mid);
		void altSoundsRewrite(std::string file, std::string trackpath, std::string mid, std::vector<bool> alts);
		std::vector<bool> checkAlts(std::string events);
		void copySongs(std::string folder, std::string trackpath, std::string dst);
		void callEdits(std::vector<std::string> folder);
		void logMsg(std::string msg, int time, std::string relation);
};