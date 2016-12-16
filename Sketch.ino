#Sketch www.kabib.net
#define relay1 2
#define relay2 3

int motorPin1=7;
int motorPin2=8;
int kecepatan=9;
#include <IRremote.h>
int RECV_PIN = 12;
IRrecv irrecv(RECV_PIN);
decode_results results;
int stat=0;

void setup()
{
  Serial.begin(9600); //buka komunikasi dengan 9600
  irrecv.enableIRIn(); // Start the receiver
  pinMode(relay1,OUTPUT);
  pinMode(relay2,OUTPUT);
  pinMode(motorPin1,OUTPUT);
  pinMode(motorPin2,OUTPUT);
  pinMode(kecepatan,OUTPUT);
  digitalWrite(relay1,HIGH);
  digitalWrite(relay2,HIGH);
}
int spd=0;

void loop() {
  if (irrecv.decode(&results)) {
    delay(600);
    int nilairecv=results.value;
    Serial.println(nilairecv);
    if(nilairecv==7603){
      Serial.println("Berhenti Berputar");
      digitalWrite(relay1,HIGH);
      digitalWrite(relay2,HIGH);
      berhenti();
    }
    if(nilairecv==12501){
      Serial.println("Berputar Kecepatan Sedang");
      digitalWrite(relay1,LOW);
      digitalWrite(relay2,HIGH);
    }
    if(nilairecv==-12367){
      Serial.println("Berputar Kecepatan Tinggi");
      digitalWrite(relay1,HIGH);
      digitalWrite(relay2,LOW);
    }
    if(nilairecv==-26325){
      Serial.println("Ungkit");
      ungkit(255);
    }
    if(nilairecv==-14323){
      Serial.println("Turun");
      normal(255);
    }
    if(nilairecv==-26534){
      Serial.println("Berhenti Ungkit");
      berhenti();
    }   
    irrecv.resume(); // Receive the next value
  }
}
void ungkit(int s){
 analogWrite(kecepatan,s);
 digitalWrite(motorPin1,HIGH);
 digitalWrite(motorPin2,LOW);
}
void berhenti(){
 analogWrite(kecepatan,0);
 digitalWrite(motorPin1,LOW);
 digitalWrite(motorPin2,HIGH);
}
void normal(int s){
 analogWrite(kecepatan,0);
 digitalWrite(motorPin1,LOW);
 digitalWrite(motorPin2,HIGH);
}
