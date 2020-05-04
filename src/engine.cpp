//
// Created by janan on 5/2/2020.
//
#include <csv2/reader.hpp>
#include <mylibrary/setup.h>
#include <cinder/app/App.h>
#include <mylibrary/engine.h>
#include <vector>
namespace mylibrary {

using namespace std;

Engine::Engine()
    : setup_{},
      curr_question{0} {
  for (int i = 0; i < setup_.GetNumQuestions(); i++) {
    user_answer.push_back("");
  }
}

vector<string> Engine::RetrieveQuestion(int num) {
  std::vector<std::vector<std::string>> questions = setup_.RetrieveQuestions();
  return questions.at(num);
}
int Engine::GetCurrQuestionIndex() {
  return curr_question;
}

void Engine::IncCurrQuestion() {
  if (curr_question < setup_.GetNumQuestions() - 1) {
    curr_question++;
  }
}
void Engine::DecCurrQuestion() {
  if (curr_question > 0) {
    curr_question--;
  }
}
void Engine::SetChoice(int choice) {
  switch (choice) {
    case 1: user_answer[curr_question] = "hello";
//          RetrieveQuestion(curr_question).at(1);
    case 2: user_answer[curr_question] =
          RetrieveQuestion(curr_question).at(2);
    case 3: user_answer[curr_question] =
          RetrieveQuestion(curr_question).at(3);
    case 4: user_answer[curr_question] =
          RetrieveQuestion(curr_question).at(4);
  }
}

std::string Engine::RetrieveAnswer(int num) {
  return setup_.RetrieveAnswers().at(num);
}

double Engine::GetScore() {
  return CheckAnswers()/setup_.GetNumQuestions() * 100;
}

double Engine::CheckAnswers() {
  int question_num = 0;
  double tally = 0;
  for (const string& user_ans : user_answer) {
    if (!user_ans.empty() && RetrieveAnswer(question_num).find(user_ans) != std::string::npos) { //strcmp(user_ans.c_str(), RetrieveAnswer(question_num).c_str()) == 0) {
      tally++;
    }
    question_num++;
  }
  return tally;
}

bool Engine::CheckIsLastQuestion () {
  return curr_question == setup_.GetNumQuestions() - 1;
}

}