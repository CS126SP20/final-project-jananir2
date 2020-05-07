# So You Think You Can Trivia?

*Author:* Janani Rajadurai

## **_Project Details_**
**_Objective_**: Create an application that allows the user to take trivia quizzes in the form of multiple choice questions and calculates their score as a percentage! The user will be able to choose from multiple quizzes that they can take as a fun way to test their knowledge of unique trivia!

**_Use of External Libraries_**:
* **CSV2** - This library will be used to create trivia quizzes from csv files containing trivia questions, 4 answers choices, and a correct answer. It will parse through the CSV file in order to create a quiz format that the user can read and answer.
  * *GITHUB:* https://github.com/p-ranav/csv2

**_Background Knowledge/Motivation_**:
* I used to play trivia games when I was younger very frequently, so I am very familiar with the kinds of features that such an application would require the implementation of.
* The application will also incorporate features that were used in the snake application. For example, rendering text on the screen to display quiz questions and answers will require using Cinder's text boxes as well as other Cinder graphical features.
* I am motivated to work on a project that is equally heavy on both the frontend and backend aspects:
  * Frontend will involve making the quiz visually appealing for the user to take in addition to displaying questions and answer choices, their score, etec.
  * Backend will involve taking in key strokes from the user (keyboard buttons A,B,C,D) to answer the quiz questions, keeping track of the users' correctly/incorrectly answered questions, and parsing through the csv files that contains the trivia quiz information.
  
**_Timeline_**:

*Week:*
  1. I will have completed the logic for creating an animated human and implement functions that allow a certain animation to be applied to it. I will start working on the UI where the user can choose, by clicking a button, the movements to be added to the routine.
  1. I will have created the UI for viewing quiz questions.
  1. I will have added features so that the user can go to the next question, get their score on their trivia quiz, and finish the rest of the application.

**_Stretch Goals_**:
* Allow the user to upload their own quizzes which can be taken as an argument to the program using gflags.
* Create a feature that keeps track of the users' best scores for each quiz using sqlite3 (and/or see below)
* Randomize quiz questions so that the user isn't taking the same quiz every time.