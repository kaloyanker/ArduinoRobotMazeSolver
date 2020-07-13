#define sensorPin A0

int distance = 0;
int E1 = 6; //M1 Speed Control
int E2 = 5; //M2 Speed Control
int M1 = 8; //M1 Direction Control
int M2 = 7; //M2 Direction Control

void setup() {
  
  int i;
  for(i=5;i<=8;i++) pinMode(i, OUTPUT);
  Serial.begin(9600);
  
}

long sensor_read() {

/* The Arduino boards contain a multichannel, 10-bit analog to digital converter. 
 *  This means that it will map the input voltage between 0 and the operating voltage into integer values between 0 and 1023. 
 *  On an Arduino Uno, this results in 5 volts / 1024 units or, 4.9 mV per unit.

The MB1240 uses a scaling factor of (Vcc/1024) per cm or 4.9 mV/cm when using a 5 V power supply. 
This makes converting the analogRead value to centimeters super easy, 
you can simply multiply the result by 1.
 */
 
 distance = analogRead(sensorPin) * 1;
 return distance;
}

void loop() {
  //free_move();
  sensor_read();
  print_data();
  delay(500);
}

void print_data() {
  Serial.print("distance = ");
  Serial.print(distance);
  Serial.println("cm");
}

/*
void free_move(){
  sensor_read();
  Serial.print(distance);
  int leftspeed = 250; //255 max
  int rightspeed = 250; //255 max
  int stopall = 0;
  int min = 3; // Minimum distance of 3 cm

  while (distance > min) {
  forward(leftspeed,rightspeed);
  distance = sensor_read();
}
 
  if(distance <= min) //If distance is less or equal minimum {
   reverse (leftspeed,rightspeed); 
   delay (1200); // Reverse during 1.2 seconds
   left (leftspeed,rightspeed); 
   delay (1500); // Go to the left during 1.5 seconds to avoid collision (for the maze mode, this has to change)
}*/

void stop() {
 digitalWrite(E1,LOW);
 digitalWrite(E2,LOW);
}

void forward(char a,char b){
 analogWrite (E1,a);
 digitalWrite(M1,LOW);
 analogWrite (E2,b);
 digitalWrite(M2,LOW);
}

void reverse (char a,char b){
 analogWrite (E1,a);
 digitalWrite(M1,HIGH);
 analogWrite (E2,b);
 digitalWrite(M2,HIGH);
}

void left (char a,char b){
 analogWrite (E1,a);
 digitalWrite(M1,HIGH);
 analogWrite (E2,b);
 digitalWrite(M2,LOW);
}

void right (char a,char b){
 analogWrite (E1,a);
 digitalWrite(M1,LOW);
 analogWrite (E2,b);
 digitalWrite(M2,HIGH);
}
