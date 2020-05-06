// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_MYAPP_H_
#define FINALPROJECT_MYAPP_H_

#include <cinder/app/App.h>
#include <mylibrary/engine.h>
#include <gflags/gflags.h>


namespace myapp {

/** State of the game */
enum class GameState {
  kTakingQuiz,
  kChoosingQuiz,
  kCoverPage,
  kShowScore,
  kInvalid,
};

/** Types of fonts to write text in */
enum class FontState {
  kRegular,
  kCaps,
  kBoldCaps,
  kBoldItalic,
};

class MyApp : public cinder::app::App {
 public:
  MyApp();
  void setup() override;
  void update() override;
  void draw() override;
  void keyDown(cinder::app::KeyEvent) override;

 private:
  /** Draw each quiz question and answer*/
  void DrawQuestion();
  /** Draws the background as either the cover page or default background */
  void DrawBackground();
  /** Draws the page where the user can choose which quiz they want to take */
  void DrawChooseQuiz();
  /** Draws the page that displays the results of the quiz */
  void DrawResultsPage();
  /** Draws the page that tells the user that the quiz they passed in is invalid */
  void DrawInvalid();
  /** Draws the page that displays the results of the quiz */
  void PlayAgain();

 private:
  mylibrary::Engine engine_;
  GameState state_;
};

}  // namespace myapp

#endif  // FINALPROJECT_MYAPP_H_
