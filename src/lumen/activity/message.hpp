#pragma once

namespace lumen::activity {

// What actions will the server be able to send?
enum class MessageCommand { increase_score, decrease_score, reset };

enum class Team { home, away };

struct Message {
    MessageCommand command;
    Team team;

    Message() = default;
    Message(MessageCommand command, Team team);
};

} // namespace lumen::activity
