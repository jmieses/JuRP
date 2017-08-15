// This code produce a PWM signal of a desired frequency controlled by the proper registers.
// I applied changes to this code given to me by Xinhai. 
#define ENABLE_PIN 12
#define PWM_PIN 7
#define ERROR_LED_PIN 13
#define ENABLE_PIN_CCW 11

#define ENCODER_PINA 2
#define ENCODER_PINB 3

#define ENCODER_A_INTERRUPT 0
#define ENCODER_B_INTERRUPT 1

String enter_duty ;
volatile long encoderCount = 0;
volatile float velocity = 0.00;
///////////////////////////////////////////////
// This is the external interrupt in pin 2 and 3 for channel A and B of the encoder.
void external_encoder_interrupt(){
  static int8_t lookup_table[]={0,-1,1,0,1,0,0,-1,-1,0,0,1,0,1,-1,0};
  static uint8_t enc_val = 0;

  enc_val = enc_val << 2;
  enc_val = enc_val | ((PINE & 0b110000)>>4);

  encoderCount = encoderCount + lookup_table[enc_val & 0b1111];
 // Serial.println(encoderCount);
}
// Create the timer interrupt for velocity calculation
void timer5_interrupt()
{
  TCCR5A = 0;
  TCCR5B = 0;

  OCR5A = 31250;
  TCCR5B |= (1<<WGM52);
  TCCR5B |= (1<<CS51);
  TIMSK5 |=(1<<OCIE5A);
  
}

ISR(TIMER5_COMPA_vect)
{
  #define COUNTS_PER_TURN 500
  velocity = (float)(encoderCount)*6000/COUNTS_PER_TURN;
  Serial.println(velocity);
  encoderCount = 0;
}



void enable_encoder(){
  pinMode(ENCODER_PINA,INPUT);
  digitalWrite(ENCODER_PINA,LOW);
  pinMode(ENCODER_PINB, INPUT);
  digitalWrite(ENCODER_PINB,LOW);

  attachInterrupt(ENCODER_A_INTERRUPT, external_encoder_interrupt, CHANGE);
    attachInterrupt(ENCODER_B_INTERRUPT, external_encoder_interrupt, CHANGE);
}

///////////////////////////////////////////////
// Enabling pin 12 after software started. 
int enabling = 1;
void enabling_setup()
{
    Serial.println("Input:  ");
  while(Serial.available()==0){
    // wait for input
  }
  digitalWrite(ENCODER_PINA,HIGH);
  digitalWrite(ENCODER_PINB,HIGH);
  enabling = Serial.parseInt();

   if (enabling==1)
  {
    digitalWrite(ENABLE_PIN_CCW,LOW);
    digitalWrite(ENABLE_PIN, HIGH);
  }
  else if(enabling==0)
  {
    digitalWrite(ENABLE_PIN, LOW);
     digitalWrite(ENABLE_PIN_CCW,LOW);
  }
  else if(enabling == -1)
  {
     digitalWrite(ENABLE_PIN, LOW);
     digitalWrite(ENABLE_PIN_CCW,HIGH);
  }
  /*for (int i = 0; i < 5; i++)
  {
// Serial.println(encoderCount);
// Serial.println(velocity);
  } */
}

////////////////////////////////////////////////
void set_error_light()
{
  digitalWrite(ERROR_LED_PIN,HIGH);
}

void clear_error_light()
{
  digitalWrite(ERROR_LED_PIN, LOW);
}
////////////////////////////////////////////////
// This function sets the desire duty cycle 0-100%
float duty = 50.0;
void set_duty(float duty)
{
  if(duty>100)
  {
  set_error_light();
  return;
}

OCR4B = (duty*OCR4A)/100;
}
////////////////////////////////////////////////
void ask_for_duty()
{
  
  Serial.println("Enter duty cycle: ");
  while(Serial.available()==0){
    // do nothing 
  }
  duty = Serial.parseFloat();
  set_duty(duty);
}
////////////////////////////////////////////////
// This function sets the PWM signal to the desired frequency. 
void PWM_signal()
{
  pinMode(PWM_PIN, OUTPUT);

  TCCR4A &=~(0XFF);
  TCCR4A |= (1<<COM4B1)|(1<<WGM40)|(1<<WGM41);
  TCCR4B &=~ (1<<CS40)|(1<<WGM43);
  OCR4A = 2000;
  //OCR4B = 1600;
}

void setup()
{
  Serial.begin(9600);
 
  pinMode(ENABLE_PIN, OUTPUT);
   digitalWrite(ENABLE_PIN, LOW);
   digitalWrite(ENABLE_PIN_CCW,LOW);
   PWM_signal();
   enable_encoder();
}

void loop(){
  ask_for_duty();
   enabling_setup();
   
  
   
   
   }


