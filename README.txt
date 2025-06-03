BASIC INTRO
- basic breakout
- simple GUIs to control game flow
- basic texts to show current score and highest score
- ball and paddle increases in speed proportionally, paddle becomes smaller to introduce some sense of difficulty increase
- basic audio for ball - brick collision and ball - paddle collision
- not using any physics engine
- SFML 3
- TGUI 1.9

- zip should contain 
	- Breakout folder ** source codes in here along with some other resource files like .wav/.txt/.ttf
	- SFML-3.0.0 folder ** proj is set to point to this for external dependencies like \lib and \include
	- TGUI-1.9 folder ** proj is set to point to this for external dependencies like \lib and \include
	- x64 folder ** exe and pdb should be generated here when first compile, zip does not contain them
		- Debug folder ** all required debug dlls should be here 
		- Release folder ** all required release dlls should be here 
	- Breakout.sln 
	- README.txt


References/Resources:
https://chatgpt.com/
https://www.bfxr.net/
https://tgui.eu/documentation/latest-stable/annotated.html
https://www.sfml-dev.org/tutorials/3.0/
https://www.reddit.com/r/gamedev/comments/1hntnb6/sfml3_or_sdl3/
https://www.youtube.com/watch?v=mdp9neFHXY8&list=PL8YBKOHPqM68Ia0LE590qq0w6jKR0fJvd&index=2
https://play.arkanoid.online/?lang=en
https://en.cppreference.com/w/cpp/container/vector.html
https://fonts.google.com/specimen/Comic+Relief
https://stackoverflow.com/questions/79523065/compatibility-errors-with-sfml-and-tgui