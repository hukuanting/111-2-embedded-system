/*
For the first demo of freeRTOS in AI Thinker ESP32-cam
switching two task by schedular

the following function will be used:
 - TaskHandle_t xTaskCreat(...);
 - void vTaskDelay( const TickType_t xTicksToDelay );

Read the document below to find more info
 - https://www.freertos.org/xTaskCreateStatic.html
 - https://www.freertos.org/a00127.html

*/

 #define DELAY_MILLIS(x) ((x) / portTICK_PERIOD_MS)

void task_A(void *arg){
  while(1){
    Serial.println("A");
    vTaskDelay(DELAY_MILLIS(300));
  }
}

void task_B(void *arg){
  while(1){
    Serial.println("B");
    vTaskDelay(DELAY_MILLIS(400));
  }
}

void setup() {
  Serial.begin(9600);
  void (*task_ptr)(void*) = task_A;
  xTaskCreate(task_ptr, "A", 1000, NULL, 1, NULL);
  task_ptr = task_B;
  xTaskCreate(task_ptr, "B", 1000, NULL, 1, NULL);
}

void loop() {
  Serial.println("in loop");
  vTaskDelay(DELAY_MILLIS(500));
}