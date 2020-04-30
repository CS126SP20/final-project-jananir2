//
// Created by janan on 4/26/2020.
//

#include "mylibrary/setup.h"
namespace mylibrary {

mylibrary::Setup::Setup() {
  curr_question = 0;
}

std::vector<std::vector<std::string>> mylibrary::Setup::retrieve_questions() {
  std::vector<std::vector<std::string>> questions;

  std::vector<std::string> question1;
  question1.push_back("What is the name for the Jewish New Year?");
  question1.push_back("A) Hanukkah");
  question1.push_back("B) Yom Kippur");
  question1.push_back("C) Kwanza");
  question1.push_back("D) Rosh Hashanah");
  question1.push_back("D) Rosh Hashanah");
  questions.push_back(question1);

  std::vector<std::string> question2;
  question2.push_back("How many blue stripes are there on the U.S. flag?");
  question2.push_back("A) 6");
  question2.push_back("B) 7");
  question2.push_back("C) 13");
  question2.push_back("D) 0");
  question2.push_back("D) 0");
  questions.push_back(question2);

  std::vector<std::string> question3;
  question3.push_back("Which country held the 2016 Summer Olympics?");
  question3.push_back("A) China");
  question3.push_back("B) Ireland");
  question3.push_back("C) Brazil");
  question3.push_back("D) Italy");
  question3.push_back("D) Brazil");
  questions.push_back(question3);

  return questions;
}

std::vector<std::string> mylibrary::Setup::retrieve_question(int num) {
  std::vector<std::vector<std::string>> questions = retrieve_questions();
  return questions.at(num);
}
int Setup::get_curr_question() {
  return curr_question;
}

void Setup::update_curr_question() { curr_question++; }
}
