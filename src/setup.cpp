//
// Created by janan on 4/26/2020.
//

#include <csv2/reader.hpp>
#include <mylibrary/setup.h>
#include <cinder/app/App.h>

#include <vector>
namespace mylibrary {

using namespace std;
using namespace csv2;
using namespace cinder;
const int kVectorSize = 6; // Sum of question, 4 answer choices, and answer

Setup::Setup() { }

int Setup::GetNumQuestions() { return questions.size(); }

void Setup::PopulateQAvectors(string file) {
  // Creates a csv file Reader provided by the csv2 class
  csv2::Reader<delimiter<','>, quote_character<'"'>,
      first_row_is_header<true>> csv;

  // Get the path to csv quiz file
  std::string filename = cinder::app::getAssetPath(file).string();
  vector<string> question;
  std::string value;

  // Check that the file/filepath exists
  if (csv.mmap(filename)) {
    const auto header = csv.header();

    // Go through each line in the csv file
    for (auto row : csv) {
      question.clear();

      //Go through each comma-separated value in the file
      for (auto cell : row) {
        value.clear();
        cell.read_value(value);
        // Add the values of each line to the question vector
        question.push_back(value);
      }

      if (question.size() != kVectorSize) {
        // If there isn't exactly 1 question, 4 answer choices, and 1 answer,
        // the quiz can't be taken & the file is invalid, so clear all questions
        questions.clear();
        return;
      } else {
        // Otherwise add the last element of the question vector to the answers
        // vector because it contains the correct answer
        answers.push_back(question.back());
        // Remove the last element of the question vector so that it only
        // contains the question and 4 answer choices
        question.pop_back();
        // Add the modified question vector to the vector that has all questions
        questions.push_back(question);
      }
    }
  }
}

vector<vector<string>> Setup::RetrieveQuestions() {
  return questions;
}

vector<string> Setup::RetrieveAnswers() {
  return answers;
}

void Setup::ClearSetup() {
  answers.clear();
  questions.clear();
}

} // namespace mylibrary
