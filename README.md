# `create_virtual_mouse.cpp`

This code is used to create a virtual mouse with both vertical and horizontal wheels.

Together with [`libinput`](https://freedesktop.org/wiki/Software/libinput/), [`xf86-input-libinput`](https://gitlab.freedesktop.org/xorg/driver/xf86-input-libinput) and [the patch that adds the ability to adjust scroll distance](https://gitlab.freedesktop.org/xorg/driver/xf86-input-libinput/-/merge_requests/12), you will finally have the incredible-and-almost-impossible power to adjust scroll distance on Linux. (The `libinput Scroll Distance Scale` setting)

All credits go to [@blackle](https://github.com/blackle/) and their amazing and very detailed tutorial on https://suricrasia.online/blog/turning-a-keyboard-into/, it helped so much.

# `get_virtual_mouse_path.cpp`

This code is used to find the device path (`/dev/input/eventX`) of the virtual mouse we created on the previous step.

You can use a [AutoKey](https://github.com/autokey/autokey) script to trigger vertical/horizontal scroll events from the keyboard:

```py
pathToVirtualMouse = system.exec_command("sudo /get_virtual_mouse_path")
# scroll up
system.exec_command(f"sudo evemu-event {pathToVirtualMouse} --type EV_REL --code REL_WHEEL_HI_RES --value 120 --sync")
# sroll down
system.exec_command(f"sudo evemu-event {pathToVirtualMouse} --type EV_REL --code REL_WHEEL_HI_RES --value -120 --sync")
# scroll left
system.exec_command(f"sudo evemu-event {pathToVirtualMouse} --type EV_REL --code REL_HWHEEL_HI_RES --value -120 --sync")
# scroll right
system.exec_command(f"sudo evemu-event {pathToVirtualMouse} --type EV_REL --code REL_HWHEEL_HI_RES --value 120 --sync")
```
