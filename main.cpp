#include <wayland-client.h>
#include <xkbcommon/xkbcommon.h>
#include <iostream>

int main() {
    struct wl_display* display = wl_display_connect(nullptr);
    if (!display) {
        std::cerr << "Failed to connect to Wayland display." << std::endl;
        return -1;
    }
    std::cout << "Connected to Wayland display." << std::endl;
    wl_display_disconnect(display);
    return 0;
}
