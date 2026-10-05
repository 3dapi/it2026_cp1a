#pragma once

#include "Bot.h"
#include "Cards.h"

#include <string>
#include <vector>


struct QuitRequested {};

struct SeatView {
    std::string name;
    int stack = 0;
    int bet = 0;
    bool isDealer = false;
    bool isActing = false;
    bool isUser = false;
    bool eliminated = false;
    bool folded = false;
    bool allIn = false;
    bool winner = false;
    bool cardsOut = false;
    int faceState = 0; 
    Card hole[2];
    std::string handName;
};

struct TableView {
    int handNo = 0;
    int level = 1;
    int smallBlind = 0;
    int bigBlind = 0;
    int secondsToNextLevel = 0;
    int pot = 0;
    std::string streetName;
    std::vector<SeatView> seats;
    std::vector<Card> board;
    int hiddenBoardCards = 0;
    std::vector<std::string> log;
};


struct ActionPrompt {
    std::string street;
    int pot = 0;
    int toCall = 0;
    int callCost = 0;
    int minTo = 0;
    int maxTo = 0;
    int potTo = 0;
    int bigBlind = 0;
    bool canRaise = false;
    bool opening = false;    
    double breakEven = -1.0;  
};

namespace ui {


bool loadAssets();            
void releaseAssets();
void resetSession();       
void requestQuit();           
bool updateTable();          
void drawTable();
void drawTitleScreen(int selectedMenu);
void drawHowToScreen();


void draw(const TableView& view);                   
void sleepMs(int milliseconds);                 
void animateChips(int seat, int amount);         
Action askAction(const ActionPrompt& prompt);        
void waitContinue(const std::string& message);       
void showResult(bool won, int handsPlayed);         
void setTimeScale(double scale);                  

std::string formatChips(int amount);

}
