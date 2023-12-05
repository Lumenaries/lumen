#include "driver/timer.h"

namespace lumen::web {

void start_timer();

class Timer {
public:
    Timer();

    void start();
    void pause();
    void stop();

    int64_t elapsed_time();

private:
    int64_t elapsed_time_ = 0;
};

} // namespace lumen::web
