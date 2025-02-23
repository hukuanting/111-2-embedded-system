int outPin[4] = {4,12,8,7};
int control[3] = {17,16,15};
int pausePin = 2;
int resetPin = 3;
volatile float count = 0;
bool check=false;

float pauseTime = 0;

void writeNum(int num)
{
  int out[10][4] = {{0,0,0,0},{1,0,0,0},{0,1,0,0},{1,1,0,0},{0,0,1,0},{1,0,1,0},{0,1,1,0},{1,1,1,0},{0,0,0,1},{1,0,0,1}};
  for(int i=0;i<4;i++) {
    digitalWrite(outPin[i], out[num][i]);
  }
}

void sevenLED(int a, int b, int c)
{
  int change[3][3] = {{1,0,0},{0,1,0},{0,0,1}};
  for(int i=0;i<3;i++) digitalWrite(control[i], change[0][i]);
  writeNum(a);
  delay(10);
  for(int i=0;i<3;i++) digitalWrite(control[i], change[1][i]);
  writeNum(b);
  delay(10);
  for(int i=0;i<3;i++) digitalWrite(control[i], change[2][i]);
  writeNum(c);
  delay(10);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  for(int i=0;i<4;i++) pinMode(outPin[i],OUTPUT);
  for(int i=0;i<3;i++) pinMode(control[i],OUTPUT);
  pinMode(pausePin, OUTPUT);
  pinMode(resetPin, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(pausePin), pause, CHANGE);
  attachInterrupt(digitalPinToInterrupt(resetPin), reset, CHANGE);
}

void loop() {
  // put your main code here, to run repeatedly:
  int a,b,c;
  if(check==true){
    count = millis()*0.001 ;
    a = int(count)/10;
    b = int(count)%10;
    c = (int(count*10))%10;
    sevenLED(a,b,c);
  }
  else{
    a=a;
    b=b;
    c=c;
    sevenLED(a,b,c);
  }
}

void pause(){
  check = !check;
}

void reset(){

}
