# BrainF-ckPP

> Original BF-Interpreter made by [Camto](https://www.youtube.com/watch?v=4uNM73pfJn0), which I modified to make the BrainF*ck++ interpreter

#### Brain F^ck++ is a superset of the very small language, Brain F^ck. This version has more features, (i.e. more commands) and it's all written in c++!

# How to run

If you're a Visual Studio enthusiast like me, just open up the .sln file and press ```F5```. If you don't want to do that, 
go to [build/Release](BrainFuckPP/build/Release) and run the ```BrainFuckPP.exe``` executable

# What's new

well, theres all of the original commands...

1. '```+```' Adds 1 to the current cell.
2. '```-```' Subtracts 1 to the current cell.
3. '```<```' Goes to the previous cell.
4. '```>```' Goes to the next cell. 
5. '```.```' Prints the byte at the current cell.
6. '```,```' Takes a 1 byte input, and places it at the current cell.
7. '```[```' Starts a while loop, until the current cell is 0.
8. '```]```' Loop back to the first bracket if the current cell is still not 0.

but then theres the new commands...

9. '```^```' Squares the current cell.
10. '```/```' Turns the next print statement into litteral. (Instead of printing an ascii character, it prints the actual number)
11. '```\```' Ignores the cell next to it.
12. '```#```' Ignores all of the characters inside the #'s. (i.e. : ```# This is a comment. #```)
13. '```$```' Clears the console.
