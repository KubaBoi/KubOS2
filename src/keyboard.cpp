#include "keyboard.h"

void printf(char* str);

KeyboardDriver::KeyboardDriver(InterruptManager* manager)
: InterruptHandler(0x21, manager),
dataPort(0x60),
commandPort(0x64) {
    while (commandPort.Read() & 0x1) {
        dataPort.Read();
    }

    commandPort.Write(0xAE); //activate interrupts
    commandPort.Write(0x20); //get current state
    uint8_t status = (dataPort.Read() | 1) & ~0x10;
    commandPort.Write(0x60); //set state
    dataPort.Write(status);  

    dataPort.Write(0xF4);
}

KeyboardDriver::~KeyboardDriver() {

}

uint32_t KeyboardDriver::HandleInterrupt(uint32_t esp) {
    uint8_t key = dataPort.Read();

    if (key < 0x80) { //only key pressed (not released)

        switch (key) {
            case 0xFA: break;
            case 0x45: case 0xC5: break;

            case 0x1E: printf("a"); break;
            case 0x1F: printf("s"); break;
            case 0x20: printf("d"); break;

            default:
                char* foo = "\nKEYBOARD 0x00";
                char* hex = "0123456789ABCDEF";
                foo[11] = hex[(key >> 4) & 0x0F];
                foo[12] = hex[(key & 0x0F)];
                printf(foo);
                break;
        }
    }
    
    return esp;
}