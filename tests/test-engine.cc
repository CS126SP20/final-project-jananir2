
#include <catch2/catch.hpp>
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

TEST_CASE("Test check valid", "[handle quiz][check valid]") {
  SECTION("One file is invalid, handle valid file") {
    mylibrary::Engine engine_{"quizzes/quiz1.csv", "quizzes/quiz2.csv",
                              "quizzes/quiz3.csv", "quizzes/quiz5.csv"};
    engine_.HandleQuizChoice(2);
    REQUIRE(engine_.CheckIsValid());
  }

  SECTION("One file is invalid, handle that file") {
    mylibrary::Engine engine_{"quizzes/quiz1.csv", "quizzes/quiz2.csv",
                              "quizzes/quiz5.csv", "simplefile.csv"};
    engine_.HandleQuizChoice(3);
    REQUIRE(!engine_.CheckIsValid());
  }
}

TEST_CASE("Test current index of function", "[increase][decrease]") {
  mylibrary::Engine engine_{"quizzes/quiz1.csv", "quizzes/quiz2.csv",
                            "quizzes/quiz3.csv", "quizzes/quiz4.csv"};
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

TEST_CASE("Test if last question", "[increase index][decrease index]") {
  mylibrary::Engine engine_{"quizzes/simplefile.csv", "quizzes/quiz2.csv",
                            "quizzes/quiz3.csv", "quizzes/quiz4.csv"};
  engine_.HandleQuizChoice(1);

  SECTION("Test is not last question") {
    REQUIRE(!engine_.CheckIsLastQuestion());
  }

  SECTION("Test is last question") {
    engine_.IncCurrQuestion();
    REQUIRE(engine_.CheckIsLastQuestion());
  }
}

TEST_CASE("Test answer selection", "[test set answer choice][test check selected]") {
  mylibrary::Engine engine_{"quizzes/simplefile.csv", "quizzes/quiz5.csv",
                            "quizzes/quiz3.csv", "quizzes/badformatquiz.csv"};
  engine_.HandleQuizChoice(3);

  SECTION("Test user's answer and selected answer are same for current question") {
    engine_.IncCurrQuestion();
    engine_.IncCurrQuestion();
    engine_.IncCurrQuestion();
    engine_.SetAnswerChoice(2);
    REQUIRE(engine_.CheckIsSelected(2));
    REQUIRE(!engine_.CheckIsSelected(3));
  }

  SECTION("Test answer user selected for current question is not also selected for next question") {
    engine_.IncCurrQuestion();
    engine_.IncCurrQuestion();
    engine_.IncCurrQuestion();
    engine_.SetAnswerChoice(2);
    engine_.IncCurrQuestion();
    REQUIRE(!engine_.CheckIsSelected(2));
  }

  SECTION("Test user can change answer selection") {
    engine_.SetAnswerChoice(3);
    engine_.SetAnswerChoice(4);
    REQUIRE(engine_.CheckIsSelected(4));
    REQUIRE(!engine_.CheckIsSelected(3));
  }
}

TEST_CASE("Get score function") {
  mylibrary::Engine engine_{
      "quizzes/simplefile.csv", "quizzes/badformatquiz.csv",
                            "quizzes/quiz3.csv", "quizzes/quiz4.csv"};

  SECTION("Test correct score for answer all D's to quiz4") {
    engine_.HandleQuizChoice(4);
    for (int i = 0; i < 30; i++) {
      engine_.SetAnswerChoice(4);
      engine_.IncCurrQuestion();
    }
    REQUIRE(engine_.GetScore() == (5.0 / 30.0 * 100));
  }

  SECTION("Test correct score for not answering any questions") {
    engine_.HandleQuizChoice(4);
    for (int i = 0; i < 30; i++) {
      engine_.IncCurrQuestion();
    }
    REQUIRE(engine_.GetScore() == 0);
  }

  SECTION("Test correct score for answering all questions correctly") {
    engine_.HandleQuizChoice(1);
    engine_.SetAnswerChoice(3);
    engine_.IncCurrQuestion();
    engine_.SetAnswerChoice(1);
    REQUIRE(engine_.GetScore() == 100.0);
  }
}

TEST_CASE("Test reset engine", "[get current question index]") {
  mylibrary::Engine engine_{"quizzes/simplefile.csv", "quizzes/quiz2.csv",
                            "quizzes/quiz3.csv", "quizzes/quiz4.csv"};
  engine_.HandleQuizChoice(3);

  engine_.IncCurrQuestion();
  engine_.IncCurrQuestion();
  engine_.IncCurrQuestion();
  REQUIRE(engine_.GetCurrQuestionIndex() == 3);

  engine_.ResetEngine();
  REQUIRE(engine_.GetCurrQuestionIndex() == 0);
}
