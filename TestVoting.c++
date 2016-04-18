/** @file TestVoting.c++
 *  @brief Contains an average of 3 tests for each method in Voting.c++
 */

#include <cassert>  // assert
#include <iostream> // endl, istream, ostream
#include <sstream>  // istringstream
#include <string>   // getline, string
#include <vector> // Vector type

#include "gtest/gtest.h"

#include "Voting.h"

using namespace std;

// -----------
// TestVoting
// -----------

// ----
// class Ballot
// ----

TEST(VotingFixture, Ballot_1) {
    Ballot b = Ballot();
    b.addInt(0);
    b.addInt(1);
    b.addInt(2);
    ASSERT_EQ(0, b.getInt(0));
    ASSERT_EQ(1, b.getInt(1));
    ASSERT_EQ(2, b.getInt(2));
}

TEST(VotingFixture, Ballot_2) {
    Ballot b = Ballot();
    b.addInt(20);
    b.addInt(19);
    ASSERT_EQ(20, b.getInt(0));
    ASSERT_EQ(19, b.getInt(1));
}

TEST(VotingFixture, Ballot_3) {
    Ballot b = Ballot();
    b.addInt(7);
    b.addInt(8);
    b.addInt(9);
    b.addInt(10);
    ASSERT_EQ(7, b.getInt(0));
    ASSERT_EQ(8, b.getInt(1));
    ASSERT_EQ(9, b.getInt(2));
    ASSERT_EQ(10, b.getInt(3));
}

TEST(VotingFixture, Ballot_4) {
    Ballot b = Ballot();
    b.addInt(7);
    b.addInt(8);
    b.addInt(9);
    b.addInt(10);
    b.addInt(11);
    ASSERT_EQ(7, b.getInt(0));
    ASSERT_EQ(8, b.getInt(1));
    ASSERT_EQ(9, b.getInt(2));
    ASSERT_EQ(10, b.getInt(3));
    ASSERT_EQ(11, b.getInt(4));
}

// ----
// class Candidate
// ----

TEST(VotingFixture, Candidate_1) {
    Candidate b = Candidate("rtx");
    Ballot a = Ballot();
    b.addBallot(a);
    ASSERT_EQ(b.getIsLoser(), false);
}

TEST(VotingFixture, Candidate_2) {
    Candidate b = Candidate("rtx");
    Ballot a = Ballot();
    b.addBallot(a);
    ASSERT_EQ(b.getName(), "rtx");
}

TEST(VotingFixture, Candidate_3) {
    Candidate b = Candidate("rtx");
    Ballot a = Ballot();
    b.addBallot(a);
    ASSERT_EQ(b.getVoteCount(), 0);
}

TEST(VotingFixture, Candidate_4) {
    Candidate b = Candidate("rtx");
    Ballot a = Ballot();
    b.addBallot(a);
    b.countUp();
    ASSERT_EQ(b.getVoteCount(), 1);
}

TEST(VotingFixture, Candidate_5_1) {
    Candidate b = Candidate("asdf");
    ASSERT_EQ(b.getIsLoser(), false);
}
TEST(VotingFixture, Candidate_5_2) {
    Candidate b = Candidate("asdf");
    ASSERT_EQ(b.getName(), "asdf");
}
TEST(VotingFixture, Candidate_5_3) {
    Candidate b = Candidate("asdf");
    b.setLoser();
    ASSERT_EQ(b.getIsLoser(), true);
}
TEST(VotingFixture, Candidate_5_4) {  
    Candidate b = Candidate("asdf");
    b.setLoser(); 
    ASSERT_EQ(b.getVoteCount(), 0);
}
TEST(VotingFixture, Candidate_5_5) {
    Candidate b = Candidate("asdf");
    b.setLoser();
    for (int i = 0; i < 10; i++)
        b.countUp();
    ASSERT_EQ(b.getVoteCount(), 10);
}

TEST(VotingFixture, Candidate_6_1) {
    Candidate b = Candidate("a");
    ASSERT_EQ(b.getIsLoser(), false);
}
TEST(VotingFixture, Candidate_6_2) {
    Candidate b = Candidate("a");
    ASSERT_EQ(b.getName(), "a");
}
TEST(VotingFixture, Candidate_6_3) {
    Candidate b = Candidate("a");
    b.setLoser();
    ASSERT_EQ(b.getIsLoser(), true);
}
TEST(VotingFixture, Candidate_6_4) {
    Candidate b = Candidate("a");
    b.setLoser();
    ASSERT_EQ(b.getVoteCount(), 0);
}
TEST(VotingFixture, Candidate_6_5) {
    Candidate b = Candidate("a");
    b.countUp();
    ASSERT_EQ(b.getVoteCount(), 1);
}

// ----
// read
// ----

TEST(VotingFixture, read_1) {
    istringstream s("3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2");
    Case a = voting_read(s);
    ASSERT_EQ(2, a.getMaxCount());
    ASSERT_EQ(5, a.getBallotsCount());
    ASSERT_EQ(3, a.getCandidates().size());

}

TEST(VotingFixture, read_2) {
    istringstream s("3\nJohn Doe\nJane Smith\nSirhan Sirhan\n");
    Case a = voting_read(s);
    ASSERT_EQ(0, a.getMaxCount());
    ASSERT_EQ(0, a.getBallotsCount());
    ASSERT_EQ(3, a.getCandidates().size());

}

TEST(VotingFixture, read_3) {
    istringstream s("3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n1 2 3\n1 2 3\n1 2 3\n1 2 3");
    Case a = voting_read(s);
    ASSERT_EQ(5, a.getMaxCount());
    ASSERT_EQ(5, a.getBallotsCount());
    ASSERT_EQ(3, a.getCandidates().size());

}

