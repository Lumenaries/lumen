#pragma once

#include "cJSON.h"

#include "esp_chip_info.h"
#include "esp_http_server.h"
#include "esp_log.h"
#include "esp_random.h"
#include "esp_vfs.h"

#include <filesystem>
#include <string>

class Server {
public:
    Server(const std::string& base_path);

private:
    esp_err_t set_content_type_from_file(httpd_req_t* req,
                                         const std::filesystem::path& filepath);

    esp_err_t common_get_handler(httpd_req_t* req);

    const std::string base_path_;
    const std::string scratch_buffer_;
};
