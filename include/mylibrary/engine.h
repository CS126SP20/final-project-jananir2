//
// Created by janan on 5/2/2020.
//

#ifndef FINALPROJECT_ENGINE_H
#define FINALPROJECT_ENGINE_H
#include <vector>
#include <csv2/reader.hpp>
#include <mylibrary/setup.h>

namespace mylibrary {
  class Engine {
   public:
    Engine();
    void GetChoice(char choice, int num_question);
    void GetCorrectAnswer();
    std::string RetrieveAnswer(int num);
    std::vector<std::string> RetrieveQuestion(int num);
    int GetCurrQuestionIndex();
    void DecCurrQuestion();
    void IncCurrQuestion();

   public:
    Setup setup_;
    int curr_question;
    std::vector<std::string> user_answer;
  };
}
#endif  // FINALPROJECT_ENGINE_H