TEST(VotingFixture, read_4) {
    istringstream s("3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n1 2 3\n1 2 3\n1 2 3\n1 2 3");
    Case a = voting_read(s);
    ASSERT_EQ("John Doe", a.getCandidate(0).getName());
    ASSERT_EQ("Jane Smith", a.getCandidate(1).getName());
    ASSERT_EQ("Sirhan Sirhan", a.getCandidate(2).getName());
}

TEST(VotingFixture, read_5) {
    istringstream s("4\na\nb\nc\nd\n1 4 2 3\n1 2 3 4\n1 2 4 3\n4 1 2 3\n1 4 2 3");
    Case a = voting_read(s);
    ASSERT_EQ(4, a.getMaxCount());
    ASSERT_EQ(5, a.getBallotsCount());
    ASSERT_EQ("d", a.getCandidate(3).getName());
}

// ----
// eval
// ----

TEST(VotingFixture, eval_1) {
    istringstream w("3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2");
    Case a = Case();
    a = voting_read(w);
    vector<Candidate> o = voting_eval(a);
    ASSERT_EQ(1, o.size());
}

TEST(VotingFixture, eval_2) {
    istringstream w("3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n3 1 2");
    Case a = Case();
    a = voting_read(w);
    vector<Candidate> o = voting_eval(a);
    ASSERT_EQ(3, o.size());
}

TEST(VotingFixture, eval_3) {
    istringstream w("3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2");
    Case a = Case();
    a = voting_read(w);
    vector<Candidate> o = voting_eval(a);
    ASSERT_EQ(1, o.size());
}

TEST(VotingFixture, eval_4) {
    istringstream w("4\na\nb\nc\nd\n1 4 2 3\n1 2 3 4\n1 2 4 3\n4 1 2 3\n1 4 2 3");
    Case a = Case();
    a = voting_read(w);
    vector<Candidate> o = voting_eval(a);
    ASSERT_EQ("a", o[0].getName());
}

TEST(VotingFixture, eval_5) {
    istringstream w("3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n3 1 2");
    Case a = Case();
    a = voting_read(w);
    vector<Candidate> o = voting_eval(a);
    ASSERT_EQ("John Doe", o[0].getName());
    ASSERT_EQ("Sirhan Sirhan", o[2].getName());
}



// ----
// print
// ----

TEST(VotingFixture, print_1) {
    istringstream i("3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2");
    Case a = voting_read(i);
    vector<Candidate> o = voting_eval(a);
    ostringstream w;
    voting_print(w, o);
    ASSERT_EQ("John Doe\n", w.str());
}

TEST(VotingFixture, print_2) {
    istringstream i("3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n");
    Case a = voting_read(i);
    vector<Candidate> o = voting_eval(a);
    ostringstream w;
    voting_print(w, o);
    ASSERT_EQ("John Doe\nJane Smith\n", w.str());
}

TEST(VotingFixture, print_3) {
    istringstream i("4\na\nb\nc\nd\n1 4 2 3\n1 2 3 4\n2 1 4 3\n2 4 2 3\n3 4 1 2\n3 4 2 1");
    Case a = voting_read(i);
    vector<Candidate> o = voting_eval(a);
    ostringstream w;
    voting_print(w, o);
    ASSERT_EQ("a\nb\nc\n", w.str());
}

TEST(VotingFixture, print_4) {
    istringstream i("4\na\nb\nc\nd\n");
    Case a = voting_read(i);
    vector<Candidate> o = voting_eval(a);
    ostringstream w;
    voting_print(w, o);
    ASSERT_EQ("a\nb\nc\nd\n", w.str());
}

// -----
// solve
// -----

TEST(VotingFixture, solve_1) {
    istringstream r("1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2");
    ostringstream w;
    voting_solve(r, w);
    ASSERT_EQ("John Doe\n", w.str());
}

TEST(VotingFixture, solve_2) {
    istringstream i("3\n\n2\na\nb\n1 2\n1 2\n1 2\n2 1\n1 2\n1 2\n2 1\n\n1\nc\n1\n\n4\nd\ne\nf\ng\n2 1 3 4\n1 3 2 4\n1 4 3 2\n2 4 1 3");
    ostringstream o;
    voting_solve(i, o);
    ASSERT_EQ("a\n\nc\n\nd\ne\n", o.str());
}

TEST(VotingFixture, solve_3) {
    istringstream i("2\n\n7\na\nb\nc\nd\ne\nf\ng\n1 2 3 4 5 6 7\n2 3 4 5 6 7 1\n3 4 5 6 7 1 2\n4 5 6 7 1 2 3\n5 6 7 1 2 3 4\n6 7 1 2 3 4 5\n\n6\nh\ni\nj\nk\nl\nm\n1 2 4 6 5 3\n4 1 2 6 3 5\n3 1 2 4 6 5\n5 3 4 1 6 2\n4 1 2 3 6 5\n2 4 5 6 3 1\n2 3 1 5 6 4\n1 2 3 4 5 6");
    ostringstream o;
    voting_solve(i, o);
    ASSERT_EQ("a\nb\nc\nd\ne\nf\n\nh\nk\n", o.str());
}
TEST(VotingFixture, solve_4) {
    istringstream i("1\n\n7\na\nb\nc\nd\ne\nf\ng\n");
    ostringstream o;
    voting_solve(i, o);
    ASSERT_EQ("a\nb\nc\nd\ne\nf\ng\n", o.str());
}