//
// Created by janan on 4/26/2020.
//

#ifndef FINALPROJECT_SETUP_H
#define FINALPROJECT_SETUP_H
#include <vector>
namespace mylibrary {
class Setup {
 public:
  int curr_question;
  Setup();
  std::vector<std::vector<std::string>> retrieve_questions();
  std::vector<std::string> retrieve_question(int num);
  int get_curr_question();
  void update_curr_question();
};


}
#endif  // FINALPROJECT_SETUP_H
