#include <vector>
#include <iostream>
#include <windows.h>
#include <ctime>

int main()
{
	std::vector<COORD> x_value;
	COORD buffSize = {80,50};
	COORD home = {0,0};
	COORD mouseCRD = {0, 48};
	SMALL_RECT screenRegion = {0,0,79,49};
	WORD lastDir = VK_LEFT;

	SHORT offset;

	CHAR_INFO ci_buffer[ 80*50];

	for (int i=0; i < 80 * 50; ++i) {
        // Fill it with white-backgrounded spaces
		ci_buffer[ i ].Char.AsciiChar = ' ';
		ci_buffer[ i ].Attributes = 
		BACKGROUND_BLUE |
		BACKGROUND_GREEN |
		BACKGROUND_RED |
		BACKGROUND_INTENSITY;
  }

	WriteConsoleOutputA( GetStdHandle( STD_OUTPUT_HANDLE ), ci_buffer, buffSize, home, &screenRegion );

	COORD temp = {10,10};

	for ( int i = 0; i < 10; i++ ){
		x_value.push_back( temp );
		temp.X++;
	}

	SetConsoleWindowInfo( GetStdHandle( STD_OUTPUT_HANDLE ), TRUE, &screenRegion );
	SetConsoleScreenBufferSize( GetStdHandle( STD_OUTPUT_HANDLE ), buffSize );

	
	
	for ( int i=0; i < x_value.size();i++ ){
		offset = buffSize.X * x_value.at( i ).Y + x_value.at( i ).X;
		ci_buffer[ offset ].Char.AsciiChar = 'O';
	}
	

	WriteConsoleOutputA( GetStdHandle( STD_OUTPUT_HANDLE ), ci_buffer, buffSize, home, &screenRegion );
	std::cout << x_value.size();

	bool appRunning = true;
	DWORD numEvents, numERead;

	while ( appRunning ){
		GetNumberOfConsoleInputEvents( GetStdHandle( STD_INPUT_HANDLE ), &numEvents );
		if (numEvents != 0) 
			{
				// Create a buffer of that size to store the events
				INPUT_RECORD *eventBuffer = new INPUT_RECORD[numEvents];

				// Read the console events into that buffer, and save how
				// many events have been read into numEventsRead.
				ReadConsoleInput( GetStdHandle( STD_INPUT_HANDLE ), eventBuffer, numEvents, &numERead);

				// Now, cycle through all the events that have happened:
				for ( DWORD i = 0; i < numERead; ++i ) {
					// Check the event type: was it a key?
					if ( eventBuffer[i].EventType == KEY_EVENT && eventBuffer[i].Event.KeyEvent.bKeyDown == TRUE ) {
						auto it = x_value.begin();
						switch ( eventBuffer[i].Event.KeyEvent.wVirtualKeyCode ){
							case VK_ESCAPE:
								appRunning = false;
								break;
							case VK_LEFT:
								if ( lastDir != VK_RIGHT )
									{
										it = x_value.begin();
										temp.X = x_value.at( 0 ).X;
										temp.Y = x_value.at( 0 ).Y;
										temp.X--;
										it = x_value.insert( it, temp );

										offset = buffSize.X * x_value.at( 0 ).Y + x_value.at( 0 ).X;
										if ( ci_buffer[ offset ].Char.AsciiChar != ' ' && ci_buffer[ offset ].Char.AsciiChar != '@' )
											{
												appRunning = false;
											} 
										else 
											{
												if ( ci_buffer[ offset ].Char.AsciiChar == ' ' )
													x_value.pop_back();
											}

										for ( int i = 0; i < x_value.size(); i++ ){
											offset = buffSize.X * x_value.at( i ).Y + x_value.at( i ).X;
											ci_buffer[ offset ].Char.AsciiChar = 'O';
										}
										lastDir = VK_LEFT;
									}
								else
									{
										appRunning = false;
									}
								break;
							case VK_UP:
								if ( lastDir != VK_DOWN )
									{
										it = x_value.begin();
										temp.X = x_value.at( 0 ).X;
										temp.Y = x_value.at( 0 ).Y;
										temp.Y--;
										it = x_value.insert( it, temp );

										offset = buffSize.X * x_value.at( 0 ).Y + x_value.at( 0 ).X;
										if ( ci_buffer[ offset ].Char.AsciiChar != ' ' && ci_buffer[ offset ].Char.AsciiChar != '@' )
											{
												appRunning = false;
											} 
										else 
											{
												if ( ci_buffer[ offset ].Char.AsciiChar == ' ' )
													x_value.pop_back();
											}

										for ( int i = 0; i < x_value.size();i++ ){
											offset = buffSize.X * x_value.at( i ).Y + x_value.at( i ).X;
											ci_buffer[ offset ].Char.AsciiChar = 'O';
										}
										lastDir = VK_UP;
									}
								else
									{
										appRunning = false;
									}
								break;
							case VK_RIGHT:
								if ( VK_LEFT != lastDir )
									{
										it = x_value.begin();
										temp.X = x_value.at( 0 ).X;
										temp.Y = x_value.at( 0 ).Y;
										temp.X++;
										it = x_value.insert( it, temp );

										offset = buffSize.X * x_value.at( 0 ).Y + x_value.at( 0 ).X;
										if ( ci_buffer[ offset ].Char.AsciiChar != ' ' && ci_buffer[ offset ].Char.AsciiChar != '@' )
											{
												appRunning = false;
											} 
										else 
											{
												if ( ci_buffer[ offset ].Char.AsciiChar == ' ' )
													x_value.pop_back();
											}

										for ( int i = 0; i < x_value.size();i++ ){
											offset = buffSize.X * x_value.at( i ).Y + x_value.at( i ).X;
											ci_buffer[ offset ].Char.AsciiChar = 'O';
										}
										lastDir = VK_RIGHT;
									}
								else
									{
										appRunning = false;
									}
								break;
							case VK_DOWN:
								if ( VK_UP != lastDir )
									{
										it = x_value.begin();
										temp.X = x_value.at( 0 ).X;
										temp.Y = x_value.at( 0 ).Y;
										temp.Y++;
										it = x_value.insert( it, temp );

										offset = buffSize.X * x_value.at( 0 ).Y + x_value.at( 0 ).X;
										if ( ' ' != ci_buffer[ offset ].Char.AsciiChar && '@' != ci_buffer[ offset ].Char.AsciiChar )
											{
												appRunning = false;
											} 
										else 
											{
												if ( ' ' == ci_buffer[ offset ].Char.AsciiChar )
													x_value.pop_back();
											}

										for ( int i = 0; i < x_value.size();i++ ){
											offset = buffSize.X * x_value.at( i ).Y + x_value.at( i ).X;
											ci_buffer[ offset ].Char.AsciiChar = 'O';
										}
										lastDir = VK_DOWN;
									}
								else
									{
										appRunning = false;
									}
								break;
						}// END SWITCH

						WriteConsoleOutputA( GetStdHandle( STD_OUTPUT_HANDLE ), ci_buffer, buffSize, home, &screenRegion );
					
						for (int i=0; i < 80 * 50; ++i) {
							// Fill it with white-backgrounded spaces
							ci_buffer[ i ].Char.AsciiChar = ' ';
							ci_buffer[ i ].Attributes = 
								BACKGROUND_BLUE  |
								BACKGROUND_GREEN |
								BACKGROUND_RED	 |
								BACKGROUND_INTENSITY;
						}

						//Sleep( 1000 );
					} // END IF
				}// END FOR LOOP
			}// END IF
		else 
			{

			}
	}// END WHILE

	SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), mouseCRD );

	return 0;
}