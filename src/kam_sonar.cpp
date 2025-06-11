
// // Store the result to file
// static llc::err_t save_distance_to_file(float distance) {
//     FILE    * f;
//     if_null_fe(f = fopen("/spiffs/distance.txt", "a"));
//     fprintf(f, "CM%.2fAT%llu\n", distance, ::llc::timeCurrent());
//     fclose(f);
//     info_printf("Saved distance: %.2f cm", distance);
//     return 0;
// }

// // Interrupt handler for ECHO_PIN
// static void IRAM_ATTR echo_isr_handler(void* arg) {
//     SKamApp & app = *(SKamApp*)arg;
//     if (gpio_get_level((gpio_num_t)app.SonarEcho)) // Rising edge - start timer
//         app.echo_start_time = esp_timer_get_time();
//     else { // Falling edge - stop timer
//         app.echo_duration        = esp_timer_get_time() - app.echo_start_time;
//         BaseType_t  xHigherPriorityTaskWoken    = pdFALSE;
//         xQueueSendFromISR(app.duration_queue, &app.echo_duration, &xHigherPriorityTaskWoken);
//         if (xHigherPriorityTaskWoken)
//             portYIELD_FROM_ISR();
//     }
// }

// // Trigger the ultrasonic pulse
// void trigger_sensor(gpio_num_t pinTrigger) {
//     gpio_set_level(pinTrigger, 0);
//     ets_delay_us(2);
//     gpio_set_level(pinTrigger, 1);
//     ets_delay_us(10);
//     gpio_set_level(pinTrigger, 0);
// }

// void trigger_task(void *arg) {
//     SKamApp & app = *(SKamApp*)arg;
//     while (1) {
//         ::trigger_sensor((gpio_num_t)app.SonarTrigger);
//         vTaskDelay(pdMS_TO_TICKS(100));  // Trigger every 100ms
//     }
// }

// void logger_task(void *arg) {
//     SKamApp & app = *(SKamApp*)arg;
//     while (1) {
//         int64_t duration;
//         if (xQueueReceive(app.duration_queue, &duration, portMAX_DELAY)) {
//             const float distance_cm = duration / 58.0; // Convert to cm
//             cw_if (distance_cm < 0 && distance_cm >= 400);
//             save_distance_to_file(distance_cm);
//             xSemaphoreTake(app.distance_mutex, portMAX_DELAY);
//             app.shared_distance_cm = distance_cm;
//             xSemaphoreGive(app.distance_mutex);
//         }
//     }
// }
