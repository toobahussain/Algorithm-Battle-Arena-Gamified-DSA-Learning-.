// tournament.h - Tournament Controller (10 Rounds + Finale)
// Demonstrates: Priority Queue, Sorting, Dynamic Arrays

#ifndef TOURNAMENT_H
#define TOURNAMENT_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include "contestant.h"
#include "controller.h"
#include "utilis.h"

using namespace std;

class Tournament {
private:
    vector<Contestant> contestants;
    vector<Contestant> finalists;
    int totalRounds;
    int finaleRounds;
    int roundsCompleted;
    string tournamentID;
    time_t startTime;
    
    // DSA Application: Category rotation for round-robin
    vector<string> categories = {"sorting", "graph", "linkedlist", "hashing", "stack_queue"};
    
    void displayRoundHeader(int roundNum, string category) {
        cout << "\n============================================================\n";
        cout << "                    ROUND " << setw(2) << roundNum << " / " << totalRounds << "                          \n";
        cout << "============================================================\n";
        cout << "Category: " << category << "\n";
        cout << "============================================================\n";
    }
    
    void displayIntermediateStandings() {
        // DSA Application: Sorting contestants by score
        vector<Contestant> sorted = contestants;
        sort(sorted.begin(), sorted.end(), [](const Contestant& a, const Contestant& b) {
            return a.getTotalScore() > b.getTotalScore();
        });
        
        cout << "\n============================================================\n";
        cout << "            STANDINGS AFTER ROUND " << setw(2) << roundsCompleted << "                      \n";
        cout << "============================================================\n";
        cout << left << setw(6) << "Rank" << setw(15) << "ID" << setw(20) << "Name" 
             << setw(12) << "Total" << "Avg\n";
        cout << "------------------------------------------------------------\n";
        
        for (size_t i = 0; i < sorted.size(); i++) {
            cout << left << setw(6) << (i+1) 
                 << setw(15) << sorted[i].getID()
                 << setw(20) << sorted[i].getName()
                 << setw(12) << sorted[i].getTotalScore()
                 << fixed << setprecision(1) << sorted[i].getAverageScore() << "\n";
        }
        cout << "============================================================\n";
    }
    
    void runRound(int roundNum) {
        // Determine category for this round (round-robin)
        string category = categories[(roundNum - 1) % categories.size()];
        
        displayRoundHeader(roundNum, category);
        
        Controller controller;
        
        // Each contestant competes in this round
        for (size_t i = 0; i < contestants.size(); i++) {
            cout << "\n-> " << contestants[i].getName() << " competing...\n";
            
            // Run algorithm battle for this contestant
            int score = controller.runAlgorithmForContestant(category, i+1);
            
            // Update contestant score
            contestants[i].addRoundScore(score);
            
            cout << "  Score: " << score << " points\n";
            sleep_ms(300);
        }
        
        roundsCompleted++;
        
        // Show standings after each round
        if (roundNum < totalRounds) {
            displayIntermediateStandings();
            pauseScreen();
        }
    }
    
    void selectFinalists() {
        cout << "\n============================================================\n";
        cout << "          SELECTING TOP 3 FOR GRAND FINALE                  \n";
        cout << "============================================================\n";
        
        // DSA Application: Selection algorithm for top-K elements
        // Using partial_sort for O(n log k) complexity
        vector<Contestant> sorted = contestants;
        sort(sorted.begin(), sorted.end(), [](const Contestant& a, const Contestant& b) {
            return a.getTotalScore() > b.getTotalScore();
        });
        
        cout << "\n FINALISTS:\n";
        cout << "------------------------------------------------------------\n";
        
        for (int i = 0; i < 3 && i < (int)sorted.size(); i++) {
            finalists.push_back(sorted[i]);
            
            string medal = (i == 0) ? "Gold" : (i == 1) ? "Silver" : "Bronze";
            cout << medal << " " << (i+1) << ". " << sorted[i].getName() 
                 << " - " << sorted[i].getTotalScore() << " points\n";
        }
        
        cout << "============================================================\n";
        sleep_ms(1000);
    }
    
    void runFinale() {
        cout << "\n============================================================\n";
        cout << "                    GRAND FINALE                            \n";
        cout << "                                                            \n";
        cout << "     Top 3 Contestants Compete for Championship!           \n";
        cout << "     3 Challenging Rounds with Complex Algorithms          \n";
        cout << "============================================================\n";
        
        vector<string> finaleCategories = {"graph", "linkedlist", "sorting"};
        vector<string> finaleDescriptions = {
            "Advanced Graph Traversal Challenge",
            "Complex Linked List Manipulation",
            "Hybrid Sorting Algorithm Test"
        };
        
        Controller controller;
        
        for (int round = 1; round <= finaleRounds; round++) {
            cout << "\n============================================================\n";
            cout << "              FINALE ROUND " << round << " / " << finaleRounds << "                          \n";
            cout << "============================================================\n";
            cout << "Challenge: " << finaleDescriptions[round-1] << "\n";
            cout << "------------------------------------------------------------\n";
            
            for (size_t i = 0; i < finalists.size(); i++) {
                cout << "\n-> " << finalists[i].getName() << " competing...\n";
                
                // Finale has higher difficulty - bonus scoring
                int baseScore = controller.runAlgorithmForContestant(
                    finaleCategories[round-1], i+1
                );
                int finaleScore = baseScore + (rand() % 20 + 10); // Bonus points
                
                finalists[i].addFinaleScore(finaleScore);
                cout << "  Score: " << finaleScore << " points (with finale bonus)\n";
                sleep_ms(400);
            }
            
            // Show finale standings
            cout << "\n Finale Standings After Round " << round << ":\n";
            cout << "------------------------------------------------------------\n";
            
            vector<Contestant> sorted = finalists;
            sort(sorted.begin(), sorted.end(), [](const Contestant& a, const Contestant& b) {
                return a.getFinaleScore() > b.getFinaleScore();
            });
            
            for (size_t i = 0; i < sorted.size(); i++) {
                cout << (i+1) << ". " << sorted[i].getName() 
                     << " - Finale: " << sorted[i].getFinaleScore() 
                     << " | Total: " << (sorted[i].getTotalScore() + sorted[i].getFinaleScore())
                     << " points\n";
            }
            
            if (round < finaleRounds) {
                pauseScreen();
            }
        }
    }
    
