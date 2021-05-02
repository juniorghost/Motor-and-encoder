#include <Wire.h> // I2C library
#include <Adafruit_SSD1306.h> // OLED display library
#define OLED_ADDR   0x3C    // I2C address
Adafruit_SSD1306 display(-1);   // no reset pin
// Rotary Encoder Inputs
#define inputCLK 2
#define inputDT 3


int counter = 0;
int currentStateCLK;
int previousStateCLK;
String encdir = "";

void setup() {
  // put your setup code here, to run once:
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  digitalWrite(4, LOW);
  // Set encoder pins as inputs
  pinMode (inputCLK, INPUT_PULLUP);
  pinMode (inputDT, INPUT_PULLUP);
  // Setup Serial Monitor

  // Read the initial state of inputCLK
  // Assign to previousStateCLK variable
  previousStateCLK = digitalRead(inputCLK);
}

void loop() {
  digitalWrite(5, HIGH);
  digitalWrite(4, LOW);
  delayMicroseconds(312.5);

  digitalWrite(4, HIGH);
  delayMicroseconds(312.5);

  // Read the current state of inputCLK
  currentStateCLK = digitalRead(inputCLK);
  display.clearDisplay(); // clear display
  // If the previous and the current state of the inputCLK are different then a pulse has occured
  if (currentStateCLK != previousStateCLK) {

    // If the inputDT state is different than the inputCLK state then
    // the encoder is rotating counterclockwise
    if (digitalRead(inputDT) != currentStateCLK) {
      counter --;
      encdir = "CCW";

    }
    if (digitalRead(inputDT) == currentStateCLK)
    {
      // Encoder is rotating clockwise
      counter ++;
      encdir = "CW";

    }

    display.setTextColor(WHITE);
    display.setTextSize(2); // bigger text
    display.setCursor(0, 0);
    display.print(encdir);

    display.print(counter/40);
    display.print(':');

    display.display();  // update display

  }



  // Update previousStateCLK with the current state
  previousStateCLK = currentStateCLK;


}