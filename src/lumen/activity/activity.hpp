#pragma once

#include "lumen/activity/display.hpp"

namespace lumen::activity {

class Activity {
public:
    Activity() = default;
    Activity(const Activity&) = default;
    Activity(Activity&&) = delete;
    Activity& operator=(const Activity&) = default;
    Activity& operator=(Activity&&) = delete;
    virtual ~Activity() = default;

    virtual void update_display() = 0;
};

} // namespace lumen::activity
