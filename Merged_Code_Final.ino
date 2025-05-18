const int potPin1 = A3; // Potentiometer input pin for group 1
const int powerPinBelow1 = 5; // Output pin for controlling power below 2.4V for group 1
const int powerPinAbove1 = 6; // Output pin for controlling power above 2.6V for group 1

const int potPin2 = A4; // Potentiometer input pin for group 2
const int powerPinBelow2 = 7; // Output pin for controlling power below 2.4V for group 2
const int powerPinAbove2 = 8; // Output pin for controlling power above 2.6V for group 2

const int potPin3 = A5; // Potentiometer input pin for group 3
const int powerPinBelow3 = 9; // Output pin for controlling power below 2.4V for group 3
const int powerPinAbove3 = 10; // Output pin for controlling power above 2.6V for group 3

const int potPin4 = A6; // Potentiometer input pin for group 4
const int powerPinBelow4 = 11; // Output pin for controlling power below 2.4V for group 4
const int powerPinAbove4 = 12; // Output pin for controlling power above 2.6V for group 4

const int potPinA1 = A1;      // Analog pin connected to potentiometer A1
const int potPinA2 = A2;      // Analog pin connected to potentiometer A2

const int mosfetPin3 = 3;    // PWM pin connected to the MOSFET gate on pin 3
const int mosfetPin4 = 4;    // PWM pin connected to the MOSFET gate on pin 4

const float lowerThreshold = -0.5;  // Lower threshold voltage (in volts)
const float upperThreshold = 0.5;   // Upper threshold voltage (in volts)

const int multiplierPin3 = 3;   // Multiplier for pin 2
const int multiplierPin4 = 4;   // Multiplier for pin 3

float multiplierValuePin3 = 1.5;   // Initial multiplier value for pin 2
float multiplierValuePin4 = 1.4;   // Initial multiplier value for pin 3

void setup() {
  pinMode(potPin1, INPUT);
  pinMode(powerPinBelow1, OUTPUT);
  pinMode(powerPinAbove1, OUTPUT);
  
  pinMode(potPin2, INPUT);
  pinMode(powerPinBelow2, OUTPUT);
  pinMode(powerPinAbove2, OUTPUT);
  
  pinMode(potPin3, INPUT);
  pinMode(powerPinBelow3, OUTPUT);
  pinMode(powerPinAbove3, OUTPUT);

  pinMode(potPin4, INPUT);
  pinMode(powerPinBelow4, OUTPUT);
  pinMode(powerPinAbove4, OUTPUT);

  pinMode(potPinA1, INPUT);
  pinMode(potPinA2, INPUT);

  pinMode(mosfetPin3, OUTPUT);     // Initialize MOSFET pin 3 as output
  pinMode(mosfetPin4, OUTPUT);     // Initialize MOSFET pin 4 as output
  
  Serial.begin(9600);               // Initialize serial communication
}

