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
  Setup();
  int GetNumQuestions();
  void PopulateQAvectors(std::string file);
  std::vector<std::vector<std::string>> RetrieveQuestions();
  std::vector<std::string> RetrieveAnswers();
  void ClearSetup();

 private:

 private:
  std::vector<std::string> answers;
  std::vector<std::vector<std::string>> questions;
  bool is_valid;
};

}
#endif  // FINALPROJECT_MYLIBRARY_SETUP_H_
