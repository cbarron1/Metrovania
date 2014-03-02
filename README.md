METROVANIA
==========

Created by: Cody Barron, Andres Martin, AJ Yeh, DeVonte Appliwhite

This game was created as part of a semester long school project and in no way do we profit monetarily from it. The sprites used belong to Nintendo (Metroid) and Konami (Castlevania). The background song for Samus is titled "The End Run" from the Mass Effect 2 Soundtrack, composed by Jack Wall and owned by EA. The songs that play on the characters' death animations are "You're Not Alone" and "Rose of May" from the Final Fantasy IX soundtrack and the song that plays upon winning the game is "Victory Fanfare" from the Final Fantasy VII Soundtrack. Both of the Final Fantasy soundtracks were composed by Nobuo Uematsu and owned by Square Enix. 


Project Overview
----------------

Metrovania is a tribute to the classic games Super Metroid and Super Castlevania IV. It is a 2D side-scrolling platformer, where the objective is to kill all enemies to win. The player can choose to play as either Samus, the protagonist from Metroid, or Simon, the protagonist from Castlevania.

Installing
----------

To run on Windows, all that is needed is to download the Windows folder and run the executable inside.

To run on Linux, there are more steps involved. Before building the program the user will need to install the SDL, SDL\_image, and SDL\_mixer libraries. Apart from that, all that should be necessary is a C++ compiler. The user runs 'make' to build the program. It has been tested on both Ubuntu and Red Hat Enterprise Linux, but should work on other platforms as well. 

Controls
--------

Main Menu:

	    Up/Down: Cycle selection between Samus and Simon

	    Enter: Choose player

Movement:

	    Left/Right: move character left or right

	    Up: aim up

	    Down: Crouch

	    Space: Jump

Samus:

	    W: aim diagonally up

	    S: aim diagonally down

	    Q: shoot / (Deploy bomb if in morph ball)

	    Down: Enter morph ball (if already crouching)

Simon:

	    Q: use whip

	    A: taunt
	    
General:

	    Press ESC to exit program

Issues
------

PulseAudio could possibly cause problems with loading the sounds, causing the game to crash. This appears to be machine specific as the error has only occurred on one of the computers that we have tested on.








