#include "lumen/activity/snapshot.hpp"

namespace lumen::activity {

Snapshot::Snapshot(Display* display) : display_{display}
{
    update_display();
}

void Snapshot::increase_score(Team team)
{
    if (team == Team::home) {
        home_++;
    } else {
        away_++;
    }

    update_display();
}

void Snapshot::decrease_score(Team team)
{
    if (team == Team::home && home_ > 0) {
        home_--;
    } else if (away_ > 0) {
        away_--;
    }

    update_display();
}

void Snapshot::update_display()
{
    display_->clearScreen();

    display_->setTextSize(2);

    display_->setTextColor(display_->color565(100, 0, 100));

    display_->setCursor(0, 0);
    display_->print(std::to_string(home_).c_str());

    display_->setCursor(20, 0);
    display_->print(std::to_string(away_).c_str());
}

} // namespace lumen::activity
