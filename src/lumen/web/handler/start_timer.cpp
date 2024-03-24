#include "lumen/web/handler/start_timer.hpp"

#include "lumen/activity/message.hpp"
#include "lumen/app_task.hpp"
#include "lumen/web/handler/root.hpp"

namespace lumen::web::handler {

esp_err_t start_timer(httpd_req_t* req)
{
    send_message_to_app(activity::Message{activity::MessageCommand::start_timer}
    );

    // Display the root page
    root(req);

    return ESP_OK;
}

} // namespace lumen::web::handler
