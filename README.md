# bserg-allegro
Game i made in c++ using the allegro game programming library

## Purpose
Get a better understand how games work on a lower level (compared to Unity).  
During this project i also wanted to implement it using a Data Oriented Design.7

## Results
So i tried to test how many objects i could place on the screen and doing some simple logic, while still having 60 frames per second on my old laptop.  
I tried to compare it to object oriented programming, and also tried to use SIMD Vector instructions and other smart instructions to improve the performance, but it turned out that the compiler was smart enough to do that itself, so the performance gain was negligeble.  
It turned out that even on bad computers you can spawn plenty of objects (if its very simple logic, like continously moving to a random position, then millions) while having a good FPS. 


# What is what
Engine folder contains files that are not exclusively for the game itself  
bserg-allegro folder contains files that are unique for the game itself

# How to do anything in the game
Well the game isn't fun at all, but you can add more "workers" to the game by pressing any of the number keys (not on keypad), and the you can remove the objects again in the UI.
