bool A[3]={};
bool B[3]={};
bool output[6]={};
bool temp[3][5]={0,0,0,0,0};
bool temp2[5]={0,0,0,0,0};
bool temp3[5]={0,0,0,0,0};

bool carrier[7]={};

const int BUTTON_PIN[7] = {7, 4, 2, 13, 12, 8, 14};
const int LED_PIN[6] = {3, 5, 6, 9, 10, 11};


int buttonState[7] = {0,0,0,0,0,0,0};  

void setup() {
  Serial.begin(9600);
  for(int i=0;i<=5;i++){
    pinMode(LED_PIN[i], OUTPUT);   //設定LED的PIN腳為輸出
    pinMode(BUTTON_PIN[i], INPUT); //設定按鈕的接腳為輸入，因為我們要讀取它的狀態
  }
}

int full_Adder(bool A, bool B, bool C){
  int sum = A^B^C;
  int carry = (A&B)|((A^B)&C);
  return sum, carry;
}

void loop() {
//讀取開關
  for(int i=0;i<=6;i++){
    buttonState[i] = digitalRead(BUTTON_PIN[i]);    
  }
  for(int i=0;i<=2;i++){
    if(buttonState[i]==LOW){
      A[i]=0;
    }
    else A[i]=1;
  }
  for(int i=3;i<=5;i++){
    if(buttonState[i]==LOW){
      B[i-3]=0;
    }
    else B[i-3]=1;
  }

  //加法器
  if(val==0){
    carrier[0]=0;
    for(int i=0;i<=2;i++){
      output[i], carrier[i+1] = full_Adder(A[i],B[i],carrier[i]);
    }
    output[4] = carrier[4];
  }
  //乘法器
  if(val==1){
    for(int i=0;i<=2; i++){
      temp[i][0+i] = A[0]&B[i];
      temp[i][1+i] = A[1]&B[i];
      temp[i][2+i] = A[2]&B[i];
    }
    carrier[0]=0;
    for(int i=0;i<=5;i++){
        output[i], carrier[i+1] = full_Adder(temp[0][i], temp[1],[i],temp[2][i]);
    }
  }

  for(int i=0; i<=5; i++){
    if(output[i]==0) digitalWrite(LED_PIN[i], LOW);
    else digitalWrite(LED_PIN[i], HIGH);
  }

}

