// Sensor pins
const int sensorPins[5] = {A0, A1, A2, A3, A4};

// Motor control pins
const int IN1 = 22;
const int IN2 = 24;
const int IN3 = 26;
const int IN4 = 28;

// Threshold value to detect the line
int threshold = 500;

void setup() {
  // Initialize sensor pins
  for (int i = 0; i < 5; i++) {
    pinMode(sensorPins[i], INPUT);
  }

  // Initialize motor pins
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  int sensors[5];

  // Read sensor values
  for (int i = 0; i < 5; i++) {
    sensors[i] = analogRead(sensorPins[i]);
    Serial.print(sensors[i]);
    Serial.print("\t");
  }
  Serial.println();

  // Basic line following logic
  if (sensors[2] < threshold) {
    // Center sensor sees line — go forward
    forward();
  } else if (sensors[1] < threshold) {
    // Line is slightly to the left — turn left slightly
    turnLeft();
  } else if (sensors[3] < threshold) {
    // Line is slightly to the right — turn right slightly
    turnRight();
  } else if (sensors[0] < threshold) {
    // Line is far left — turn left hard
    sharpLeft();
  } else if (sensors[4] < threshold) {
    // Line is far right — turn right hard
    sharpRight();
  } else {
    // No line detected — stop or continue previous direction
    stopMotors();
  }

  delay(10);
}

// Motor control functions
void forward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void turnLeft() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void turnRight() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void sharpLeft() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void sharpRight() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
