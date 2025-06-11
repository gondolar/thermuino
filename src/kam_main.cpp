// #include "nlc_app.h"

// #ifdef LLC_ESP32
// #include "nlc_sensor_pir.h"
// #include "nlc_ov2640.h"

// #include "llc_safe.h"
// #include "llc_micro.h"
// #include "llc_array_static.h"
// #include "llc_chrono.h"
// //  Rui Santos. Complete project details at https://RandomNerdTutorials.com/esp32-cam-video-streaming-web-server-camera-home-assistant/
// //  IMPORTANT!!! 
// //   - Select Board "AI Thinker ESP32-CAM"
// //   - GPIO 0 must be connected to GND to upload a sketch
// //   - After connecting GPIO 0 to GND, press the ESP32-CAM on-board RESET button to put your board in flashing mode
// //  Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files. This copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

// #include <esp_camera.h>
// #include <WiFi.h>
// #include <esp_timer.h>
// #include <img_converters.h>
// #include <fb_gfx.h>
// ////#include "soc/soc.h" //disable brownout problems
// //#include "soc/rtc_cntl_reg.h"  //disable brownout problems 
// #include <esp_http_server.h>
// #include <esp_http_client.h>
// #include <SPIFFS.h>
// #include <dirent.h>
// #include <stdio.h>
// #include <driver/gpio.h>
// #include <esp_timer.h>
// #include <esp_log.h>
// #include <esp_spiffs.h>
// #include <esp_event.h>
// #include <esp_tls.h>
// //#include "esp_vfs.h"
// //#include <string.h>
// //#include <sys/unistd.h>
// //#include <sys/stat.h>
// //#include <esp_vfs_fat.h>
// //#include <sdmmc_cmd.h>
// //#include <driver/sdmmc_host.h>

// stxp const uint16_t MAX_HTTP_RECV_BUFFER    = 512;
// stxp const uint16_t MAX_HTTP_OUTPUT_BUFFER  = 1024*8;

// // This project was tested with the AI Thinker Model, M5STACK PSRAM Model and M5STACK WITHOUT PSRAM
// LLC_USING_TYPEINT();

// //GDEFINE_ENUM_TYPE (PIN_MODE, s0_t);
// //GDEFINE_ENUM_VALUE(PIN_MODE, Digital_In     , 0);
// //GDEFINE_ENUM_VALUE(PIN_MODE, Digital_Out    , 1);
// //GDEFINE_ENUM_VALUE(PIN_MODE, Analog_In      , 2);
// //GDEFINE_ENUM_VALUE(PIN_MODE, Analog_Out     , 3);   // only for GPIO25/26
// //GDEFINE_ENUM_VALUE(PIN_MODE, PWM_Out        , 4);   // for ledc
// //GDEFINE_ENUM_VALUE(PIN_MODE, Unused         , 0xFF);
// //
// //#pragma pack(push, 1)
// //struct SPinSetup {
// //    ::llc::vcst_t   Name = LLC_CXS("unassigned");
// //    PIN_MODE        Mode = PIN_MODE_Unused;
// //};
// //
// //struct SPinEventAnalog {
// //    u0_t            Pin = 0xFFU;
// //    u2_t            Old = {};
// //    u2_t            New = {};
// //    u3_t            Clk = {};
// //};
// //struct SPinEventDigital {
// //    u0_t            Pin = 0xFFU;
// //    u3_t            Old : 1;
// //    u3_t            New : 1;
// //    u3_t            Clk : 62;
// //};
// //#pragma pack(pop)
// //f8exry5gxrxhagq
// struct SKamApp : ::nlc::SNLCApp {

//     ::nlc::SCameraPinout                    Camera              = {};
//     s0_t                                    Alert               = 15;
//     s0_t                                    PIR                 = 12;
//     //s0_t                                    SonarTrigger        = 13;
//     //s0_t                                    SonarEcho           = 14;

