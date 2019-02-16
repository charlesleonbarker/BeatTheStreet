/* Charles Barker
P15181036
March 2017 */
#include "game.h"

//Deafult
game::game()
{
	window = new sf::RenderWindow(sf::VideoMode(800, 830), "Beat the Street", sf::Style::Close);//Initialize render window and properties, inc Name, Size, Style.
	window->setFramerateLimit(60); //Limit refresh rate to 60fps
	window->setPosition(sf::Vector2i(100, 100)); //Set window position in relation tot the top left of the screen. 
	window->setKeyRepeatEnabled(false); //Disable key repeat, so that the user must press the button for every movement.

	mBackgroundMusic = new sf::Music;//Initialize background music 
	if (!mBackgroundMusic->openFromFile(".\\Assets\\audio\\backgroundmusic.ogg"))EXIT_FAILURE;//Load music file
	mBackgroundMusic->setLoop(true);//Set the music to loop
	mBackgroundMusic->play(); //Start playing
	mBackgroundMusic->setVolume(010);//Set Volume to 10%

	bMute = false;
}

//Int function for the aplication loop 
int game::loop()
{
	while (window->isOpen()) //While the game window is open
	{
		bool bInMenu = true;
		while (bInMenu) //While the menu is open
		{

			bool clickedPlay = bGameMenu(); //Run menu function and return if the user has clicked to play

			if (clickedPlay)//If the user clicked play
			{
				int iPlayAgain = 2;//Reset variable
				while (iPlayAgain == 2)
				{
					int iTimeTaken = 0;//Reset variable
					iPresentsCollected = 0;

					iPresentsCollected = iGameLoop();//Run the game loop and return the number of presents collected int the game
					
					if (iPresentsCollected == 999) return 0;//If user chooses to quit, the game loop returns 999, exit the program
					
					std::cout << iPresentsCollected << std::endl;

					iPlayAgain = iFailScreen();//Display the fail screen and return if the user wants to play again 
				}
				if (iPlayAgain == 0) return 0;//If the user chooses to quit, exit the program
			}
			else return 0;
		}
	}
	return 0;
}

//Bool function that displays the menu and returns true when the user has chosen to start the game.
bool game::bGameMenu()
{
	//Initiate sprites for background and menu screen
	sf::Sprite sMenuScreenBackgroundSprite, tInstructionSprite;

	//Initiate textures
	sf::Texture tInstructionTexture, sMenuScreenBackgroundTexture;

	//Load the textures, if any fail, exit the program with a failure
	if (!tInstructionTexture.loadFromFile(".\\Assets\\graphics\\400.png")) EXIT_FAILURE;
	if (!sMenuScreenBackgroundTexture.loadFromFile(".\\Assets\\graphics\\menuback.png")) EXIT_FAILURE;

	//set the textures for the sprites
	sMenuScreenBackgroundSprite.setTexture(sMenuScreenBackgroundTexture);
	tInstructionSprite.setTexture(tInstructionTexture);

	//set the sprite positions
	sMenuScreenBackgroundSprite.setPosition(0, 0);
	tInstructionSprite.setPosition(150, 115);

	//Initiate the buttons for the menu screen 
	button btonPlayNow((".\\Assets\\graphics\\buttonplay.png"), sf::Vector2f(200, 100), sf::Vector2f(300, 325));
	button btnHowToPlay((".\\Assets\\graphics\\buttonhow.png"), sf::Vector2f(200, 100), sf::Vector2f(300, 450));
	button btnClose((".\\Assets\\graphics\\close.png"), sf::Vector2f(25, 25), sf::Vector2f(650, 95));
	button btnMute((".\\Assets\\graphics\\sound.png"), sf::Vector2f(40, 30), sf::Vector2f(740, 0));
	if (bMute)btnMute.changetexture(".\\Assets\\graphics\\mute.png");				//Change pause button texture to play icon

	//Initiate the colors bright and dim, so that they can be used to dim the background when necessary.
	sf::Color bright(255, 255, 255, 255), dim(50, 50, 50, 255);

	//Initiate the boolean variables.
	bool bInMenu = true, bHowToPlayUp = false;


	//---------------------------------------------------------------------------------------------------------------


	while (bInMenu == true)// while the user is in the menu
	{
		//Initialize the event for user input/
		sf::Event event;
		while (window->pollEvent(event))
		{

			if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))//If the user chooses to close the window
			{
				return false; //Return false so that the program ends
			}

			if (btnMute.isclicked(event))//If the mute button is pressed
			{
				if (bMute == false)//If the game is currently not muted
				{
					bMute = true;											//Set Mute to true
					btnMute.changetexture(".\\Assets\\graphics\\mute.png");				//Change texture of button to un-mute
					mBackgroundMusic->setVolume(0);								//Set volume of all sounds to zero



				}
				else // if already muted
				{
					bMute = false;											//Set Mute to false
					btnMute.changetexture(".\\Assets\\graphics\\sound.png");				//Change texture of button to mute
					mBackgroundMusic->setVolume(010);								//Set volumes of sounds

				}
			}

			if (btnHowToPlay.isclicked(event) == true) //If the how to play button is clicked
			{
				bHowToPlayUp = true; //Set bHowToPlayUp to true
				sMenuScreenBackgroundSprite.setColor(dim);//set background to dim
			}

			if (bHowToPlayUp) //If the menu is up
			{
				if (btnClose.isclicked(event))// if the close button is pressed
				{
					bHowToPlayUp = false;//Set bHowToPlayUp to false
					sMenuScreenBackgroundSprite.setColor(bright); //Set the background back to bright
				}
			}

			if (!bHowToPlayUp) //If the menu is not up
			{
				if (btonPlayNow.isclicked(event))//If the play now button is clicked
				{
					bInMenu = false; //set the variable to false so that the program exits the while loop and returns true to the main function.
				}
			}
		}


		//---------------------------------------------------------------------------------------------------------------


		//Clear the render window and draw the background sprite
		window->clear(sf::Color::White);
		window->draw(sMenuScreenBackgroundSprite);

		//depending on if the menu is up or not, different things are drawn to the screen
		if (bHowToPlayUp)
		{
			window->draw(tInstructionSprite);
			btnClose.drawbutton(*window);
		}

		if (!bHowToPlayUp)
		{
			btnHowToPlay.drawbutton(*window);
			btonPlayNow.drawbutton(*window);
		}

		//Display the window
		btnMute.drawbutton(*window);
		window->display();
	}

	//Return true so that the main function knows that the user clicked to play the game.
	return true;
}

