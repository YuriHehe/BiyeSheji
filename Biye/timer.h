#include "predefine.h"
#include "util.h"

namespace timer {
class Timer {
public:
    Timer() : start_(util::get_timestamp_ms()) {};

    int64_t get_elapsed_us() {
        return util::get_timestamp_ms() - start_;
    }
private:
    const int64_t start_;
};
}