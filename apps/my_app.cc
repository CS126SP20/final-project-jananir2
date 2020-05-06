// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"
#include <cinder/gl/draw.h>
#include <cinder/gl/gl.h>

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

const cinder::ivec2 kDefaultSize = {800, 500};
const Color kDefaultColor = Color::black();
const int kLineSpacing = 100;
const float kFontSize = 20.0;
const int kNumQuizzes = 4;

MyApp::MyApp()
    : engine_{FLAGS_filename1, FLAGS_filename2,
              FLAGS_filename3, FLAGS_filename4} {}

// Prints text using the provided color, size, location and type of font desired
template <typename C>
void PrintText(const string& text, const C& color, const ivec2& size,
               const vec2& loc, FontState font_state) {
  Font font = Font(app::loadAsset(
                   "fonts/SFCartoonistHand.ttf"), kFontSize);
  if (font_state == FontState::kBoldCaps) {
    font = Font(app::loadAsset(
                "fonts/SFCartoonistHandSC-Bold.ttf"), kFontSize);
  } else if (font_state == FontState::kCaps) {
    font = Font(app::loadAsset(
                "fonts/SFCartoonistHandSC.ttf"), kFontSize);
  } else if (font_state == FontState::kBoldItalic) {
    font = Font(app::loadAsset(
                "fonts/SFCartoonistHand-BoldItalic.ttf"), kFontSize);
  }

  TextBox box = TextBox()
                 .alignment(TextBox::CENTER)
                 .font(font)
                 .size(size)
                 .color(color)
                 .backgroundColor(ColorA(0, 0, 0, 0))
                 .text(text);

  const auto box_size = box.getSize();
  const vec2 locp = {loc.x - box_size.x / 2,
                             loc.y - box_size.y / 2};
  const auto surface = box.render();
  const auto texture = gl::Texture::create(surface);
  gl::draw(texture, locp);
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
      engine_.SetAnswerChoice(1);
      break;
    }
    case KeyEvent::KEY_b: {
      engine_.SetAnswerChoice(2);
      break;
    }
    case KeyEvent::KEY_c: {
      engine_.SetAnswerChoice(3);
      break;
    }
    case KeyEvent::KEY_d: {
      engine_.SetAnswerChoice(4);
      break;
    }
    case KeyEvent::KEY_RETURN: {
      if (state_ == GameState::kInvalid || state_ == GameState::kShowScore) {
        // Pressing enter when the user is on the Invalid or Score page allows
        // them to play again
        PlayAgain();
        break;
      } else if (state_ == GameState::kTakingQuiz && engine_.CheckIsLastQuestion()) {
        // Pressing enter when the user is on the last question takes them to
        // the score page
        state_ = GameState::kShowScore;
        break;
      } else if (state_ == GameState::kCoverPage) {
        // Pressing enter when the user is on the cover page takes them to the
        // page where they can choose their quiz
        state_ = GameState::kChoosingQuiz;
        break;
      }
      break;
    }
    case KeyEvent::KEY_1: {
      engine_.HandleQuizChoice(1);
      // If quiz1 is valid then user can take it, otherwise goes to invalid page
      if (engine_.CheckIsValid()) {
        state_ = GameState::kTakingQuiz;
      } else {
        state_ = GameState::kInvalid;
      }
      break;
    }
    case KeyEvent::KEY_2: {
      engine_.HandleQuizChoice(2);
      // If quiz2 is valid then user can take it, otherwise goes to invalid page
      if (engine_.CheckIsValid()) {
        state_ = GameState::kTakingQuiz;
      } else {
        state_ = GameState::kInvalid;
      }
      break;
    }
    case KeyEvent::KEY_3: {
      // If quiz3 is valid then user can take it, otherwise goes to invalid page
      engine_.HandleQuizChoice(3);
      if (engine_.CheckIsValid()) {
        state_ = GameState::kTakingQuiz;
      } else {
        state_ = GameState::kInvalid;
      }
      break;
    }
    case KeyEvent::KEY_4: {
      // If quiz4 is valid then user can take it, otherwise goes to invalid page
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

  int line_index = 0; // The index of quiz_question vector
  int row = line_index - 1; // The row at which text begins printing
  FontState curr_font;

  // Go through each line in the quiz_question vector
  for (string line : quiz_question) {
    if (line_index == 0) {
      // If at the first line, then it is the question -- display in all caps
      curr_font = FontState::kCaps;
    } else if (engine_.CheckIsSelected(line_index)) {
      // If the answer choice at this index is selected, display in bold italics
      curr_font = FontState::kBoldItalic;
    } else {
      // Otherwise display it as regular text
      curr_font = FontState::kRegular;
    }

    PrintText(line, kDefaultColor, kDefaultSize,
              {getWindowCenter().x,
               getWindowCenter().y + (row++) * kLineSpacing}, curr_font);
    line_index++;
  }

  if (engine_.CheckIsLastQuestion()) {
    PrintText("Press ENTER to view results",
              Color(1, 0, 0), kDefaultSize,
              {getWindowCenter().x,
               getWindowCenter().y + (row++) * kLineSpacing},
              FontState::kBoldCaps);
  } else {
    row++;
  }
  // Display the number of the current question
  PrintText(to_string(engine_.GetCurrQuestionIndex() + 1),
            Color(1, 0, 0), kDefaultSize,
            {getWindowCenter().x,
             getWindowCenter().y + (row++) * kLineSpacing},
            FontState::kRegular);
}

void MyApp::DrawInvalid() {
  PrintText("Invalid file provided",
            Color(1, 0, 0), kDefaultSize,
            {getWindowCenter().x, getWindowCenter().y},
            FontState::kBoldCaps);
  PrintText("Press ENTER to choose another quiz!",
            Color(0, 0, 0), kDefaultSize,
            {getWindowCenter().x, getWindowCenter().y + kLineSpacing},
            FontState::kBoldCaps);
}

void MyApp::DrawBackground() {
  string image_file = "backgrounds/quizpagetext.png";
  if (state_ == GameState::kCoverPage) {
    image_file = "backgrounds/coverpage.png";
  }
  Texture2dRef background = Texture2d::create(loadImage(
          loadAsset(image_file)));

  ci::gl::draw( background, getWindowBounds() );
}

void MyApp::DrawResultsPage() {
  PrintText("Results", kDefaultColor, kDefaultSize,
            {getWindowCenter().x, getWindowCenter().y - kLineSpacing},
            FontState::kBoldCaps);
  PrintText("You scored " + to_string(int(engine_.GetScore())) + "%!",
            kDefaultColor, kDefaultSize,
            {getWindowCenter().x, getWindowCenter().y},
            FontState::kRegular);
  PrintText("Press ENTER to choose another quiz!",
            Color(0, 0, 0), kDefaultSize,
            {getWindowCenter().x, getWindowCenter().y + kLineSpacing},
            FontState::kCaps);
}

void MyApp::DrawChooseQuiz() {
  for (int i = 0; i <= kNumQuizzes; i++) {
    if (i == 0) {
      PrintText("Enter the number of the quiz you want to take",
                Color(1, .2, 1), kDefaultSize,
                {getWindowCenter().x, getWindowCenter().y},
                FontState::kBoldCaps);
    } else {
      PrintText("Quiz " + to_string(i), Color(1, 0, 1),
                kDefaultSize, {getWindowCenter().x,
                               getWindowCenter().y + i * kLineSpacing},
                FontState::kRegular);
    }
  }
}

void MyApp::PlayAgain() {
  engine_.ResetEngine();
  state_ = GameState::kChoosingQuiz;
}
} // namespace myapp