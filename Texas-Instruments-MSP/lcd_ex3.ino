/*
 * This code was designed by Dimitrios Gkiokezas & Panagiotis Tiktapanidis on July 24th 2023.
 * It is intended for academic use at the Dept. of Informatics and Telecommunications 
 * of University of Ioannina.
 * 
 * This code was designed and compiled at Energia IDE v1.8.11E23
 * It was designed for use with TI MSP430F5529LP
 * 
 * This code prints the message "Upper row" to the first row of the LCD,
 * and the message "Down row" to the second row of the LCD.
 * The messages appear and disappear after pressing the buttons PUSH1 and PUSH2 respectively.
*/

#include <LiquidCrystal_I2C.h> // Include library for lcd 
  
int lcdcolumns = 16; // Declare the number of columns for the lcd
int lcdrows = 2; // Declare the number of rows for the lcd
LiquidCrystal_I2C lcd(0x27, lcdcolumns, lcdrows); // Declare object for lcd handling

volatile bool push1Pushed = false; // Variable to control the button through ISR (Interrupt Service Routine)
volatile bool push2Pushed = false; // Variable to control the button through ISR (Interrupt Service Routine)

void setup() {
  lcd.init();
  lcd.backlight();

  pinMode(PUSH1, INPUT_PULLUP); // Initialize the P1.1 button as input
  attachInterrupt(PUSH1, push1_interrupt, FALLING); // Associate interrupt method to PUSH1 button
  pinMode(PUSH2, INPUT_PULLUP); // Initialize the P2.1 button as input
  attachInterrupt(PUSH2, push2_interrupt, FALLING); // Associate interrupt method to PUSH2 button
}

void loop() {
  if(push1Pushed==false && push2Pushed==false)
  {
    lcd.clear();
  }
  else if(push1Pushed==false && push2Pushed==true)
  {
     lcd.clear();
     lcd.setCursor(0,1);
     lcd.print("Down Row");
  }
  else if(push1Pushed==true && push2Pushed==false)
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Upper row");
  }
  else
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Upper row");
    lcd.setCursor(0,1);
    lcd.print("Down row");
  }

  delay(1000);
}

void push1_interrupt()
{
  if(push1Pushed == false) // If the button hasn't been pushed
  {
    push1Pushed = true;
  }
  else // If the button has been pushed
  {
    push1Pushed = false;
  }
}

void push2_interrupt()
{
  if(push2Pushed == false) // If the button hasn't been pushed
  {
    push2Pushed = true;
  }
  else // If the button has been pushed
  {
    push2Pushed = false;
  }
}
