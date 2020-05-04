// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"
#include <csv2/reader.hpp>
#include <cinder/app/App.h>
#include <cinder/gl/draw.h>
#include <cinder/gl/gl.h>
#include <mylibrary/setup.h>
#include <gflags/gflags.h>

namespace myapp {

using cinder::app::KeyEvent;
using namespace csv2;
using namespace cinder;

#if defined(CINDER_COCOA_TOUCH)
const char kNormalFont[] = "Arial";
const char kBoldFont[] = "Arial-BoldMT";
const char kDifferentFont[] = "AmericanTypewriter";
#elif defined(CINDER_LINUX)
const char kNormalFont[] = "Arial Unicode MS";
const char kBoldFont[] = "Arial Unicode MS";
const char kDifferentFont[] = "Purisa";
#else
const char kNormalFont[] = "Arial";
const char kBoldFont[] = "Arial Bold";
const char kDifferentFont[] = "Papyrus";
#endif

MyApp::MyApp()
    : engine_{},
      state_{GameState::kCoverPage} {}
template <typename C>
void PrintText(const std::string& text, const C& color,
               const cinder::ivec2& size, const cinder::vec2& loc, FontState font_state) {
  cinder::TextBox box = TextBox()
                 .alignment(TextBox::CENTER)
                 .font(cinder::Font(cinder::app::loadAsset("BubaDEMO-Outline.otf"), 15.0))
                 .size(size)
                 .color(color)
                 .backgroundColor(ColorA(0, 0, 0, 0))
                 .text(text);


  const auto box_size = box.getSize();
  const cinder::vec2 locp = {loc.x - box_size.x / 2, loc.y - box_size.y / 2};
  const auto surface = box.render();
  const auto texture = cinder::gl::Texture::create(surface);
  cinder::gl::draw(texture, locp);
}

void MyApp::setup() {
  //  std::string contents = "hello";
  //  if (csv.parse(contents)) {
  //    bool enteredIf = true;
  //  }
}

void MyApp::update() {}

void MyApp::draw() {
  cinder::gl::clear();

  if (state_ == GameState::kCoverPage) {
    DrawCoverPage();
  } else if (state_ == GameState::kTakingQuiz) {
    DrawQuestion();
  } else {
    DrawResultsPage();
  }
}
  void MyApp::keyDown(KeyEvent event) {
    switch (event.getCode()) {
      case KeyEvent::KEY_RIGHT: {
        engine_.IncCurrQuestion();
        break;
      }
      case KeyEvent::KEY_LEFT: {
        engine_.DecCurrQuestion();
        break;
      }
      case KeyEvent::KEY_a: {
        engine_.SetChoice(1);
      }
      case KeyEvent::KEY_b: {
        engine_.SetChoice(2);
      }
      case KeyEvent::KEY_c: {
        engine_.SetChoice(3);
      }
      case KeyEvent::KEY_d: {
        engine_.SetChoice(4);
      }
      case KeyEvent::KEY_RETURN: {
        if (engine_.CheckIsLastQuestion()) {
          state_ = GameState::kShowScore;
        } else {
        state_ = GameState::kTakingQuiz;
        }
      }
    }
  }

  void MyApp::DrawQuestion() {
    DrawQuestionBackground();
    const cinder::vec2 center = getWindowCenter();
    const cinder::ivec2 size = {800, 500};
    const Color color = Color::black();

    std::vector<std::string> quiz_question =
        engine_.RetrieveQuestion(engine_.GetCurrQuestionIndex());
    int row = -1;
    for (std::string line : quiz_question) {
      PrintText(line, color, size, {center.x, center.y + (row++) * 100}, FontState::kRegular);
    }
    if (engine_.CheckIsLastQuestion()) {
      PrintText("Press ENTER to view results",
                Color(1, 0, 0), size, {center.x, center.y + (row++) * 100}, FontState::kRegular);
    }
    PrintText(std::to_string(engine_.GetCurrQuestionIndex()),
              Color(1, 0, 0), size, {center.x, center.y + (row++) * 100}, FontState::kRegular);
  }

  void MyApp::DrawQuestionBackground() {
    using cinder::gl::Texture2d;
    using cinder::gl::Texture2dRef;
    Texture2dRef background = Texture2d::create(loadImage(
            loadAsset("quizpagetext.png")));

    ci::gl::draw( background, getWindowBounds() );
  }

  void MyApp::DrawCoverPage() {
    using cinder::gl::Texture2d;
    using cinder::gl::Texture2dRef;
    Texture2dRef background = Texture2d::create(loadImage(
        loadAsset("coverpage.png")));

    ci::gl::draw( background, getWindowBounds() );
  }

  void MyApp::DrawResultsPage() {
    DrawQuestionBackground();
    const cinder::vec2 center = getWindowCenter();
    const cinder::ivec2 size = {1000, 500};
    const Color color = Color::black();
    PrintText("Results",
              color, size, {center.x, center.y - 100}, FontState::kRegular);
    PrintText(std::to_string(engine_.GetScore()) + "%",
              color, size, {center.x, center.y}, FontState::kRegular);
  }
// namespace myapp
}