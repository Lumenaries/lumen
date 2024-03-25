#pragma once

#include "lumen/activity/activity.hpp"
#include "lumen/activity/display.hpp"

namespace lumen::activity {

enum class Team { home, away };

class Snapshot : public Activity {
public:
    explicit Snapshot(Display* display);

    void increase_score(Team team);

    void decrease_score(Team Team);

    void update_display() override;

private:
    uint home_ = 0;
    uint away_ = 0;

    Display* display_;
};

} // namespace lumen::activity
