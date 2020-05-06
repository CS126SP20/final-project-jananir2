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
using namespace std;

DECLARE_uint32(size);
DECLARE_string(filename1);
DECLARE_string(filename2);
DECLARE_string(filename3);
DECLARE_string(filename4);

const cinder::vec2 kCenter = cinder::app::getWindowCenter();
const cinder::ivec2 kDefaultSize = {800, 500};
const Color kDefaultColor = Color::black();
const int kLineSpacing = 100;
const float kFontSize = 20.0;
const int kNumQuizzes = 4;

MyApp::MyApp()
    : engine_{FLAGS_filename1, FLAGS_filename2,
              FLAGS_filename3, FLAGS_filename4} {}

template <typename C>
void PrintText(const string& text, const C& color,
               const cinder::ivec2& size, const cinder::vec2& loc,
               FontState font_state) {
  cinder::Font font = cinder::Font(cinder::app::loadAsset(
                                   "SFCartoonistHand.ttf"), kFontSize);
  if (font_state == FontState::kBoldCaps) {
    font = cinder::Font(cinder::app::loadAsset(
                            "SFCartoonistHandSC-Bold.ttf"), kFontSize);
  } else if (font_state == FontState::kCaps) {
    font = cinder::Font(cinder::app::loadAsset(
                            "SFCartoonistHandSC.ttf"), kFontSize);
  } else if (font_state == FontState::kBoldItalic) {
    font = cinder::Font(cinder::app::loadAsset(
                        "SFCartoonistHand-BoldItalic.ttf"), kFontSize);
  }

  cinder::TextBox box = TextBox()
                 .alignment(TextBox::CENTER)
                 .font(font)
                 .size(size)
                 .color(color)
                 .backgroundColor(ColorA(0, 0, 0, 0))
                 .text(text);

  const auto box_size = box.getSize();
  const cinder::vec2 locp = {loc.x - box_size.x / 2,
                             loc.y - box_size.y / 2};
  const auto surface = box.render();
  const auto texture = cinder::gl::Texture::create(surface);
  cinder::gl::draw(texture, locp);
}

void MyApp::setup() {
  state_ = GameState::kCoverPage;
}

void MyApp::update() {}

void MyApp::draw() {
  DrawBackground();
  if (state_ == GameState::kTakingQuiz) {
    DrawQuestion();
  } else if (state_ == GameState::kChoosingQuiz) {
    DrawChooseQuiz();
  } else if (state_ == GameState::kShowScore) {
    DrawResultsPage();
  } else if (state_ == GameState::kInvalid) {
    DrawInvalid();
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
      if (state_ == GameState::kInvalid || state_ == GameState::kShowScore) {
        PlayAgain();
        break;
      } else if (engine_.CheckIsLastQuestion()) {
        state_ = GameState::kShowScore;
        break;
      } else if (state_ != GameState::kTakingQuiz) {
        state_ = GameState::kChoosingQuiz;
        break;
      }
    }
    case KeyEvent::KEY_1: {
      engine_.HandleQuizChoice(1);
      if (engine_.CheckIsValid()) {
        state_ = GameState::kTakingQuiz;
      } else {
        state_ = GameState::kInvalid;
      }
      break;
    }
    case KeyEvent::KEY_2: {
      engine_.HandleQuizChoice(2);
      if (engine_.CheckIsValid()) {
        state_ = GameState::kTakingQuiz;
      } else {
        state_ = GameState::kInvalid;
      }
      break;
    }
    case KeyEvent::KEY_3: {
      engine_.HandleQuizChoice(3);
      if (engine_.CheckIsValid()) {
        state_ = GameState::kTakingQuiz;
      } else {
        state_ = GameState::kInvalid;
      }
      break;
    }
    case KeyEvent::KEY_4: {
      engine_.HandleQuizChoice(4);
      if (engine_.CheckIsValid()) {
        state_ = GameState::kTakingQuiz;
      } else {
        state_ = GameState::kInvalid;
      }
      break;
    }
  }
}

void MyApp::DrawQuestion() {
  vector<string> quiz_question =
      engine_.RetrieveQuestion(engine_.GetCurrQuestionIndex());

  int line_index = 0;
  int row = line_index - 1;
  FontState curr_font;

  for (string line : quiz_question) {
    if (line_index == 0) {
      curr_font = FontState::kCaps;
    } else if (engine_.CheckIsSelected(line_index)) {
      curr_font = FontState::kBoldItalic;
    } else {
      curr_font = FontState::kRegular;
    }

    PrintText(line, kDefaultColor, kDefaultSize,
              {kCenter.x, kCenter.y + (row++) * kLineSpacing}, curr_font);
    line_index++;
  }

  if (engine_.CheckIsLastQuestion()) {
    PrintText("Press ENTER to view results",
              Color(1, 0, 0), kDefaultSize,
              {kCenter.x, kCenter.y + (row++) * kLineSpacing},
              FontState::kBoldCaps);
  } else {
    row++;
  }
  PrintText(to_string(engine_.GetCurrQuestionIndex() + 1),
            Color(1, 0, 0), kDefaultSize,
            {kCenter.x, kCenter.y + (row++) * kLineSpacing},
            FontState::kRegular);
}

void MyApp::DrawInvalid() {
  PrintText("Invalid file provided",
            Color(1, 0, 0), kDefaultSize,
            {kCenter.x, kCenter.y},FontState::kBoldCaps);
  PrintText("Press ENTER to choose another quiz!",
            Color(0, 0, 0), kDefaultSize,
            {kCenter.x, kCenter.y + kLineSpacing},
            FontState::kBoldCaps);
}

void MyApp::DrawBackground() {
  string image_file = "quizpagetext.png";
  if (state_ == GameState::kCoverPage) {
    image_file = "coverpage.png";
  }
  Texture2dRef background = Texture2d::create(loadImage(
          loadAsset(image_file)));

  ci::gl::draw( background, getWindowBounds() );
}

void MyApp::DrawResultsPage() {
  PrintText("Results", kDefaultColor, kDefaultSize,
            {kCenter.x, kCenter.y - kLineSpacing},
            FontState::kBoldCaps);
  PrintText("You scored " + to_string(int(engine_.GetScore())) + "%!",
            kDefaultColor, kDefaultSize, {kCenter.x, kCenter.y},
            FontState::kRegular);
  PrintText("Press ENTER to choose another quiz!",
            Color(0, 0, 0), kDefaultSize,
            {kCenter.x, kCenter.y + kLineSpacing},
            FontState::kCaps);
}

void MyApp::DrawChooseQuiz() {
  for (int i = 0; i <= kNumQuizzes; i++) {
    if (i == 0) {
      PrintText("Enter the number of the quiz you want to take",
                Color(1, .2, 1), kDefaultSize,
                {kCenter.x, kCenter.y},FontState::kBoldCaps);
    } else {
      PrintText("Quiz " + to_string(i), Color(1, 0, 1),
                kDefaultSize, {kCenter.x, kCenter.y + i * kLineSpacing},
                FontState::kRegular);
    }
  }
}

void MyApp::PlayAgain() {
  engine_.ClearEngine();
  state_ = GameState::kChoosingQuiz;
}
} // namespace myapp