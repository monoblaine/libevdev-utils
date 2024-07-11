/*
 * CREDITS: https://suricrasia.online/blog/turning-a-keyboard-into/
 */
#include <libevdev/libevdev.h>
#include <libevdev/libevdev-uinput.h>
#include <iostream>
#include <unistd.h>
#include <fcntl.h>

// g++ get_virtual_mouse_path.cpp -o get_virtual_mouse_path `pkg-config --cflags --libs libevdev`
int main () {
    const std::string deviceName = "Virtual Mouse";
    struct libevdev *dev = nullptr;
    for (int i = 0;; i++) {
        std::string path = "/dev/input/event" + std::to_string(i);
        int fd = open(path.c_str(), O_RDONLY);
        if (fd == -1) {
            break; // no more character devices
        }
        if (libevdev_new_from_fd(fd, &dev) == 0) {
            std::string name = libevdev_get_name(dev);
            libevdev_free(dev);
            dev = nullptr;
            if (name == deviceName) {
                close(fd);
                std::cout << path << std::endl;
                return 0;
            }
        }
        close(fd);
    }
    return -1;
}