//Int function for the main game loop
int game::iGameLoop()
{
	//Initialize color used for text
	sf::Color cColourOfText(87, 42, 87);

	//Initialize Font used for text
	sf::Font fGameFont;
	if (!fGameFont.loadFromFile("gamefont.ttf"))EXIT_FAILURE;

	//Initialize text 
	sf::Text tClockText, tNumberOPresentsText;

	//Set font
	tClockText.setFont(fGameFont);
	tNumberOPresentsText.setFont(fGameFont);

	//Set color
	tClockText.setFillColor(cColourOfText);
	tNumberOPresentsText.setFillColor(cColourOfText);

	//Set font size
	tClockText.setCharacterSize(25);
	tNumberOPresentsText.setCharacterSize(25);

	//Set text position
	tClockText.setPosition(400, 0.0f);
	tNumberOPresentsText.setPosition(235, 0.0f);

	//set the string for number of presents collected to zero
	tNumberOPresentsText.setString("0");


	//---------------------------------------------------------------------------------------------------------------


	//Initialize sound buffers
	sf::SoundBuffer sbPresentCollected, sbLifeCollect;

	//Load files into sound buffers
	if (!sbPresentCollected.loadFromFile(".\\Assets\\audio\\coincollect.ogg"))EXIT_FAILURE;
	if (!sbLifeCollect.loadFromFile(".\\Assets\\audio\\life.ogg"))EXIT_FAILURE;

	//Initialize sounds
	sf::Sound sPresentCollect, sLifeCollect;

	//Set sounds to sound buffers
	sPresentCollect.setBuffer(sbPresentCollected);
	sLifeCollect.setBuffer(sbLifeCollect);


	//---------------------------------------------------------------------------------------------------------------


	//Initialize vectors used for sizes of sprites
	sf::Vector2f v2fSizeofPresentIcon(30, 35), v2fSizeOfCountIn(400, 400);

	sf::Sprite sInGameBackgroundSprite, sCountIn1, sCountIn2, sCountIn3, sPresentIcon;

	//Initialize Sprite textures
	sf::Texture tInGameBackgroundTexture, tPresentIcon, tCountIn1, tCountIn2, tCountIn3;

	//load textures
	if (!tInGameBackgroundTexture.loadFromFile(".\\Assets\\graphics\\Background.png")) EXIT_FAILURE;
	if (!tPresentIcon.loadFromFile(".\\Assets\\graphics\\present.png")) EXIT_FAILURE;
	if (!tCountIn1.loadFromFile(".\\Assets\\graphics\\countin1.png"))EXIT_FAILURE;
	if (!tCountIn2.loadFromFile(".\\Assets\\graphics\\countin2.png"))EXIT_FAILURE;
	if (!tCountIn3.loadFromFile(".\\Assets\\graphics\\countin3.png"))EXIT_FAILURE;

	//Set sprite textures
	sInGameBackgroundSprite.setTexture(tInGameBackgroundTexture);
	sPresentIcon.setTexture(tPresentIcon);
	sPresentIcon.setTextureRect(sf::IntRect(0, 0, 50, 75));
	sCountIn1.setTexture(tCountIn1);
	sCountIn2.setTexture(tCountIn2);
	sCountIn3.setTexture(tCountIn3);

	//Set sprite scales
	sPresentIcon.setScale(v2fSizeofPresentIcon.x / 60, v2fSizeofPresentIcon.y / 80);
	sCountIn1.setScale(v2fSizeOfCountIn.x / tCountIn1.getSize().x, v2fSizeOfCountIn.y / tCountIn1.getSize().y);
	sCountIn2.setScale(v2fSizeOfCountIn.x / tCountIn2.getSize().x, v2fSizeOfCountIn.y / tCountIn2.getSize().y);
	sCountIn3.setScale(v2fSizeOfCountIn.x / tCountIn3.getSize().x, v2fSizeOfCountIn.y / tCountIn3.getSize().y);

	//Set sprite origins
	sInGameBackgroundSprite.setOrigin(0, 0);
	sPresentIcon.setOrigin(0, 0);
	sCountIn2.setOrigin(v2fSizeOfCountIn.x / sCountIn2.getScale().x / 2.0f, v2fSizeOfCountIn.y / sCountIn2.getScale().y / 2.0f);
	sCountIn1.setOrigin(v2fSizeOfCountIn.x / sCountIn1.getScale().x / 2.0f, v2fSizeOfCountIn.y / sCountIn1.getScale().y / 2.0f);
	sCountIn3.setOrigin(v2fSizeOfCountIn.x / sCountIn3.getScale().x / 2.0f, v2fSizeOfCountIn.y / sCountIn3.getScale().y / 2.0f);

	//Set sprite positions
	sInGameBackgroundSprite.setPosition(0, 0);
	sPresentIcon.setPosition(204, 0);
	sCountIn1.setPosition(400, 415);
	sCountIn2.setPosition(400, 415);
	sCountIn3.setPosition(400, 415);


	//---------------------------------------------------------------------------------------------------------------


	//Construct the collectible present
	Presents cpPresent;

	//Construct the collectible hearts
	collectableLives clLife;

	//Construct the pause and mute buttons
	button btonPause((".\\Assets\\graphics\\pause.png"), sf::Vector2f(30, 30), sf::Vector2f(700, 0));

	button btnMute((".\\Assets\\graphics\\sound.png"), sf::Vector2f(40, 30), sf::Vector2f(740, 0));
	if (bMute)btnMute.changetexture(".\\Assets\\graphics\\mute.png");				//Change pause button texture to play icon
	

	//Construct the game obstacles
		//Water obstacles
		obsticle	 oBoat1(5, 2, 1, 700);
		obsticle	 oBoat2(6, 2, 1, -200);
		obsticle	 oBoat3(7, 3, 0, 100);
		obsticle	 oboat4(5, 3, 0, 500);
//		obsticle	 oBoat5(6, 4, 1, 100);
		obsticle	 oBoat6(5, 4, 1, 400);
		obsticle	 oBoat7(7, 5, 0, 700);
		obsticle	 oBoat8(6, 5, 0, 10);
		obsticle	 oBoat9(5, 6, 1, 700);
		obsticle	 oBoat10(6, 6, 1, 380);

		//Train obstacles
		obsticle	 oTrain1(4, 8, 0, -400);
		obsticle	 oTrain2(4, 9, 1, 1300);

		//Road obstacles
		obsticle	 oCar1(1, 11, 0, 100);
		obsticle	 oCar2(2, 11, 0, 500);
		obsticle	 oCar3(3, 12, 1, 100);
		obsticle	 oCar4(3, 12, 1, 400);
		obsticle	 oCar5(2, 13, 1, 700);
		obsticle	 oCar6(2, 13, 1, 10);
		obsticle	 oCar7(1, 14, 0, -10);
		obsticle	 oCar8(1, 14, 0, 500);
		obsticle	 oCar9(2, 15, 1, 400);
		obsticle	 oCar10(3, 15, 1, 10);


	//Construct the player
	Player myPlayer;

	//Construct the lives that 
	livesRemaining playerLivesRemaining;


	//---------------------------------------------------------------------------------------------------------------


	//Initialize game event

	//Initialize clocks;
	sf::Clock cObsticleMovementClock, cGameClock, cPauseClock, cCountInClock;

	//Initialize times;
	sf::Time tTotalPauseTime, tTempPauseTime, tCountInTime, tGameElapsedTime, tObsticleMovementTime;

	//Initialize boolean variables
	bool bIsPlayerDead = false;
	bool bIsPaused = false;
	bool bIsGameRunning = true;
	bool bIsExtraLifeOnScreen = false;
	bool bCountingIn = true;
	bool bPlayerFadingIn = true;

	//Initialize integer variables
	int iTimetakenInMilliseconds = 0;
	int itimetofadeininms = 1000;
	int iLivesRemaining = 3;

	//Initialize float Variables
	float fExtraObsticleSpeed = 0;


	//---------------------------------------------------------------------------------------------------------------


	while (bIsGameRunning)//Game Loop that refreshes every frame.
	{
		sf::Event event;
		while (window->pollEvent(event))//While event is polled
		{
			if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))//If user chooses to close
			{
				window->close();			//Close the window
				return 999;				//So that the main function knows to end program
			}

			if (!bIsPaused && !bCountingIn)//Movement only possible when not pause and not counting in.
			{
				if (event.type == sf::Event::KeyPressed)//If a key is pressed on the keyboard.
				{
					//Depending on which key is pressed, myPlayer.moveplayer is triggered.
					if (event.key.code == sf::Keyboard::Up)				myPlayer.movePlayer('u');
					else if (event.key.code == sf::Keyboard::Down)		myPlayer.movePlayer('d');
					else if (event.key.code == sf::Keyboard::Left)		myPlayer.movePlayer('l');
					else if (event.key.code == sf::Keyboard::Right)		myPlayer.movePlayer('r');
				}
			}

			iTimeTaken = iTimetakenInMilliseconds;

			if (btonPause.isclicked(event) && !bCountingIn)//If the pause button is clicked -- can not pause when counting in
			{
				if (!bIsPaused)//if not paused
				{
					//Pause
					btonPause.changetexture(".\\Assets\\graphics\\play.png");				//Change pause button texture to play icon
					bIsPaused = true;											//Set bPause to true so movement further on in the code does not continue
					cPauseClock.restart();										//Restart the pause clock so it can count how long the game has been paused
				}
				else
				{
					//Un-pause
					btonPause.changetexture(".\\Assets\\graphics\\pause.png");			//Change button texture back to pause icon
					bIsPaused = false;											//Set bPause to false
					tTempPauseTime = cPauseClock.getElapsedTime();				//Get the time spent in the pause state
					tTotalPauseTime = tTotalPauseTime + tTempPauseTime;			//Add this temporary pause time to the overall pause time, so that the clock ac adjust accordingly
				}
			}

			if (btnMute.isclicked(event))//If the mute button is pressed
			{
				if (bMute == false)//If the game is currently not muted
				{
					bMute = true;											//Set Mute to true
					btnMute.changetexture(".\\Assets\\graphics\\mute.png");				//Change texture of button to un-mute
					mBackgroundMusic->setVolume(0);								//Set volume of all sounds to zero
					sPresentCollect.setVolume(0);
					sLifeCollect.setVolume(0);

				}
				else // if already muted
				{
					bMute = false;											//Set Mute to false
					btnMute.changetexture(".\\Assets\\graphics\\sound.png");				//Change texture of button to mute
					mBackgroundMusic->setVolume(010);								//Set volumes of sounds
					sPresentCollect.setVolume(100);
					sLifeCollect.setVolume(100);
				}
			}
		}


		//---------------------------------------------------------------------------------------------------------------


		if (!bIsPaused)//Only do this if the game is not muted, there is no need to so some of this if the game is muted, waste of processing power
		{

			//The time for the game is taken from the game clock.
			tGameElapsedTime = cGameClock.getElapsedTime();

			//Time is then taken as milliseconds and assigned as an integer to ITimeTakenInMiliseconds. The total paused time is then taken off, along with 3000 milliseconds for the countdown at the beginning of the game.
			iTimetakenInMilliseconds = tGameElapsedTime.asMilliseconds() - tTotalPauseTime.asMilliseconds() - 3000;

			//Whilst the game is counting down, display the time as 00:00
			if (bCountingIn)tClockText.setString("00:00");

			//After the counting in has finished set the time. The sTimeToString function is used to convert the time in milliseconds to a suitable string format.
			else tClockText.setString(sTimeToString(iTimetakenInMilliseconds));

			//A clock is used to ensure the obstacles move at a constant speed, not relying on frame rate.
			tObsticleMovementTime = cObsticleMovementClock.getElapsedTime();


			if (tObsticleMovementTime.asSeconds() > (1 / 60))	//If the obstacle movement time is above 1/60th of a second.
			{
				//All obstacles are moved using the .moveObsticle function. The "extraspeed" is also passed though to the function, so that the obstacles move at the adjusted speed.
				oBoat1.moveObsticle(fExtraObsticleSpeed);
				oBoat2.moveObsticle(fExtraObsticleSpeed);
				oBoat3.moveObsticle(fExtraObsticleSpeed);
				oboat4.moveObsticle(fExtraObsticleSpeed);
		//		oBoat5.moveObsticle(fExtraObsticleSpeed);
				oBoat6.moveObsticle(fExtraObsticleSpeed);
				oBoat7.moveObsticle(fExtraObsticleSpeed);
				oBoat8.moveObsticle(fExtraObsticleSpeed);
				oBoat9.moveObsticle(fExtraObsticleSpeed);
				oBoat10.moveObsticle(fExtraObsticleSpeed);
				oTrain1.moveObsticle(fExtraObsticleSpeed);
				oTrain2.moveObsticle(fExtraObsticleSpeed);
				oCar1.moveObsticle(fExtraObsticleSpeed);
				oCar2.moveObsticle(fExtraObsticleSpeed);
				oCar3.moveObsticle(fExtraObsticleSpeed);
				oCar4.moveObsticle(fExtraObsticleSpeed);
				oCar5.moveObsticle(fExtraObsticleSpeed);
				oCar6.moveObsticle(fExtraObsticleSpeed);
				oCar7.moveObsticle(fExtraObsticleSpeed);
				oCar8.moveObsticle(fExtraObsticleSpeed);
				oCar9.moveObsticle(fExtraObsticleSpeed);
				oCar10.moveObsticle(fExtraObsticleSpeed);
				cObsticleMovementClock.restart(); //reset the movement clock to zero
			}

			//---------------------------------------------------------------------------------------------------------------

			//playerContact function returns true if the object intersects with the floatrect that is passed through to it.
			if (oTrain1.playerContact(myPlayer.playerIntercectBounds(), 0) ||
				oTrain2.playerContact(myPlayer.playerIntercectBounds(), 0) ||
				oCar1.playerContact(myPlayer.playerIntercectBounds(), 0) ||
				oCar2.playerContact(myPlayer.playerIntercectBounds(), 0) ||
				oCar3.playerContact(myPlayer.playerIntercectBounds(), 0) ||
				oCar4.playerContact(myPlayer.playerIntercectBounds(), 0) ||
				oCar5.playerContact(myPlayer.playerIntercectBounds(), 0) ||
				oCar6.playerContact(myPlayer.playerIntercectBounds(), 0) ||
				oCar7.playerContact(myPlayer.playerIntercectBounds(), 0) ||
				oCar8.playerContact(myPlayer.playerIntercectBounds(), 0) ||
				oCar9.playerContact(myPlayer.playerIntercectBounds(), 0) ||
				oCar10.playerContact(myPlayer.playerIntercectBounds(), 0)
				)
			{
				bIsPlayerDead = true; //player is dead
			}

			if (myPlayer.water())//.water function returns true if the player is in the water area of the screen
			{
				//If the player contacts any of the boats
				if (oBoat1.playerContact(myPlayer.playerIntercectBounds(), 1) ||
					oBoat2.playerContact(myPlayer.playerIntercectBounds(), 1) ||
					oBoat3.playerContact(myPlayer.playerIntercectBounds(), 1) ||
					oboat4.playerContact(myPlayer.playerIntercectBounds(), 1) ||
				//	oBoat5.playerContact(myPlayer.playerIntercectBounds(), 1) ||
					oBoat6.playerContact(myPlayer.playerIntercectBounds(), 1) ||
					oBoat7.playerContact(myPlayer.playerIntercectBounds(), 1) ||
					oBoat8.playerContact(myPlayer.playerIntercectBounds(), 1) ||
					oBoat9.playerContact(myPlayer.playerIntercectBounds(), 1) ||
					oBoat10.playerContact(myPlayer.playerIntercectBounds(), 1))
				{
					myPlayer.moveOnBoat(fExtraObsticleSpeed); //.moveOnLog function moves the player so that it moves with the boat that it is on. 
				}
				else //if the player is in the water but not on a boat.
				{
					bIsPlayerDead = true;//the player is dead.
				}
			}

			if (myPlayer.playerXPosition() > 800 || myPlayer.playerXPosition() < 0) //if the players origin is taken off the screen by a boat 
			{
				bIsPlayerDead = true;													//the player is dead.
			}

			if (bIsPlayerDead) //if the player is dead
			{
				bIsPlayerDead = false;													//Set player dead to false.
				iLivesRemaining = myPlayer.lostLife(bMute);
				myPlayer.resetPlayer(cpPresent.playerMovingDown());						//Reset the players position back to the start.
				if (iLivesRemaining < 1)												//If the player has zero lives remaining
				{
					bIsGameRunning = false;												//Set the game running bool to false so that the game knows to exit
				}
			}


			//---------------------------------------------------------------------------------------------------------------


			if (cpPresent.presentContact(myPlayer.playerIntercectBounds()))//if the present and the player intersect
			{
				iPresentsCollected++;													//Add one to the number of presents collected
				cpPresent.movePresent();												//move the present to a new position wising the movePresent function
				sPresentCollect.play();													//Play the sound for collect a present
				tNumberOPresentsText.setString(std::to_string(iPresentsCollected));		//Set the string for the number of presents collected. the to_string function comes from the std namespace and changes an int to a string
				fExtraObsticleSpeed = 0.15f*iPresentsCollected;							//Change the extraspeed variable because another present has been collected 
				mBackgroundMusic->setPitch(1 + (0.05*iPresentsCollected));

				if (iPresentsCollected % 4 == 0 && iPresentsCollected != 0 && iLivesRemaining != 3 && !bIsExtraLifeOnScreen)//If the new number of presents collected is a multiple of four and the player does not have full lives

				{
					clLife.newheart(myPlayer.playerYPosition());								//Add a collectible life to the screen, the function uses the players y position, so that the life is as far away as possible from the player.
					bIsExtraLifeOnScreen = true;										//set the bool of life on screen to true
				}
			}

			if (clLife.lifeContact(myPlayer.playerIntercectBounds()))//If the player contacts a collectible life
			{
				sLifeCollect.play();													//Play the collect life sound
				bIsExtraLifeOnScreen = false;
				iLivesRemaining = myPlayer.gainedlife();								//player lives increase by one
				clLife.removeLife();													// Remove the heart from the screen
			}


			//---------------------------------------------------------------------------------------------------------------


			clLife.anamate();
			cpPresent.anamate();
		}


		//---------------------------------------------------------------------------------------------------------------


		//clear the render window and draw all the background information.
		window->clear(sf::Color::White);
		window->draw(sInGameBackgroundSprite);
		window->draw(tClockText);
		window->draw(tNumberOPresentsText);
		window->draw(sPresentIcon);
		btonPause.drawbutton(*window);
		btnMute.drawbutton(*window);
		playerLivesRemaining.drawlives(*window, iLivesRemaining);


		//DUE TO THE 3D LOOK OF THE GAME, ALL SPRITES MUST BE DRAWN IN ORDER, FROM TOP TO BOTTOM.
		//DEPENDING ON THE Y-POSISION OF THE SPRITES, THEY MUST BE DRAWN AT DIFFRENT TIMES.
		//SPRITES THT CAN CHANGE Y-POSISION (myPlayer, clLife, and cpPresent ) HAVE IF STATMENTS TO DRAW THEM IN THE OCORRECT ORDER


		//============================================================================================
		if (myPlayer.playerYPosition() == 55)myPlayer.drawPlayer(*window);
		if (cpPresent.YPosition() == 55)cpPresent.drawPresent(*window);
		if (clLife.spriteYPosition() == 55)clLife.drawLifes(*window);
		//============================================================================================
		oBoat1.drawObsticle(*window);
		oBoat2.drawObsticle(*window);
		if (myPlayer.playerYPosition() == 105)myPlayer.drawPlayer(*window);
		//============================================================================================
		oboat4.drawObsticle(*window);
		oBoat3.drawObsticle(*window);
		if (myPlayer.playerYPosition() == 155)myPlayer.drawPlayer(*window);
		//============================================================================================
		//oBoat5.drawObsticle(*window);
		oBoat6.drawObsticle(*window);
		if (myPlayer.playerYPosition() == 205)myPlayer.drawPlayer(*window);
		//============================================================================================
		oBoat7.drawObsticle(*window);
		oBoat8.drawObsticle(*window);
		if (myPlayer.playerYPosition() == 255)myPlayer.drawPlayer(*window);
		//============================================================================================
		oBoat9.drawObsticle(*window);
		oBoat10.drawObsticle(*window);
		if (myPlayer.playerYPosition() == 305)myPlayer.drawPlayer(*window);
		//============================================================================================
		if (myPlayer.playerYPosition() == 355) myPlayer.drawPlayer(*window);
		if (cpPresent.YPosition() == 355) cpPresent.drawPresent(*window);
		if (clLife.spriteYPosition() == 355)clLife.drawLifes(*window);
		//============================================================================================
		oTrain1.drawObsticle(*window);
		if (myPlayer.playerYPosition() == 405)myPlayer.drawPlayer(*window);
		//============================================================================================
		oTrain2.drawObsticle(*window);
		if (myPlayer.playerYPosition() == 455)myPlayer.drawPlayer(*window);
		//============================================================================================
		if (myPlayer.playerYPosition() == 505)myPlayer.drawPlayer(*window);
		if (cpPresent.YPosition() == 505)cpPresent.drawPresent(*window);
		if (clLife.spriteYPosition() == 505)clLife.drawLifes(*window);
		//============================================================================================
		oCar1.drawObsticle(*window);
		oCar2.drawObsticle(*window);
		if (myPlayer.playerYPosition() == 555)myPlayer.drawPlayer(*window);
		//============================================================================================
		oCar4.drawObsticle(*window);
		oCar3.drawObsticle(*window);
		if (myPlayer.playerYPosition() == 605)myPlayer.drawPlayer(*window);
		//============================================================================================
		oCar5.drawObsticle(*window);
		oCar6.drawObsticle(*window);
		if (myPlayer.playerYPosition() == 655)myPlayer.drawPlayer(*window);
		//============================================================================================
		oCar7.drawObsticle(*window);
		oCar8.drawObsticle(*window);
		if (myPlayer.playerYPosition() == 705)myPlayer.drawPlayer(*window);
		//============================================================================================
		oCar9.drawObsticle(*window);
		oCar10.drawObsticle(*window);
		if (myPlayer.playerYPosition() == 755)myPlayer.drawPlayer(*window);
		//============================================================================================
		if (myPlayer.playerYPosition() == 805)myPlayer.drawPlayer(*window);
		if (cpPresent.YPosition() == 805)cpPresent.drawPresent(*window);
		if (clLife.spriteYPosition() == 805)clLife.drawLifes(*window);
		//============================================================================================


		if (bCountingIn)//If the game is counting in
		{
			//cCountInClock is used to know when to draw each sprite on the screen. Depending on the time different sprites are shown on the screen
			tCountInTime = cCountInClock.getElapsedTime();
			if (tCountInTime.asSeconds() < 1) window->draw(sCountIn3);
			else if (tCountInTime.asSeconds() < 2)  window->draw(sCountIn2);
			else if (tCountInTime.asSeconds() < 3)  window->draw(sCountIn1);
			else if (tCountInTime.asSeconds() > 3)  bCountingIn = false;
		}

		window->display();//Display the window for the frame

	}
	return iPresentsCollected; // The number of presents that where collected is returned to the main function so that it can be shown on the fail screen.}
}

