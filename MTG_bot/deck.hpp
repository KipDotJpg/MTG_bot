/*
    Class definition for a Magic: The Gathering deck
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <fstream>
#include <stdexcept>

#ifndef MTG_DECK_HPP
#define MTG_DECK_HPP

using CardPtr = std::shared_ptr<Card>;

class Deck {
public:
    Deck(const std::vector<CardPtr>& d) : decklist{ d } {
    }
    Deck() : decklist{} {
    }
    void shuffle() {
        std::random_device rd {};
        std::default_random_engine rng {rd()};
        std::shuffle(std::begin(decklist), std::end(decklist), rng);
        return;
    }
    CardPtr draw() {
        CardPtr D{ decklist.back() };
        decklist.pop_back();
        return D;
    }
    void add_card_top(CardPtr C) {
        decklist.push_back(C);
        return;
    }
    void add_card_bottom(CardPtr C) {
        decklist.insert(decklist.begin(), C);
        return;
    }
    //template<typename search_id>
    Deck const search(std::string name) {
        Deck search_return{};
        for (auto c : decklist) {
            if (c->get_name() == name) {
                search_return.add_card_top(c);
            }
        }
        return search_return;
    }
    std::vector<CardPtr> get_decklist() {
        return decklist;
    }
private:
    std::vector<CardPtr> decklist;
};

unsigned int check_fields(std::string const& input_line) {
    int fields{ 1 };
    for (auto& current_character : input_line) {
        if (current_character == ',') {
            fields++;
        }
    }
    return fields;
}

CardPtr parse_card(std::string const& input_line) {
    Permanent card_true{};
    CardPtr card = std::make_shared<Permanent>(card_true);
    int empty{ -1 };
    unsigned int section{ 1 };
    int index{ 0 };
    int check{ 0 };
    char manatype{};
    // if(check_fields(input_line) != 5){
    //     throw IncompleteLineException {check_fields(input_line)};
    // }
    auto iter{ input_line.begin() };
    for (auto& current_character : input_line) {
        if (current_character == ',') {
            section++;
        }
        else {
            switch (section) {
            case 1: {
                if (stoi(input_line.substr(index, input_line.find(',', index))) > 1) {
                    std::string temp{ input_line };
                    temp.at(0) = (stoi(input_line.substr(index, input_line.find(',', index))) - 1) + '0';
                    parse_card(temp);
                }
                break;
            }
            case 2: {
                card->name.push_back(current_character);
                break;
            }
            case 3: {
                if(check == 0){
                    std::string temp{ input_line.substr(index,input_line.find(',',index)-index)};
                    std::vector<std::string> types{};
                    std::vector<std::string> subtypes{};
                    types.push_back(temp);
                    card->typeline = std::make_pair(types, subtypes);
                    check = 1;
                }
                break;
            }
            case 4: {
                check = 0;
                //nothing
                break;
            }
            case 5: {
                if (check == 0) {
                    manatype = 'b';
                    check = 1;
                }
                break;
            }
            case 6: {
                int num{ stoi(input_line.substr(index,input_line.find(',',index))) };
                while (num > 0) {
                    card->manacost.insert(manatype);
                    num--;
                }
                break;
            }
            }
        }
        index++;
    }
    return card;
}

Deck read_decklist(std::string const& input_filename) {
    Deck decklist{};
    std::ifstream input_file{};
    input_file.open(input_filename);

    int valid_cards{ 0 };
    int total_lines{ 0 };

    if (input_file.is_open()) {

        std::string line{};
        while (std::getline(input_file, line)) {
            total_lines++;
            //try{
            CardPtr c{ parse_card(line) };
            valid_cards++;
            decklist.add_card_top(c);
            // }catch( IncompleteLineException& e ){
            //     std::cout << "Line " << total_lines << " is invalid: ";
            //     std::cout << e.num_fields << " fields found." << std::endl;
            // }catch( EmptyFieldException& e ){
            //     std::cout << "Line " << total_lines << " is invalid: "; 
            //     std::cout << "Field " << e.which_field << " is empty." << std::endl;
            // }catch( NonNumericDataException& e ){
            //     std::cout << "Line " << total_lines << " is invalid: ";
            //     std::cout << "\"" << e.bad_field << "\" is non-numeric." << std::endl;
            // }catch( InvalidTimeException& e ){
            //     std::cout << "Line " << total_lines << " is invalid: ";
            //     std::cout << e.bad_time.hour << ":" << e.bad_time.minute << " is not a valid time." << std::endl;
            // }
        }
        input_file.close();

    }
    else {
        throw std::runtime_error{ "Unable to open input file" };
    }
    int invalid_decklist{ total_lines - valid_cards };
    std::cout << "Read " << valid_cards << " valid cards." << std::endl;
    std::cout << "Skipped " << invalid_decklist << " invalid cards." << std::endl;
    return decklist;
}

#endif