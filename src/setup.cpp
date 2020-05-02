//
// Created by janan on 4/26/2020.
//

#include <mylibrary/setup.h>
#include <vector>
namespace mylibrary {

using namespace std;

Setup::Setup(int index) {
  curr_question = index;
}

vector<vector<string>> Setup::retrieve_questions() {
  vector<vector<string>> questions;

  vector<string> question1;
  question1.push_back("What is the name for the Jewish New Year?");
  question1.push_back("A) Hanukkah");
  question1.push_back("B) Yom Kippur");
  question1.push_back("C) Kwanza");
  question1.push_back("D) Rosh Hashanah");
  question1.push_back("D) Rosh Hashanah");
  questions.push_back(question1);

  vector<string> question2;
  question2.push_back("How many blue stripes are there on the U.S. flag?");
  question2.push_back("A) 6");
  question2.push_back("B) 7");
  question2.push_back("C) 13");
  question2.push_back("D) 0");
  question2.push_back("D) 0");
  questions.push_back(question2);

  vector<string> question3;
  question3.push_back("Which country held the 2016 Summer Olympics?");
  question3.push_back("A) China");
  question3.push_back("B) Ireland");
  question3.push_back("C) Brazil");
  question3.push_back("D) Italy");
  question3.push_back("D) Brazil");
  questions.push_back(question3);

  return questions;
}

vector<string> Setup::retrieve_question(int num) {
  std::vector<std::vector<std::string>> questions = retrieve_questions();
  return questions.at(num);
}
int Setup::get_curr_question() {
  return curr_question;
}

void Setup::inc_curr_question() { curr_question++; }
void Setup::dec_curr_question() { curr_question--; }

} // namespace mylibrary
