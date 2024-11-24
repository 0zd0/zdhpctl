#include <xkbcommon/xkbregistry.h>

#include "modules/hyprland/language.hpp"
#include "modules/hyprland/extract.hpp"

namespace zdhpctl::modules::hyprland {
    auto Language::getCurrentLocaleCode() -> std::string {
        if (!gIPC) {
            gIPC = std::make_unique<IPC>();
        }

        const std::string inputDevices = gIPC->getSocket1Reply("devices");
        const std::string activeKeymap = extractActiveKeymap(inputDevices);

        if (Layout layout = getLayout(activeKeymap); !layout.full_name.empty()) {
            return layout.short_name;
        }

        return "";
    }
    auto Language::getLayout(const std::string& fullName) -> Layout {
        auto* const context = rxkb_context_new(RXKB_CONTEXT_LOAD_EXOTIC_RULES);
        rxkb_context_parse_default_ruleset(context);

        rxkb_layout* layout = rxkb_layout_first(context);
        while (layout != nullptr) {
            std::string nameOfLayout = rxkb_layout_get_description(layout);

            if (nameOfLayout != fullName) {
                layout = rxkb_layout_next(layout);
                continue;
            }

            const auto name = std::string(rxkb_layout_get_name(layout));
            const auto* variantPtr = rxkb_layout_get_variant(layout);
            const std::string variant = variantPtr == nullptr ? "" : std::string(variantPtr);

            const auto* descriptionPtr = rxkb_layout_get_brief(layout);
            const std::string description = descriptionPtr == nullptr ? "" : std::string(descriptionPtr);

            rxkb_context_unref(context);

            return Layout{nameOfLayout, name, variant, description};
        }

        rxkb_context_unref(context);

        std::cerr << "Layout not found\n";
        return Layout{"", "", "", ""};
    }

}