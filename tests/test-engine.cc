
#include <catch2/catch.hpp>
#include <cinder/Rand.h>
#include <mylibrary/setup.h>

#include <mylibrary/engine.h>

using namespace std;


TEST_CASE("Test handles quiz choice correctly",
          "[retrieve question][retrieve answer]") {
  mylibrary::Engine engine_{"quizzes/quiz1.csv", "quizzes/quiz2.csv",
                            "quizzes/quiz3.csv", "quizzes/quiz4.csv"};
  engine_.HandleQuizChoice(1);

  SECTION("Test retrieve question") {
    vector<string> test_question;

    test_question.push_back(
        "What was the name of the band Lionel Richie was a part of?");
    test_question.push_back("A) King Harvest");
    test_question.push_back("B) Spectrums");
    test_question.push_back("C) Commodores");
    test_question.push_back("D) The Marshall Tucker Band");

    REQUIRE(engine_.RetrieveQuestion(4) == test_question);
  }

  SECTION("Test retrieve answer") {
    REQUIRE(engine_.RetrieveAnswer(4).find("C) Commodores") != string::npos);
  }
}

TEST_CASE("Test current index of function", "[increase][decrease]") {
  mylibrary::Engine engine_{"quizzes/quiz1.csv", "quizzes/quiz2.csv",
                            "quizzes/quiz3.csv", "quizzes.quiz4.csv"};
  engine_.HandleQuizChoice(2);

  SECTION("Test increase index by two") {
    engine_.IncCurrQuestion();
    engine_.IncCurrQuestion();
    REQUIRE(engine_.GetCurrQuestionIndex() == 2);
  }

  SECTION("Test decrease index") {
    engine_.IncCurrQuestion();
    engine_.IncCurrQuestion();
    engine_.DecCurrQuestion();
    REQUIRE(engine_.GetCurrQuestionIndex() == 1);
  }

  SECTION("Test decrease index past 0") {
    engine_.DecCurrQuestion();
    engine_.DecCurrQuestion();
    REQUIRE(engine_.GetCurrQuestionIndex() == 0);
  }

  SECTION("Test increase index past list size") {
    for (int i = 0; i < 50; i++) {
      engine_.IncCurrQuestion();
    }
    REQUIRE(engine_.GetCurrQuestionIndex() == 29);
  }
}