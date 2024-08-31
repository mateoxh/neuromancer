## Overview

Neuromancer is a **chess engine** compatible with the UCI protocol.

The program can be used from the command line but a graphical user interface (GUI) is recommended to be able to display the chessboard and for a more comfortable way to analyze chess positions
. A list of chess GUIs can be found [here](https://github.com/official-stockfish/Stockfish/wiki/Download-and-usage#download-a-chess-gui).


### Rating

You can check out the ELO rating at the [CCRL website](https://computerchess.org.uk/ccrl/404/cgi/engine_details.cgi?print=Details&each_game=1&eng=Neuromancer%201.4%2064-bit#Neuromancer_1_4_64-bit)

## Installing

To build the program you need a compiler that supports the C++20 standard.

After downloading the sources run these commands

	cd neuromancer/src/
	make -j

You should now have a binary that is specifically optimized for your platform.
