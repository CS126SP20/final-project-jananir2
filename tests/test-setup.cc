// Copyright (c) 2020 CS126SP20. All rights reserved.

#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include <cinder/Rand.h>
#include <mylibrary/setup.h>

#include <mylibrary/engine.h>


TEST_CASE("Check Setup methods for regular file", "[simplefile]") {
  using namespace std;

  mylibrary::Setup setup_{};
  setup_.PopulateQAvectors("simplefile.csv");

  SECTION("Check correct number of questions") {
    REQUIRE(setup_.GetNumQuestions() == 2);
  }

  SECTION("Check correct answers") {
    REQUIRE(setup_.RetrieveAnswers().at(0).find(
                "C) green") != std::string::npos);
    REQUIRE(setup_.RetrieveAnswers().at(1).find("A) moo") != std::string::npos);
  }

  SECTION("Check correct questions") {
    REQUIRE(setup_.RetrieveQuestions().at(0).at(0).find(
                "What color is grass?") != std::string::npos);
    REQUIRE(setup_.RetrieveQuestions().at(1).at(0).find(
                "What sound does a cow make?") != std::string::npos);
  }

  SECTION("Check correct choices") {
    REQUIRE(setup_.RetrieveQuestions().at(0).at(3).find(
        "C) green") != std::string::npos);
    REQUIRE(setup_.RetrieveQuestions().at(1).at(4).find(
        "D) boo") != std::string::npos);
  }

  SECTION("Check is valid") {
    REQUIRE(setup_.CheckIsValid());
  }

}

TEST_CASE("Check Setup methods for invalid filepath", "[nonexistent file]") {
  using namespace std;

  mylibrary::Setup setup_{};
  setup_.PopulateQAvectors("hello.csv");

  SECTION("Check correct number of questions") {
    REQUIRE(setup_.GetNumQuestions() == 1);
  }

  SECTION("Check correct answers") {
    REQUIRE(setup_.RetrieveAnswers().at(0).find(
        "Invalid file provided") != std::string::npos);
  }

  SECTION("Check correct questions") {
    REQUIRE(setup_.RetrieveQuestions().at(0).at(0).find(
        "Invalid file provided") != std::string::npos);
    REQUIRE(setup_.RetrieveQuestions().at(0).size() == 1);
  }

  SECTION("Check is not valid") {
    REQUIRE(!setup_.CheckIsValid());
  }

}