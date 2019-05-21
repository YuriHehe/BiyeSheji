#pragma once

#include "predefine.h"
#include "log.h"
#include <sys/timeb.h>
#include <sys/types.h>

namespace util {
template<typename INT>
std::string int_vector_to_string(const std::vector<INT>& vec) {
    std::string ret;
    for (auto v : vec) {
        if (ret.size() != 0) ret += ",";
        ret += std::to_string(v);
    }
    return ret;
}

void string_split_to_vector(std::string str, char spliter, std::vector<std::string>& vec);

template<typename INT>
void string_split_to_int_vector(std::string str, char spliter, std::vector<INT>& vec) {
    std::string str;
    string_split_to_vector(str, spliter, str);
    std::vector<INT> vec;
    try {
        for (auto s : str) {
            int64_t tar;
            std::stoll(s, tar);
            vec.push_back(INT(tar));
        }
    } catch (...) {
        ERROR_LOG("error target item value!");
        return;
    }
}

int64_t get_timestamp_ms();

}