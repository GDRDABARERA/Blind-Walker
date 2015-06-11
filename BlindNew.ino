
#define trigPin 13
#define echoPin 12
#define trigPin2 9
#define echoPin2 8
#define led 11
#define led2 10
#include <Servo.h>
int pos = 0; // variable to store the servo position
int defPOS = 0;
int array[20];

Servo myservo;
void setup() {
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(led, OUTPUT);
  pinMode(led2, OUTPUT);
  myservo.attach(9);
  myservo.write(0);

}

void loop() {
  int x;
  long duration, distance;
  long duration2, distance2 ;
  for(x=0 ; x< 5 ; x++){
    
    digitalWrite(trigPin, LOW); // Added this line
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2); // Added this line
    digitalWrite(trigPin, HIGH);
    digitalWrite(trigPin2, HIGH);
    // delayMicroseconds(1000); - Removed this line
    delayMicroseconds(10); // Added this line
    digitalWrite(trigPin, LOW);
    digitalWrite(trigPin2, HIGH);
    duration = pulseIn(echoPin, HIGH);
    distance = (duration/2) / 58.2;
    duration2 = pulseIn(echoPin2, HIGH);
    distance2 = (duration2/2) / 58.2;
    array[x] = distance;
    array[x+5] = distance2;
  }
  distance = median(array);
  //0 Left
  //1 Center
  //2 Right
  int buttonState1 = digitalRead(led); //red
  int buttonState2 = digitalRead(led2); //green
  if( (buttonState1 == 0 && buttonState2 == 1) && (defPOS != 1))
  {
    delay(2000);
    if(defPOS == 2)
    {
      for(pos = 0; pos <= 90; pos += 1) // goes from 0 degrees to 180 degrees
      { // in steps of 1 degree
        myservo.write(pos); // tell servo to go to position in variable 'pos'
        delay(2); // waits 15ms for the servo to reach the position
      }
    }
    else if(defPOS == 0)
    {
      for(pos = 0; pos <= 90; pos += 1) // goes from 0 degrees to 180 degrees
      { // in steps of 1 degree
        myservo.write(pos); // tell servo to go to position in variable 'pos'
        delay(2); // waits 15ms for the servo to reach the position
      }
    }
    defPOS = 1;
  }
  
  if (distance < 30) { // This is where the LED On/Off happens
    digitalWrite(led,HIGH); // When the Red condition is met, the Green LED should turn off
    digitalWrite(led2,LOW);
    if(defPOS == 0)
    {
      for(pos = 90; pos>=0; pos-=1) // goes from 180 degrees to 0 degrees
      {
        myservo.write(pos); // tell servo to go to position in variable 'pos'
        delay(2); // waits 15ms for the servo to reach the position
      }
      defPOS = 2;
    }
    else if(defPOS == 2)
    {
      for(pos = 0; pos <= 90; pos += 1) // goes from 0 degrees to 180 degrees
      { // in steps of 1 degree
        myservo.write(pos); // tell servo to go to position in variable 'pos'
        delay(2); // waits 15ms for the servo to reach the position
      }
      defPOS = 1;
    }
    else if(defPOS == 1)
    {
      for(pos = 0; pos <= 180; pos += 1) // goes from 0 degrees to 180 degrees
      { // in steps of 1 degree
          myservo.write(pos); // tell servo to go to position in variable 'pos'
          delay(2); // waits 15ms for the servo to reach the position
      }
      defPOS = 0;
    }
    //myservo.write(180);
    // delay(1000);
    //myservo.write(0);
  }
  else {
    digitalWrite(led,LOW);
    digitalWrite(led2,HIGH);
  }
  
  if (distance >= 400 || distance <= 0){
    Serial.println("Out of range sensor 1");
  }
  else {
    Serial.print(distance);
    Serial.println(" cm from sensor 1");
  }
  /*
  if (distance2 >= 400 || distance2 <= 0){
    Serial.println("Out of range sensor 2");
  }
  else {
    Serial.print(distance2);
    Serial.println(" cm from sensor 2");
  }
  */
  delay(50);
}


void bubbleSort(int array[]){
        boolean status;
        int i,x;
        for( x = 0 ; x < 10 ; x++ ){
            status = false;
            for( i = 9 ; i > x ; i-- ){
                if(array[i] < array[i-1]){
                    int temp = array[i-1];
                    array[i-1] = array[i];
                    array[i] = temp ;
                    status = true;
                }
            }
            
            if(status == false){
                break;
            }
        }      
        //return array;
}

int median(int array[]){
  
  bubbleSort(array);
  
  int i = 0;
  int sum = 0;
  int len = 0;
  
  
  for(i=0;i<10-1;i++){
    //len = i;
    if((array[i+1]-array[i])> 50){
      break;
    }else{
      sum = sum + array[i];
      len++;
    }
  }
  return (int)(sum/len);
}


