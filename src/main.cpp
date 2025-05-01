#include "llc_log.h"
#include "LittleFS.h"

//llc::error_t spiffs_init() {
//    info_printf("Initializing SPIFFS");
//    
//    esp_vfs_spiffs_conf_t         conf  = {};
//    conf.base_path              = "/spiffs";
//    conf.partition_label        = {};
//    conf.max_files              = 5;
//    conf.format_if_mount_failed = true;
//
//    esp_err_t ret;  // Use settings defined above to initialize and mount SPIFFS filesystem. Note: esp_vfs_spiffs_register is an all-in-one convenience function.
//    if_true_fef(ret = esp_vfs_spiffs_register(&conf), "Failed to initialize SPIFFS (%s)", esp_err_to_name(ret));
//
//    size_t total = 0, used = 0;
//    if_true_fef(ret = esp_spiffs_info(NULL, &total, &used), "Failed to get SPIFFS partition information (%s)", esp_err_to_name(ret));
//    info_printf("Partition size: total: %d, used: %d", total, used);
//    return 0;
//}
//
struct STempApp {
  
};

void setup() { 
    Serial.begin(115200);  
    if_zero_e(LittleFS.begin());
    //llc::error_t result;
    //if_fail_e(result = spiffs_init());
}

void loop() { 
}
