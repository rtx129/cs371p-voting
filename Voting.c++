/** @file Voting.c++
 *  @brief Contains 3 sub-classes: Ballot, Candidate, and Case. Contains 4 methods: voting_read, voting_eval\n
 * voting_eval, voting_print, and voting_solve.
 */

#include <cassert>  // assert
#include <iostream> // endl, istream, ostream
#include <sstream>  // istringstream
#include <string>   // getline, string
#include <vector> // Vector type

#include "Voting.h"

using namespace std;


// // ------------
// // voting_read
// // ------------

// /**
//  * read the 1st int for the number of candidates,
//  * then read all candidates' names, and finally read all of the ballots that follow. 
//  * @param r the inStream with information for a case
//  * @return a case that contains all the infomation that has just been read.
//  */
Case voting_read (istream& r) {
    Case thisCase = Case(); // the case that will be returned
    string s; // to save one line read from getline()
    int num; // to save the number of candidates
    getline (r, s); // get the first number, which is the number of candadates
    istringstream sin(s); // convert s into an int
    sin >> num; // assign the converted number to num
    

    for (int i = 0; i < num; i++){
        getline (r, s); // get a name
        Candidate candidate = Candidate(s); // create a new candidate with that name
        thisCase.addCandidate(candidate); // push the candidate to the candidates vector
    }

    // collect the ballots
    while (getline(r,s) && !s.empty()){

        // create a new ballot
        Ballot ballot = Ballot();
        ballot.setIndex(0);
        thisCase.countUp();

        // fill in the values of the ballot
        istringstream sin(s);
        for (int i = 0; i < num; i++){
            int a;
            sin >> a;
            ballot.addInt(a);
        }

        int chosenCandidate = ballot.getInt(0) - 1;

        // put the ballot to the chosen candidate
        thisCase.getCandidate(chosenCandidate).addBallot(ballot);
        thisCase.getCandidate(chosenCandidate).countUp();
        if (thisCase.getCandidate(chosenCandidate).getVoteCount() > thisCase.getMaxCount()){
            thisCase.setMaxCount(thisCase.getCandidate(chosenCandidate).getVoteCount());
        }

    }
    return thisCase;

}

// // ------------
// // voting_eval
// // ------------

// /**
//  * Assign the ballots to the candidates and find out who is the winner
//  * @param aCase a case that needs solving for the winners
//  * @return a vector of candidates who win
//  */

vector<Candidate> voting_eval(Case aCase) {

    bool run = true;
    int minCount;
    vector<Candidate> winners;

    while (run){
        // Step 1: if there is one candidate who get the majority of votes, return that candidate
        if (aCase.getMaxCount() > (aCase.getBallotsCount() / 2)){
            run = false;
            for (unsigned i = 0; i < aCase.getCandidates().size(); i++){
                if (aCase.getCandidate(i).getVoteCount() == aCase.getMaxCount()){
                    winners.push_back(aCase.getCandidate(i));
                    return winners;
                }
            }
        }

        // Step 2: check for minCount
        run = false;

        minCount = aCase.getMaxCount();
        for (unsigned i = 0; i < aCase.getCandidates().size(); i++){
            if ((aCase.getCandidate(i).getIsLoser() == false) && (aCase.getCandidate(i).getVoteCount() < minCount)){
                run = true;
                minCount = aCase.getCandidate(i).getVoteCount();
            }
        }

        // if there is no minCount, there is a tie between all candidates. So, simply return them.
        if (minCount == aCase.getMaxCount()) {
            return aCase.getCandidates();
        }

        //Step 3: recount the votes
        for (unsigned i = 0; i < aCase.getCandidates().size(); i++){
            if (aCase.getCandidate(i).getVoteCount() == minCount){
                for (unsigned j = 0; j < aCase.getCandidate(i).getBallots().size(); j++){
                    Ballot ballot = aCase.getCandidate(i).getBallot(j);

                    int chosenCandidate = 0;
                    for (unsigned k = 0; k < ballot.getInts().size(); k++){
                        chosenCandidate = ballot.getInt(k) - 1;
                        if ((aCase.getCandidate(chosenCandidate).getIsLoser() == false) && (aCase.getCandidate(chosenCandidate).getVoteCount() > minCount)){
                            break;
                        }
                        
                    }

                    // put the ballot to the chosen candidate
                    aCase.getCandidate(chosenCandidate).addBallot(ballot);
                    aCase.getCandidate(chosenCandidate).countUp();
                    if (aCase.getCandidate(chosenCandidate).getVoteCount() > aCase.getMaxCount()){
                        aCase.setMaxCount(aCase.getCandidate(chosenCandidate).getVoteCount());
                    }
                }
                // marked the candidate as Loser
                aCase.getCandidate(i).setLoser();
            }
        }

    }
        return aCase.getCandidates();
}


// // ------------
// // voting_print
// // ------------

// /**
//  * Assign the ballots to the candidates and find out who is the winner
//  * @param aCase a case that needs solving for the winners
//  * @return a vector of candidates who win
//  */

void voting_print(ostream& w, vector<Candidate> c){
    for (unsigned i = 0; i < c.size(); i++){
        if (!c[i].getIsLoser())
            w << c[i].getName() << endl;
    }
}


// // ------------
// // voting_solve
// // ------------

// /**
//  * Read the input, and return the ouput
//  * @param r an istream for input
//  * @param w an ostream for output
//  */
void voting_solve (istream& r, ostream& w) {

    string s; // one line read from getline()
    int num_case; // the number of cases
    getline (r, s); // get the first number, which is the number of cases
    istringstream sin(s); // convert s into an int
    sin >> num_case; // assign the converted number to num_case
    
    getline (r, s); // read the blank line and discard it

    //test
    // for (int i = 0; i < num_case; i++) {
    //     cout << "case " << i << endl;
    //     Case aCase = Case();
    //     aCase = voting_read (r);
    //     for (int j = 0; j < aCase.candidates.size(); j++){
    //         cout << aCase.candidates[j].name << "   ";
    //         for (int k = 0; k < aCase.candidates[j].ballots.size(); k++){
    //             for (int l = 0; l < aCase.candidates[j].ballots[k].ints.size(); l++){
    //                 cout << aCase.candidates[j].ballots[k].ints[l] << " ";
    //             }
    //             cout << " | ";
    //         }
    //         cout << "votes: " <<aCase.candidates[j].voteCount << endl;
    //         cout << endl;
    //     }
    //     cout << "max # of votes: " << aCase.maxCount << endl;
    //     cout << endl;

    //     // Counting the votes and return the winnner(s)
    //     voting_print(voting_eval(aCase));   
    // }

    for (int i = 0; i < num_case; i++) {
        Case aCase = Case();
        aCase = voting_read (r);
        voting_print(w, voting_eval(aCase));
        if ( i != num_case - 1){
            w << endl;
        }
    }
}