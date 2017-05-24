#include <Servo.h>     
#define trigPin1 3
#define echoPin1 4
#define trigPin2 7
#define echoPin2 8
#define trigPin3 9
#define echoPin3 10
Servo left;
Servo right;

void setup() {
 Serial.begin (9600);
 pinMode(trigPin1, OUTPUT);
 pinMode(echoPin1, INPUT);
 pinMode(trigPin2, OUTPUT);
 pinMode(echoPin2, INPUT);
 pinMode(trigPin3, OUTPUT);
 pinMode(echoPin3, INPUT);
 pinMode(12,OUTPUT);
 pinMode(13,OUTPUT);
 left.attach(5);
 right.attach(6);

}


void loop() {

 if(sensorVoor() >= 10 || sensorGrond() < 9){  // wanneer je geen muur en ook geen grond hebt 

  if(sensorLinks() <= 13){ //muur links.
   center();
  }
  
  else if(sensorLinks() > 13){ //geen muur links.
    vooruit();
    delay(430);
    turnLeft();
    vooruit();
    delay(430);
  }
}

 if((sensorVoor() < 10 && sensorVoor() > 0 || sensorGrond() >= 9) && sensorLinks() <= 13 ){// wanneer je wel muur of grond hebt en een muur links
    int i = 0;
    if(sensorGrond() >= 9) { //indien afgrond ga eerst achteruit.
      achteruit();
      delay(700);    
      i=1;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                     
    }
   turnRight();
   
   if (sensorVoor() > 8){ // rij naar de rechterkant van de muur van waar de helling zich bevind
    vooruit();
    delay(200);
    if(i == 1){
      delay(300);
      turnRight();
      i = 0;
    }
   }
    else if(sensorVoor() <= 8){ //wanneer je een muur ziet, draai rechts 
      turnRight();
   }
 }
}

int sensorVoor(){
  int duration, afstand;
  digitalWrite(trigPin1, LOW);  
  delayMicroseconds(2); 
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10); 
  digitalWrite(trigPin1, LOW);
  duration = pulseIn(echoPin1, HIGH);
  afstand = (duration/2) / 29.1;
  Serial.println("Sensor 0");
  //Serial.println(afstand);
  if(afstand < 0){
    afstand = 13;
  }
    Serial.println(afstand);
    return afstand;
}

int sensorGrond(){
  int duration, afstand;
  digitalWrite(trigPin2, LOW);  
  delayMicroseconds(2); 
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10); 
  digitalWrite(trigPin2, LOW);
  duration = pulseIn(echoPin2, HIGH);
  afstand = (duration/2) / 29.1;
  Serial.println("Sensor grond:");
  Serial.println(afstand);
  if(afstand < 0){ 
    afstand = 10;
  }
    return afstand;
}


double sensorLinks(){
  double duration, afstand;
  digitalWrite(trigPin3, LOW);  
  delayMicroseconds(2); 
  digitalWrite(trigPin3, HIGH);
  delayMicroseconds(10); 
  digitalWrite(trigPin3, LOW);
  duration = pulseIn(echoPin3, HIGH);
  afstand = (duration/2) / 29.1;
  Serial.println("Sensor links:");
  Serial.println(afstand);
  if(afstand < 0){ 
    afstand = 0;
  }
    return afstand;
}

void vooruit(){
 left.writeMicroseconds(2000);
 right.writeMicroseconds(1000);
}
void Stop(){
 left.writeMicroseconds(1490);
 right.writeMicroseconds(1480);
}
void achteruit(){
 left.writeMicroseconds(1100);
 right.writeMicroseconds(2000);
}

void turnRight(){                                   // Rechts afslaan
 left.writeMicroseconds(2000);
 right.writeMicroseconds(1000);
 delay(625);
 left.writeMicroseconds(1850);
 right.writeMicroseconds(1850);
 delay(585);
}

void turnLeft(){                                       // Links afslaan
 left.writeMicroseconds(2000);
 right.writeMicroseconds(1000);
 delay(625);
 left.writeMicroseconds(1300);
 right.writeMicroseconds(1300);
 delay(585);
}

void checkDL(){                                         // Stuur een beetje bij naar links
 left.writeMicroseconds(1580);
 right.writeMicroseconds(40);
}

void checkDR(){                                        // Stuur een beetje bij naar rechts
 left.writeMicroseconds(2000);
 right.writeMicroseconds(1400);
}

void midden(){                                          // zorgt ervoor door in het midden van de gang te rijden
    if(sensorLinks() < 7){
      checkDR();
    }
    else if(sensorLinks() >= 7){
      checkDL();
    }
}
