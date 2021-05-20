
#ifndef __KUBOS__DRIVERS__MOUSE_H
#define __KUBOS__DRIVERS__MOUSE_H

#include <common/types.h>
#include <hardwarecommunication/port.h>
#include <drivers/driver.h>
#include <hardwarecommunication/interrupts.h>

namespace kubos
{
    namespace drivers
    {
    
        class MouseEventHandler
        {
        public:
            MouseEventHandler();

            virtual void OnActivate();
            virtual void OnMouseDown(kubos::common::uint8_t button);
            virtual void OnMouseUp(kubos::common::uint8_t button);
            virtual void OnMouseMove(int x, int y);
        };
        
        
        class MouseDriver : public kubos::hardwarecommunication::InterruptHandler, public Driver
        {
            kubos::hardwarecommunication::Port8Bit dataport;
            kubos::hardwarecommunication::Port8Bit commandport;
            kubos::common::uint8_t buffer[3];
            kubos::common::uint8_t offset;
            kubos::common::uint8_t buttons;

            MouseEventHandler* handler;
        public:
            MouseDriver(kubos::hardwarecommunication::InterruptManager* manager, MouseEventHandler* handler);
            ~MouseDriver();
            virtual kubos::common::uint32_t HandleInterrupt(kubos::common::uint32_t esp);
            virtual void Activate();
        };

    }
}
    
#endif
