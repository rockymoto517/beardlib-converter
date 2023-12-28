#pragma once
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

class Track {
  private:
    std::string name;
    std::string id;
    std::unordered_map<std::string, std::string> events;
    std::unordered_map<std::string, std::pair<std::string, float>> alts;
    std::unordered_map<std::string, std::string> starts;
    std::unordered_map<std::string, std::string> altStarts;

    float setupWeight = 0.0f;
    float buildupWeight = 0.0f;
    float assaultWeight = 0.0f;
    float controlWeight = 0.0f;

    friend class XML;

  public:
    Track() = default;
    ~Track() = default;
    Track(const Track &) = default;
    Track &operator=(const Track &) = default;

    Track(const std::string &);

    void set(const std::string &);
    std::string get_id();
    std::string get_name();
};