//     //stxp s0_c                               PIN_COUNT           = 48;
//     //::llc::astatic<SPinSetup, PIN_COUNT>    PinConfig           = {{{},{},{},{},{},{},{},{},{},{},{},{},{"PIR", PIN_MODE_Digital_In},{"Alert", PIN_MODE_Digital_Out}}};
//     //::llc::astatic<s2_t     , PIN_COUNT>    PinStates           = {};
//     //::llc::apod<SPinEventAnalog>            PinEventsAnalog     = {};
//     //::llc::apod<SPinEventDigital>           PinEventsDigital    = {};
//     ::llc::vcst_t                           SSID                = LLC_CXS("Firewall");
//     ::llc::vcst_t                           PASS                = LLC_CXS("!1232MiaU2321!");

//     //int64_t                                 echo_start_time     = {};
//     //int64_t                                 echo_duration       = {};
//     //float                                   shared_distance_cm  = {};
//     //QueueHandle_t                           duration_queue      = {};
//     //SemaphoreHandle_t                       distance_mutex      = {};
//     //TaskHandle_t                            Tasktrigger         = {};
//     //TaskHandle_t                            Tasklogger          = {};
// };
// using nlc::vector, nlc::string, nlc::byte_array, nlc::char_array, nlc::byte_view, nlc::char_view, nlc::string_view, nlc::pobj;

// httpd_handle_t stream_httpd = {};

// #define fs_printlnf info_printf // do {} while(0) // 

// llc::err_t     listFiles               (nlc::string_view path, nlc::vector<nlc::string> & filenames) {
// #if !(defined(LLC_LINUX) || defined(LLC_ARDUINO))
//     aasc_t  files = {};
//     if_fail_fef(llc::pathList(path, files), "path:\"%s\".", path.begin());
//     for(const auto file : files) {
//         fs_printlnf("Found file: %s.", de->d_name);
//         if_fail_fe(filenames.push_back(file));
//     }
// #else // LLC_LINUX || LLC_ARDUINO
//     DIR             * dir;
//     if_null_fef(dir = opendir(path), "Failed to open directory '%s'.", path.begin());
//     while (true) {
//         struct dirent   * de;
//         if_null_bif(de = readdir(dir), "No more contents in dir: \"%s\"", path.begin());
//         const string_view   filename    = de->d_name;
//         if_fail_fe(filenames.push_back(filename));
//         fs_printlnf("Found file: %s.", de->d_name);
//     }
//     closedir(dir);
// #endif // !(LLC_LINUX || LLC_ARDUINO)
//     return 0;
// }
// static  nlc::err_t   spiffsPath  (string & fixed, string_view path) {
//     nlc::char_view trimmed;
//     nlc::ltrim(trimmed, path, "/ \t\n");
//     return append_strings(fixed, '/', trimmed);
// }
// #define PATH_CHECKS()                                       \
//     if_fail_fe(0 == _path.size());                          \
//     const char  * path              = _path;                \
//     string      _fixedSpiffsPath;                           \
//     if('/' != path[0]) {                                    \
//         if_fail_fe(::spiffsPath(_fixedSpiffsPath, _path));  \
//         path = _fixedSpiffsPath.begin();                    \
//     }
        
