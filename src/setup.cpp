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

Setup::Setup() { }

int Setup::GetNumQuestions() { return questions.size(); }

void Setup::PopulateQAvectors(string file) {

  csv2::Reader<delimiter<','>, quote_character<'"'>, first_row_is_header<true>> csv;
  std::string filename = cinder::app::getAssetPath(file).string();
  vector<string> question;
  std::string value;
  if (csv.mmap(filename)) {
    const auto header = csv.header();
    for (auto row : csv) {
      question.clear();
      for (auto cell : row) {
        value.clear();
        cell.read_value(value);
        question.push_back(value);
      }
      answers.push_back(question.back());
      question.pop_back();
      questions.push_back(question);
    }
  }

}

vector<vector<string>> Setup::RetrieveQuestions() {
  return questions;
}

vector<string> Setup::RetrieveAnswers() {
  return answers;
}

} // namespace mylibrary
