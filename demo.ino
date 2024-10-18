uint8_t CMD = 0x7F;

void setup() {
  Serial.begin(115200);
}

void loop() {  //--------------------- TEXT MODE ----------------------------------------------------

  Serial.write(CMD);  //CMD followed by T put's the device in text mode (not really needed here since it starts in text mode)
  Serial.print("T");  //CMD characters are not printed to the screen
  delay(3000);

  Serial.println();
  for (int i = 0; i < 11; i++) {  //Display RGB loading bar
    Serial.write(CMD); //Set text colour to red
    Serial.print("R");
    Serial.print('#');
    delay(60);
    Serial.write(CMD); //Set text colour to green
    Serial.print("G");
    Serial.print('#');
    delay(60);
    Serial.write(CMD); //Set text colour to blue
    Serial.print("B");
    Serial.print('#');
    delay(60);
  }
  Serial.write(CMD); //Set text colour to red
  Serial.print("R");
  Serial.print('#');
  delay(1000);
  Serial.write(CMD); //Set text colour to white
  Serial.print("W");

  Serial.println();  //Display title
  Serial.println("    ---------------------");
  Serial.println("    | MINI TERMINAL AND |");
  Serial.println("    | WAVEFORM  PLOTTER |");
  Serial.println("    ---------------------");
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.println();
  delay(5000);

  for (int i = 0; i < 20; i++) {  //Display counter
    Serial.print("This is a test, i = ");
    Serial.println(i);
    delay(100);
  }

  Serial.println("Turning off the backlight..");
  delay(2000);
  Serial.write(CMD);  //CMD followed by D turns off the backlight
  Serial.print("D");
  delay(2000);
  Serial.write(CMD);  //CMD followed by L turns on the backlight
  Serial.print("L");

  Serial.println("Turning on white mode..");
  delay(2000);
  Serial.write(CMD);  //CMD followed by I put's the device in inverting mode
  Serial.print("I");
  delay(1000);
  Serial.println("IT'S TOO BRIGHT!");
  delay(3000);
  Serial.println("Turning off white mode..");
  delay(1500);
  Serial.write(CMD);  //CMD followed by N put's the device in non-inverting mode
  Serial.print("N");
  delay(1000);
  Serial.println();
  Serial.println();
  Serial.println("Let's plot a sine wave:");
  delay(2000);

  Serial.write(CMD);  //CMD followed by P put's the device in plotter mode
  Serial.print("P");  //--------------------- PLOTTER MODE ----------------------------------------------------
  Serial.write(CMD);
  Serial.print("W");  // W = wide lines (P = precise, N = normal)
  delay(2000);

  float current_time = 0;

  for (int i = 0; i < 2000; i++) {
    delay(5);
    float sinewave = 1.0 + sin(current_time);
    int sigRED = int(100 * sinewave) + 20;  //Generate an integer wave between 0-239
    Serial.print('R');                      // R indicates the following byte is on the red channel
    Serial.write(sigRED);
    current_time += 0.035;  //Update time-step
    Serial.write(CMD);
    Serial.print("S");  //CMD, S scrolls the display 1 pixel
  }

  Serial.write(CMD);
  Serial.print("T");  //--------------------- TEXT MODE ----------------------------------------------------
  Serial.println("    -------------------------");
  Serial.println("    | BACK IN TEXT MODE NOW |");
  Serial.println("    -------------------------");
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.println();
  delay(1000);
  Serial.println("--------------------------------");
  Serial.println("This device is also capable of ");
  Serial.println("plotting 3 channels, let's use");
  Serial.println("them to show 3 phases:");
  Serial.println("--------------------------------");
  Serial.println();
  Serial.println();
  delay(8000);

  for (int i = 0; i < 30; i++) {
    Serial.println();
    delay(100);
  }
  Serial.write(CMD);
  Serial.print("P");  //--------------------- PLOTTER MODE ----------------------------------------------------
  Serial.write(CMD);
  Serial.print("W");
  delay(2000);

  for (int i = 0; i < 2000; i++) {  //Same generation routine as before, but with additional G and B channels
    delay(3);
    float sinewave = 1.0 + sin(current_time);
    float sinewave2 = 1.0 + sin(current_time + 2.094);  // + 2/3 pi radians
    float sinewave3 = 1.0 + sin(current_time + 4.188);  // + 4/3 pi radians
    int sigRED = int(100 * sinewave) + 20;
    int sigGREEN = int(100 * sinewave2) + 20;
    int sigBLUE = int(100 * sinewave3) + 20;
    Serial.print('R');
    Serial.write(sigRED);
    Serial.print('G');
    Serial.write(sigGREEN);
    Serial.print('B');
    Serial.write(sigBLUE);
    current_time += 0.035;
    Serial.write(CMD);
    Serial.print("S");
  }

  Serial.write(CMD);
  Serial.print("T");  //--------------------- TEXT MODE ----------------------------------------------------
  delay(1000);

  Serial.println("  ---------------");
  Serial.println("  | END OF DEMO |");
  Serial.println("  ---------------");
  for (int i = 0; i < 35; i++) {
    Serial.println();
    delay(200);
  }
}
