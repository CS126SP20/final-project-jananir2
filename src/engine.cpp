//
// Created by janan on 5/2/2020.
//
#include <mylibrary/setup.h>
#include <mylibrary/engine.h>
#include <vector>
namespace mylibrary {

using namespace std;
const int kPercentMultiplier = 100;

Engine::Engine(string file1, string file2, string file3, string file4)
    : setup_{},
      curr_question{0} {
  filename1 = file1;
  filename2 = file2;
  filename3 = file3;
  filename4 = file4;
}

vector<string> Engine::RetrieveQuestion(int num) {
  return setup_.RetrieveQuestions().at(num);
}

int Engine::GetCurrQuestionIndex() {
  return curr_question;
}

void Engine::IncCurrQuestion() {
  // Does not increase the current question past the total number of questions
  if (curr_question < setup_.GetNumQuestions() - 1) {
    curr_question++;
  }
}

void Engine::DecCurrQuestion() {
  // Does not decrease the current question below the first question
  if (curr_question > 0) {
    curr_question--;
  }
}

void Engine::SetAnswerChoice(int choice) {
  user_answer[curr_question] = RetrieveQuestion(curr_question).at(choice);
}

std::string Engine::RetrieveAnswer(int num) {
  return setup_.RetrieveAnswers().at(num);
}

double Engine::GetScore() {
  return CheckAnswers()/setup_.GetNumQuestions() * kPercentMultiplier;
}

double Engine::CheckAnswers() {
  int question_num = 0;
  double tally = 0;
  // Go through all of the users answers and compare them to the correct answer
  for (const string& user_ans : user_answer) {
    // If they are the same, then increase the tally of correct questions
    if (RetrieveAnswer(question_num).find(user_ans) != std::string::npos) {
      tally++;
    }
    question_num++;
  }
  return tally;
}

bool Engine::CheckIsLastQuestion () {
  return curr_question == setup_.GetNumQuestions() - 1;
}

bool Engine::CheckIsSelected (int choice) {
  bool isSelected = false;
  for (const string& user_ans : user_answer) {
    // If the choice at the current question is in the user_answer vector
    // then it has been selected
    if (RetrieveQuestion(curr_question).at(choice).find(user_ans)
          != std::string::npos) {
      isSelected = true;
    }
  }
  return isSelected;
}

void Engine::HandleQuizChoice(int choice) {
  // Populate the questions and answers vectors in the setup class with the
  // quiz of the user's choice
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
    case 4: {
      setup_.PopulateQAvectors(filename4);
      break;
    }
  }

  // Populate the user_answers vector with the same number of values as the
  // number of questions so that it can be indexed at any time
  for (int i = 0; i < setup_.GetNumQuestions(); i++) {
    user_answer.push_back("-----------");
  }
}

bool Engine::CheckIsValid() {
  // If there are no questions to answer then the file passed in was invalid
  return setup_.GetNumQuestions() != 0;
}

void Engine::ResetEngine() {
  setup_.ClearSetup();
  curr_question = 0;
  user_answer.clear();
}

}