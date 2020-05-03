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
  if (curr_question < setup_.GetNumQuestions()) {
    curr_question++;
  }
}
void Engine::DecCurrQuestion() {
  if (curr_question > 0) {
    curr_question--;
  }
}
void Engine::GetChoice(char choice, int num_question) {

}
std::string Engine::RetrieveAnswer(int num) {
  return setup_.RetrieveAnswers().at(num);
}
void Engine::GetCorrectAnswer() {}
}