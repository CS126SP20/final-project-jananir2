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
using cinder::gl::Texture2d;
using cinder::gl::Texture2dRef;
using namespace csv2;
using namespace cinder;

DECLARE_uint32(size);
DECLARE_string(filename1);
DECLARE_string(filename2);
DECLARE_string(filename3);

MyApp::MyApp()
    : engine_{FLAGS_filename1, FLAGS_filename2, FLAGS_filename3} {}

template <typename C>
void PrintText(const std::string& text, const C& color,
               const cinder::ivec2& size, const cinder::vec2& loc, FontState font_state) {
  cinder::Font font = cinder::Font(
      cinder::app::loadAsset("BurstMyBubble.ttf"), 20.0);
  if (font_state == FontState::kBold) {
    font = cinder::Font(cinder::app::loadAsset(
                            "BurstMyBubbleBold.ttf"), 20.0);
  } else if (font_state == FontState::kItalic) {
    font = cinder::Font(cinder::app::loadAsset(
                            "BurstMyBubbleItalic.ttf"), 20.0);
  }

  cinder::TextBox box = TextBox()
                 .alignment(TextBox::CENTER)
                 .font(font)
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
  state_ = GameState::kCoverPage;
}

void MyApp::update() {}

void MyApp::draw() {
  cinder::gl::clear();

  DrawBackground();
  if (state_ == GameState::kTakingQuiz) {
    DrawQuestion();
  } else if (state_ == GameState::kChoosingQuiz) {
    DrawChooseQuiz();
  } else if (state_ == GameState::kShowScore) {
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
      break;
    }
    case KeyEvent::KEY_b: {
      engine_.SetChoice(2);
      break;
    }
    case KeyEvent::KEY_c: {
      engine_.SetChoice(3);
      break;
    }
    case KeyEvent::KEY_d: {
      engine_.SetChoice(4);
      break;
    }
    case KeyEvent::KEY_RETURN: {
      if (engine_.CheckIsLastQuestion()) {
        state_ = GameState::kShowScore;
        break;
      } else {
        state_ = GameState::kChoosingQuiz;
        break;
      }
    }
    case KeyEvent::KEY_1: {
      engine_.HandleQuizChoice(1);
      state_ = GameState::kTakingQuiz;
      break;
    }
    case KeyEvent::KEY_2: {
      engine_.HandleQuizChoice(2);
      state_ = GameState::kTakingQuiz;
      break;
    }
    case KeyEvent::KEY_3: {
      engine_.HandleQuizChoice(3);
      state_ = GameState::kTakingQuiz;
      break;
    }
  }
}

void MyApp::DrawQuestion() {
  const cinder::vec2 center = getWindowCenter();
  const cinder::ivec2 size = {800, 500};
  const Color color = Color::black();

  std::vector<std::string> quiz_question =
      engine_.RetrieveQuestion(engine_.GetCurrQuestionIndex());

  int line_index = 0;
  int row = line_index - 1;
  for (std::string line : quiz_question) {
    if (line_index == 0) {
      PrintText(line, color, size, {center.x, center.y + (row++) * 100},
                FontState::kBold);
    } else if (engine_.CheckIsSelected(line_index)) {
      PrintText(line, color, size, {center.x, center.y + (row++) * 100},
                FontState::kItalic);
    } else {
      PrintText(line, color, size, {center.x, center.y + (row++) * 100},
                FontState::kRegular);
    }
    line_index++;
  }

  if (engine_.CheckIsLastQuestion()) {
    PrintText("Press ENTER to view results",
              Color(1, 0, 0), size,
              {center.x, center.y + (row++) * 100},
              FontState::kBold);
  } else {
    row++;
  }
  PrintText(std::to_string(engine_.GetCurrQuestionIndex() + 1),
            Color(1, 0, 0), size,
            {center.x, center.y + (row++) * 100},
            FontState::kRegular);
}

void MyApp::DrawBackground() {
  std::string image_file = "quizpagetext.png";
  if (state_ == GameState::kCoverPage) {
    image_file = "coverpage.png";
  }
  Texture2dRef background = Texture2d::create(loadImage(
          loadAsset(image_file)));

  ci::gl::draw( background, getWindowBounds() );
}

void MyApp::DrawResultsPage() {
  const cinder::vec2 center = getWindowCenter();
  const cinder::ivec2 size = {800, 500};
  const Color color = Color::black();
  PrintText("Results", color, size, {center.x, center.y - 100},
            FontState::kBold);
  PrintText("You scored " + std::to_string(engine_.GetScore()) + "%!",
            color, size, {center.x, center.y}, FontState::kRegular);
}

void MyApp::DrawChooseQuiz() {
  const cinder::vec2 center = getWindowCenter();
  const cinder::ivec2 size = {800, 500};
  const Color color = Color::black();

  for (int i = 0; i <= 3; i++) {
    if (i == 0) {
      PrintText("Enter the number of the quiz you want to take",
                Color(1, .2, 1), size, {center.x, center.y},
                FontState::kBold);
    }
    else {
      PrintText("Quiz " + std::to_string(i),
                Color(1, 0, 1), size,
                {center.x, center.y + i * 100},
                FontState::kRegular);
    }
  }
}
} // namespace myapp