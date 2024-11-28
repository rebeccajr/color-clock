As a child, I could spend entire days engrossed in puzzles. My favorites were the Mind Benders series logic puzzles, where a set of clues were provided to determine matches with limited information, such as figuring out which child owned which pet. I found immense satisfaction in solving these problems and took comfort in the certainty that there was always one correct solution. My chosen career path reflects this passion for problem-solving. Today, the puzzles I tackle are far more complex, with numerous possible solutions, each varying in its degree of optimality.

---
## The Circuit Board

My big puzzle for the week has been how to lay out the final circuit board. There wasn't enough time to have a board printed, so I'll be wiring and soldering everything manually. For the second version of ColorClock, I would like to design a printed circuit board (PCB) to simplify the soldering effort. All integrated component boards, e.g. level shifter, Arduino board, will be attached to the board with female headers, so if a component dies for some reason it can easily be swapped out without re-soldering.

I decided to go with a board that is connected much like a solderless prototyping breadboard, where each column of holes are electrically connected. This does limit the possible orientation of the modules, but it will make the final wiring a little easier given that it can be laid out nearly exactly the same as the solderless prototype.

<>

This photo shows the underside of one of the ElectroCookie breadboards. The project will have two boards side by side to accommodate for all of the control electronics. The stand offs in the middle of the board are to raise it up off the bottom of the electronics enclosure.

<>

This diagram illustrates the layout of the board, and is mostly to scale. The groups of wires extending beyond the breadboard's borders will be routed to external electronics, such as the participant buttons, power input, and light display. Although the wires are shown overlapping the modules in the diagram, they will actually be routed underneath the modules, as the modules will be elevated using female headers.

<>

This diagram illustrates the soldering layout primarily for the wires and female headers.

---
## The Box

The control panel enclosure will house the participant-facing buttons in addition to the control electronics for the installation, i.e. the breadboard discussed earlier in this post. I was planning on modeling and 3D printing the enclosure, but now I am contemplating making it out of wood and simply printing an enclosure for the breadboard that will sit inside the box. With regards to the enclosure as a whole, there are a few mechanical factors to consider, like how it will be mounted and accessed from the outside in case of malfunction.

The participant control panel will be located beneath the light display, which is mounted on a 45-degree wooden panel. The enclosure is designed as a diagonally cut rectangular prism to position the buttons vertically for easy access.

<>

This is the initial 3D model I was planning on printing. The triangular holes in the front are for the arcade buttons that the participants can use to modify one of the LED strips. With this design, there is no way to access the enclosed electronics without unscrewing the cover from the wooden panel that it would be mounted to.

<>

The little nubs at the bottom of the box are to stabilize the stand offs used to elevate the circuit board off the bottom of the box.

---
## The Structure

My partner, Bo, has been working hard on the structure, experiencing a multitude of challenges, and has practically rebuilt the frame, piece by piece. Home Depot has become our second home 😅 I have such immense respect for his tenacity in constructing a sturdy frame to bring my vision to fruition.

<>

We each spent most of the day working on our respective parts of ColorClock. I was mostly CAD-ing in the AC while he was sweating in the garage playing with power tools.

<>

This is Bo's exasperated "I can't wait to burn this thing" look. I love him 😘

<>

Me, for scale.

---
## TODOs For This Week

- Solder circuit board
- Model circuit board enclosure
- Modify software to output lower power at night


---
LinkedIn post

As a child, I found satisfaction in solving puzzles and comfort in knowing that there was always one 'correct' solution. As an engineer, the puzzles I get to solve have many 'correct' solutions with varying degrees of optimality. My Saturday was spent figuring an 'optimal' circuit board layout for the LED art installation I've been working on. I've updated my blog with some recent ColorClock progress 🤓 #colorclockevolution