// Copyright (c) 2020 [Your Name]. All rights reserved.

#include <cinder/app/App.h>
#include <cinder/app/RendererGl.h>
#include <gflags/gflags.h>

#include "my_app.h"


using cinder::app::App;
using cinder::app::RendererGl;
using std::vector;
using std::string;


namespace myapp {

DEFINE_uint32(size, 1200, "the height and width of the window");
DEFINE_string(filename, "names.csv", "the name of the quiz file");

const int kSamples = 8;

void ParseArgs(vector<string>* args) {
  gflags::SetUsageMessage(
      "Take a trivia quiz on So You Think You Can Trivia?.");
  int argc = static_cast<int>(args->size());

  vector<char*> argvs;
  for (string& str : *args) {
    argvs.push_back(&str[0]);
  }

  char** argv = argvs.data();
  gflags::ParseCommandLineFlags(&argc, &argv, true);
}

void SetUp(App::Settings* settings) {
  vector<string> args = settings->getCommandLineArgs();
  ParseArgs(&args);
  settings->setWindowSize(FLAGS_size, FLAGS_size);
  settings->setTitle("So You Think You Can Trivia?");
}

}  // namespace myapp


// This is a macro that runs the application.
CINDER_APP(myapp::MyApp,
           RendererGl(RendererGl::Options().msaa(myapp::kSamples)),
           myapp::SetUp)
