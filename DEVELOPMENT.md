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
 
        [ ] Fix parsing error (problem with source code)
        
        [ ] Create method to display quiz questions and answer on screen