#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>
#include <sstream>
#include <regex>
#include <cstdio>
#include <algorithm>
#include "Converter.h"
#include "rapidjson/filereadstream.h"
#include "rapidjson/writer.h"
#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"

namespace fs = std::filesystem;
namespace rj = rapidjson;

Converter::Converter(std::string ost, std::string dst, const char* _SEPARATOR):
	original(ost), destination(dst), SEPARATOR(_SEPARATOR) {
	bool success = readJson(original);
	if (trackExists()) {
		name = track["name"].GetString();
		id = track["id"].GetString();
	}
}

void Converter::copyDir(bool is_recursive) {
	try {
		if (is_recursive) {
			std::string pre_destination = destination.substr(0, destination.find(SEPARATOR));
			fs::create_directory(pre_destination);
		}
        fs::copy(SOURCE, destination, fs::copy_options::overwrite_existing | fs::copy_options::recursive);
    }
    catch (std::exception& e) {std::cout << "File copying error.\n";}
}

bool Converter::readJson(std::string folder) {
	try {
		FILE* in = fopen(folder.c_str(), "rb");	
		if (in == 0) { 
			std::cout << "File could not be read.\n";
			return false;
		}
		else {
		char buffer[65536];
		rj::FileReadStream stream(in, buffer, sizeof(buffer));

		track.ParseStream(stream);
		}
		fclose(in);
		return true;
	}

	catch (std::exception& e) {
		std::cout << "JSON Reading error: Please fix the formatting of the track.txt file.\n";
		return false;
	}
}

void Converter::locRewrite(std::string file) {
	try{
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
		std::cout << e.what() << "\n";
	}
}

void Converter::altSoundsRewrite(std::string file, std::vector<bool> alts) {
	try {
		std::ifstream readfile(file);
		std::string fstring;
		std::ostringstream sstr;

		sstr << readfile.rdbuf();
		readfile.close();
		fstring = sstr.str();

		//Adding the alt parts before editing
		std::size_t index = 0;
		for (size_t i = 0; i < alts.size(); i++) {
			if (alts[i]) {
				if (i == 0) {
					std::ifstream replacementFile("alt_templates/alt_setup.xml");
					std::ostringstream rstream;
					rstream << replacementFile.rdbuf();
					replacementFile.close();
					std::string replacement = rstream.str(); 
					index = fstring.find("<event name=\"setup\" source=\"stealthPart\"/>", index);
					fstring.replace(index, 43, replacement);
				}
				else if (i == 1) {
					std::ifstream replacementFile("alt_templates/alt_control.xml");
					std::ostringstream rstream;
					rstream << replacementFile.rdbuf();
					replacementFile.close();
					std::string replacement = rstream.str();
					index = fstring.find("<event name=\"control\" source=\"controlPart\"/>", index);
					fstring.replace(index, 45, replacement);
				}
				else if (i == 2) {
					std::ifstream replacementFile("alt_templates/alt_anticipation.xml");
					std::ostringstream rstream;
					rstream << replacementFile.rdbuf();
					replacementFile.close();
					std::string replacement = rstream.str();
					index = fstring.find("<event name=\"anticipation\" source=\"anticipationPart\"/>", index);
					fstring.replace(index, 55, replacement);
				}
				else if (i == 3) {
					std::ifstream replacementFile("alt_templates/alt_assault.xml");
					std::ostringstream rstream;
					rstream << replacementFile.rdbuf();
					replacementFile.close();
					std::string replacement = rstream.str();
					index = fstring.find("<event name=\"assault\" source=\"assaultPart\"/>", index);
					fstring.replace(index, 45, replacement);
				}
			}			
		}

		for (auto& m : track["events"].GetObject()) {
			std::string xmltag = m.value["file"].GetString();
			std::string part = m.name.GetString();


			if (m.value.HasMember("start_file")) {
				assert(m.value.IsObject());
				xmltag += "\" start_source=\"";
				xmltag += m.value["start_file"].GetString();
				if (part == "setup")
					fstring = std::regex_replace(fstring, std::regex("stealthPart"), xmltag);
				else if (part == "control")
					fstring = std::regex_replace(fstring, std::regex("controlPart"), xmltag);
				else if (part == "buildup")
					fstring = std::regex_replace(fstring, std::regex("anticipationPart"), xmltag);
				else
					fstring = std::regex_replace(fstring, std::regex("assaultPart"), xmltag);
			}
			else {
				if (part == "setup")
					fstring = std::regex_replace(fstring, std::regex("stealthPart"), xmltag);
				else if (part == "control")
					fstring = std::regex_replace(fstring, std::regex("controlPart"), xmltag);
				else if (part == "buildup")
					fstring = std::regex_replace(fstring, std::regex("anticipationPart"), xmltag);
				else
					fstring = std::regex_replace(fstring, std::regex("assaultPart"), xmltag);
			}
			if (m.value.HasMember("alt")) {
				std::string alttag = m.value["alt"].GetString();
				if (part == "setup" && alts[0]) {
					fstring = std::regex_replace(fstring, std::regex("altStealthPart"), alttag);
				}
				else if (part == "control" && alts[1]) {
					fstring = std::regex_replace(fstring, std::regex("altControlPart"), alttag);
				}
				else if (part == "anticipation" && alts[2]) {
					fstring = std::regex_replace(fstring, std::regex("altAnticipationPart"), alttag);
				}
				else if (part == "assault" && alts[3]) {
					fstring = std::regex_replace(fstring, std::regex("altAssaultPart"), alttag);
				}
			}
		}

		fstring = std::regex_replace(fstring, std::regex("sample_id"), track["id"].GetString());
		std::ofstream outfile(file);
		outfile << fstring;
		outfile.close();
	}

	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}
}

