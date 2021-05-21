#ifndef __KUBOS__GUI__DESKTOP_H
#define __KUBOS__GUI__DESKTOP_H

#include <gui/widget.h>
#include <drivers/mouse.h>

namespace kubos {
    namespace gui {
        class Desktop : public CompositeWidget, public kubos::drivers::MouseEventHandler {
        protected:
            common::uint32_t MouseX;
            common::uint32_t MouseY;

        public:
            Desktop(common::int32_t w, common::int32_t h, common::int8_t r, common::int8_t g, common::int8_t b);
            ~Desktop();

            void Draw(common::GraphicsContext* gc);

            void OnMouseDown(common::uint8_t button);
            void OnMouseUp(common::uint8_t button);
            void OnMouseMove(int x, int y);
        };
    }
} 



#endif