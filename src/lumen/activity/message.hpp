#pragma once

#include <optional>

namespace lumen::activity {

enum class MessageCommand {
    start_timer,
    stop_timer,
    activate_buzzer,
    change_team_name,
    increase_score,
    decrease_score
};

enum class Team { home, away };

struct Message {
    MessageCommand command;
    std::optional<Team> team;

    Message() = default;
    explicit Message(MessageCommand command, std::optional<Team> team = {});
};

} // namespace lumen::activity
