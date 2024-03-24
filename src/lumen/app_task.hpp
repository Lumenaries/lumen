#pragma once

#include "lumen/activity/message.hpp"

namespace lumen {

void app_task(void* parameters);

void send_message_to_app(activity::Message const& message);

} // namespace lumen
