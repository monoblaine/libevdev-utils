/*
 * CREDITS: https://suricrasia.online/blog/turning-a-keyboard-into/
 */
#include <libevdev/libevdev.h>
#include <libevdev/libevdev-uinput.h>
#include <iostream>
#include <signal.h>

struct libevdev_uinput* m_uinput = nullptr;

void signal_handler (sig_atomic_t s) {
    libevdev_uinput_destroy(m_uinput);
    exit(0);
}

// g++ create_virtual_mouse.cpp -o create_virtual_mouse `pkg-config --cflags --libs libevdev`
int main () {
    struct libevdev* dev = libevdev_new();
    libevdev_set_name(dev, "Virtual Mouse");
    libevdev_enable_property(dev, INPUT_PROP_POINTER);
    libevdev_enable_event_type(dev, EV_REL);
    libevdev_enable_event_code(dev, EV_REL, REL_X, nullptr);
    libevdev_enable_event_code(dev, EV_REL, REL_Y, nullptr);
    libevdev_enable_event_code(dev, EV_REL, REL_WHEEL, nullptr);
    libevdev_enable_event_code(dev, EV_REL, REL_WHEEL_HI_RES, nullptr);
    libevdev_enable_event_code(dev, EV_REL, REL_HWHEEL, nullptr);
    libevdev_enable_event_code(dev, EV_REL, REL_HWHEEL_HI_RES, nullptr);
    libevdev_enable_event_type(dev, EV_KEY);
    libevdev_enable_event_code(dev, EV_KEY, BTN_LEFT, nullptr);
    libevdev_enable_event_code(dev, EV_KEY, BTN_RIGHT, nullptr);
    libevdev_enable_event_code(dev, EV_KEY, BTN_MIDDLE, nullptr);
    int deviceCreateStatus = libevdev_uinput_create_from_device(dev, LIBEVDEV_UINPUT_OPEN_MANAGED, &m_uinput);
    if (deviceCreateStatus != 0) {
        std::cerr << "libevdev_uinput_create_from_device failed!" << std::endl;
    }
    libevdev_free(dev);
    signal(SIGINT, signal_handler);
    pause();
    return 0;
}
