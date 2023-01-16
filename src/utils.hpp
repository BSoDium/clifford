#ifndef CLIFFORD_UTILS_HPP
#define CLIFFORD_UTILS_HPP

#include <string>
#include <vector>

std::vector<std::string> mergeStringTokens(std::vector<std::string> tokens) {
  for (int i = 0; i < tokens.size(); i++)
  {
    if (tokens[i].front() == '"' && tokens[i].back() != '"')
    {
      tokens[i].erase(0, 1);
      while (i + 1 < tokens.size() && tokens[i + 1].back() != '"')
      {
        tokens[i] += " " + tokens[i + 1];
        tokens.erase(tokens.begin() + i + 1);
      }
      tokens[i] += " " + tokens[i + 1];
      tokens[i].erase(tokens[i].size() - 1, 1);
      tokens.erase(tokens.begin() + i + 1);
    } else if (tokens[i].front() == '"' && tokens[i].back() == '"')
    {
      tokens[i].erase(0, 1);
      tokens[i].erase(tokens[i].size() - 1, 1);
    }
  }
  return tokens;
}

#endif // CLIFFORD_UTILS_HPP