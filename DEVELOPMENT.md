# Development

---
 - **4/14/20** Finished final project proposal
 
 - **4/18/20** Started working on building Horde3D library
 
 - **4/20/20** Linked Horde3D library to cinder app
 
 - **4/23/20** Was able to include Horde3D header file in my_app
    - Need to fix error where application window doesn't open
    
 - **4/25/20** Tried to fix runtime error that prevents application window from opening
    
 - **4/26/20** Linked nanogui library in case that would work better than Horde3D
    - Got the same error as with Horde3D
    - Switched to header-only library called CSV2 to avoid the same run-time error
    - Changed project idea completely because this library would not accomplish original goals
    - Linked CSV2 library to cinder
    
 - **4/27/20** Worked on component of project for parsing through CSV files using library
    - Modified method in CSV2 source file because of error thrown when constructing library-specific object
    - Created trivia quiz CSV files containing:
        - Question
        - 4 Answer Choices
        - Correct Answer
        
 - **4/28/20** Updated project proposal on github
    - Need to work on the following:
  
        [x] Fix parsing error (problem with source code)
        
        [x] Create method to display quiz questions and answer on screen
        
 - **4/29/20**
    - Created class and implemented methods for setting up trivia quiz display
    - Added logic for going back and forth on questions
    
 - **4/30/20** Worked on parsing error
    - Used debugger to figure out that error was due to not being able to access file
    - Posted on piazza for help on how to get correct filepath
    
 - **5/1/20** Fixed parsing error with help from piazza
    Need to:
    
      [x] Fix error preventing main class from accessing helper methods
        
 - **5/2/20** Worked on UI
    - Changed font and background display
    - Still need to:
    
        [ ] Add logic for calculating score
        
        [x] Add logic for answering questions using keyboard   
             
 - **5/3/20** Completed logic for taking in users' answers
    - Completed command line component where user can pass in their own quiz file
    - Added cover page and results page
    - Almost done with score calculation method
    - Still need to:
    
        [x] Fix error where only choice D is selected
        
        [x] Add logic fo italicizing selected questions
        
 - **5/3/20** Completed application and began testing
    - Added feature where user can enter their own quiz csv file(s)
    - Added feature where user can choose which quiz to take
    - Need to:
    
        [ ] Finish testing
        
        [ ] Complete README.md
        
        [ ] Add documentation using comments