    void declareWinner() {
        // Calculate final combined scores
        for (size_t i = 0; i < finalists.size(); i++) {
            finalists[i].calculateFinalScore();
        }
        
        // Sort by final score
        sort(finalists.begin(), finalists.end(), [](const Contestant& a, const Contestant& b) {
            return a.getFinalScore() > b.getFinalScore();
        });
        
        cout << "\n============================================================\n";
        cout << "                  TOURNAMENT RESULTS                   \n";
        cout << "============================================================\n";
        
        cout << "\n           ======= FINAL PODIUM =======\n\n";
        
        vector<string> medals = {" GOLD", " SILVER", " BRONZE"};
        
        for (size_t i = 0; i < finalists.size(); i++) {
            cout << "  " << medals[i] << ": " << finalists[i].getName() << "\n";
            cout << "     Regular Tournament: " << finalists[i].getTotalScore() << " pts\n";
            cout << "     Finale Performance: " << finalists[i].getFinaleScore() << " pts\n";
            cout << "     ==============================\n";
            cout << "     FINAL SCORE: " << finalists[i].getFinalScore() << " pts\n";
            cout << "     ==============================\n\n";
        }
        
        cout << "============================================================\n";
        cout << "                                                            \n";
        cout << "          CONGRATULATIONS TO THE CHAMPION!             \n";
        cout << "                                                            \n";
        cout << "             " << setw(30) << finalists[0].getName() << "                 \n";
        cout << "                                                            \n";
        cout << "============================================================\n";
        
        sleep_ms(1000);
    }
    
    void saveTournamentResults() {
        ofstream file("data/tournament_results.txt", ios::app);
        
        if (!file.is_open()) {
            cerr << "Error: Could not save tournament results!\n";
            return;
        }
        
        time_t endTime = time(nullptr);
        
        file << "==========================================\n";
        file << "Tournament ID: " << tournamentID << "\n";
        file << "Date: " << ctime(&startTime);
        file << "Contestants: " << contestants.size() << "\n";
        file << "Rounds: " << totalRounds << "\n";
        file << "------------------------------------------\n";
        file << "CHAMPION: " << finalists[0].getName() << "\n";
        file << "Final Score: " << finalists[0].getFinalScore() << "\n";
        file << "------------------------------------------\n";
        file << "Final Standings:\n";
        
        for (size_t i = 0; i < finalists.size(); i++) {
            file << (i+1) << ". " << finalists[i].getName() 
                 << " - " << finalists[i].getFinalScore() << " points\n";
        }
        
        file << "==========================================\n\n";
        file.close();
        
        cout << "\n Tournament results saved successfully!\n";
    }

public:
    Tournament(int numContestants) {
        totalRounds = 10;
        finaleRounds = 3;
        roundsCompleted = 0;
        startTime = time(nullptr);
        
        // Generate unique tournament ID
        tournamentID = "T" + to_string(startTime);
        
        // Create contestants
        for (int i = 1; i <= numContestants; i++) {
            string id = "C" + string(3 - to_string(i).length(), '0') + to_string(i);
            string name = "Contestant_" + to_string(i);
            contestants.push_back(Contestant(id, name));
        }
        
        cout << "\n Tournament initialized with " << numContestants << " contestants!\n";
        sleep_ms(500);
    }
    
    void runTournament() {
        clearScreen();
        cout << "============================================================\n";
        cout << "              TOURNAMENT BEGINS!                            \n";
        cout << "              10 Rounds + Grand Finale                      \n";
        cout << "============================================================\n";
        pauseScreen();
        
        // Run 10 regular rounds
        for (int round = 1; round <= totalRounds; round++) {
            clearScreen();
            runRound(round);
        }
        
        // Show final regular standings
        displayIntermediateStandings();
        pauseScreen();
        
        // Select top 3 finalists
        selectFinalists();
        pauseScreen();
        
        // Run finale
        runFinale();
        pauseScreen();
        
        // Declare winner
        declareWinner();
        pauseScreen();
        
        // Save results
        saveTournamentResults();
    }
};

#endif // TOURNAMENT_H