void loop() {
  // Read voltages from potentiometers
  float voltageA1 = analogRead(potPinA1) * (5.0 / 1023.0);
  float voltageA2 = analogRead(potPinA2) * (5.0 / 1023.0);

  // Calculate voltage difference
  float voltageDifference = voltageA1 - voltageA2;

  // Apply multipliers to voltage difference for pins 2 and 3
  float voltageDifferencePin3 = voltageDifference * multiplierValuePin3;
  float voltageDifferencePin4 = voltageDifference * multiplierValuePin4;

  // Map absolute voltage difference to PWM range (0 to 255) for all pins
  int pwmValue3 = map(abs(voltageDifferencePin3), 0, 5, 0, 255);
  int pwmValue4 = map(abs(voltageDifferencePin4), 0, 5, 0, 255);

  // Check if voltage difference is within threshold
  if (voltageDifference >= lowerThreshold && voltageDifference <= upperThreshold) {
    pwmValue3 = 0;  // Turn off MOSFET on mosfetPin2
    pwmValue4 = 0;  // Turn off MOSFET on mosfetPin3
  }

  // Set PWM value for mosfetPin2 if voltageDifference is positive and within range
  if (voltageDifference > 0 && voltageDifference <= 5.0) {
    analogWrite(mosfetPin3, pwmValue3);
  } else {
    analogWrite(mosfetPin3, 0); // Turn off mosfetPin2
  }
  
  // Set PWM value for mosfetPin3 if voltageDifference is negative and within range
  if (voltageDifference < 0 && abs(voltageDifference) <= 5.0) {
    analogWrite(mosfetPin4, pwmValue4);
  } else {
    analogWrite(mosfetPin4, 0); // Turn off mosfetPin3
  }

  // Group 1
  int potValue1 = analogRead(potPin1); // Read potentiometer value for group 1
  float voltage1 = potValue1 * (5.0 / 1023.0); // Convert potentiometer value to voltage (0-5V) for group 1

  if (voltage1 < 2.4) {
    // Map the voltage to the range of 255-0 for analogWrite for powerPinBelow1
    int outputValueBelow1 = map(voltage1, 0.0, 2.4, 255, 0);
    analogWrite(powerPinBelow1, outputValueBelow1);

    // Ensure powerPinAbove1 is off
    analogWrite(powerPinAbove1, 0);
  } else if (voltage1 > 2.6) {
    // Map the voltage to the range of 0-255 for analogWrite for powerPinAbove1
    int outputValueAbove1 = map(voltage1, 2.6, 5.0, 0, 255);
    analogWrite(powerPinAbove1, outputValueAbove1);

    // Ensure powerPinBelow1 is off
    analogWrite(powerPinBelow1, 0);
  } else {
    // If voltage is between 2.4V and 2.6V, or exactly 2.4V or 2.6V, turn off both pins for group 1
    analogWrite(powerPinBelow1, 0);
    analogWrite(powerPinAbove1, 0);
  }

  // Group 2
  int potValue2 = analogRead(potPin2); // Read potentiometer value for group 2
  float voltage2 = potValue2 * (5.0 / 1023.0); // Convert potentiometer value to voltage (0-5V) for group 2

  if (voltage2 < 2.4) {
    // Map the voltage to the range of 255-0 for analogWrite for powerPinBelow2
    int outputValueBelow2 = map(voltage2, 0.0, 2.4, 255, 0);
    analogWrite(powerPinBelow2, outputValueBelow2);

    // Ensure powerPinAbove2 is off
    analogWrite(powerPinAbove2, 0);
  } else if (voltage2 > 2.6) {
    // Map the voltage to the range of 0-255 for analogWrite for powerPinAbove2
    int outputValueAbove2 = map(voltage2, 2.6, 5.0, 0, 255);
    analogWrite(powerPinAbove2, outputValueAbove2);

    // Ensure powerPinBelow2 is off
    analogWrite(powerPinBelow2, 0);
  } else {
    // If voltage is between 2.4V and 2.6V, or exactly 2.4V or 2.6V, turn off both pins for group 2
    analogWrite(powerPinBelow2, 0);
    analogWrite(powerPinAbove2, 0);
  }

  // Group 3
  int potValue3 = analogRead(potPin3); // Read potentiometer value for group 3
  float voltage3 = potValue3 * (5.0 / 1023.0); // Convert potentiometer value to voltage (0-5V) for group 3

  if (voltage3 < 2.4) {
    // Map the voltage to the range of 255-0 for analogWrite for powerPinBelow3
    int outputValueBelow3 = map(voltage3, 0.0, 2.4, 255, 0);
    analogWrite(powerPinBelow3, outputValueBelow3);

    // Ensure powerPinAbove3 is off
    analogWrite(powerPinAbove3, 0);
  } else if (voltage3 > 2.6) {
    // Map the voltage to the range of 0-255 for analogWrite for powerPinAbove3
    int outputValueAbove3 = map(voltage3, 2.6, 5.0, 0, 255);
    analogWrite(powerPinAbove3, outputValueAbove3);

    // Ensure powerPinBelow3 is off
    analogWrite(powerPinBelow3, 0);
  } else {
    // If voltage is between 2.4V and 2.6V, or exactly 2.4V or 2.6V, turn off both pins for group 3
    analogWrite(powerPinBelow3, 0);
    analogWrite(powerPinAbove3, 0);
  }

  // Group 4
  int potValue4 = analogRead(potPin4); // Read potentiometer value for group 4
  float voltage4 = potValue4 * (5.0 / 1023.0); // Convert potentiometer value to voltage (0-5V) for group 4

  if (voltage4 < 2.4) {
    // Map the voltage to the range of 255-0 for analogWrite for powerPinBelow4
    int outputValueBelow4 = map(voltage4, 0.0, 2.4, 255, 0);
    analogWrite(powerPinBelow4, outputValueBelow4);

    // Ensure powerPinAbove4 is off
    analogWrite(powerPinAbove4, 0);
  } else if (voltage4 > 2.6) {
    // Map the voltage to the range of 0-255 for analogWrite for powerPinAbove4
    int outputValueAbove4 = map(voltage4, 2.6, 5.0, 0, 255);
    analogWrite(powerPinAbove4, outputValueAbove4);

    // Ensure powerPinBelow4 is off
    analogWrite(powerPinBelow4, 0);
  } else {
    // If voltage is between 2.4V and 2.6V, or exactly 2.4V or 2.6V, turn off both pins for group 4
    analogWrite(powerPinBelow4, 0);
    analogWrite(powerPinAbove4, 0);
  }

  // Print measured voltages and voltage difference to serial monitor
  Serial.print("  A1-");
  Serial.print(voltageA1);
  Serial.print("  A2-");
  Serial.print(voltageA2);
  Serial.print("  V Diff-");
  Serial.print(voltageDifference);
  Serial.print("  D3-");
  Serial.print(voltageDifferencePin3 > 0 ? voltageDifferencePin3 : 0);
  Serial.print("  D4-");
  Serial.print(voltageDifferencePin4 < 0 ? abs(voltageDifferencePin4) : 0);
  Serial.println("  |||");

  delay(100); // Delay for stability and to reduce serial output rate
}