// u3_t     fileSize    (fs::FS & fs, string_view _path) {
//     PATH_CHECKS(); 
//     File		file	= fs.open(path);
//     if_fail_fef(!file, "%s", path);
//     return file.size();
// }
// llc::err_t     listFiles   (string_view path, vector<string> & filenames, const std::function<err_t(string_view)> & funcFilter) {
// #if !(defined(LLC_LINUX) || defined(LLC_ARDUINO))
//     aasc_t  files = {};
//     if_fail_fef(llc::pathList(path, files), "path:\"%s\".", path.begin());
//     for(const char_view filename : files) {
//         int result;
//         if_fail_fef(result = funcFilter(filename), "%s", filename.begin());
//         if(result) {
//             if_fail_fe(filenames.push_back(filename));
//             fs_printlnf("Found file: %s.", de->d_name);
//         }
//     }
// #else // LLC_LINUX || LLC_ARDUINO
//     DIR             * dir;
//     if_null_fef(dir = opendir(path), "Failed to open directory: \"%s\"", path.begin());
//     while (true) {
//         struct dirent   * de;
//         if_null_bif(de = readdir(dir), "No more contents in dir: \"%s\"", path.begin());
//         const string_view   filename    = de->d_name;
//         int result;
//         if_fail_fef(result = funcFilter(filename), "%s", filename.begin());
//         if(result) {
//             if_fail_fe(filenames.push_back(filename));
//             fs_printlnf("Found file: %s.", de->d_name);
//         }
//     }
//     closedir(dir);
// #endif // !(LLC_LINUX || LLC_ARDUINO)
//     return 0;
// }
// stxp llc::vcst_t CAMERA_FILE_EXTENSION   = LLC_CXS(".jpg");
// sttc esp_err_t handler_files(httpd_req_t *req){ 
// 	nlc::char_array output;
// 	if_fail_fe(append_strings(output, "<html><head><link rel=\"stylesheet\" href=\"/defaults.css\" /></head><body>" "<table>")); // abro html y body
//     llc::ESP_ERROR              res                     = {};
//     if_true_fef(res = (::llc::ESP_ERROR)httpd_resp_set_type(req, "text/html"), "%s", ::llc::get_value_namep(res));
//     if_true_fef(res = (::llc::ESP_ERROR)httpd_resp_send_chunk(req, output.begin(), output.size()), "%s", ::llc::get_value_namep(res));
//     output.clear();
// 	{
// 		nlc::vector<nlc::string> filenames;
// 		if_fail_fe(listFiles("/spiffs", filenames, [](string_view filename){ return nlc::endsWith(filename, CAMERA_FILE_EXTENSION); } )); // 
// 		for(string & path : filenames) {
// 			info_printf("Capture found: '%s'.", path.begin());
// 			if_fail_fe(append_strings(output, "<tr><td><a target=\"_blank\" href=\"/", path, "\">/", path, "(", llc::str((uint32_t)fileSize(SPIFFS, path)), ")</a></td></tr>"));
//             if_true_fef(res = (::llc::ESP_ERROR)httpd_resp_send_chunk(req, output.begin(), output.size()), "%s", ::llc::get_value_namep(res));
//             output.clear();
// 			path.clear_pointer();
// 		}
// 	}
// 	if_fail_fe(append_strings(output, "<tr style=\"height:100%;\"><td></td></tr>" "</table>" "</body></html>"));
//     if_true_fef(res = (::llc::ESP_ERROR)httpd_resp_send_chunk(req, output.begin(), output.size()), "%s", ::llc::get_value_namep(res));
//     return 0;
// }
// sttc esp_err_t handler_image(httpd_req_t *req) {
//     info_printf("GET: '%s'", req->uri);
//     nlc::string     filepath;
//     if_fail_fe(append_strings(filepath, req->uri));
//     info_printf("Serving file: '%s'", filepath.begin());
//     u2_t            byteCount;
//     if_zero_fef(byteCount = fileSize(SPIFFS, filepath), "%s", filepath.begin());
//     info_printf("File size: %u.", byteCount);
//     auto            file        = SPIFFS.open(filepath.begin(), FILE_READ, false);
//      llc::ESP_ERROR  res                     = {};
//     if_true_fef(res = (::llc::ESP_ERROR)httpd_resp_set_type(req, "image/jpeg"), "%s", ::llc::get_value_namep(res));
//     while(byteCount) {
//         stxp    u1_c    CHUNK_SIZE              = 1024;
//         u0_t    jpg_buf [CHUNK_SIZE]    = {};
//         u2_c            bytesToSend             = min(llc::size(jpg_buf), byteCount);
//         file.read(jpg_buf, bytesToSend);
//         if_true_fef(res = (::llc::ESP_ERROR)httpd_resp_send_chunk(req, (const char*)jpg_buf, bytesToSend), "%s", ::llc::get_value_namep(res));
//         byteCount -= bytesToSend;
//     }
//     if_true_fef(res = (::llc::ESP_ERROR)httpd_resp_set_hdr(req, "Connection", "close"), "%s", ::llc::get_value_namep(res));
//     if_true_fef(res = (::llc::ESP_ERROR)httpd_resp_send_chunk(req, NULL, 0), "%s", ::llc::get_value_namep(res));
//     return 0;
// }
// namespace nlc 
// {
//     GDEFINE_ENUM_TYPE(ESP_HTTP_EVENT, u0_t);
//     GDEFINE_ENUM_VALUE(ESP_HTTP_EVENT, ERROR         , HTTP_EVENT_ERROR         );      //       /*!< This event occurs when there are any errors during execution */
//     GDEFINE_ENUM_VALUE(ESP_HTTP_EVENT, ON_CONNECTED  , HTTP_EVENT_ON_CONNECTED  );        //*!< Once the HTTP has been connected to the server, no data exchange has been performed */
//     GDEFINE_ENUM_VALUE(ESP_HTTP_EVENT, HEADERS_SENT  , HTTP_EVENT_HEADERS_SENT  );        //*!< After sending all the headers to the server */
//     GDEFINE_ENUM_VALUE(ESP_HTTP_EVENT, HEADER_SENT   , HTTP_EVENT_HEADER_SENT   );        // /*!< This header has been kept for backward compatability and will be deprecated in future versions esp-idf */
//     GDEFINE_ENUM_VALUE(ESP_HTTP_EVENT, ON_HEADER     , HTTP_EVENT_ON_HEADER     );       //*!< Occurs when receiving each header sent from the server */
//     GDEFINE_ENUM_VALUE(ESP_HTTP_EVENT, ON_DATA       , HTTP_EVENT_ON_DATA       );         //*!< Occurs when receiving data from the server, possibly multiple portions of the packet */
//     GDEFINE_ENUM_VALUE(ESP_HTTP_EVENT, ON_FINISH     , HTTP_EVENT_ON_FINISH     );       //*!< Occurs when finish a HTTP session */
//     GDEFINE_ENUM_VALUE(ESP_HTTP_EVENT, DISCONNECTED  , HTTP_EVENT_DISCONNECTED  );        //*!< The connection has been disconnected */
// } // namespace
// esp_err_t _http_event_handler(esp_http_client_event_t *evt)
// {
//     static char *output_buffer  = 0;  // Buffer to store response of http request from event handler
//     static int output_len       = 0;       // Stores number of bytes read
//     info_printf("HTTP_EVENT:'%s'.", llc::get_value_namep((nlc::ESP_HTTP_EVENT)evt->event_id));
//     switch(evt->event_id) {
//     case HTTP_EVENT_ON_HEADER   : info_printf("key=%s, value=%s", evt->header_key, evt->header_value); break;
//         //case HTTP_EVENT_REDIRECT:
//         //    esp_http_client_set_header(evt->client, "From", "user@example.com");
//         //    esp_http_client_set_header(evt->client, "Accept", "text/html");
//         //    esp_http_client_set_redirection(evt->client);
//         //    break;
//     case HTTP_EVENT_ON_FINISH: ::llc::llc_safe_free(output_buffer); output_len = 0; break;
//     case HTTP_EVENT_DISCONNECTED: {
//         int mbedtls_err = 0;
//         esp_err_t err = esp_tls_get_and_clear_last_error((esp_tls_error_handle_t)evt->data, &mbedtls_err, NULL);
//         if (err != 0) {
//             info_printf("Last esp error code: 0x%x", err);
//             info_printf("Last mbedtls failure: 0x%x", mbedtls_err);
//         }
//         if (output_buffer != NULL) {
//             free(output_buffer);
//             output_buffer = NULL;
//         }
//         output_len = 0;
//     }
//         break;
//     case HTTP_EVENT_ON_DATA     : info_printf("HTTP_EVENT_ON_DATA, len=%d", evt->data_len);
//         // Clean the buffer in case of a new request
//         if (output_len == 0 && evt->user_data) { // we are just starting to copy the output data into the use
//             memset(evt->user_data, 0, MAX_HTTP_OUTPUT_BUFFER);
//         }
//         if (!esp_http_client_is_chunked_response(evt->client)) { // If user_data buffer is configured, copy the response into the buffer
//             int copy_len = 0;
//             if (evt->user_data) {
//                 // The last byte in evt->user_data is kept for the NULL character in case of out-of-bound access.
//                 copy_len = min(evt->data_len, (MAX_HTTP_OUTPUT_BUFFER - output_len));
//                 if (copy_len)
//                     memcpy((char*)evt->user_data + output_len, evt->data, copy_len);
//             } else {
//                 int content_len = esp_http_client_get_content_length(evt->client);
//                 if (output_buffer == NULL) {
//                     // We initialize output_buffer with 0 because it is used by strlen() and similar functions therefore should be null terminated.
//                     output_buffer = (char *) calloc(content_len + 1, sizeof(char));
//                     output_len = 0;
//                     if (output_buffer == NULL) {
//                         error_printf("Failed to allocate memory for output buffer");
//                         return ESP_FAIL;
//                     }
//                 }
//                 copy_len = min(evt->data_len, (content_len - output_len));
//                 if (copy_len)
//                     memcpy(output_buffer + output_len, evt->data, copy_len);
//             }
//             output_len += copy_len;
//         }

