// Project UID 1d9f47bfc76643019cfbf037641defe1

#include <iostream>
#include <string>
#include "Player.h"
#include <algorithm>
#include <vector>
#include <cassert>
using namespace std;

class SimplePlayer : public Player {
private:
    string name;
    vector<Card> hand;
    int hand_size;
public:
    SimplePlayer(string name) {
        this->name = name;
        hand_size = 0;
    }

    const std::string& get_name() const override {
        return name;
    }

    void add_card(const Card& c) override {
        assert(hand_size <= 5);
        hand.push_back(c);
        hand_size++;
    }

    //they have two or more trump face cards in their hand.
    //Trump face cards are the right and left bowers, and Q, K, A of the trump suit,
    // which is the suit proposed by the upcard.
    bool make_trump(const Card& upcard, bool is_dealer,
        int round, std::string& order_up_suit) const override
    {
        assert(round == 1 || round == 2);
        int count = 0;
        if (round == 1) {
            for (int i = 0; i < hand_size; i++) {
                if ((hand[i].is_face() && hand[i].get_suit() == upcard.get_suit()) ||
                    hand[i].is_left_bower(upcard.get_suit()) ||
                    hand[i].is_right_bower(upcard.get_suit())) {
                    count++;
                }
                if (count >= 2) {
                    order_up_suit = upcard.get_suit();
                    return true;
                }
            }
        }
        else {
            string next = Suit_next(upcard.get_suit());
            if (is_dealer) {
                order_up_suit = next;
                return true;
            }

            for (int i = 0; i < hand_size; i++) {
                if ((hand[i].is_face() && hand[i].get_suit() == next) ||
                    hand[i].is_left_bower(next) ||
                    hand[i].is_right_bower(next)) {
                    count++;
                    order_up_suit = next;
                    return true;
                }
            }
        }

        return false;
    }

    void add_and_discard(const Card& upcard) override {
        assert(hand_size > 0);
        int min_index = 0;
        Card min = hand[0];
        for (int i = 1; i < hand_size; i++) {
            if (Card_less(hand[i], min, upcard.get_suit())) {
                min = hand[i];
                min_index = i;
            }
        }
        if (Card_less(hand[min_index], upcard, upcard.get_suit())) {
            hand[min_index] = upcard;
        }
    }

    //When a Simple Player leads a trick,
    //they play the highest non-trump card in their hand.
    //If they have only trump cards,
    //they play the highest trump card in their hand.
    Card lead_card(const std::string& trump) override {
        assert(hand_size > 0);
        sort(hand.begin(), hand.end());//ascending order
        Card leadingCard;
        for (int i = hand_size - 1; i >= 0; i--) {
            if (hand[i].get_suit(trump) != trump) {
                leadingCard = hand[i];
                hand.erase(hand.begin() + i);
                hand_size--;
                return leadingCard;
            }
        }

        //only have trump cards then leading with highest trump card
        Card max = hand[0];
        int max_index = 0;
        for (int i = 0; i < hand_size; i++) {
            if (Card_less(max, hand[i], trump)) {
                max = hand[i];
                max_index = i;
            }
        }
        hand.erase(hand.begin() + max_index);
        hand_size--;
        return max;
    }

    Card play_card(const Card& led_card, const std::string& trump) override {
        assert(hand_size > 0);
        //If a Simple Player can follow suit, they play the highest card that follows suit
        Card max;
        int max_index = -1; // to find the highest card that follows suit

        Card min_consiering_trump = hand[0];
        int min_considering_trump_index = 0;

        for (int i = 0; i < hand_size; i++) {
            if (hand[i].get_suit(trump) == led_card.get_suit(trump)) {
                if (max_index == -1) {
                    max = hand[i];
                    max_index = i;
                }
                if (Card_less(max, hand[i], trump)) {
                    max = hand[i];
                    max_index = i;
                }
            }

            if (Card_less(hand[i], min_consiering_trump, trump)) {
                min_consiering_trump = hand[i];
                min_considering_trump_index = i;
            }
        }

        if (max_index != -1) // there exists the suit that follows the led suit
        {
            hand.erase(hand.begin() + max_index);
            hand_size--;
            return max;
        }
        else {//consider trump to pick the minimum card
            //cannot find the suit that follows the led suit.
            //so return the min
            hand.erase(hand.begin() + min_considering_trump_index);
            hand_size--;
            return min_consiering_trump;
        }
    }
};

