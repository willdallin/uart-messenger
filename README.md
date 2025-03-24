# uart-messenger

# UART Messenger

This project implements a generic UART communication protocol for a microcontroller. The application handles asynchronous data reception using interrupts, ensuring that each message is properly delimited, validated, and parsed. It is designed to process various commands and payloads, including both positive and negative values.

## Table of Contents
- [Features](#features)
- [How to Compile and Run](#how-to-compile-and-run)
- [Usage Examples](#usage-examples)
- [Future Improvements](#future-improvements)

## Features

- **Interrupt Driven Communication:** Uses UART interrupts to receive data byte-by-byte.
- **Message Delimitation:** Employs designated start and end bytes to mark the boundaries of each message.
- **Checksum Validation:** Implements a simple checksum to ensure data integrity.
- **Flexible Parsing:** A generic parser that can handle multiple commands with varying payloads.
- **Platform Agnostic:** Can be adapted for various microcontrollers and frameworks (e.g., Arduino, ESP32).

## How to Compile and Run

### Requirements
- A C compiler (e.g., GCC)
- A microcontroller platform or simulation environment with UART support
- Proper configuration of the UART interrupt in your target system

### Compilation

Compile the project using the following command:

```bash
gcc -Iinclude main.c -o uart_messenger
```

### Execution
```bash
./uart_messenger
```
Note: The actual UART functionality and interrupts require deployment on a microcontroller. For simulation or testing, ensure you have an appropriate UART setup or a dummy implementation.

## Usage Examples

### Interrupt-Driven Data Reception

- **Start of Message Detection:** The application waits for the start byte (`0x02`), which signals the beginning of a new message.
- **Byte-by-Byte Storage:** Each received byte is stored in a buffer until the end byte (`0x03`) is detected.
- **Validation and Parsing:** After the complete message is received, the parser validates the structure and checksum, then processes the command accordingly.

### Custom Command Processing

- **Command 0x10:** Configurable to perform a specific task.
- **Command 0x20:** Configurable for an alternative task.
- **Extensible Design:** New commands can be added by modifying the parser function to suit application needs.