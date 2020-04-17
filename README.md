# Tetris_cpp
This is a simple program of Tetris game implemented by cpp. 
It is my first cpp program. 
There might be some potential bugs, or somewhere not so efficient to run. 
So if you guys have better idea, feel free to contact me ^_^

The core to run this program is ncurses, which is a GUI package. 
There are many tutorials on the Internet about how to install and configure ncurses cpp.
I used CLion IDE for this program. 
In CMakeLists.txt, you'll have find the packages and link them to the executable files.

Another very important package is thread, which allows you to run the program with multiple threads. 
In this program, the thread I created is to let the block fall automatically. 
The main function is to detect the keyboard event, and move left or right, or rotate the blocks.

In a word, this is a very good trial of object-oriented programming, and get familiar with GUI and multi-thread programming.

To run my project, simply enter cmake-build-debug directory, and run the executable file called 1.
Don't forget to chmod after you clone it. 
There is an error "Error opening terminal: unknown." when running it with CLion.
The error might be solved with the system environment variables TERM and TERMINFO, according to some tutorials, but still not solved by me.
But on my PC there's no problem running it with terminal. 
And the variables on my are set to "ansi" and "". 
And if you try to run it, make sure your terminal window is large enough.
Forget the other executable files, which are some simple demos when I implemented the main function.