std::vector<bool> Converter::checkAlts() {
	std::vector<bool> alts;
	for (auto& itr : track["events"].GetObject()) {
		if (itr.value.HasMember("alt"))
			alts.push_back(true);
		else
			alts.push_back(false);
	}
	return alts;
}

void Converter::copySongs(std::string folder, std::string dst) {
	std::vector<std::string> names;
	std::string current_title;

	for (auto& m : track["events"].GetObject()) {
		assert(m.value.IsObject());
		if (m.value.HasMember("alt"))
			if (!std::count(names.begin(), names.end(), m.value["alt"].GetString()))
				names.push_back(m.value["alt"].GetString());

		if (m.value.HasMember("start_file"))
			if (!std::count(names.begin(), names.end(), m.value["start_file"].GetString()))
				names.push_back(m.value["start_file"].GetString());
				
		if (!std::count(names.begin(), names.end(), m.value["file"].GetString()))
			names.push_back(m.value["file"].GetString());
	}

	for(size_t i = 0; i < names.size(); i++) {
		std::string srcs(SOURCE_DIR);
					srcs += folder;
					srcs += SEPARATOR;
					srcs += names[i];
		std::string dsts(SOURCE_DIR);
					dsts += dst;
					dsts += SEPARATOR;
					dsts += "sounds";
					dsts += SEPARATOR;
					dsts += names[i];
		fs::copy(srcs, dsts);
	}

	std::string _remove_file = dst;
				_remove_file += SEPARATOR +
								"sounds" +
								SEPARATOR +
								".gitkeep";
	fs::remove(_remove_file);
}

void Converter::callEdits(std::string in, std::string out, bool is_recursive) {
	std::string loc = out + 
					  SEPARATOR + 
					  "loc" + 
					  SEPARATOR + 
					  "en.txt";
	std::string mxml = out + 
					   SEPARATOR + 
					   "main.xml";

	if (!is_recursive) std::cout << "Copying directory...\n";
	copyDir(is_recursive);

	if (!is_recursive) std::cout << "Copied directory.\n" <<
	"Rewriting localization...\n";
	locRewrite(loc);

	if (!is_recursive) std::cout << "Rewrote localization file.\n" <<
	"Rewriting xml...\n";
	altSoundsRewrite(mxml, checkAlts());

	if (!is_recursive) std::cout << "Rewrote xml.\n" <<
	"Copying songs...\n";
	copySongs(in, out);

	if (!is_recursive) std::cout << "Copied songs.\n";
	std::cout << "Successfuly Converted " << track["name"].GetString() << ".\n\n";
}
