#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>
#include <sstream>
#include <regex>
#include "Converter.h"
#include "rapidjson/writer.h"
#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"

namespace fs = std::filesystem;
namespace rj = rapidjson;

Converter::Converter(std::string ost, std::string dst):
	destination(dst), original(ost) {
	readJson(original);
	name = track["name"].GetString();
	id = track["id"].GetString();
}

void Converter::copyDir() {
	try {
        fs::copy(SOURCE, destination, fs::copy_options::overwrite_existing | fs::copy_options::recursive);
    }
    catch (std::exception& e) {std::cout << e.what();}
}

void Converter::readJson(std::string folder) {
	try {
		std::ifstream file(folder);	
		char buffer[4096];
		int i = 0;

		while (file >> buffer[i])
			i++;
		file.close();

		track.Parse(buffer);
	}

	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}
}

void Converter::locRewrite(std::string file) {
	try{
		std::cout << "Preparing to rewrite localization file..." << std::endl;
		std::ifstream readfile(file);
		std::string fstring;
		std::ostringstream sstr;

		sstr << readfile.rdbuf();
		fstring = sstr.str();
		readfile.close();

		fstring = std::regex_replace(fstring, std::regex("sample_id"), id);
		fstring = std::regex_replace(fstring, std::regex("sample_name"), name);

		std::ofstream outfile(file);
		outfile << fstring;
		outfile.close();
	}

	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}
}

/* Legacy
void Converter::soundsRewrite(std::string file, std::string trackpath, std::string mid) {
	try {
		std::ifstream readfile(file);
		std::string fstring;
		std::ostringstream sstr;
		rj::Document track = readJson(trackpath);

		sstr << readfile.rdbuf();
		readfile.close();
		fstring = sstr.str();

		for (rj::Value::ConstMemberIterator itr = track["events"].MemberBegin();
			itr != track["events"].MemberEnd(); ++itr) {

			std::ostringstream sstream;
			std::string ss;
			std::string part = itr->name.GetString();
			sstream << itr->value["file"].GetString();

			if (itr->value.HasMember("start_file")) {
				sstream << "\" start_source=\"" << itr->value["start_file"].GetString();
				ss = sstream.str();
				if (part == "setup")
					fstring = std::regex_replace(fstring, std::regex("stealthPart"), ss);
				else if (part == "control")
					fstring = std::regex_replace(fstring, std::regex("controlPart"), ss);
				else if (part == "buildup")
					fstring = std::regex_replace(fstring, std::regex("anticipationPart"), ss);
				else
					fstring = std::regex_replace(fstring, std::regex("assaultPart"), ss);
			}
			else {
				ss = sstream.str();
				if (part == "setup")
					fstring = std::regex_replace(fstring, std::regex("stealthPart"), ss);
				else if (part == "control")
					fstring = std::regex_replace(fstring, std::regex("controlPart"), ss);
				else if (part == "buildup")
					fstring = std::regex_replace(fstring, std::regex("anticipationPart"), ss);
				else
					fstring = std::regex_replace(fstring, std::regex("assaultPart"), ss);
			}			
		}
		
		std::ofstream outfile(file);
		outfile << fstring;
		outfile.close();
	}

	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}
}
*/

