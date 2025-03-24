#include <stdint.h>
#include <stdbool.h>

#define MSG_START 0x02
#define MSG_END   0x03
#define MAX_BUFFER_SIZE 128
#define MAX_PAYLOAD_SIZE 64

volatile uint8_t message_buffer[MAX_BUFFER_SIZE];
volatile uint8_t message_index = 0;
volatile bool message_ready = false;
volatile bool receiving_message = false;

uint8_t UART_Read(void) {
    return 0;
}

void UART_ISR(void) {
    uint8_t data = UART_Read();
    if (!receiving_message) {
        if (data == MSG_START) {
            receiving_message = true;
            message_index = 0;
            message_buffer[message_index++] = data;
        }
    } else {
        message_buffer[message_index++] = data;
        if (data == MSG_END || message_index >= MAX_BUFFER_SIZE) {
            message_ready = true;
            receiving_message = false;
        }
    }
}

uint8_t calculate_checksum(uint8_t *data, uint8_t length) {
    uint8_t sum = 0;
    for (uint8_t i = 0; i < length; i++) {
        sum += data[i];
    }
    return sum;
}

void parse_message(void) {
    if (!message_ready)
        return;
    if (message_buffer[0] != MSG_START || message_buffer[message_index - 1] != MSG_END) {
        message_ready = false;
        return;
    }
    if (message_index < 5) {
        message_ready = false;
        return;
    }
    uint8_t command = message_buffer[1];
    uint8_t payload_length = message_buffer[2];
    if (payload_length != message_index - 5) {
        message_ready = false;
        return;
    }
    uint8_t checksum_received = message_buffer[3 + payload_length];
    uint8_t checksum_calculated = calculate_checksum((uint8_t *)&message_buffer[1], payload_length + 2);
    if (checksum_received != checksum_calculated) {
        message_ready = false;
        return;
    }
    int8_t *payload = (int8_t *)&message_buffer[3];
    switch(command) {
        case 0x10:
            break;
        case 0x20:
            break;
        default:
            break;
    }
    message_ready = false;
}

int main(void) {
    while (1) {
        if (message_ready) {
            parse_message();
        }
    }
    return 0;
}
