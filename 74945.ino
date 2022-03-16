
 const int DAT = 2;
 const int CLK = 3;
 const int STR = 4;
 const int BTN = 5;
 uint8_t leds = 0; //0b00000000
 
 //0|0=>0
 //0|1=>1
 //1|0=>1
 //1|1=>1

 void OnLED(uint8_t n){
   //n=0 => 0b00000001;
   //n=1 => 0b00000010;
   leds |= 1<<n;
  // Serial.println("Led" +String(n) + "on!");
 }

 //0&0=>0
 //0&1=>0
 //1&0=>0
 //1&1=>1
//~00000000=>11111111
//~10101010=>01010101
  void OffLED(uint8_t n){ //0b11111111 & 0b11111110
   //n=0 => 0b00000001;
   //n=1 => 0b00000010;
   leds &= ~(1<<n);
   //Serial.println("Led" +String(n) + "off!");
 }

//ABCDEFGH
//10000000
//A0000000

//ABCDEFGH
//01000000
//0B000000
 void Update(){
   for(uint8_t mask = 0b10000000; mask != 0 ; mask>>=1){
    //Serial.println("looping" + String(mask));
     if((leds & mask) != 0){
       digitalWrite(DAT, HIGH);
     }else{
        digitalWrite(DAT, LOW);
     }
     delay(1);
     digitalWrite(CLK, HIGH);
     delay(1);
     digitalWrite(CLK, LOW);
   }
  // Serial.println("strobing");
     digitalWrite(STR, HIGH);
     delay(1);
     digitalWrite(STR, LOW);  
 }
  
void setup() {
  Serial.begin(115200);
  pinMode(DAT, OUTPUT);
  digitalWrite(DAT, LOW);
  pinMode(CLK, OUTPUT);
  digitalWrite(CLK, LOW);
  pinMode(STR, OUTPUT);
  digitalWrite(STR, LOW);
  pinMode(BTN, INPUT_PULLUP);
  
}

int led = 0;
void Chase1(){
    OnLED(led%8);
    OffLED((led-1)%8);
    led++;
    Update();
    delay(100);
//    Serial.println("Chasing! Chasing!! Chasing!!!");
}

void Chase2(){
    OnLED(led%8);
    OnLED((led+1)%8);
    OffLED((led-1)%8);
    led++;
    Update();
    delay(100);
//    Serial.println("Chasing! Chasing!! Chasing!!!");
}
void Blink(){
  for (int i = 0; i < 8; i++)
  {
    OnLED(i);
    Update();
  }
  delay(100);
   for (int i = 0; i < 8; i++)
  {
    OffLED(i);
    Update();
  }
}

bool bstate = true;
void Blinker(){
    for (int i = 0; i < 8; i++){
      if (bstate){
        OnLED(i);
      }else{
        OffLED(i);
      }
    }
    bstate = !bstate;
    Update();
    delay(1000);
//    Serial.println("Blinking! Blinking!! Blinking!!!");
}


int p = 1;
void loop() {
  if(digitalRead(BTN)==LOW)
  {
    Serial.println("keypressed");
    delay(200);
    if (p>4){
      p=1;
    }
    else
      p+=1;
  }
   Serial.println(String(p));
   switch (p){
    case 1:
    Blink();
    Serial.println("blinks");
    break;
    case 2:
    Chase1();
    Serial.println("chasing 1");
    break;
    case 3:
    Chase2();
    Serial.println("chasing 2");
    break;
    case 4:
    Blinker();
    Serial.println("blinking");
    break;
    default:
    Blink();
    Serial.println("default");
    break;
   }
 }
