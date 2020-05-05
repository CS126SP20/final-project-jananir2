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

Engine::Engine(string file1, string file2, string file3)
    : setup_{},
      curr_question{0} {
  filename1 = file1;
  filename2 = file2;
  filename3 = file3;
}

vector<string> Engine::RetrieveQuestion(int num) {
  vector<vector<string>> questions = setup_.RetrieveQuestions();
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
  user_answer[curr_question] = RetrieveQuestion(curr_question).at(choice);
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
    if (RetrieveAnswer(question_num).find(user_ans) != std::string::npos) {
      tally++;
    }
    question_num++;
  }
  return tally;
}

bool Engine::CheckIsLastQuestion () {
  return setup_.CheckIsValid() && curr_question == setup_.GetNumQuestions() - 1;
}

bool Engine::CheckIsSelected (int choice) {
  bool isSelected = false;
  for (const string& user_ans : user_answer) {
    if (RetrieveQuestion(curr_question).at(choice).find(user_ans)
          != std::string::npos) {
      isSelected = true;
    }
  }
  return isSelected;
}

void Engine::HandleQuizChoice(int choice) {
  switch (choice) {
    case 1: {
      setup_.PopulateQAvectors(filename1);
      break;
    }
    case 2: {
      setup_.PopulateQAvectors(filename2);
      break;
    }
    case 3: {
      setup_.PopulateQAvectors(filename3);
      break;
    }
  }
  for (int i = 0; i < setup_.GetNumQuestions(); i++) {
    user_answer.push_back("-----------");
  }
}

}