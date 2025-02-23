/*
For the second demo of freeRTOS in AI Thinker ESP32-cam
This demo will trigger task watchdog, which will reset the whole process.
Please set your CPU frequency to the highest level: Arduino IDE -> Tools -> CPU frequency

requirement I:
1. Explain the event and solve the problem

requirement II:
1. Every 3 seconds, let the task B pause for 3 seconds
2. You should use task handler to suspend or resume the task

requirement III:
1. Analyze the maximum memory usage of two task
2. Observe what will happend if the stack size lower than the maximum memory usage of two task?

the following function or data structure will be used:
 - TaskHandle_t
 - uxTaskGetStackHighWaterMark()
 - vTaskSuspend()
 - vTaskResume()

Read the document below to find more info
 - https://www.freertos.org/a00019.html
 - https://www.freertos.org/uxTaskGetStackHighWaterMark.html
 - https://www.freertos.org/a00112.html
*/



#define DELAY_MILLIS(x) ((x) / portTICK_PERIOD_MS)

TaskHandle_t handler_A;
TaskHandle_t handler_B;
uint32_t stack_size = 1000;

// requirement II
int start_time;
int curr_time;
bool task_B_is_running = true;

void setup() {
  Serial.begin(9600);
  start_time = millis();
  xTaskCreate(task_A, "A", stack_size, NULL, 1, &handler_A);
  xTaskCreate(task_B, "B", stack_size, NULL, 2, &handler_B);
  // requirement III
  Serial.printf("Analyze the maximum memory usage of two task... \n");
  uint32_t m = stack_size - uxTaskGetStackHighWaterMark(handler_A);
  uint32_t m2 = stack_size - uxTaskGetStackHighWaterMark(handler_B);
  vTaskSuspend(handler_A);
  vTaskSuspend(handler_B);
  Serial.printf("Task A: %u bytes\n", m);
  Serial.printf("Task B: %u bytes\n", m2);
  delay(5000);
  vTaskResume(handler_A);
  vTaskResume(handler_B);
}

void loop() {
  // requirement II
  curr_time = millis();
  if(curr_time - start_time > 3000){
    task_B_is_running = !task_B_is_running;
    if(task_B_is_running){
      vTaskSuspend(handler_B);
    }else{
      vTaskResume(handler_B);
    }
    start_time = curr_time;
  }
  vTaskDelay(DELAY_MILLIS(1000));
}

void task_A(void *arg){
  while(1){
    printf("it is for task A turn\n");
    // requirement I
    vTaskDelay(DELAY_MILLIS(500));
  }
}

void task_B(void *arg){
  while(1){
    printf("B task occupies the queue\n");
    // requirement I
    vTaskDelay(DELAY_MILLIS(100));
  }
}
