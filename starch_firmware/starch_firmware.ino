long randNumber;
unsigned int xAxisMaximum;
unsigned int yAxisMaximum;
unsigned int limitSwitch1;
unsigned int limitSwitch2;
unsigned int limitSwitch3;
unsigned int limitSwitch4;
unsigned int xPosition;
unsigned int yPosition;
int xChange;
int yChange;
unsigned int xLowerBound;
unsigned int xUpperBound;
unsigned int yLowerBound;
unsigned int yUpperBound;
int Sensor1;
int Sensor2;

void setup() {
  // put your setup code here, to run once:
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, INPUT);
  pinMode(7, INPUT);
  pinMode(8, INPUT);
  pinMode(9, INPUT);
  pinMode(10, INPUT);
  pinMode(11, INPUT);
  Serial.begin(9600);
  // =====  calibration for x and reset =====
  // ========== go to x = 0 ==========
  digitalWrite(2, LOW);
  limitSwitch1 = digitalRead(6); // Serial.print("limitSwitch1: "); Serial.println(limitSwitch1); // COMMENT THIS LATER
  while (limitSwitch1) {
    for (int i = 6400; i > 0; i--) {
      digitalWrite(3, LOW); digitalWrite(3, HIGH);
      limitSwitch1 = digitalRead(6); // Serial.print("limitSwitch1: "); Serial.println(limitSwitch1); // COMMENT THIS LATER
      if (!limitSwitch1) break;
      delayMicroseconds(180);
    }
  }

  // ========== go to x = max ==========
  digitalWrite(2, HIGH); xAxisMaximum = 0;
  limitSwitch2 = digitalRead(7); // Serial.print("limitSwitch2: "); Serial.println(limitSwitch2); // COMMENT THIS LATER
  while (limitSwitch2) {
    for (int i = 6400; i > 0; i--) {
      digitalWrite(3, LOW); digitalWrite(3, HIGH); xAxisMaximum = xAxisMaximum + 1; // Serial.print("xAxisMaximum: "); Serial.println(xAxisMaximum); // COMMENT THIS LATER
      limitSwitch2 = digitalRead(7); // Serial.print("limitSwitch2: "); Serial.println(limitSwitch2); // COMMENT THIS LATER
      if (!limitSwitch2) break;
      delayMicroseconds(180);
    }
  }
  xPosition = xAxisMaximum; Serial.print("xAxisMaximum: "); Serial.println(xAxisMaximum);

  // ========== go to x = max / 2 ==========
  digitalWrite(2, LOW);
  while (xPosition > xAxisMaximum / 2) {
    for (int i = 6400; i > 0; i--) {
      digitalWrite(3, LOW); digitalWrite(3, HIGH);
      xPosition = xPosition - 1; // Serial.print("xPosition: "); Serial.println(xPosition); // COMMENT THIS LATER
      if (xPosition < xAxisMaximum / 2) break;
      delayMicroseconds(180);
    }
  }
    
  // =====  calibration for y and reset =====
  // ========== go to y = 0 ==========
  digitalWrite(4, LOW);
  limitSwitch3 = digitalRead(8); // Serial.print("limitSwitch3: "); Serial.println(limitSwitch3);
  while (limitSwitch3) {
    for (int i = 6400; i > 0; i--) {
      digitalWrite(5, LOW); digitalWrite(5, HIGH);
      limitSwitch3 = digitalRead(8); // Serial.print("limitSwitch3: "); Serial.println(limitSwitch3); // COMMENT THIS LATER
      if (!limitSwitch3) break;
      delayMicroseconds(180);
    }
  }

  // ========== go to y = max ==========
  digitalWrite(4, HIGH); yAxisMaximum = 0;
  limitSwitch4 = digitalRead(9); // Serial.print("limitSwitch4: "); Serial.println(limitSwitch4);
  while (limitSwitch4) {
    for (int i = 6400; i > 0; i--) {
      digitalWrite(5, LOW); digitalWrite(5, HIGH); yAxisMaximum = yAxisMaximum + 1; // Serial.print("yAxisMaximum: "); Serial.println(yAxisMaximum); // COMMENT THIS LATER
      limitSwitch4 = digitalRead(9); // Serial.print("limitSwitch4: "); Serial.println(limitSwitch4); // COMMENT THIS LATER
      if (!limitSwitch4) break;
      delayMicroseconds(180);
    }
  }
  yPosition = yAxisMaximum; Serial.print("yAxisMaximum: "); Serial.println(yAxisMaximum);

  // ========== go to x = max / 2 ==========
  digitalWrite(4, LOW);
  while (yPosition > yAxisMaximum / 2) {
    for (int i = 6400; i > 0; i--) {
      digitalWrite(5, LOW); digitalWrite(5, HIGH);
      yPosition = yPosition - 1; // Serial.print("yPosition: "); Serial.println(yPosition); // COMMENT THIS LATER
      if (yPosition < yAxisMaximum / 2) break;
      delayMicroseconds(180);
    }
  }

  xLowerBound = xAxisMaximum * 0.25; Serial.print("xLowerBound: "); Serial.println(xLowerBound);
  xUpperBound = xAxisMaximum * 0.75; Serial.print("xUpperBound: "); Serial.println(xUpperBound);
  yLowerBound = yAxisMaximum * 0.25; Serial.print("yLowerBound: "); Serial.println(yLowerBound);
  yUpperBound = yAxisMaximum * 0.75; Serial.print("yUpperBound: "); Serial.println(yUpperBound);
}

