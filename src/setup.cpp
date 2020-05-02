//
// Created by janan on 4/26/2020.
//

#include <cinder/gl/wrapper.h>
#include <csv2/reader.hpp>
#include <mylibrary/setup.h>
#include <cinder/app/App.h>

#include <vector>
namespace mylibrary {

using namespace std;
using namespace csv2;
using namespace cinder;

Setup::Setup(int index) {
  curr_question = index;
}

vector<vector<string>> Setup::retrieve_questions() {
  vector<vector<string>> questions;

  csv2::Reader<delimiter<','>, quote_character<'"'>, first_row_is_header<true>> csv;
  std::string filename = cinder::app::getAssetPath("names.csv").string();
  vector<string> question;
  std::string value;
  if (csv.mmap(filename)) {
    const auto header = csv.header();
    for (auto row : csv) {
      question.clear();
      for (auto cell : row) {
        value = "";
        cell.read_value(value);
        question.push_back(value);
      }
      question.pop_back();
      questions.push_back(question);
    }
  }

  return questions;
}

vector<string> Setup::retrieve_question(int num) {
  std::vector<std::vector<std::string>> questions = retrieve_questions();
  return questions.at(num);
}
int Setup::get_curr_question() {
  return curr_question;
}

void Setup::inc_curr_question() { curr_question++; }
void Setup::dec_curr_question() { curr_question--; }

} // namespace mylibrary
