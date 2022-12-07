
int led=7;
int sm1=2;
int sm2=12;
long lastNoiseTime = 0;
long currentNoiseTime = 0;
int lastSoundValue;
long lastLightChange = 0;
void setup() {
  // put your setup code here, to run once:
  pinMode(led,OUTPUT);
 pinMode(sm1,OUTPUT);
 pinMode(sm2,OUTPUT);
 Serial.begin(9600); 
 
}

void loop() {
  // put your main code here, to run repeatedly:
   int analog_val;                 // analog value read from A0
  static bool led_state = false;  // current state of LED
  
  analog_val = analogRead(A0);
   currentNoiseTime = millis();

  if (analog_val > 30) {          // trigger threshold
    // toggle LED
    Serial.println(analog_val);
     
    if (analog_val >= 70) {
     digitalWrite(12, LOW);
      digitalWrite(2, HIGH);

       if (
      (currentNoiseTime > lastNoiseTime + 200) && // to debounce a sound occurring in more than a loop cycle as a single noise
      (currentNoiseTime < lastNoiseTime + 400) && // if current clap is less than 0.8 seconds after the first clap
      (currentNoiseTime > lastLightChange + 1000) // to avoid taking a third clap as part of a pattern
    ) {
      led_state = false;          // LED was on, now off
      digitalWrite(7, LOW);
      lastLightChange = currentNoiseTime;
    }
    else {
      led_state = true;
      digitalWrite(7, HIGH);      // LED was off, now on
    }
      delay(50);
      digitalWrite(12, LOW);
      digitalWrite(2, LOW);
      lastNoiseTime = currentNoiseTime;
    }
    else{
      digitalWrite(2, LOW);
      digitalWrite(12, HIGH);
    }
  }
  lastSoundValue = analog_val;
 

}
