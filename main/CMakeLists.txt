idf_component_register(SRCS "main.cpp"
                            "lumen/application.cpp"
                            "lumen/net/dns_server.cpp"
                            "lumen/net/wifi.cpp"
                            "lumen/sys/filesystem.cpp"
                            "lumen/web/rest_server.cpp"
                            "lumen/web/timer.cpp"
                    INCLUDE_DIRS ".")

if(CONFIG_EXAMPLE_WEB_DEPLOY_SF)
    set(WEB_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../frontend")
    if(EXISTS ${WEB_SRC_DIR}/dist)
        spiffs_create_partition_image(www ${WEB_SRC_DIR}/dist FLASH_IN_PROJECT)
    else()
        message(FATAL_ERROR "${WEB_SRC_DIR}/dist doesn't exit. Please run 'npm run build' in ${WEB_SRC_DIR}")
    endif()
endif()
