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
  Setup(int index);
  std::vector<std::string> retrieve_question(int num);
  int get_curr_question();
  void dec_curr_question();
  void inc_curr_question();

 private:
  std::vector<std::vector<std::string>> retrieve_questions();

 private:
  int curr_question;
  int num_questions;
};

}
#endif  // FINALPROJECT_MYLIBRARY_SETUP_H_
