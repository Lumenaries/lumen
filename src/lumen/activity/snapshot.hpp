#pragma once

#include "lumen/activity/activity.hpp"
#include "lumen/activity/display.hpp"
#include "lumen/activity/message.hpp"

namespace lumen::activity {

class Snapshot : public Activity {
public:
    explicit Snapshot(Display* display);

    void reset();

    void increase_score(Team team);

    void decrease_score(Team Team);

    void update_display() override;

private:
    uint home_ = 0;
    uint away_ = 0;

    Display* display_ = nullptr;
};

} // namespace lumen::activity