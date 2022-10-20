# Snake-Game
A simple snake game written in C++ using SFML library.
    
## Install
**1. Install [SFML library](https://www.sfml-dev.org/download.php)**    

**2. Install MinGW**

**3. Download the source code**
```
git clone https://github.com/yueyazhi/Snake-Game.git
```
**4. Set PATH system variable in windows**    
* Add `</path/to/sfml/>/bin`      
* Add `</path/to/mingw/>/bin`

**5. Import into Visual Studio Code**

**6. Configure `c_cpp_properties.json` in .vscode folder**
  *  Set your `</path/to/sfml/>/include` in **includePath**   
  *  Set your `</path/to/mingw/>/bin/gcc.exe` in **compilerPath**     

**7. Execute Snake-Game by terminal**   
* Compile **main.cpp**    
```   
$ g++ -c main.cpp -I"</path/to/sfml/>/include"    
```   

* Link **SFML library**
```   
$ g++ main.o -o main -L"</path/to/sfml/>/lib" -lsfml-graphics -lsfml-window -lsfml-system
```   

* Execute **main.cpp**    
```   
$ ./main.exe    
```   

## Description
Control the snake's direction by arrow keys.  
    
More food blocks you eat, higher score you get!

### Details
* Press any key to start the game.    

* The movement speed of snake increases each time after eating 10 food blocks.    
   
* Food blocks appear in random free locations on screen.    

* If player want to challenge again when game is over, press any key can restart the game.    

### Demo
![snake-game demo](https://user-images.githubusercontent.com/107618403/196966559-06ef2a34-40cf-4dab-93e3-f809ea08aa66.gif)