//         break;
//     }
//     return ESP_OK;
// }

// #define CONFIG_EXAMPLE_HTTP_ENDPOINT        "192.168.8.10"
// stxp const char         save_url    []          = "http://" CONFIG_EXAMPLE_HTTP_ENDPOINT "/cpp/gpk_cgi_file.exe";

// llc::err_t imagePost(const uint8_t * data, uint32_t length) {
//     llc::ESP_ERROR              res                     = {};
//     char local_response_buffer[MAX_HTTP_OUTPUT_BUFFER + 1] = {0};
//     esp_http_client_config_t config = {};
//     config.host = CONFIG_EXAMPLE_HTTP_ENDPOINT;
//     config.path = "/cpp/gpk_cgi_file.exe";
//     config.query = "esp";
//     config.event_handler = _http_event_handler;
//     config.user_data = local_response_buffer;
//     config.disable_auto_redirect = true;
//     config.buffer_size_tx   = 1024*8;
//     esp_http_client_handle_t client = esp_http_client_init(&config);

//     if_true_ef(res = (llc::ESP_ERROR)esp_http_client_set_url        (client, save_url), "%s", esp_err_to_name((esp_err_t)res))
//     if_true_ef(res = (llc::ESP_ERROR)esp_http_client_set_method     (client, HTTP_METHOD_POST), "%s", esp_err_to_name((esp_err_t)res))
//     if_true_ef(res = (llc::ESP_ERROR)esp_http_client_set_header     (client, "Content-Type", "image/jpeg"), "%s", esp_err_to_name((esp_err_t)res))
//     if_true_ef(res = (llc::ESP_ERROR)esp_http_client_set_post_field (client, (const char*)data, length), "%s", esp_err_to_name((esp_err_t)res))
//     if_true_ef(res = (llc::ESP_ERROR)esp_http_client_perform        (client), "HTTP POST request failed: %s", esp_err_to_name((esp_err_t)res))
//     else 
//         info_printf("HTTP POST Status = %d, content_length = %" PRId64
//             , esp_http_client_get_status_code(client)
//             , esp_http_client_get_content_length(client)
//             );
//     return res;
// }
// llc::error_t jpgSave(FS & fs, uint8_t * jpg_buf , size_t jpg_buf_len) {
//     char finame [128] = {};
//     llc::sprintf_s(finame, "/la_betty_criminal_at_%lli.jpg", llc::timeCurrent());
//     auto file = fs.open(finame, FILE_WRITE, true);
//     file.write(jpg_buf, jpg_buf_len);
//     return 0;
// }
// llc::error_t cameraCapture(SKamApp & app) {
//     camera_fb_t                 * fb;
//     if_null_fe(fb = esp_camera_fb_get());
//     size_t                      jpg_buf_len             = 0;
//     uint8_t                     * jpg_buf               = {};
//     if(fb->width > 400 && fb->format != PIXFORMAT_JPEG) {
//         if_zero_e(frame2jpg(fb, 80, &jpg_buf, &jpg_buf_len));
//     }
//     else {
//         jpg_buf_len    = fb->len;
//         jpg_buf        = fb->buf;
//     }
//     if(jpg_buf_len) {
//         if_fail_e(::jpgSave(SPIFFS, jpg_buf, jpg_buf_len));
//         //if_fail_e(::jpgSave(SD, jpg_buf, jpg_buf_len));
//         if_fail_e(::imagePost(jpg_buf, jpg_buf_len));
//     }
//     esp_camera_fb_return(fb);
//     return 0;
// }
// llc::error_t cameraStartAndCapture(SKamApp & app) {
//     if_fail_e(::cameraCapture(app));
//     //if_fail_fe(nlc::cameraShutdown(app.Camera));
//     return 0;
// }
// sttc esp_err_t handler_shoot(httpd_req_t *req){
//     SKamApp                     & app                   = *(SKamApp*)req->user_ctx;
//     if_fail_fe(::cameraStartAndCapture(app));
//     return 0;
// }
// sttc esp_err_t handler_clear(httpd_req_t *req){
//     SKamApp                     & app                   = *(SKamApp*)req->user_ctx;
//     nlc::vector<nlc::string> filenames;
//     if_fail_fe(listFiles("/spiffs", filenames, [](string_view filename){ return nlc::endsWith(filename, CAMERA_FILE_EXTENSION); } )); // 
//     for(nlc::string & path : filenames) {
//         nlc::string filename;
//         append_strings(filename, '/', path);
//         SPIFFS.remove(filename.begin());
//     }
    
