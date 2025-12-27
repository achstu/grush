#include "map.hpp"
#include "process.hpp"
#include <chrono>
#include <format>
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char *argv[]) {

  int players = argc - 1;
  std::vector<ChildProcess> childs;

  for (int p = 0; p < players; p++) {
    std::string command = argv[p + 1];
    if (command.ends_with(".py")) {
      command = "python3 " + command;
    }

    childs.emplace_back(command);
  }

  Grush grush;
  std::cout << grush.to_string() << std::endl;
  exit(0);

  for (int p = 0; p < players; p++) {
    ChildProcess &bot = childs[p];

    bot.write(std::format("{} {}\n{}\n", N, ITER, players));
    bot.write(grush.players[p].base.to_string() + "\n");

    for (int i = 0; i < players; i++) {
      if (i == p)
        continue;
      bot.write(grush.players[i].base.to_string() + "\n");
    }
  }

  for (int it = 0; it < ITER; it++) {

    grush.update_vision();

    for (int p = 0; p < players; p++) {

      // measure time
      auto start = std::chrono::high_resolution_clock::now();

      ChildProcess &bot = childs[p];

      bot.write(std::format("{}\n", grush.players[p].agents.size()));
      for (auto& agent : grush.players[p].agents) {
        bot.write(agent.describe() + "\n");
      }

      for (auto& agent : grush.players[p].agents) {
        agent.action = parse(bot.readline());
      }
      
      auto end = std::chrono::high_resolution_clock::now();
      auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

      std::cout << std::format("player {} on iter {}: {}ms\n", p, it, duration.count());

      grush.update({});
      
    }
  }
}
