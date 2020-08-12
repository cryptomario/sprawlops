# sprawlops
WARNING: This code is by no means production grade. It does almost no input validation or error handling and has not been tested. Use at your own risk.

LICENSE: CC0 (public domain).

This repo contains two things:
1. A program to simulate dice-rolls for the Shadowrun:Sprawl Ops board game.
2. Tools to examine the results and prepare graphs.

The program
-----------
The program can be used to simulate a variety of experiments with varying skill levels, difficulty, armor points and re-rolls.


Data analysis
-------------
Prerequesites: For data processing, gnuplot is used.
runexperiments.sh is an example script that runs experiments with and without armor and re-rolls.
The results can then be plotted using the sprawlops.gnuplot script.


Version history
---------------
0.1 Minimal functional program: Roll single-color dice for a team consisting of a single runner.

0.2 Added options for armor points and re-rolls. Options can now be passed via a file



