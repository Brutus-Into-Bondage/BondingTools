int lightpin = 13;
#define A_pin 8
#define B_pin 9
#define C_pin 10
#define D_pin 5
#define E_pin 4
#define F_pin 7
#define G_pin 6
#define DP_pin 11
#define buttonA 12

int state = 1;

void setup() 
{ 
  pinMode(buttonA, INPUT_PULLUP);
  pinMode(A_pin, OUTPUT);
  pinMode(B_pin, OUTPUT);
  pinMode(C_pin, OUTPUT);
  pinMode(D_pin, OUTPUT);
  pinMode(E_pin, OUTPUT);
  pinMode(F_pin, OUTPUT);
  pinMode(G_pin, OUTPUT);
  pinMode(DP_pin, OUTPUT);
  pinMode(lightpin, OUTPUT);
}

void loop() 
{


while (digitalRead(buttonA) == LOW)
{
   switch (state)
   {
    case 1: 
      digitalWrite(A_pin, HIGH);
      digitalWrite(B_pin, LOW);
      digitalWrite(C_pin, LOW);
      digitalWrite(D_pin, HIGH);
      digitalWrite(E_pin, HIGH);
      digitalWrite(F_pin, HIGH);
      digitalWrite(G_pin, LOW);
      digitalWrite(DP_pin, LOW);
     
      state = 2;
      break;
      
    case 2:
      digitalWrite(A_pin, LOW);
      digitalWrite(B_pin, LOW);
      digitalWrite(C_pin, LOW);
      digitalWrite(D_pin, HIGH);
      digitalWrite(E_pin, HIGH);
      digitalWrite(F_pin, HIGH);
      digitalWrite(G_pin, LOW);
      digitalWrite(DP_pin, LOW);
      
      state = 3;
      break;
      
    case 3:
      digitalWrite(A_pin, HIGH);
      digitalWrite(B_pin, HIGH);
      digitalWrite(C_pin, HIGH);
      digitalWrite(D_pin, HIGH);
      digitalWrite(E_pin, HIGH);
      digitalWrite(F_pin, HIGH);
      digitalWrite(G_pin, LOW);
      digitalWrite(DP_pin, LOW);
     
      state = 4;
      break;
      
    case 4:
      digitalWrite(A_pin, HIGH);
      digitalWrite(B_pin, LOW);
      digitalWrite(C_pin, LOW);
      digitalWrite(D_pin, HIGH);
      digitalWrite(E_pin, HIGH);
      digitalWrite(F_pin, HIGH);
      digitalWrite(G_pin, LOW);
      digitalWrite(DP_pin, LOW);
     
      state = 5;
      break;
      
    case 5:
      digitalWrite(A_pin, HIGH);
      digitalWrite(B_pin, LOW);
      digitalWrite(C_pin, HIGH);
      digitalWrite(D_pin, LOW);
      digitalWrite(E_pin, HIGH);
      digitalWrite(F_pin, HIGH);
      digitalWrite(G_pin, HIGH);
      digitalWrite(DP_pin, LOW);
     
      state = 1;
      break;
   }
delay(1000);
}



  dash(); dot(); dash(); dot();
  delay(1000);
  dot(); dash(); dot(); dot();
  delay(1000);
  dash(); dash(); dash();
  delay(1000);
  dash(); dot(); dash(); dot();
  delay(1000);
  dash(); dot(); dash();
  delay(5000);

  
}

void dot()
{
  digitalWrite(lightpin, HIGH);
  delay(250);
  digitalWrite(lightpin, LOW);
  delay(250);
}

void dash()
{
  digitalWrite(lightpin, HIGH);
  delay(1000);
  digitalWrite(lightpin, LOW);
  delay(250);
} 
