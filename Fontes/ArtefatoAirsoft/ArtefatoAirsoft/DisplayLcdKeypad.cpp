// 
// 
// 

#include "DisplayLcdKeypad.h"

DisplayLcdKeypad::DisplayLcdKeypad() { }

DisplayLcdButton DisplayLcdKeypad::getKeyPressed()
{
	return readLcdButtons();
}

String DisplayLcdKeypad::getKeyPressedDescription()
{
	DisplayLcdButton keyPressed = readLcdButtons();
	return getKeyPressedDescription(keyPressed);
}

String DisplayLcdKeypad::getKeyPressedDescription(DisplayLcdButton keyPressed)
{
	switch (keyPressed)
	{
		case DisplayLcdButton::Down:
			return "Baixo";
		case DisplayLcdButton::Left:
			return "Esquerda";
		case DisplayLcdButton::Right:
			return "Direita";
		case DisplayLcdButton::Up:
			return "Cima";
		case DisplayLcdButton::Select:
			return "Selecionar";
		default:
			return "Não Mapeado";
	};
}



DisplayLcdButton DisplayLcdKeypad::readLcdButtons()
{
	int analogReadValue = analogRead(ANALOG_BUTTON_READ_PIN);
	String analogReadValueStr = String(analogReadValue);
	String showtext = String("Valor lido analogico = ");
	showtext.concat(analogReadValueStr);
	Serial.println(showtext);
	delay(5); 
	int k = (analogRead(ANALOG_BUTTON_READ_PIN) - analogReadValue);	
	if (5 < abs(k)) return DisplayLcdButton::None;									 
	if (analogReadValue > 1000) return DisplayLcdButton::None; 
	if (analogReadValue < 50)   return DisplayLcdButton::Right;
	if (analogReadValue < 195)  return DisplayLcdButton::Up;
	if (analogReadValue < 380)  return DisplayLcdButton::Down;
	if (analogReadValue < 555)  return DisplayLcdButton::Left;
	if (analogReadValue < 790)  return DisplayLcdButton::Select;
	return DisplayLcdButton::None;  
}
