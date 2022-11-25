# UoM Concurrent Systems | Assignment

This program simulates four-by-one hundred metres sprint relay race. There are four competing teams and four athletes in every team, each represented by a unique thread executing the run function.
The code utilise c++ map, mutexes, random number generation, synchronisation mechanisms.

### Build details

Built with mingw g++ (Rev1, Built by MSYS2 project) 12.2.0

### Formatting and commenting
- [ ] Code formatted with **Clang** based on Google style with specific parameters: { BasedOnStyle: Google, ColumnLimit: 0, IndentWidth: 4, TabWidth: 4 }
- [ ] **Doxygen** style used for commenting files, functions and other elements of the code 

### Classes implemented in the code:
1. **Competitor**
2. **StartAgent**
3. **EZAgent**
4. **FinishAgent**
5. **RandomTwister**
6. **Results**
7. **ThreadMap**

### Naming convention in the project
- macros - MACRO_NAME
-------------------------------------------
- classes - ClassName
- objects - objectName
- member functions - functionName
- private data members - (preferably) _variable_name
-------------------------------------------
- variables - (preferably) variable_name
- functions - (preferably) functionName
