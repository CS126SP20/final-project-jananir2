// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_MYAPP_H_
#define FINALPROJECT_MYAPP_H_

#include <cinder/app/App.h>
#include <mylibrary/setup.h>


namespace myapp {

class MyApp : public cinder::app::App {
 public:
  MyApp();
  void setup() override;
  void update() override;
  void draw() override;
  void keyDown(cinder::app::KeyEvent) override;

 private:
  void DrawQuestion();

 private:
  mylibrary::Setup setup_;
};

}  // namespace myapp

#endif  // FINALPROJECT_MYAPP_H_
