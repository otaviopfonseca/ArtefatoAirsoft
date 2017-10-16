// 
// 
// 

#include "GameKeypad.h"

byte ROW_PINS_GAME[ROWS_GAME_KEYPAD] = { 22 };
byte COLUMN_PINS_GAME[COLUMNS_GAME_KEYPAD] = { 23, 24 };
char KEYS_GAME[ROWS_GAME_KEYPAD][COLUMNS_GAME_KEYPAD] =
{
	{ 'R', 'G' }
};

GameKeypad::GameKeypad() :
	Keypad(makeKeymap(KEYS_GAME), ROW_PINS_GAME, COLUMN_PINS_GAME, ROWS_GAME_KEYPAD, COLUMNS_GAME_KEYPAD)
{
}
