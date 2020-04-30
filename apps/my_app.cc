// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"
#include <csv2/reader.hpp>
#include <cinder/app/App.h>
#include <cinder/gl/draw.h>
#include <cinder/gl/gl.h>
#include <mylibrary/setup.h>

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

namespace myapp {

using cinder::app::KeyEvent;
using namespace csv2;
using namespace cinder;

MyApp::MyApp() {}

template <typename C>
void PrintText(const std::string& text, const C& color,
               const cinder::ivec2& size, const cinder::vec2& loc) {
  cinder::gl::color(color);

  auto box = TextBox()
                 .alignment(TextBox::CENTER)
                 .font(cinder::Font(kNormalFont, 30))
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
  const cinder::vec2 center = getWindowCenter();
  const cinder::ivec2 size = {50, 50};
  const Color color = Color::black();

//  csv2::Reader<delimiter<','>, quote_character<'"'>, first_row_is_header<true>,
//               trim_policy::trim_whitespace> csv;
//  std::string filename = "resources/names.csv";
//  if (csv.mmap(filename)) {
//    //    const auto header = csv.header();
//    std::string value = "Hi";
//    //    auto row_iter = csv.begin();
//    //    auto row = *row_iter;
//    //    auto cell_iter = row.begin();
//    //    auto cell = *cell_iter;
//    //    cell.read_value(value);
//    PrintText(value, color, size, center);
//  }

  //  auto cell_iter = row.begin();
  //  auto cell = *cell_iter;
  //  cell.read_value(value);

  //  for (int i = 0; i < 4; i++) { auto row_iter = csv.begin(); //row_iter != csv.end(); ++row_iter) {
  //    value = "yo";
  //    auto curr_row = *row_iter;
  //    for (auto cell_iter = curr_row.begin(); cell_iter != curr_row.end(); ++cell_iter) {
  //      // Do something with cell value
  //      auto curr_cell = *cell_iter;
  //      curr_cell.read_value(value);
  //    }
  //  }
  DrawQuestion();
}
  void MyApp::keyDown(KeyEvent event) {}
  void MyApp::DrawQuestion() {
    const cinder::vec2 center = getWindowCenter();
    const cinder::ivec2 size = {50, 50};
    const Color color = Color::black();

    mylibrary::Setup* quiz = new mylibrary::Setup();
    int curr_question = quiz->get_curr_question();
    std::vector<std::string> quiz_question = quiz->retrieve_question(curr_question);
    size_t row = 0;
    PrintText("Game Over :(", color, size, center);
    for (std::string line : quiz_question) {
      PrintText(line, color, size, {center.x, center.y + (++row) * 50});
    }
  }

// namespace myapp
}