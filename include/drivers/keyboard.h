
#ifndef __KUBOS__DRIVERS__KEYBOARD_H
#define __KUBOS__DRIVERS__KEYBOARD_H

#include <common/types.h>
#include <hardwarecommunication/interrupts.h>
#include <drivers/driver.h>
#include <hardwarecommunication/port.h>

namespace kubos
{
    namespace drivers
    {
    
        class KeyboardEventHandler
        {
        public:
            KeyboardEventHandler();

            virtual void OnKeyDown(char);
            virtual void OnKeyUp(char);
        };
        
        class KeyboardDriver : public kubos::hardwarecommunication::InterruptHandler, public Driver
        {
            kubos::hardwarecommunication::Port8Bit dataport;
            kubos::hardwarecommunication::Port8Bit commandport;
            
            KeyboardEventHandler* handler;
        public:
            KeyboardDriver(kubos::hardwarecommunication::InterruptManager* manager, KeyboardEventHandler *handler);
            ~KeyboardDriver();
            virtual kubos::common::uint32_t HandleInterrupt(kubos::common::uint32_t esp);
            virtual void Activate();
        };

    }
}
    
#endif