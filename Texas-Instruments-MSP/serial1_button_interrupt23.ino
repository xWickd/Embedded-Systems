/*
 * This code was designed by Panagiotis Tiktapanidis & Dimitris Gkiokezas on June 27th 2023.
 * It is intended for academic use at the Dept. of Informatics and Telecommunications 
 * of University of Ioannina.
 * 
 * This code was designed and compiled at Energia IDE v1.8.11E23
 * It was designed for use with TI MSP430F5529LP
 * 
 * This code prints to the locally connected LCD and the Serial Console a message,
 * with the push of the button PUSH1 transmits another message to the other MSP, 
 * and shows it to the other MSP's locally connected LCD and Serial console.
*/

#include <LiquidCrystal_I2C.h> // Include library for lcd 
  
int lcdcolumns = 16; // Declare the number of columns for the lcd
int lcdrows = 2; // Declare the number of rows for the lcd
LiquidCrystal_I2C lcd(0x27, lcdcolumns, lcdrows); // Declare object for lcd handling

String serial_message, serial1_message; // Variables for getting the messages from the Serial buffers 
volatile bool buttonPushed = false; // Variable to control the button through ISR (Interrupt Service Routine)

void setup() {
  Serial.begin(9600); // Set baudrate for Serial
  Serial1.begin(9600); // Set baudrate for Serial1

  pinMode(PUSH1, INPUT_PULLUP); // Initialize the P1.1 button as input
  attachInterrupt(PUSH1, btn_interrupt, FALLING); // Associate interrupt method to PUSH1 button

  lcd.init(); // Initialize the connection to lcd
  lcd.backlight(); // Turn on the backlight of the lcd 

//  UCA0STAT |= UCLISTEN; // Loopback (UART)
//  Comment the above line of code when connecting two MCUs together for communication
//  Or else short the pins P3.3 and P3.4
}

void loop() {
  serial_message = "Serial message";
  serial1_message = "Serial1 message";
  
  if(buttonPushed == false) // Check if the button hasn't been pushed
  {
    lcd.clear(); // Clear the output of the display
    lcd.setCursor(0,0); // Set the point of writing to the first row, and first column

    Serial.print("S: ");
    lcd.print("S:");
    for(int i=0; i<serial_message.length(); i++)
    {
      Serial.print(serial_message[i]); // Send the character to the Serial console
      lcd.print(serial_message[i]); // Print the character to the lcd
    }
    Serial.println(); // Print an empty line in the Serial console

    if(Serial1.available()) // Check if the other MSP sent a message
    {
      serial1_message = Serial1.readString(); // Read the Serial1 buffer into the serial1_message variable
      Serial.print("S1: ");
      lcd.setCursor(0,1);
      lcd.print("S1:");
      for(int i=0; i<serial1_message.length(); i++)
      {
        Serial.print(serial1_message[i]); // Send the character to the Serial console
        lcd.print(serial1_message[i]); // Print the character to the lcd
      }
      Serial.println(); // Print an empty line in the Serial console
    }
  }

  if(buttonPushed == true) // Check if the button has been pushed
  {
    lcd.clear(); // Clear the output of the display
    lcd.setCursor(0,1); // Set the point of writing to the second row, and first column

    for(int i=0; i<serial1_message.length(); i++) // For every character of the message variable
    {
      Serial1.print(serial1_message[i]); // Send the character to the Serial1 (other MSP430)
    }
    lcd.print("Sending to S1");
    Serial1.println(); // Print an empty line in the Serial1 console

    if(Serial1.available()) // Check if the other MSP is also sending to Serial1
    {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Sending to S1");
      lcd.setCursor(0,1);
      lcd.print("S1:");
      for(int i=0; i<serial1_message.length(); i++)
      {
        Serial1.print(serial1_message[i]);
        lcd.print(serial1_message[i]); 
      }
      Serial1.println();
    }
  }

  delay(2000); // Delay the next loop for ~2 seconds
}

// Interrupt Service Routine - Change buttonPushed value/state
void btn_interrupt()
{
  if(buttonPushed == false) // If the button hasn't been pushed
  {
    buttonPushed = true;
  }
  else // If the button has been pushed
  {
    buttonPushed = false;
  }
}
