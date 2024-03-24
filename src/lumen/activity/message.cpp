#include "lumen/activity/message.hpp"

namespace lumen::activity {

Message::Message(MessageCommand command, std::optional<Team> team /* = {} */)
    : command{command}, team{team}
{
}

} // namespace lumen::activity
