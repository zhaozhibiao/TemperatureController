#include <stdio.h>
#include <stdint.h>

// Mock FreeRTOS Task creation
void vTaskSafety(void *pvParameters) { while(1) {} }
void vTaskProfinet(void *pvParameters) { while(1) {} }
void vTaskADC(void *pvParameters) { while(1) {} }
void vTaskPID(void *pvParameters) { while(1) {} }

int main(void) {
    printf("Temperature Controller Booting...\n");
    // System Init
    // Task Creation (Mock)
    printf("RTOS Started.\n");
    return 0;
}
