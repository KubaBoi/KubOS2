#include <gui/desktop.h>

using namespace kubos;
using namespace kubos::common;
using namespace kubos::gui;

Desktop::Desktop(int32_t w, int32_t h, int8_t r, int8_t g, int8_t b) 
: CompositeWidget(0,0,0,w,h,r,g,b),
MouseEventHandler() {
    MouseX = w/2;
    MouseY = h/2;
}

Desktop::~Desktop() {

}

void Desktop::Draw(GraphicsContext* gc) {
    CompositeWidget::Draw(gc);

    //cursor
    for (int i = 0; i < 4; i++) {
        gc->PutPixel(MouseX-i, MouseY, 0xFF, 0xFF, 0xFF);
        gc->PutPixel(MouseX+i, MouseY, 0xFF, 0xFF, 0xFF);
        gc->PutPixel(MouseX, MouseY-i, 0xFF, 0xFF, 0xFF);
        gc->PutPixel(MouseX, MouseY+i, 0xFF, 0xFF, 0xFF);
    }
}

void Desktop::OnMouseDown(uint8_t button) {
    CompositeWidget::OnMouseDown(MouseX, MouseY, button);
}

void Desktop::OnMouseUp(uint8_t button) {
    CompositeWidget::OnMouseUp(MouseX, MouseY, button);
}

void Desktop::OnMouseMove(int x, int y) {
    x /= 4; //slowing mouse
    y /= 4;

    int32_t newMouseX = MouseX + x; 
    int32_t newMouseY = MouseY + y;

    if (newMouseX < 0) newMouseX = 0;
    if (newMouseX >= w) newMouseX = w - 1;

    if (newMouseY < 0) newMouseY = 0;
    if (newMouseY >= h) newMouseY = h - 1;

    CompositeWidget::OnMouseMove(MouseX, MouseY, newMouseX, newMouseY);

    MouseX = newMouseX;
    MouseY = newMouseY;
}