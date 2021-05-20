#ifndef __KUBOS__GDT_H
#define __KUBOS__GDT_H

#include <common/types.h>

namespace kubos
{
    
    class GlobalDescriptorTable
    {
        public:

            class SegmentDescriptor
            {
                private:
                    kubos::common::uint16_t limit_lo;
                    kubos::common::uint16_t base_lo;
                    kubos::common::uint8_t base_hi;
                    kubos::common::uint8_t type;
                    kubos::common::uint8_t limit_hi;
                    kubos::common::uint8_t base_vhi;

                public:
                    SegmentDescriptor(kubos::common::uint32_t base, kubos::common::uint32_t limit, kubos::common::uint8_t type);
                    kubos::common::uint32_t Base();
                    kubos::common::uint32_t Limit();
            } __attribute__((packed));

        private:
            SegmentDescriptor nullSegmentSelector;
            SegmentDescriptor unusedSegmentSelector;
            SegmentDescriptor codeSegmentSelector;
            SegmentDescriptor dataSegmentSelector;

        public:

            GlobalDescriptorTable();
            ~GlobalDescriptorTable();

            kubos::common::uint16_t CodeSegmentSelector();
            kubos::common::uint16_t DataSegmentSelector();
    };

}
    
#endif