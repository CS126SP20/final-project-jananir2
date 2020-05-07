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
    /** Creates an engine with 4 options for trivia quizzes the user can take */
    Engine(std::string file1, std::string file2, std::string file3, std::string file4);
    /** Takes in the user's answer choice for the current question and stores it in the user_answers vector */
    void SetAnswerChoice(int choice);
    /** Returns the correct answer for the question specified by the number passed in */
    std::string RetrieveAnswer(int num);
    /** Returns the question and answer choices specified by the number passed in */
    std::vector<std::string> RetrieveQuestion(int num);
    /** Gets the index of the current question */
    int GetCurrQuestionIndex();
    /** Decreases the index of the current question by 1 */
    void DecCurrQuestion();
    /** Increases the index of the current question by 1 */
    void IncCurrQuestion();
    /** Returns whether the current question is the last question */
    bool CheckIsLastQuestion ();
    /** Returns whether the choice passed in is the one the user selected */
    bool CheckIsSelected(int choice);
    /** Returns the score the user got on the quiz */
    double GetScore();
    /** Takes in the quiz the user chose to take and passes it to the setup class */
    void HandleQuizChoice(int choice);
    /** Checks whether the quiz the user chose is valid */
    bool CheckIsValid();
    /** Resets the engine */
    void ResetEngine();

   private:
    /** Checks and returns how many answers the user got correct */
    double CheckAnswers();

   private:
    Setup setup_;
    int curr_question;
    std::vector<std::string> user_answer;
    std::string filename1;
    std::string filename2;
    std::string filename3;
    std::string filename4;
  };
}
#endif  // FINALPROJECT_ENGINE_H
