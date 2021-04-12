#include "RotaryEncoder_Adapter.h"

void RotaryEncoder_Read();
void RotaryEncoder_Process();

esp_err_t RotaryEncoder_get_command(uint8_t val){
    uint16_t data = 0;
    switch (val)
    {
    case 0:
        /* idle*/
        break;
    case 1:
        /* draaien */
        RotaryEncoder_get_diff(&data);
        if(data > 0 && data < 1000)
        commands.right();
        else commands.left();
        break;
    case 2:
        /* button press */
        break;
    case 3:
        /* press + draaien */
        break;
    case 4:
        /* press release */
        commands.press();
        break;
    case 5:
        /* press release + draaien */
        break;
    default:
    ESP_LOGE("Rotary", "HOW DID YOU GET HERE!");
        break;
    }
    return ESP_OK;
}

esp_err_t RotaryEncoder_get_diff(uint16_t *val){

    RotaryEncoder_port_read16(&dev,5,val);
    RotaryEncoder_port_write16(&dev,5,0);
    return ESP_OK;
}

esp_err_t RotaryEncoder_AdapterInit(commands_t void_Function_Calls){
    RotaryEncoder_init(&dev,0,0x3F,SDA_GPIO,SCL_GPIO);
    commands = void_Function_Calls;
    rotaryQueue = xQueueCreate(queueSize, itemSize);

    xTaskCreate(RotaryEncoder_Read, "Rotary_read_task", configMINIMAL_STACK_SIZE * 5, NULL, 5, NULL);
    xTaskCreate(RotaryEncoder_Process, "Rotary_process_task", configMINIMAL_STACK_SIZE * 5, NULL, 5, NULL);
    return ESP_OK;
}

esp_err_t RotaryEncoder_AdapterFree(){
    RotaryEncoder_free(&dev);
    return ESP_OK;
}

void RotaryEncoder_Read() {
    uint8_t val = 0;

    while (1) {
        RotaryEncoder_port_read(&dev,STAT,&val);
        RotaryEncoder_port_write(&dev,STAT,0);

        if (val > 0) {
            xQueueSend(rotaryQueue, &val, 20);
            vTaskDelay(250 / portTICK_PERIOD_MS); //timout to prevent too many duplicates.
        }

        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}

void RotaryEncoder_Process() {
    while (1) {
        if (uxQueueMessagesWaiting(rotaryQueue) > 0) {
            uint8_t buffer = 0;
            if(xQueueReceive(rotaryQueue, &buffer, 0)) {
                RotaryEncoder_get_command(buffer);
            }
        }
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}



