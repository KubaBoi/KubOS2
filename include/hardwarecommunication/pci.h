#ifndef __KUBOS__HARDWARECOMMUNICATION__PCI_H
#define __KUBOS__HARDWARECOMMUNICATION__PCI_H

#include <common/types.h>
#include <hardwarecommunication/port.h>
#include <hardwarecommunication/interrupts.h>
#include <drivers/driver.h>

namespace kubos {
    namespace hardwarecommunication {

        class PeripheralComponentInterconnectDeviceDescriptor {
            public:
                common::uint32_t portBase;
                common::uint32_t interrupt;

                common::uint16_t bus;
                common::uint16_t device;
                common::uint16_t function;

                common::uint16_t vendor_id;
                common::uint16_t device_id;
                
                common::uint8_t class_id;
                common::uint8_t subclass_id;
                common::uint8_t interface_id;

                common::uint8_t revision;

                PeripheralComponentInterconnectDeviceDescriptor();
                ~PeripheralComponentInterconnectDeviceDescriptor();
        };

        class PeripheralComponentInterconnectController {
                Port32Bit dataPort;
                Port32Bit commandPort;
                

            public:
                PeripheralComponentInterconnectController();
                ~PeripheralComponentInterconnectController();

                common::uint32_t Read(common::uint16_t bus, common::uint16_t device, common::uint16_t function, common::uint32_t registeroffset);
                void Write(common::uint16_t bus, common::uint16_t device, common::uint16_t function, common::uint32_t registeroffset, common::uint32_t value);
                bool DeviceHasFunctions(common::uint16_t bus, common::uint16_t device);

                void SelectDrivers(kubos::drivers::DriverManager* driverManager);
                PeripheralComponentInterconnectDeviceDescriptor GetDeviceDescriptor(common::uint16_t bus, common::uint16_t device, common::uint16_t function);
        };  
    }
}

#endif
