#define resolution 8
#define mains 50  // 60: north america, japan; 50: most other places

#define refresh 2 * 1000000 / mains

int maxval = 20; //This value was obtained by experimenting. Touch the pad
                 //connetced to pin eight. The value in the serial window
                 //corresponding to pin 8 will be maxval.                
int x, y, z;
int R = 2;
int B = 3;
int G = 4;
int red, blu, gre;

void setup() {
  Serial.begin(115200);
  pinMode(R, OUTPUT);
    pinMode(B, OUTPUT);
      pinMode(G, OUTPUT);

  for(int i = 8; i < 11; i++)
    pinMode(i, INPUT);

  startTimer();
}

void loop() {  
  
  Serial.print(time(8, B00000001), DEC);
  Serial.print(" ");
  Serial.print(time(9, B00000010), DEC);
  Serial.print(" ");
  Serial.println(time(10, B00000100), DEC);
  
  
 x = time(8, B00000001), DEC;
 y = time(9, B00000010), DEC;
 z = time(10, B00000100), DEC;
 
 map(red, 0, maxval, 0, 255);
 map(blu, 0, maxval, 0, 255);
 map(gre, 0, maxval, 0, 255); 
 
analogWrite(R, red); 
analogWrite(B, blu);
analogWrite(G, gre);

/* This works for both common anode and cathode LEDs. However, 
   analogWrite(R, 255) will make the red in common anode RGB LED
   off and analogWrite(R, 0) will give it full brightness. The 
   opposite for common cathode. */
} 

// Everything below doesnt need to be changed... 

long time(int pin, byte mask) {
  unsigned long count = 0, total = 0;
//  while(checkTimer() < refresh) {
    // pinMode is about 6 times slower than assigning
    // DDRB directly, but that pause is important
    pinMode(pin, OUTPUT);
    PORTH = 0;
    pinMode(pin, INPUT);
    while((PINH & mask) == 0){
      count++;
    total++;
    }
//  }

  startTimer();
  return (count << resolution) / total;
}

extern volatile unsigned long timer0_overflow_count;

void startTimer() {
  timer0_overflow_count = 0;
  TCNT0 = 0;
}

unsigned long checkTimer() {
  return ((timer0_overflow_count << 8) + TCNT0) << 2;
}


