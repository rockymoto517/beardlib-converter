#pragma once
#include "track.hpp"
#include <string>
#include <vector>

class XML {
  public:
    std::string file;
    std::string xml = "<table name=\"%name%\">\n"
                      "\t<Localization directory=\"loc\" default=\"en.txt\">\n"
                      "\t<HeistMusic id=\"%id%\" directory=\"sounds\">\n"
                      "\t</HeistMusic>\n"
                      "</table>\n";

  public:
    XML() = delete;
    ~XML() = default;
    XML(const XML &) = delete;
    XML &operator=(const XML &) = delete;

    XML(Track &, const std::string &);

    void add_event(const std::string &, Track &);
    void add_alt_event(const std::string &, Track &);
    void add_weighted_event(const std::string &, Track &,
                            const std::string::size_type);
    void replace_id(const std::string &);
    void replace_name(const std::string &);
    void write_file();
};
