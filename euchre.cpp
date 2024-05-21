// Project UID 1d9f47bfc76643019cfbf037641defe1

#include <iostream>
#include <string>
#include <fstream>
#include <cassert>
#include "Player.h"
#include "Pack.h"
#include "Card.h"
using namespace std;

bool checkArgs(int point, string shuffle, Player* players[]) {
    if (!(1 <= point && point <= 100)) return false;
    if (!(shuffle == "shuffle" || shuffle == "noshuffle")) return false;
    for (int i = 0; i < 4; i++) {
        if (players[i] == nullptr) {
            return false;
        }
    }
    return true;
}

class Game {
private:
    Pack pack;
    Player* players[4];
    string isShuffle;
    int score02;
    int score13;
    int set;
    int dealerIndex;
    int pointToWinGame;
public:
    Game(std::istream& packFile, Player* players[4], int pointToWin, string shuffle)
        : pack(packFile), isShuffle(shuffle), score02(0), score13(0), set(0),
        dealerIndex(0), pointToWinGame(pointToWin) {
        for (int i = 0; i < 4; i++) {
            this->players[i] = players[i];
        }
    }
    //if shuffle is true, then shuffle the pack
    void shuffle(string shuffle) {
        if (shuffle == "shuffle") {
            pack.shuffle();
        }
    }

