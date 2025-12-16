// menu.h - Main Menu System
// Demonstrates: User Interface Design, Menu Navigation

#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <string>
#include "controller.h"
#include "tournament.h"
#include "organizer.h"
#include "leaderboard.h"
#include "utilis.h"

using namespace std;

class Menu {
private:
    Controller controller;
    Organizer organizer;
    
    void displayMainMenu() {
        
        cout << "============================================================\n";
        cout << "               ALGORITHM BATTLE ARENA                         \n";
        cout << "                   TOURNAMENT SYSTEM                          \n";
        cout << "============================================================\n\n";
        
        cout << "============================================================\n";
        cout << "                          MAIN MENU                           \n";
        cout << "============================================================\n";
        cout << "   1. Quick Battle Arena                                     \n";
        cout << "   2. Tournament Mode (10 Rounds + Finale)                   \n";
        cout << "   3. View Tournament Leaderboard                            \n";
        cout << "   4. View Algorithm Statistics                              \n";
        cout << "   5. Organizer Panel                                        \n";
        cout << "   6. Exit                                                   \n";
        cout << "============================================================\n";
        cout << "Enter your choice (1-6): ";
    }
    
    void displayBattleArenaMenu() {
        
        cout << "============================================================\n";
        cout << "                   QUICK BATTLE ARENA                         \n";
        cout << "============================================================\n";
        cout << "   1. Sorting Algorithms (QuickSort, MergeSort, BubbleSort)   \n";
        cout << "   2. Graph Algorithms (BFS, DFS)                             \n";
        cout << "   3. Linked List Algorithms                                  \n";
        cout << "   4. Hashing Algorithms                                      \n";
        cout << "   5. Stack & Queue Algorithms                                \n";
        cout << "   6. Back to Main Menu                                       \n";
        cout << "============================================================\n";
        cout << "Select category (1-6): ";
    }
    
    void displayTournamentInfo() {
        
        cout << "============================================================\n";
        cout << "                   TOURNAMENT MODE                            \n";
        cout << "============================================================\n";
        cout << "   This mode features:                                        \n";
        cout << "                                                              \n";
        cout << "    10 Rounds of algorithm battles                           \n";
        cout << "    Different algorithm categories each round                \n";
        cout << "    Cumulative scoring system                                \n";
        cout << "    Top 3 contestants advance to finale                      \n";
        cout << "    Grand finale with special challenges                     \n";
        cout << "                                                              \n";
        cout << "   Demonstrates real-world DSA applications in:               \n";
        cout << "    Tournament scheduling (Graph Theory)                     \n";
        cout << "    Contestant ranking (Sorting Algorithms)                  \n";
        cout << "    Score aggregation (Dynamic Programming)                  \n";
        cout << "============================================================\n\n";
        
        cout << "Press Enter to start tournament...";
        cin.ignore();
        cin.get();
    }

public:
    void run() {
        int choice;
        
        do {
            displayMainMenu();
            cin >> choice;
            
            switch(choice) {
                case 1: {
                    // Quick Battle Arena
                    int battleChoice;
                    do {
                        displayBattleArenaMenu();
                        cin >> battleChoice;
                        
                        if (battleChoice >= 1 && battleChoice <= 5) {
                            controller.runQuickBattle(battleChoice);
                            pauseScreen();
                        }
                        else if (battleChoice != 6) {
                            cout << "Invalid choice! Please try again.\n";
                            pauseScreen();
                        }
                    } while (battleChoice != 6);
                    break;
                }
                
                case 2: {
                    // Tournament Mode
                    displayTournamentInfo();
                    
                    int numContestants;
                    cout << "\nEnter number of contestants (4-12): ";
                    cin >> numContestants;
                    
                    // Validate input
                    if (numContestants < 4) numContestants = 4;
                    if (numContestants > 12) numContestants = 12;
                    
                    Tournament tournament(numContestants);
                    tournament.runTournament();
                    
                    pauseScreen();
                    break;
                }
                
                case 3: {
                    // Tournament Leaderboard
                    showTournamentLeaderboard();
                    pauseScreen();
                    break;
                }
                
                case 4: {
                    // Algorithm Statistics
                    showAlgorithmStats();
                    pauseScreen();
                    break;
                }
                
                case 5: {
                    // Organizer Panel
                    organizer.showPanel();
                    break;
                }
                
                case 6: {
                    // Exit
                    
                    cout << "============================================================\n";
                    cout << "               THANK YOU FOR PLAYING!                         \n";
                    cout << "         Algorithm Battle Arena Tournament System             \n";
                    cout << "                                                              \n";
                    cout << "   Demonstrating Real-World DSA Applications in:              \n";
                    cout << "    Algorithm Design & Analysis                              \n";
                    cout << "    Tournament Management Systems                            \n";
                    cout << "    Performance Evaluation & Scoring                         \n";
                    cout << "    Data Structures for Competition Systems                  \n";
                    cout << "============================================================\n";
                    break;
                }
                
                default:
                    cout << "Invalid choice! Please enter a number between 1 and 6.\n";
                    pauseScreen();
            }
        } while (choice != 6);
    }
};

// Global function to launch main menu
void mainMenu() {
    Menu menu;
    menu.run();
}

#endif // MENU_H
