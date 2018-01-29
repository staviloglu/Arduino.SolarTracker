const int READ_THRESHOLD = 1000 * 3600; //one hour
const int MOVE_THRESHOLD = 50;
const int NEGATIVE = 0;
const int POSITIVE = 1;
const int STOP = 2;
const int LDR1_PIN = 1;
const int LDR2_PIN = 2;
int LDR1_VAL = 0;
int LDR2_VAL = 0;
int direct0 = 7;
#define Step 7      
#define Dir 6     
int lives = 5;

void setup() {
	Serial.begin(9600);
	pinMode(Step, OUTPUT);
	pinMode(Dir, OUTPUT);
	digitalWrite(Step, LOW);
	digitalWrite(Dir, LOW);
}

void loop() {
	direct0 = MeasureAxisFirst();

	if (direct0 != STOP)    {
		MoveAxisFirst(direct0);
	}
	if (direct0 == STOP)   {
		Serial.println("STOPPED!");
		delay(READ_THRESHOLD);
	}
}

int MeasureAxisFirst() {
	LDR1_VAL = analogRead(LDR1_PIN);
	LDR2_VAL = analogRead(LDR2_PIN);

	Serial.print("MeasureAxisFirst");
	Serial.print("  LDR1 = ");
	Serial.print(LDR1_VAL);
	Serial.print(" - LDR2 = ");
	Serial.println(LDR2_VAL);

	int diff = abs(LDR1_VAL - LDR2_VAL);
	Serial.print(" diff = ");
	Serial.println(diff);

	if (diff >= MOVE_THRESHOLD)   {
		if (LDR1_VAL > LDR2_VAL) {
			return NEGATIVE;
		}
		else {
			return POSITIVE;
		}
	}
	return STOP;
}

void MoveAxisFirst(int direct) {
	digitalWrite(Dir, direct);
	digitalWrite(Step, HIGH);
	delay(lives);
	digitalWrite(Step, LOW);
	delay(lives);
}
