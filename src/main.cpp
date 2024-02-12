#include "lumen/application.hpp"
#include "lumen/net/wifi.hpp"

#include <cstring>

extern "C" void app_main()
{
    lumen::net::init_wifi_softap();

    lumen::Application app{};
}