//     return 0;
// }
// llc::err_t startCameraServer(SKamApp & app){
//     httpd_config_t          config      = HTTPD_DEFAULT_CONFIG();
//     config.server_port  = 6789;
//     config.stack_size   = 1024 * 16; 
//     config.uri_match_fn = httpd_uri_match_wildcard;
//     info_printf("Starting web server on port: '%i'", config.server_port);
//     ::llc::ESP_ERROR        result;
//     if_true_fef(result = (::llc::ESP_ERROR)httpd_start(&stream_httpd, &config), "%s", ::llc::get_value_namep(result));

//     httpd_uri_t             files_uri   = {"/files"     , HTTP_GET, handler_files, &app};
//     httpd_uri_t             shoot_uri   = {"/shoot"     , HTTP_GET, handler_shoot, &app};
//     httpd_uri_t             clear_uri   = {"/clear"     , HTTP_GET, handler_clear, &app};
//     httpd_uri_t             image_uri   = {"/*"         , HTTP_GET, handler_image, &app};
//     if_true_fef(result = (::llc::ESP_ERROR)httpd_register_uri_handler(stream_httpd, &files_uri), "%s", ::llc::get_value_namep(result));
//     if_true_fef(result = (::llc::ESP_ERROR)httpd_register_uri_handler(stream_httpd, &shoot_uri), "%s", ::llc::get_value_namep(result));
//     if_true_fef(result = (::llc::ESP_ERROR)httpd_register_uri_handler(stream_httpd, &clear_uri), "%s", ::llc::get_value_namep(result));
//     if_true_fef(result = (::llc::ESP_ERROR)httpd_register_uri_handler(stream_httpd, &image_uri), "%s", ::llc::get_value_namep(result));
//     return 0;
// }

