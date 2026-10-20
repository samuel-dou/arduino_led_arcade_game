# arduino_led_arcade_game
This repository contains the basic information for an Arduino LED arcade game, which utilizes microelectronics to test a user's reaction speed and finger dexterity. 
It was showcased at my high school's club fair to promote the Computer Science Honor Society, and will be used for similar CS outreach events such as tech fairs / hackathons at my school.

Features:
A white light moves back and forth on the LED strip. In the center, there is a group of red panels that the user aims to hit. When the user sees that the white panel will land on the red section, they press a physical button.
This becomes a reaction speed game, where the user aims to predict the movement of the white panel accurate. If they land the white panel on the red target, the strip flashes green. If they miss, the strip flashes red.
There are five levels throughout the game. Succeeding at one level leads the user to progress to the next, and the levels repeat in a cycle indefinitely.
At Level 0: The red region is 9 pixels wide. This initiates the game for a given player, and serves to be an easy starting point for them to hit the target.
At Level 1: The red region is 5 pixels wide.
At Level 2: The red region is 3 pixels wide.
At Level 3: The red region is 1 pixel wide.
At Level 4: The red region is 1 pixel wide, and it moves up and down the strip as well. This is the 'ultimate' level, which proves to be quite difficult for most players.

Hardware:
Arduino UNO R3, WS12812b LED strip (144 panels), 5 inch diameter arcade button, Breadboard, 220 ohm resistor, 10k ohm resistor, 1000 mirofarad capacitor. The circuit diagram can be found at arcade_circuit_diagram-6.jpg.

Implementation:
LED Indexing - the program iterates through each element of the LED strip, using a loop to activate and deactivate every panel. 
Button Input & Success/Failure Detection - if the program detects the button being pressed (given by a HIGH input for the button pin), it checks to see if the LED Index is aligned with the target range at the given level. If yes, it flashes green and progresses to the next level. If not, it flashes red.

Engineering Process:
I had several key iterations throughout this process: The first one was a basic prototype of the white panel moving up and down the LED Strip with a red target, just to ensure that visually the game appeared to be coherent.
Next, I tried to implement the button input using a digital pin on the Arduino. To start with, I had tried to use the basic buttons that fit directly onto the breadboard from the arduino kit. While this appeared to work, that button was too small and appeared to create too much electrical noise. When I replaced the small button with the large arcade button, I realized that this electrical noise was not due to the button itself. Redesigning the circuit, I placed the 10k resistor after the digital pin to ensured that it functioned as a pull-down resistor in junction with ground - it had been in series before. Finally, after some code iterations, I implemented levels, with the final level having a moving red target for some extra difficulty. I created this by tracking a counter through the LED index: every time the LED moved, the counter increased by 1. Every time the counter reached 4, signaling 4 movements of the white LED, the red target would move. I set this number of 4 equal to a variable, allowing easy manipulation of moving the red target based on how many times the white LED moved.


Sources and Acknowledgements:
I learned the basic wiring of the LED strip and the indexing strategy for manipulating the WS2812b through this YouTube video:
Ultimate Guide to Programming LED Strips with Arduino | Wiring, Powering & Code with FastLED (https://youtu.be/zj3sa5HV2Bg?si=k6_UNSr7d26ViiZg)

I also make use of the FastLED library.

Furthermore, I would like to thank Yoav Shuall for his help with the hardware component, specifically with soldering the arcade button.