void Converter::altSoundsRewrite(std::string file, std::vector<bool> alts) {
	try {
		std::cout << "Preparing to rewrite xml..." << std::endl;
		std::ifstream readfile(file);
		std::string fstring;
		std::ostringstream sstr;

		sstr << readfile.rdbuf();
		readfile.close();
		fstring = sstr.str();

		//Adding the alt parts before editing
		std::cout << "Checking alt tracks..." << std::endl;
		for (size_t i = 0; i < alts.size(); i++) {
			if (alts.at(i)) {
				if (i == 0) {
					std::ifstream replacementFile("alt_templates/alt_setup.xml");
					std::ostringstream rstream;
					rstream << replacementFile.rdbuf();
					replacementFile.close();
					std::string replacement = rstream.str(); 
					std::size_t index = 0;
					index = fstring.find("<event name=\"setup\" source=\"stealthPart\"/>", index);
					fstring.replace(index, 43, replacement);
				}
				else if (i == 1) {
					std::ifstream replacementFile("alt_templates/alt_control.xml");
					std::ostringstream rstream;
					rstream << replacementFile.rdbuf();
					replacementFile.close();
					std::string replacement = rstream.str();
					std::size_t index = 0;
					index = fstring.find("<event name=\"control\" source=\"controlPart\"/>", index);
					fstring.replace(index, 45, replacement);
				}
				else if (i == 2) {
					std::ifstream replacementFile("alt_templates/alt_anticipation.xml");
					std::ostringstream rstream;
					rstream << replacementFile.rdbuf();
					replacementFile.close();
					std::string replacement = rstream.str();
					std::size_t index = 0;
					index = fstring.find("<event name=\"anticipation\" source=\"anticipationPart\"/>", index);
					fstring.replace(index, 55, replacement);
				}
				else if (i == 3) {
					std::ifstream replacementFile("alt_templates/alt_assault.xml");
					std::ostringstream rstream;
					rstream << replacementFile.rdbuf();
					replacementFile.close();
					std::string replacement = rstream.str();
					std::size_t index = 0;
					index = fstring.find("<event name=\"assault\" source=\"assaultPart\"/>", index);
					fstring.replace(index, 45, replacement);
				}
			}			
		}

		std::cout << "Replacing xml..." << std::endl;
		for (auto& m : track["events"].GetObject()) {
			std::ostringstream sstream;
			std::string ss;
			std::string part = m.name.GetString();
			sstream << m.value["file"].GetString();


			if (m.value.HasMember("start_file")) {
				assert(m.value.IsObject());
				sstream << "\" start_source=\"" << m.value["start_file"].GetString();
				ss = sstream.str();
				if (part == "setup")
					fstring = std::regex_replace(fstring, std::regex("stealthPart"), ss);
				else if (part == "control")
					fstring = std::regex_replace(fstring, std::regex("controlPart"), ss);
				else if (part == "buildup")
					fstring = std::regex_replace(fstring, std::regex("anticipationPart"), ss);
				else
					fstring = std::regex_replace(fstring, std::regex("assaultPart"), ss);
			}
			else {
				ss = sstream.str();
				if (part == "setup")
					fstring = std::regex_replace(fstring, std::regex("stealthPart"), ss);
				else if (part == "control")
					fstring = std::regex_replace(fstring, std::regex("controlPart"), ss);
				else if (part == "buildup")
					fstring = std::regex_replace(fstring, std::regex("anticipationPart"), ss);
				else
					fstring = std::regex_replace(fstring, std::regex("assaultPart"), ss);
			}
			if (m.value.HasMember("alt")) {
				std::ostringstream temps;
				std::string alts;
				assert(m.value.IsObject());
				temps << m.value["alt"].GetString();
				alts = temps.str();
				if (part == "setup" && alts.at(0)) {
					fstring = std::regex_replace(fstring, std::regex("altStealthPart"), alts);
				}
				else if (part == "control" && alts.at(1)) {
					fstring = std::regex_replace(fstring, std::regex("altControlPart"), alts);
				}
				else if (part == "anticipation" && alts.at(2)) {
					fstring = std::regex_replace(fstring, std::regex("altAnticipationPart"), alts);
				}
				else if (part == "assault" && alts.at(3)) {
					fstring = std::regex_replace(fstring, std::regex("altAssaultPart"), alts);
				}
			}
		}

		std::cout << "Writing xml..." << std::endl;
		fstring = std::regex_replace(fstring, std::regex("sample_id"), track["id"].GetString());
		std::ofstream outfile(file);
		outfile << fstring;
		outfile.close();
		std::cout << "Successfuly wrote xml..." << std::endl;
	}

	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}
}

std::vector<bool> Converter::checkAlts() {
	std::vector<bool> alts;

	for (rj::Value::ConstMemberIterator itr = track["events"].MemberBegin();
			itr != track["events"].MemberEnd(); ++itr) {

			if (itr->value.HasMember("alt"))
				alts.push_back(true);
			else
				alts.push_back(false);
		}
	
	return alts;
}

void Converter::copySongs(std::string folder, std::string dst) {
	std::vector<std::string> names;

	for (auto& m : track["events"].GetObject()) {
		assert(m.value.IsObject());
		if (m.value.HasMember("alt"))
			names.push_back(m.value["alt"].GetString());
		if (m.value.HasMember("start_file"))
			names.push_back(m.value["start_file"].GetString());
		names.push_back(m.value["file"].GetString());
	}

	for(size_t i = 0; i < names.size(); i++) {
		std::ostringstream inputs;
		std::ostringstream outputs;
		std::string srcs;
		std::string dsts;
		inputs << folder << "/" << names.at(i);
		outputs << dst << "/sounds/" << names.at(i);
		srcs = inputs.str();
		dsts = outputs.str();
		std::cout << srcs << " : " << dsts << std::endl;
		std::filesystem::copy(srcs, dsts);
	}
}