    void setDealer() {// 0(0), 1, 2, 3, 4(0) ...
        dealerIndex = set % 4;
        cout << players[dealerIndex]->get_name() << " deals" << endl;
    }
    //Dealing Cards
    void dealCard() {
        int dealingCardNumber[8] = { 3,2,3,2,2,3,2,3 };
        int receiverIndex = (dealerIndex + 1) % 4;
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < dealingCardNumber[i]; j++) {
                players[receiverIndex]->add_card(pack.deal_one());
            }//deal cards
            receiverIndex = (receiverIndex + 1) % 4;
        }
    }

    bool playRound(const Card upcard, const int round) {
        string order_up_suit;
        if (round == 1) order_up_suit = upcard.get_suit();
        int makingTrumpIndex = (dealerIndex + 1) % 4;
        bool isMakingTrump = false;
        for (int i = 0; i < 4; i++) {
            isMakingTrump = players[makingTrumpIndex]->make_trump(
                upcard, (dealerIndex == makingTrumpIndex), round, order_up_suit);
            if (isMakingTrump) {
                cout << players[makingTrumpIndex]->get_name() <<
                    " orders up " << order_up_suit << endl;
                if (makingTrumpIndex == dealerIndex && round == 1)
                    players[makingTrumpIndex]->add_and_discard(upcard);
                break;
            }
            cout << players[makingTrumpIndex]->get_name() << " passes" << endl;
            makingTrumpIndex = (makingTrumpIndex + 1) % 4;
        }
        if (isMakingTrump) {
            if (round == 1 && makingTrumpIndex != dealerIndex)
                players[dealerIndex]->add_and_discard(upcard);
            //makingTrumpIndex is who order up the suit
            trick(order_up_suit, makingTrumpIndex);
            //start trick
            return true;
        }
        else {
            if (round == 2) assert(false);
            // round 2 and no one makes trump? should not happen!
            return false;
        }
    }

    void scoringForEachTrick(int& trickWin02, int& trickWin13, int winnerIndex) {
        if (winnerIndex == 0 || winnerIndex == 2) {
            trickWin02++;
        }
        else {
            trickWin13++;
        }
        cout << players[winnerIndex]->get_name() << " takes the trick" << endl;
    }

    void trick(const string order_up_suit, int orderUpIndex) {
        int trickWin02 = 0;
        int trickWin13 = 0;
        int leadingTrickIndex = (dealerIndex + 1) % 4;
        for (int i = 0; i < 5; i++) {//total 5 tricks
            Card cardOnTrick[4];
            cardOnTrick[0] = players[leadingTrickIndex]->lead_card(order_up_suit);
            //Ace of Clubs led by Herb
            cout << endl;

            cout << cardOnTrick[0] << " led by " <<
                players[leadingTrickIndex]->get_name() << endl;
            for (int j = 1; j < 4;j++) {//following tricks
                cardOnTrick[j] =
                    players[(leadingTrickIndex + j) % 4]->play_card(cardOnTrick[0],
                        order_up_suit);
                cout << cardOnTrick[j] << " played by " <<
                    players[(leadingTrickIndex + j) % 4]->get_name() << endl;
            }
            //judge the winner
            int winnerIndex = (leadingTrickIndex +
                judgeWinner(cardOnTrick, cardOnTrick[0], order_up_suit)) % 4;

            scoringForEachTrick(trickWin02, trickWin13, winnerIndex);
            //Judea takes the trick
            leadingTrickIndex = winnerIndex;
        }
        scoringAfterAllTrick(trickWin02, trickWin13, orderUpIndex);
    }

    void printTheResultOfHand(int winnerIndex0, int winnerIndex1,
        bool isEuchred, bool isMarched) {
        cout << endl;
        cout << players[winnerIndex0]->get_name() << " and " <<
            players[winnerIndex1]->get_name() << " win the hand" << endl;
        if (isEuchred) cout << "euchred!" << endl;
        if (isMarched) cout << "march!" << endl;

        cout << players[0]->get_name() << " and " << players[2]->get_name()
            << " have " << score02 << " points" << endl;
        cout << players[1]->get_name() << " and " << players[3]->get_name()
            << " have " << score13 << " points" << endl;

    }

    void scoringAfterAllTrick(int trickWin02, int trickWin13, int orderUpIndex) {
        // cout << trickWin02 << " " << trickWin13 << endl;
        assert((trickWin02 + trickWin13) == 5 && trickWin02 >= 0 && trickWin13 >= 0);

        if (trickWin02 >= 3) {//02 win
            if (orderUpIndex == 0 || orderUpIndex == 2) {//win the trick and ordered up
                if (trickWin02 < 5) {
                    score02++;
                    printTheResultOfHand(0, 2, false, false);
                }
                else {//march! ordered up and win the 5 trick
                    score02 += 2;
                    printTheResultOfHand(0, 2, false, true);
                }
            }
            else {//euchred!! win and did not order up
                score02 += 2;
                printTheResultOfHand(0, 2, true, false);
            }
        }
        else {//13 win  if(trickWin13 >= 3)
            if (orderUpIndex == 1 || orderUpIndex == 3) {//win the trick and ordered up
                if (trickWin13 < 5) {
                    score13++;
                    printTheResultOfHand(1, 3, false, false);
                }
                else {//march! ordered up and win the 5 trick
                    score13 += 2;
                    printTheResultOfHand(1, 3, false, true);
                }
            }
            else {//euchred!! win and did not order up
                score13 += 2;
                printTheResultOfHand(1, 3, true, false);
            }
        }

    }

    int judgeWinner(const Card cards[4], const Card led_card, const string trump_suit) {
        int highestIndex = 0;
        Card highest = cards[highestIndex];
        for (int i = 0; i < 4;i++) {
            if (Card_less(highest, cards[i], led_card, trump_suit)) {
                highest = cards[i];
                highestIndex = i;
            }
        }
        return highestIndex;
    }

    void playSet() {
        Card upcard = pack.deal_one();
        cout << upcard << " turned up" << endl;
        bool isFirstPlayed = playRound(upcard, 1);
        if (!isFirstPlayed) {
            playRound(upcard, 2);
        }
    }

    void run() {
        while (!(score02 >= pointToWinGame || score13 >= pointToWinGame)) {
            cout << "Hand " << set << endl;
            shuffle(isShuffle);
            pack.reset();
            setDealer();
            dealCard();
            playSet();
            set++;
            cout << endl;
        }
        assert(!(score02 >= pointToWinGame && score13 >= pointToWinGame));

        if (score02 >= pointToWinGame) {
            cout << players[0]->get_name() << " and " <<
                players[2]->get_name() << " win!" << endl;
        }
        else if (score13 >= pointToWinGame) {
            cout << players[1]->get_name() << " and " <<
                players[3]->get_name() << " win!" << endl;
        }
    }
};

int main(int argc, char* argv[])
{
    bool argCheck = false;
    if (argc == 12) {
        string pack_filename = argv[1];
        ifstream fin;
        fin.open(pack_filename);
        if (!fin.is_open())
        {
            cout << "Error opening " << pack_filename << endl;
            return 1;
        }
        string shuffle = argv[2];
        int pointToWinGame = atoi(argv[3]);
        Player* players[4];
        //4,6,8,10 -> 0,1,2,3
        for (int i = 4; i < 12; i = i + 2) {
            players[(i - 4) / 2] = Player_factory(argv[i], argv[i + 1]);
        }
        argCheck = checkArgs(pointToWinGame, shuffle, players);

        if (argCheck) {//pass checking arguments
            for (int i = 0; i < argc; i++) {
                cout << argv[i] << " ";
            }
            cout << endl;

            Game game(fin, players, pointToWinGame, shuffle);
            game.run();
            for (int i = 0; i < 4; ++i) {
                delete players[i];
            }
        }

    }

    if (!argCheck) {
        cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
            << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
            << "NAME4 TYPE4" << endl;
        return 1;
    }
}
