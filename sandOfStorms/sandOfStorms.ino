int PIEZO = 9;
int del = 2000;

#define BPM 136.0f
#define DELAY (1.0f/BPM)*60.0f

void setup() {
  // put your setup code here, to run once:
  //pinMode(14, INPUT);
  pinMode(PIEZO, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
    multi   (329.64f,4,4);
  playStac(329.64f,2);
  
  multi   (329.64f,4,6);
  playStac(329.64f,2);
  
  multi   (440.00f,4,6);
  playStac(440.00f,2);
  
  multi   (392.00f,4,6);
  playStac(392.00f,2);
  
  playStac(293.67f,2);
  
  multi   (329.64f,4,4);
  playStac(329.64f,2);
  
  multi   (329.64f,4,6);
  playStac(329.64f,2);
  
  playStac(440.00f,2);
  
  multi   (329.64f,4,4);
  playStac(329.64f,2);
  
  multi   (329.64f,4,6);
  playStac(329.64f,2);
  
  playStac(392.00f,2);
}

void multi(float freq, int len, int rep)
{
  int i;
  for(i = 0; i < rep; i++)
    playStac(freq,len);
}

void playStac(float freq, int len)
{
   playNote(freq,len*2);
   playRest(len*2);
}

void playRest(int len)
{
  delay(1000.0f*DELAY/((float)len));
}

//freq is frequency of note
//len is length of note eg 4 is quarter note 8 is quaver
void playNote(float freq,int len)
{
   float period = 1.0f/freq;
   float t;
   for(t = 0.0f; t < DELAY/((float)len); t+= period)
   {
     digitalWrite(PIEZO, HIGH);
     delayMicroseconds(period*1000000.0f/2.0f);
     digitalWrite(PIEZO,LOW);
     delayMicroseconds(period*1000000.0f/2.0f);
   }
}
