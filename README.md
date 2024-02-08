# numerical-integral
C++ code to solve integrals via the basic definition of a definite integral. 

Mathematical Prerequisites- <br>
1.) The function must be **continuous** and **bounded** between the limits specified. <br>
2.) The function must have defined values for the upper and lower limits.

How does it work ?<br>
1.) This code uses the literal definition of a definite integral. <br>
2.) Since the function is defined as *continuous* between the two intervals, it can be visualised as the area under the curve, over the x axis.<br>
3.) Since the value of the definite integral is the area under the curve, we can find the definite integral if we find the area enclosed by the curve.<br>
4.) This area under the curve can be visualised as the sum of the areas of infinite rectangles. These rectangles, or "strips" are infitessimally small. This is mathematically known as a <a href = "https://en.wikipedia.org/wiki/Riemann_sum">Reimann Sum</a>. 

How to run it ?<br>
1.) The file is in c++. It requires you to have the gnu c++ compiler (doesn't need to be gnu, but it's tested on gnu) so that it can be turned into an executable for your computer to run.<br>
2.) Assuming you already have gnu, open up your terminal of choice and put in the command "g++ integral.cpp" in the directory where you've saved the file. (You can use the "cd" command to navigate through your directories.)<br>
3.) Assuming the last step went smoothly and without errors (which it should), you need to type in "./a.out" to execute the executable created by the compiler.<br>
4.) The code is now executed.<br>
