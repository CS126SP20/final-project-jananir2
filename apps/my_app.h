// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_MYAPP_H_
#define FINALPROJECT_MYAPP_H_

#include <cinder/app/App.h>
#include <mylibrary/engine.h>
#include <gflags/gflags.h>


namespace myapp {

enum class GameState {
  kTakingQuiz,
  kCoverPage,
  kShowScore,
};

enum class FontState {
  kRegular,
  kBold,
  kItalic,
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
  void DrawQuestionBackground();
  void DrawCoverPage();
  void DrawResultsPage();
  GameState state_;

 private:
  mylibrary::Engine engine_;
};

}  // namespace myapp

#endif  // FINALPROJECT_MYAPP_H_
