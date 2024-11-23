#pragma once

#include <string>
#include "modules/hyprland/IPC.hpp"

namespace zdhpctl::modules::hyprland {
    class Language {
        public:
        static auto getCurrentLocaleCode() -> std::string;

        private:
        struct Layout {
            std::string full_name;
            std::string short_name;
            std::string variant;
            std::string description;
        };

        static auto getLayout(const std::string&) -> Layout;

        Layout layout_;
    };
}