// sttc SKamApp g_app = {}; 

// llc::err_t setupWiFi(SKamApp & app) {
//     if_zero_w(WiFi.config(IPAddress(192,168,8,20), IPAddress(192,168,8,1), IPAddress(255,255,255,0)));
//     //if_zero_w(WiFi.softAPConfig(IPAddress(192,168,20,1), IPAddress(192,168,20,1), IPAddress(255,255,255,0)));
//     if_zero_w(WiFi.begin(app.SSID.begin(), app.PASS.begin()));
//     //if_zero_w(WiFi.softAP("AYE", app.PASS.begin()));
//     if_zero_w(WiFi.config(IPAddress(192,168,8,20), IPAddress(192,168,8,1), IPAddress(255,255,255,0)));
//     //if_zero_w(WiFi.softAPConfig(IPAddress(192,168,20,1), IPAddress(192,168,20,1), IPAddress(255,255,255,0)));
//     if_zero_w(WiFi.isConnected());
//     return 0;
// }

// //static llc::err_t spiffsInit() {
// //    esp_vfs_spiffs_conf_t conf = {"/spiffs", 0, 5, true};
// //    if_true_e(esp_vfs_spiffs_register(&conf));
// //    return 0;
// //}
// //#define MOUNT_POINT "/sdcard"
// //#define EXAMPLE_IS_UHS1    (CONFIG_EXAMPLE_SDMMC_SPEED_UHS_I_SDR50 || CONFIG_EXAMPLE_SDMMC_SPEED_UHS_I_DDR50)
// //stxp u0_c CONFIG_EXAMPLE_PIN_CLK = 14;
// //stxp u0_c CONFIG_EXAMPLE_PIN_CMD = 15;
// //stxp u0_c CONFIG_EXAMPLE_PIN_D0  = 2;
// //stxp u0_c CONFIG_EXAMPLE_PIN_D1  = 4;
// //stxp u0_c CONFIG_EXAMPLE_PIN_D2  = 12;
// //stxp u0_c CONFIG_EXAMPLE_PIN_D3  = 13;