//Fail screen function, displays the end menu once the player has lost all lives, it returnes an intiger depending on what the player chooses to do next.
int game::iFailScreen()
{
	//Initiate sprites
	sf::Sprite sFailScreenBackgroundSprite;

	//Initiate Textures
	sf::Texture tFailScreenBackgroundTexture;

	//Load textures
	if (!tFailScreenBackgroundTexture.loadFromFile(".\\Assets\\graphics\\deadscreenback.png")) EXIT_FAILURE;

	//Set sprite textures
	sFailScreenBackgroundSprite.setTexture(tFailScreenBackgroundTexture);

	//Initialize buttons
	button btnPlayAgain((".\\Assets\\graphics\\buttonplayagain.png"), sf::Vector2f(200, 100), sf::Vector2f(150, 650));
	button btnReturnToMenu((".\\Assets\\graphics\\buttontomenu.png"), sf::Vector2f(200, 100), sf::Vector2f(450, 650));
	button btnMute((".\\Assets\\graphics\\sound.png"), sf::Vector2f(40, 30), sf::Vector2f(740, 0));
	if (bMute)btnMute.changetexture(".\\Assets\\graphics\\mute.png");				//Change pause button texture to play icon


	//Initialize Fonts
	sf::Font fGameFont;

	//Load fonts from file
	if (!fGameFont.loadFromFile("gamefont.ttf"))EXIT_FAILURE;

	//Initialize colors used for text and set color, size, 
	sf::Color textcolor(87, 42, 87);

	//Initialize texts
	sf::Text tTimeTaken, tPresentsColelcted;

	//Set fonts
	tTimeTaken.setFont(fGameFont);
	tPresentsColelcted.setFont(fGameFont);

	//Set text colors
	tTimeTaken.setFillColor(textcolor);
	tPresentsColelcted.setFillColor(textcolor);

	//Set text sizes
	tTimeTaken.setCharacterSize(75);
	tPresentsColelcted.setCharacterSize(130);

	//Set the position of the texts
	tPresentsColelcted.setPosition(400, 300);
	tTimeTaken.setPosition(100, 450);

	//Set the string for number of presents collected
	std::string sNumberOfPresentsCollectedString = "- ";
	sNumberOfPresentsCollectedString.append(std::to_string(iPresentsCollected));
	tPresentsColelcted.setString(sNumberOfPresentsCollectedString);

	//Set the string for time taken
	std::string endtext = "TIME TAKEN: ";
	endtext.append(sTimeToString(iTimeTaken));
	tTimeTaken.setString(endtext);

	mBackgroundMusic->setPitch(1);
	while (1) //keeps looping until the user chooses an option and the function returns an integer.
	{

		//Clear the screen
		window->clear(sf::Color::White);

		//Draw everything to the screen
		window->draw(sFailScreenBackgroundSprite);
		btnPlayAgain.drawbutton(*window);
		btnReturnToMenu.drawbutton(*window);
		window->draw(tTimeTaken);
		btnMute.drawbutton(*window);
		window->draw(tPresentsColelcted);
		window->display();

		//Initialize event
		sf::Event event;
		while (window->pollEvent(event))
		{

			if (btnMute.isclicked(event))//If the mute button is pressed
			{
				if (bMute == false)//If the game is currently not muted
				{
					bMute = true;											//Set Mute to true
					btnMute.changetexture(".\\Assets\\graphics\\mute.png");				//Change texture of button to un-mute
					mBackgroundMusic->setVolume(0);								//Set volume of all sounds to zero
				}
				else // if already muted
				{
					bMute = false;											//Set Mute to false
					btnMute.changetexture(".\\Assets\\graphics\\sound.png");				//Change texture of button to mute
					mBackgroundMusic->setVolume(010);								//Set volumes of sounds
				}
			}

			if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))//If the user chooses to close
			{
				window->close();		//Close the window
				return 0;			//Return zero
			}

			if (btnReturnToMenu.isclicked(event))//If the return to menu button is clicked 
			{
				return 1;			//return int 1.
			}


			if (btnPlayAgain.isclicked(event))//If the play again button is clicked
			{
				return 2;			//Return int 2.
			}
		}
	}

	return 0; //Default

}

//string function that converts the elapsed time to a string, used to display time taken.
std::string game::sTimeToString(int iTimetakenInMilliseconds)
{
	//Initializes strings for different parts of the time which will be appended together.
	std::string minutesstring, secondsstring, fulltimestring;

	//The minutes and seconds are calculated from the duration in milliseconds that is passed into the function.
	int minutes = iTimetakenInMilliseconds / 60000;
	int seconds = (iTimetakenInMilliseconds / 1000) - (minutes * 60);

	//the to_string function from the st library is used to convert the integers into strings.
	minutesstring = std::to_string(minutes);
	secondsstring = std::to_string(seconds);

	//if the strings are only one digit long, add an extra zero to the beginning of the string. e.g. 2:45 becomes 02:45.
	if (minutesstring.length() == 1) minutesstring.insert(0, "0");
	if (secondsstring.length() == 1) secondsstring.insert(0, "0");

	//The full time string that is returned is made from the individual strings appended together.
	fulltimestring = minutesstring;
	fulltimestring.append(":");
	fulltimestring.append(secondsstring);

	//The string is returned.
	return fulltimestring;
	
}

