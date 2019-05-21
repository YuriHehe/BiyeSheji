#include "util.h"


namespace util {
void string_split_to_vector(std::string str, char spliter, std::vector<std::string>& vec) {
    std::string split;
    for (auto c : str) {
        if (c == spliter && split.size()) {
            vec.push_back(split);
            split.clear();
        } else {
            split += c;
        }
    }
    if (split.size()) {
        vec.push_back(split);
        split.clear();
    }
}
int64_t get_timestamp_ms()
{
    struct timeb t;
    
    ftime(&t);
    
    return 1000ll*t.time + t.millitm;
}
}