// //static llc::err_t sdcardInit() {
// //
// //    esp_vfs_fat_sdmmc_mount_config_t mount_config = {};
// //    mount_config.max_files = 5;
// //    const char mount_point[] = MOUNT_POINT;
// //    sdmmc_host_t host = SDMMC_HOST_DEFAULT();
// //#if CONFIG_EXAMPLE_SDMMC_SPEED_HS
// //    host.max_freq_khz = SDMMC_FREQ_HIGHSPEED;
// //#endif
// //    sdmmc_slot_config_t slot_config = SDMMC_SLOT_CONFIG_DEFAULT();      // This initializes the slot without card detect (CD) and write protect (WP) signals. Modify slot_config.gpio_cd and slot_config.gpio_wp if your board has these signals.
// //    slot_config.width = 4;
// //    // On chips where the GPIOs used for SD card can be configured, set them in the slot_config structure:
// //    slot_config.clk = (gpio_num_t)CONFIG_EXAMPLE_PIN_CLK;
// //    slot_config.cmd = (gpio_num_t)CONFIG_EXAMPLE_PIN_CMD;
// //    slot_config.d0  = (gpio_num_t)CONFIG_EXAMPLE_PIN_D0;
// //    slot_config.d1  = (gpio_num_t)CONFIG_EXAMPLE_PIN_D1;
// //    slot_config.d2  = (gpio_num_t)CONFIG_EXAMPLE_PIN_D2;
// //    slot_config.d3  = (gpio_num_t)CONFIG_EXAMPLE_PIN_D3;
// //    slot_config.flags |= SDMMC_SLOT_FLAG_INTERNAL_PULLUP;    // Enable internal pullups on enabled pins. The internal pullups are insufficient however, please make sure 10k external pullups areconnected on the bus. This is for debug / example purpose only.
// //    sdmmc_card_t *card = {};
// //    esp_err_t ret = esp_vfs_fat_sdmmc_mount(mount_point, &host, &slot_config, &mount_config, &card);
// //    if (ret) {
// //        if (ret == ESP_FAIL)
// //            ESP_LOGE(TAG, "Failed to mount filesystem. If you want the card to be formatted, set the EXAMPLE_FORMAT_IF_MOUNT_FAILED menuconfig option.");
// //        else
// //            ESP_LOGE(TAG, "Failed to initialize the card (%s). Make sure SD card lines have pull-up resistors in place.", esp_err_to_name(ret));
// //        return -1;
// //    }
// //    sdmmc_card_print_info(stdout, card);
// //    return 0;
// //}

