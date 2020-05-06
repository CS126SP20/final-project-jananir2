// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_MYAPP_H_
#define FINALPROJECT_MYAPP_H_

#include <cinder/app/App.h>
#include <mylibrary/engine.h>
#include <gflags/gflags.h>


namespace myapp {

enum class GameState {
  kTakingQuiz,
  kChoosingQuiz,
  kCoverPage,
  kShowScore,
  kInvalid,
};

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
  void DrawQuestion();
  void DrawBackground();
  void DrawChooseQuiz();
  void DrawResultsPage();
  void DrawInvalid();
  GameState state_;

 private:
  mylibrary::Engine engine_;
  void PlayAgain();
};

}  // namespace myapp

#endif  // FINALPROJECT_MYAPP_H_
