# Overview
As part of my continued learning and practice with C++, I developed a pack-opening simulator application based off the current app Pokemon TCG Pocket. The software allows a user to simulate the experience of opening card pack, where the user can select a specific pack type, specify how many packs they want to open, and then receive randomized cards based on actuall game pack pull probabilities.

My goal in writing this software was to further explore C++ concepts such as random number generation, file handling, and working with JSON data. This project gave me an opportunity to practice handling complex data structures (like packs of cards), incorporating external libraries (such as JSON for C++), and designing a simple yet engaging user interface for a console-based application.

[Software Demo Video](https://www.awesomescreenshot.com/video/34471766?key=02ed03c90c68b8d04eb66cfbbcb20a6f)

# Development Environment
- Programming Language: C++
- Libraries: 
    - nlohmann/json: A header-only library for parsing and generating JSON, which I used to load and save pack data.
- Development Environment:
    - IDE: Visual Studio Code
    - Compiler: GCC (GNU Compiler Collection) for compiling the C++ code.

# Useful Websites
- [Pokemon TCG Pocket](https://tcgpocket.pokemon.com/en-us/)
- [C++ W3Schools](https://www.w3schools.com/cpp/)
- [JSON for modern C++](https://github.com/nlohmann/json)
- [ChatGPT](https://chatgpt.com/share/67574250-209c-8005-a075-3208620a9675)

# Future Work
- Add card art
- Add a way to categorize obtained cards for easy viewing
- Inlcude an option that will run the program untill a specific card is pulled. Then displays how many packs had to be opened until the card was found.