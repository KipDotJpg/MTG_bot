/*
    A bot to play Magic: The Gathering against. WIP
*/
// #include <iostream>
// #include <string>
// #include <vector>
// #include <algorithm>
// #include <random>
#include "card.hpp"
#include "deck.hpp"

using CardPtr = std::shared_ptr<Card>;

int main(int argc, char** argv) {
    std::cout << "do i get here?" << std::endl;
    if (argc < 2) {
        std::cout << "Usage: ./MTG_bot input_filename" << std::endl;
        return 1;
    }
    std::string input_filename{ argv[1] };

    Deck my_deck{ read_decklist(input_filename) };

    // Permanent Island {"Island",std::multiset<char> {}, std::pair<std::vector<std::string>,std::vector<std::string>> {}, std::set<std::string> {}, -1, -1};
    // CardPtr CardPointer = std::make_shared<Permanent>(Island);
    // my_deck.add_card_top(CardPointer);

    for (auto x : my_deck.get_decklist()) {
        std::cout << x->get_name() << std::endl;
    }

    return 0;
}