void loop() {
  // put your main code here, to run repeatedly:
  randNumber = random(0, 2);
  if (xPosition < xLowerBound) {
    Serial.print("xPosition exceeding lower bound. xPosition: "); Serial.println(xPosition);
    digitalWrite(2, HIGH); xChange = 1;
  } else if (xPosition > xUpperBound) {
    Serial.print("xPosition exceeding upper bound. xPosition: "); Serial.println(xPosition);
    digitalWrite(2, LOW); xChange = -1;
  } else if (randNumber) {
    digitalWrite(2, HIGH); xChange = 1;
  } else {
    digitalWrite(2, LOW); xChange = -1;
  }
  randNumber = random(0, 2);
  if (yPosition < yLowerBound) {
    // Serial.print("yPosition exceeding lower bound. yPosition: "); Serial.println(yPosition);
    digitalWrite(4, HIGH); yChange = 1;
  } else if (yPosition > yUpperBound) {
    // Serial.print("yPosition exceeding upper bound. yPosition: "); Serial.println(yPosition);
    digitalWrite(4, LOW); yChange = -1;
  } else if (randNumber) {
    digitalWrite(4, HIGH); yChange = 1;
  } else {
    digitalWrite(4, LOW); yChange = -1;
  }
  for (int i = 6400; i > 0; i--) {
    digitalWrite(3, LOW); digitalWrite(3, HIGH); xPosition += xChange; // Serial.println(xPosition);
    digitalWrite(5, LOW); digitalWrite(5, HIGH); yPosition += yChange; // Serial.println(yPosition);
    limitSwitch1 = digitalRead(6); limitSwitch2 = digitalRead(7); limitSwitch3 = digitalRead(8); limitSwitch4 = digitalRead(9);
    if (!limitSwitch1) {
      xPosition = 0;
    } else if (!limitSwitch2) {
      xPosition = xAxisMaximum;
    }
    if (!limitSwitch3) {
      yPosition = 0;
    } else if (!limitSwitch4) {
      yPosition = yAxisMaximum;
    }
    if (xPosition < xLowerBound | xPosition > xUpperBound | yPosition < yLowerBound | yPosition > yUpperBound) break;
    Sensor1 = digitalRead(10); Sensor2 = digitalRead(11);
    if (Sensor1 || Sensor2) {
      delayMicroseconds(360);
    } else {
      delayMicroseconds(180);
    }
  }
}
