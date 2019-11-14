Project: EGRE 591: Compiler Construction Project
Language: C++
Group Members: Matthew Gelber and Jeremy Price

Part 1: completed
    - scanner/lexer

Part 2: completed
    - parser
    - abstract syntax tree

Part 3: in progress
    - code generation

Documentation for running part 3:
    - to test the main project, proceed as normal
        - make clean -> make -> tc -v "<file_name>.tc"

    - to run D_JAVA
        - download the d-java project from the class webpage
        - unzip the file into any location
        - in command/terminal navigate to where d-java is (C:\...\d-java)
        - type "make" to build the d-java program
        - using some java compiler like eclipse, write a basic java program that you want to see the assembly to
        - export that file/project/directory and copy the .class file created into the main d-java directory
        - navigate back to where d-java is located and type (for windows) "D-Java.exe -o jasmin main.class>file_name.txt"
        - the ">file_name.txt" sends the output from d-java to that file

    - to run Jasmin
        - go to http://jasmin.sourceforge.net/ and download the jasmin file
        - jasmin is already compiled into a .jar file
        - when you run the main project, a .j file will be created in the bin directory
        - .j files are needed for input for jasmin in order to create the .class file
        - navigate to the directory where jasmin-<version#> is located and copy the .j from
          the compiler project bin folder into the examples folder in the jasmin directory
        - in the C:\...\jasmin-<version#> directory type "java -jar jasmin.jar examples\<file_name_you_just_pasted>.j"
        - this should result in an output message "Generated: main.class"