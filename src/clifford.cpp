#include "../include/clifford.hpp"

namespace core
{

  CLI::CLI(std::string name, std::string description, std::string author, std::string year)
  {
    _name = name;
    _description = description;
    _author = author;
    _year = year;

    _addCommand("help", "Prints this help message.", [this](CLI *cli)
                { cli->_printHelp(); });
    _addCommand("about", "Prints information about this program.", [this](CLI *cli)
                { cli->_printAbout(); });
    _addCommand("commands", "Prints a list of available commands.", [this](CLI *cli)
                { cli->_printCommands(); });
    _addCommand("history", "Prints a list of previously entered commands.", [this](CLI *cli)
                { cli->_printHistory(); });
    _addCommand("exit", "Exits the program.", [this](CLI *cli)
                { cli->exit(); });
    _addCommand("splash", "Prints the splash screen.", [this](CLI *cli)
                { cli->_printSplash(); });
  }

  void CLI::_addCommand(std::string name, std::string description, std::function<void(CLI *)> action)
  {
    _addCommand(name, description, [action](CLI *cli, std::vector<std::string> args)
                { action(cli); });
  }

  void CLI::_addCommand(std::string name, std::string description, std::function<void(CLI *, std::vector<std::string>)> action)
  {
    CLICommand command;
    command.name = name;
    command.description = description;
    command.action = action;
    _commands.push_back(command);
  }

  void CLI::_printCommands()
  {
    std::cout << "Available commands:" << std::endl;
    for (auto command : _commands)
    {
      std::cout << "  " << BLUE(command.name) << " - " << command.description << std::endl;
    }
  }

  void CLI::_printHistory()
  {
    std::cout << "Command history:" << std::endl;
    for (auto input : _history)
    {
      std::cout << "  " << input.command;
      for (auto argument : input.arguments)
      {
        std::cout << " " << argument;
      }
      std::cout << std::endl;
    }
  }

  void CLI::_printHelp()
  {
    std::cout << "This is a generic command line interface." << std::endl;
    std::cout << "It can be used to run commands and keep a history of them." << std::endl;
    std::cout << "Type 'commands' to see a list of available commands." << std::endl;
  }

  void CLI::_printAbout()
  {
    std::cout << "This program was written by " << _author << " in " << _year << "." << std::endl;
  }

  void CLI::_printSplash()
  {
    std::cout << std::endl;
    std::cout << BLUE(" ▄████████   ▄█        ▄█     ▄████████    ▄████████  ▄██████▄     ▄████████ ████████▄  ") << std::endl;
    std::cout << BLUE(" ███    ███ ███       ███    ███    ███   ███    ███ ███    ███   ███    ███ ███   ▀███ ") << std::endl;
    std::cout << BLUE(" ███    █▀  ███       ███▌   ███    █▀    ███    █▀  ███    ███   ███    ███ ███    ███ ") << std::endl;
    std::cout << BLUE(" ███        ███       ███▌  ▄███▄▄▄      ▄███▄▄▄     ███    ███  ▄███▄▄▄▄██▀ ███    ███ ") << std::endl;
    std::cout << BLUE(" ███        ███       ███▌ ▀▀███▀▀▀     ▀▀███▀▀▀     ███    ███ ▀▀███▀▀▀▀▀   ███    ███ ") << std::endl;
    std::cout << BLUE(" ███    █▄  ███       ███    ███          ███        ███    ███ ▀███████████ ███    ███ ") << std::endl;
    std::cout << BLUE(" ███    ███ ███▌    ▄ ███    ███          ███        ███    ███   ███    ███ ███   ▄███ ") << std::endl;
    std::cout << BLUE(" ████████▀  █████▄▄██ █▀     ███          ███         ▀██████▀    ███    ███ ████████▀  ") << std::endl;
    std::cout << BLUE("           ▀                                                     ███    ███             ") << std::endl;
    std::cout << std::endl;

    std::cout << "Welcome to " << GREEN(_name) << "!" << std::endl;
    std::cout << _description << std::endl;
  }

  void CLI::_printPrompt()
  {
    std::cout << GREEN(_name) << "> ";
  }

  void CLI::printError(std::string message)
  {
    std::cerr << RED("Error: " << message) << std::endl;
  }

  void CLI::run()
  {
    _status = CLIStatus::RUNNING;
    while (_status)
    {
      _printPrompt();
      std::string input;
      std::getline(std::cin, input);
      std::istringstream iss(input);
      std::vector<std::string> tokens{std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{}};
      if (tokens.size() > 0)
      {
        UserInput userInput;
        userInput.command = tokens[0];
        for (int i = 1; i < tokens.size(); i++)
        {
          userInput.arguments.push_back(tokens[i]);
        }
        for (auto command : _commands)
        {
          if (command.name == userInput.command)
          {
            try
            {
              command.action(this, userInput.arguments);
              userInput.success = true;
            }
            catch (std::exception &e)
            {
              printError(e.what());
            }
            userInput.run = true;
            break;
          }
        }
        _history.push_back(userInput);
        if (!userInput.run)
        {
          printError("Unknown command '" + userInput.command + "'.");
        }
      }
    }
  }

  void CLI::exit()
  {
    _status = CLIStatus::STOPPED;
  }
}