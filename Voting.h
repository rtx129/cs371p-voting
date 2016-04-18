/** @file Voting.h
 *  @brief Contains 3 sub-classes: Ballot, Candidate, and Case. Contains 4 methods: voting_read, voting_eval\n
 * voting_eval, voting_print, and voting_solve.
 */
 /** \mainpage Voting
 *  This program solves Australian Voting in C++ with an optimization that when reassigning the ballots of a loser,\n
 * 	and it does not iterate over all the ballots. \n
 *	Class: CS371p - Fall 2015 \n
 *	Student 1: Raymond Ton - rjt549
 *  Student 2 : Hieu Nguyen - hn3935
 */


#ifndef Voting_h
#define Voting_h

// --------
// includes
// --------

#include <iostream> // istream, ostream
#include <string>   // string
#include <utility>  // pair
#include <vector> // Vector type

using namespace std;

// /**
//  * Contains information needed for a ballot
//  */
class Ballot {

    vector<int> ints;
    int index;
  
  public:

    //contructor
    Ballot() {
        index = 0;
    };

    // set Index for the ballot
    void setIndex(int a){
        this->index = a;
    }
    // add an int to the ballot
    void addInt(int a){
        this->ints.push_back(a);
    }

    //get ints
    vector<int>& getInts(){
        return this->ints;
    }

    // get the int in the ballot based on an index
    int getInt(int index){
        return this->ints[index];
    }

};

// // ------------
// // Class: Candidate
// // ------------

// /**
//  * Contains information needed for a candidate
//  */

class Candidate {

    string name;
    bool isLoser;
    int voteCount;
    vector<Ballot> ballots;
    
  public:
    
    //constructors
    Candidate (string n){
        name = n;
        voteCount = 0;
        isLoser = false;
    }

    //get a name
    string& getName(){
        return this->name;
    }

    //is lost yet?
    bool getIsLoser(){
        return this->isLoser;
    }

    //set lost
    void setLoser(){
        this->isLoser = true;
    }

    //add a ballot
    void addBallot(Ballot& b){
        this->ballots.push_back(b);
    }

    //count up one vote
    void countUp(){
        this->voteCount++;
    }

    //get ballots
    vector<Ballot>& getBallots(){
        return this->ballots;
    }

    //get ballot
    Ballot& getBallot(int index){
        return this->ballots[index];
    }

    //get voteCount
    int getVoteCount(){
        return this->voteCount;
    }
};

// /**
//  * Contains information needed for a case, in which the program will solve and return the winner(s).
//  */
class Case {
    
    vector<Candidate> candidates;
    int maxCount;
    int ballotsCount;

  public:

    //constructors
    Case () {
        maxCount = 0;
        ballotsCount = 0;
    };

    //get candidates
    vector<Candidate>& getCandidates(){
        return this->candidates;
    }

    //add a candidate
    void addCandidate(Candidate candidate) {
        this->candidates.push_back(candidate);
    }

    //get a candidate
    Candidate& getCandidate(int index){
        return this->candidates[index];
    }

    // count up 1 vote
    void countUp(){
        this->ballotsCount++;
    }

    //get voteCount
    int getBallotsCount(){
        return this->ballotsCount;
    }

    //get maxCount
    int getMaxCount(){
        return this->maxCount;
    }

    //set maxCount
    void setMaxCount(int a){
        this->maxCount = a;
    }

};

// // ------------
// // voting_read
// // ------------

// /**
//  * read the 1st int for the number of candidates,
//  * then read all candidates' names, and finally read all of the ballots that follow. 
//  * @param r the inStream with information for a case
//  * @return a case that contains all the infomation that has just been read.
//  */
Case voting_read (istream& r);

// // ------------
// // voting_eval
// // ------------

// /**
//  * Assign the ballots to the candidates and find out who is the winner
//  * @param aCase a case that needs solving for the winners
//  * @return a vector of candidates who win
//  */
vector<Candidate> voting_eval(Case aCase);

// // ------------
// // voting_print
// // ------------

// /**
//  * Assign the ballots to the candidates and find out who is the winner
//  * @param aCase a case that needs solving for the winners
//  * @return a vector of candidates who win
//  */
void voting_print(ostream& w, vector<Candidate> c);

// // ------------
// // voting_solve
// // ------------

// /**
//  * Read the input, and return the ouput
//  * @param r an istream for input
//  * @param w an ostream for output
//  */
void voting_solve (istream& r, ostream& w);

#endif // Voting_h
