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
    Engine(std::string file1, std::string file2, std::string file3);
    void SetChoice(int choice);
    std::string RetrieveAnswer(int num);
    std::vector<std::string> RetrieveQuestion(int num);
    int GetCurrQuestionIndex();
    void DecCurrQuestion();
    void IncCurrQuestion();
    bool CheckIsLastQuestion ();
    bool CheckIsSelected(int choice);
    double GetScore();
    void HandleQuizChoice(int choice);
    bool CheckIsValid();

   private:
    double CheckAnswers();

   public:
    Setup setup_;
    int curr_question;
    std::vector<std::string> user_answer;
    std::string filename1;
    std::string filename2;
    std::string filename3;
  };
}
#endif  // FINALPROJECT_ENGINE_H
