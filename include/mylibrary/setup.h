//
// Created by janan on 4/26/2020.
//

#ifndef FINALPROJECT_MYLIBRARY_SETUP_H_
#define FINALPROJECT_MYLIBRARY_SETUP_H_
#include <vector>
#include <csv2/reader.hpp>

namespace mylibrary {

class Setup {
 public:
  /** Constructs an empty Setup object */
  Setup();
  /** Returns the number of questions in the quiz */
  int GetNumQuestions();
  /** Populates the question and answer vectors if the file is valid */
  void PopulateQAvectors(std::string file);
  /** Returns all of the questions and answer choices in the quiz */
  std::vector<std::vector<std::string>> RetrieveQuestions();
  /** Returns all of the correct answers to the quiz */
  std::vector<std::string> RetrieveAnswers();
  /** Clears the setup class and returns it to its initial state */
  void ClearSetup();

 private:
  std::vector<std::string> answers;
  std::vector<std::vector<std::string>> questions;
};

}
#endif  // FINALPROJECT_MYLIBRARY_SETUP_H_
