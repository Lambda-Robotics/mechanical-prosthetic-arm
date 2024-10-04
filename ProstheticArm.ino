// For more information, please visit https://github.com/Lambda-Robotics/mechanical-prosthetic-arm

#define EN        8     // Stepper Motor Switch Pin
#define X_DIR     5     // X Motor Direction Pin
#define Y_DIR     6     // Y Motor Direction Pin
#define X_STP     2     // X Motor Steps Pin
#define Y_STP     3     // Y Motor Steps Pin

int emgValue = 0; // Variable for EMG
bool stepperClose = true;
bool stepperOpen = true;

// Function for stepper motor controlling
void step(boolean dir, byte dirPin, byte stepperPin, int steps) {
  digitalWrite(dirPin, dir);
  delay(50);
  for (int i = 0; i < steps; i++) {  
    digitalWrite(stepperPin, HIGH);
    delayMicroseconds(800);        
    digitalWrite(stepperPin, LOW);
    delayMicroseconds(800);       
  }
}
// Same function, but for reverse direction
void stepreverse(boolean dir, byte dirPin, byte stepperPin, int steps) {
  digitalWrite(dirPin, !dir);
  delay(50);
  for (int i = 0; i < steps; i++) {
    digitalWrite(stepperPin, HIGH);
    delayMicroseconds(800);        
    digitalWrite(stepperPin, LOW); 
    delayMicroseconds(800);        
  }
}

void setup() {
  // Define motor pins as output
  pinMode(X_DIR, OUTPUT); pinMode(X_STP, OUTPUT);
  pinMode(Y_DIR, OUTPUT); pinMode(Y_STP, OUTPUT);
  pinMode(EN, OUTPUT);

  // Enable the motors
  digitalWrite(EN, LOW);

  // Enable Serial Monitor
  Serial.begin(9600);
}

void loop() {
  emgValue = analogRead(A8);
  Serial.println(emgValue);

  // Check conditions
  if (emgValue < 240) {
    stepperClose = true;
    if (stepperOpen) {
      step(true, X_DIR, X_STP, 200);
      stepperOpen = false;
    }
  } else {
    stepperOpen = true;
    if (stepperClose) {
      stepreverse(true, X_DIR, X_STP, 200);
      stepperClose = false;
    }
  }
  delay(1000);
}
