/*
    Class definition for a Magic: The Gathering card
*/
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <list>
#include <memory>

#ifndef MTG_CARD_HPP
#define MTG_CARD_HPP

class Card {
public:
    Card() {
        std::multiset<char> m{};
        m.insert('g');
        std::pair<std::vector<std::string>, std::vector<std::string>> t{};
        std::vector<std::string> t1{};
        t1.push_back("creature");
        std::vector<std::string> t2{};
        t1.push_back("cat");
        t = std::make_pair(t1, t2);
        std::set<std::string> k{};
        k.insert("first strike");
        name = "test card";
        manacost = m;
        typeline = t;
        keywords = k;
    }
    Card(std::string n, std::multiset<char> m, std::pair<std::vector<std::string>, std::vector<std::string>> t, std::set<std::string> k) : name{ n }, manacost{ m }, typeline{ t }, keywords{ k } {
    }
    //     Card(const Card& other): Card{}{

    //     }
    virtual std::string get_name() const = 0;
    virtual std::multiset<char> get_manacost() const = 0;
    virtual std::vector<std::string> get_type() const = 0;
    virtual std::vector<std::string> get_subtype() const = 0;
    virtual std::set<std::string> get_keywords() const = 0;

    using CardPtr = std::shared_ptr<Card>;
    friend CardPtr parse_card(std::string const& input_line);

private:
protected:
    std::string name;
    std::multiset<char> manacost;
    std::pair<std::vector<std::string>, std::vector<std::string>> typeline;
    std::set<std::string> keywords;
};

class Permanent : public Card {
public:
    Permanent(std::string n, std::multiset<char> m, std::pair<std::vector<std::string>, std::vector<std::string>> ty, std::set<std::string> k, int p, int t) :
        Card{ n,m,ty,k }, power{ p }, toughness{ t } {
        //if (keywords.contains("is_token")) {
        //    is_token = true;
        //}
    }
    Permanent() : Card{}, power{ 1 }, toughness{ 1 } {
        //if (keywords.contains("is_token")) {
        //    is_token = true;
        //}
    }
    /*Permanent(std::string n,std::string m,std::string ty,std::string k, int p, int t){
        std::multiset<char> tempmana {};
        Card{n,
        if(keywords.contains("is_token")){
            is_token = true;
        }
    }*/
    virtual std::string get_name() const override {
        return name;
    };
    virtual std::multiset<char> get_manacost() const override {
        return manacost;
    };
    virtual std::vector<std::string> get_type() const override {
        return typeline.first;
    };
    virtual std::vector<std::string> get_subtype() const override {
        return typeline.second;
    };
    virtual std::set<std::string> get_keywords() const override {
        return keywords;
    };
    virtual int get_power() const {
        return power;
    };
    virtual int get_toughness() const {
        return toughness;
    };
private:
protected:
    int power;
    int toughness;
    bool is_token{ false };
};

class Non_Permanent : public Card {
public:
    Non_Permanent(std::string n, std::multiset<char> m, std::pair<std::vector<std::string>, std::vector<std::string>> t, std::set<std::string> k) : Card{ n,m,t,k } {
    }
    virtual std::string get_name() const override {
        return name;
    };
    virtual std::multiset<char> get_manacost() const override {
        return manacost;
    };
    virtual std::vector<std::string> get_type() const override {
        return typeline.first;
    };
    virtual std::vector<std::string> get_subtype() const override {
        return typeline.second;
    };
    virtual std::set<std::string> get_keywords() const override {
        return keywords;
    };
private:
protected:
};

#endif