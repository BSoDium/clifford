#ifndef CLI_HPP
#define CLI_HPP

#define RED(x) "\033[31m" << x << "\033[0m"
#define GREEN(x) "\033[32m" << x << "\033[0m"
#define YELLOW(x) "\033[33m" << x << "\033[0m"
#define BLUE(x) "\033[34m" << x << "\033[0m"
#define MAGENTA(x) "\033[35m" << x << "\033[0m"
#define CYAN(x) "\033[36m" << x << "\033[0m"
#define WHITE(x) "\033[37m" << x << "\033[0m"

#define APP_NAME "CLIfford"
#define APP_DESCRIPTION "A generic command line interface for C++ applications."
#define AUTHOR "BSoDium"
#define YEAR "2022"

#include <iostream>
#include <sstream>
#include <iterator>
#include <functional>
#include <vector>
#include <optional>

namespace core
{

  class CLI;

  struct CLICommandArgument
  {
    std::string name;
    std::string description;
    bool required;
  };

  struct CLICommand
  {
    std::string name;
    std::string description;
    std::vector<CLICommandArgument> arguments;
    std::function<void(CLI *, std::vector<std::string>)> action;
  };

  enum CLIStatus
  {
    RUNNING = 1,
    STOPPED = 0
  };

  struct UserInput
  {
    std::string command;
    std::vector<std::string> arguments;
    bool run = false;
    bool success = false;
  };

  /**
   * @brief A generic command line interface.
   */
  class CLI
  {
  private:
    std::string _name;
    std::string _description;
    std::string _author;
    std::string _year;

  protected:
    std::vector<CLICommand> _commands;
    std::vector<UserInput> _history;
    CLIStatus _status = CLIStatus::STOPPED;

    void _addCommand(std::string name, std::string description, std::function<void(CLI *)> action);
    void _addCommand(std::string name, std::string description, std::function<void(CLI *, std::vector<std::string>)> action);
    void _printCommands();
    void _printHistory();
    void _printHelp();
    void _printAbout();
    void _printSplash();
    void _printPrompt();

  public:
    CLI(std::string name = APP_NAME, std::string description = APP_DESCRIPTION, std::string author = AUTHOR, std::string year = YEAR);
    void run();
    void exit();
    void printError(std::string message);
  };
}

#endif // CLI_HPP