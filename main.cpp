#include <iostream>
#include <string>
#include <modules/hyprland/language.hpp>

namespace zdhpctl {
    class Command {
    public:
        virtual ~Command() = default;
        virtual void execute(const std::vector<std::string>& args) = 0;
        virtual std::string getHelp() const = 0;
    };

    class ActiveLocaleCommand final : public Command {
    public:
        void execute(const std::vector<std::string>& args) override {
            std::cout << modules::hyprland::Language::getCurrentLocaleCode() << std::endl;
        }

        std::string getHelp() const override {
            return "activelocale - shows the current locale code";
        }
    };

    class CommandRegistry {
    public:
        static CommandRegistry& getInstance() {
            static CommandRegistry instance;
            return instance;
        }

        void registerCommand(const std::string& name, std::unique_ptr<Command> command) {
            commands[name] = std::move(command);
        }

        bool executeCommand(const std::string& name, const std::vector<std::string>& args) {
            if (const auto it = commands.find(name); it != commands.end()) {
                it->second->execute(args);
                return true;
            }
            return false;
        }

        void showHelp() {
            std::cout << "Available commands:\n";
            for (const auto& [name, command] : commands) {
                std::cout << command->getHelp() << "\n";
            }
        }

    private:
        std::map<std::string, std::unique_ptr<Command>> commands;
        CommandRegistry() = default;
    };
}

int main(const int argc, char* argv[]) {
    auto& registry = zdhpctl::CommandRegistry::getInstance();

    registry.registerCommand("activelocale",
        std::make_unique<zdhpctl::ActiveLocaleCommand>());

    if (argc < 2) {
        registry.showHelp();
        return 1;
    }

    const std::string command = argv[1];

    if (const std::vector<std::string> args(argv + 2, argv + argc); !registry.executeCommand(command, args)) {
        std::cout << "Unknown command: " << command << "\n";
        registry.showHelp();
        return 1;
    }

    return 0;
}