class HumanPlayer : public Player {
private:
    string name;
    vector<Card> hand;
    int hand_size;
    void print_hand() const {
        for (int i = 0; i < hand_size; i++) {
            cout << "Human player " << name <<
                "'s hand: [" << i << "] " << hand[i] << endl;
        }
    }
public:
    HumanPlayer(string name) {
        this->name = name;
        hand_size = 0;
    }

    const std::string& get_name() const override {
        return name;
    }

    void add_card(const Card& c) override {
        assert(hand_size <= 5);
        hand.push_back(c);
        hand_size++;
    }

    bool make_trump(const Card& upcard, bool is_dealer,
        int round, std::string& order_up_suit) const override {
        assert(round == 1 || round == 2);
        vector<Card> copyHand = hand;
        sort(copyHand.begin(), copyHand.end());

        for (int i = 0; i < hand_size; i++) {
            cout << "Human player " << name <<
                "'s hand: [" << i << "] " << copyHand[i] << endl;
        }
        cout << "Human player " << name <<
            ", please enter a suit, or \"pass\":" << endl;
        string user_input;
        cin >> user_input;
        if (user_input == "pass") {
            // cout << name << " passes" << endl;
            return false;
        }
        else {
            order_up_suit = user_input;
            // cout << name << " orders up " << order_up_suit << endl;
            return true;
        }
    }

    void add_and_discard(const Card& upcard) override {
        assert(hand_size > 0);
        sort(hand.begin(), hand.end());
        print_hand();
        cout << "Discard upcard: [-1]" << endl;
        cout << "Human player " << name <<
            ", please select a card to discard:" << endl;
        int discard_index;
        cin >> discard_index;

        if (discard_index == -1) return;
        else {
            hand[discard_index] = upcard;
        }
    }

    Card lead_card(const std::string& trump) override {
        assert(hand_size > 0);
        sort(hand.begin(), hand.end());
        print_hand();
        cout << "Human player " << name <<
            ", please select a card:" << endl;
        int leading_card_index;
        cin >> leading_card_index;
        Card leadingCard = hand[leading_card_index];
        hand.erase(hand.begin() + leading_card_index);
        hand_size--;
        //Jack of Diamonds led by Judea
        // cout << leadingCard << " led by " << name << endl;
        return leadingCard;
    }

    Card play_card(const Card& led_card, const std::string& trump) override {
        assert(hand_size > 0);
        sort(hand.begin(), hand.end());
        print_hand();
        cout << "Human player " << name <<
            ", please select a card:" << endl;
        int playing_card_index;
        cin >> playing_card_index;
        Card playingCard = hand[playing_card_index];
        hand.erase(hand.begin() + playing_card_index);
        hand_size--;
        //Nine of Spades played by Kunle
        // cout << playingCard << " played by " << name << endl;
        return playingCard;
    }

};

Player* Player_factory(const std::string& name, const std::string& strategy)
{
    // We need to check the value of strategy and return
    // the corresponding player type.
    if (strategy == "Simple") {
        // The "new" keyword dynamically allocates an object.
        return new SimplePlayer(name);
    }
    else if (strategy == "Human") {
        return new HumanPlayer(name);
    }
    // Repeat for each other type of Player

    // Invalid strategy if we get here
    return nullptr;
}

std::ostream& operator<<(std::ostream& os, const Player& p)
{
    os << p.get_name();
    return os;
}
