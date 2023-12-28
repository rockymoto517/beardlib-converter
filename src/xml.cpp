#include "xml.hpp"
#include <fstream>

XML::XML(Track &track, const std::string &dest) : file(dest + "/main.xml") {
    replace_name(track.name);
    replace_id(track.id);

    for (const auto &[event, fileName] : track.events) {
        if (track.alts.contains(event)) {
            add_alt_event(event, track);
        } else {
            add_event(event, track);
        }
    }
}

void XML::add_event(const std::string &event, Track &track) {
    char buff[256];

    std::string::size_type insert_pos = this->xml.find("</HeistMusic>") - 1;
    if (track.starts.contains(event)) {
        snprintf(buff, 256,
                 "\t\t<event name=\"%s\" source=\"%s\" start_source=\"%s\">\n",
                 event.c_str(), track.events[event].c_str(),
                 track.starts[event].c_str());
        this->xml.insert(insert_pos, buff);

    } else {
        snprintf(buff, 256, "\t\t<event name=\"%s\" source=\"%s\">\n",
                 event.c_str(), track.events[event].c_str());
        this->xml.insert(insert_pos, buff);
    }
}

void XML::add_alt_event(const std::string &event, Track &track) {
    char buff[256];

    std::string::size_type insert_pos = this->xml.find("</HeistMusic>") - 1;
    snprintf(buff, 256, "\t\t<event name=\"%s\">\n", event.c_str());
    this->xml.insert(insert_pos, buff);

    insert_pos = this->xml.find("</HeistMusic>") - 1;
    snprintf(buff, 256, "\t\t\t<track source=\"%s\"/>\n",
             track.events[event].c_str());
    this->xml.insert(insert_pos, buff);

    insert_pos = this->xml.find("</HeistMusic>") - 1;
    if (track.alts[event].second == 0) {
        if (track.altStarts.contains(event)) {
            snprintf(buff, 256,
                     "\t\t\t<track source=\"%s\" start_source=\"%s\"/>\n",
                     track.alts[event].first.c_str(),
                     track.altStarts[event].c_str());
            this->xml.insert(insert_pos, buff);
        } else {
            snprintf(buff, 256, "\t\t\t<track source=\"%s\"/>\n",
                     track.alts[event].first.c_str());
            this->xml.insert(insert_pos, buff);
        }
    } else {
        add_weighted_event(event, track, insert_pos);
    }

    insert_pos = this->xml.find("</HeistMusic>") - 1;
    this->xml.insert(insert_pos, "\t\t</event>\n");
}

void XML::add_weighted_event(const std::string &event, Track &track,
                             const std::string::size_type pos) {
    char buff[256];
    if (track.altStarts.contains(event)) {
        snprintf(
            buff, 256,
            "\t\t\t<track source=\"%s\" start_source=\"%s\" weight=\"%g\"/>\n",
            track.alts[event].first.c_str(), track.altStarts[event].c_str(),
            track.alts[event].second);
        this->xml.insert(pos, buff);
    } else {
        snprintf(buff, 256, "\t\t\t<track source=\"%s\" weight=\"%g\"/>\n",
                 track.alts[event].first.c_str(), track.alts[event].second);
        this->xml.insert(pos, buff);
    }
}

void XML::replace_id(const std::string &id) {
    std::string replace("%id%");
    this->xml.replace(this->xml.find(replace), replace.size(), id);
}

void XML::replace_name(const std::string &name) {
    std::string replace("%name%");
    this->xml.replace(this->xml.find(replace), replace.size(), name);
}

void XML::write_file() {
    std::ofstream outXml(this->file);
    outXml << this->xml << std::endl;
    outXml.close();
}
