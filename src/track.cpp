#include "track.hpp"
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

Track::Track(const std::string &trackFile) { set(trackFile); }

void Track::set(const std::string &trackFile) {
    std::ifstream trackStream(trackFile);
    json trackData;
    try {
        trackData = json::parse(trackStream);
    } catch (std::exception &e) {
        printf("Error parsing json file\n\n");
        printf("%s\n", e.what());
    }

    this->name = trackData["name"];
    this->id = trackData["id"];
    this->events["setup"] = trackData["events"]["setup"]["file"];
    this->events["buildup"] = trackData["events"]["buildup"]["file"];
    this->events["assault"] = trackData["events"]["assault"]["file"];
    this->events["control"] = trackData["events"]["control"]["file"];

    for (auto &[event, part] : trackData["events"].items()) {
        if (part.contains("alt")) [[unlikely]] {
            this->alts[event] = {part["alt"], 0};
            if (part.contains("alt_chance")) [[likely]] {
                this->alts[event].second = part["alt_chance"];
            }
        }

        if (part.contains("start_file")) {
            this->starts[event] = part["start_file"];
        }

        if (part.contains("alt_start")) [[unlikely]] {
            this->altStarts[event] = part["alt_start"];
        }
    }

    trackStream.close();
}

std::string Track::get_id() { return this->id; }

std::string Track::get_name() { return this->name; }
