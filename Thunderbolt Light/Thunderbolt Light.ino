int pin[5] = {3, 5, 6, 9, 10};
int bright[5] = {200, 150, 100, 50 ,0};
bool right = true;
int major = 0;

void setup() {
  // put your setup code here, to run once:
  for(int i =0;i<5;i++)
  { 
    pinMode(pin[i], OUTPUT);
  }
}

void loop() {
  // put your major code here, to run repeatedly:   
  for(int i=0; i<5;i++)
  {
    if(major-i>=0) analogWrite(pin[major-i], bright[i]);
    if(major+i<5) analogWrite(pin[major+i], bright[i]);
  }
  delay(100);
  if(right)
  {
    major++;
    if(major >=5) right = false;
  }
  else
  {
    major--;
    if(major <0) right = true;
  }
}