// void setup() {
//     SKamApp & app = g_app;
//     //WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0); //disable brownout detector
// 	nlc::evalResetCause(g_app, g_app.BootInfo.ResetCause, g_app.BootInfo.AwakeCause, g_app.BootInfo.WakeupPins);
//     if_zero_e(SPIFFS.begin());

// //    if_fail_e(::sdcardInit());
    
//     if_fail_e(nlc::pirSetup(app.PIR));
//     //Serial.setDebugOutput(false);
//     if_fail_e(::setupWiFi(app));
//     if_fail_e(startCameraServer(app));
//     if_fail_e(nlc::cameraSetup(app.Camera));

//     //gpio_set_direction  ((gpio_num_t)app.SonarTrigger, GPIO_MODE_OUTPUT);
//     //gpio_set_level      ((gpio_num_t)app.SonarTrigger, 0);
//     // Configure echo pin
//     //gpio_set_direction((gpio_num_t)app.SonarEcho, GPIO_MODE_INPUT);
//     //gpio_set_intr_type((gpio_num_t)app.SonarEcho, GPIO_INTR_ANYEDGE);
//     //gpio_install_isr_service(0);
//     //gpio_isr_handler_add((gpio_num_t)app.SonarEcho, echo_isr_handler, &app);
//     //if_null_e(app.duration_queue  = xQueueCreate(10, sizeof(int64_t)));
//     //if_null_e(app.distance_mutex  = xSemaphoreCreateBinary());
//     //
//     //// Launch tasks
//     //xTaskCreate(trigger_task, "trigger_task", 2048, &app, 10, &app.Tasktrigger);
//     //xTaskCreate(logger_task , "logger_task" , 4096, &app,  9, &app.Tasklogger );
// }

// void loop() {
//     SKamApp & app = g_app;

//     static llc::u2_t i = 0;
//     if(0 == (i % 1000000LLU)) {
//         info_printf("STA %s", WiFi.isConnected() ? "Connected" : "Disconnected");
//         if(WiFi.isConnected())
//             info_printf("%s", WiFi.localIP().toString().begin());
//         //info_printf("%s", WiFi.softAPIP().toString().begin());
//         LLC_PLATFORM_CRT_CHECK_MEMORY();
//     }
//     ++i;

//     bool captureCamera = nlc::pirState(app.PIR);
//     //{
//     //    xSemaphoreTake(app.distance_mutex, portMAX_DELAY);
//     //    const float localCopy = app.shared_distance_cm;
//     //    xSemaphoreGive(app.distance_mutex);
//     //    captureCamera |= localCopy < 400;
//     //}
//     if(captureCamera) {
//         if_fail_e(cameraStartAndCapture(app));
//         digitalWrite(app.Alert, captureCamera);
//     }
// }

// #endif // LLC_ESP32