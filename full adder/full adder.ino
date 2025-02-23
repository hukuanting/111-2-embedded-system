bool A[3]={};
bool B[3]={};
bool output[6]={};
bool sum, sum1, sum2, sum3, sum4, sum5;
bool carrier, carrier1, carrier2, carrier3, carrier4, carrier5;


const int BUTTON_PIN[6] = {7, 4, 2, 13, 12, 8};
const int LED_PIN[6] = {3, 5, 6, 9, 10, 11};

int buttonState[6] = {0,0,0,0,0,0};  

void setup() {
  Serial.begin(9600);
  for(int i=0;i<=5;i++){
    pinMode(LED_PIN[i], OUTPUT);   //設定LED的PIN腳為輸出
    pinMode(BUTTON_PIN[i], INPUT); //設定按鈕的接腳為輸入，因為我們要讀取它的狀態
  }
}
bool halfAdder_sum(bool X, bool Y){
  bool sum = X^Y;
  return sum;
}
bool halfAdder_carry(bool X, bool Y){
  bool carry = X&Y;
  return carry;
}

bool fullAdder_sum(bool A, bool B, bool C){
  bool sum = A^B^C;
  return sum;
}
bool fullAdder_carry(bool A, bool B, bool C){
  bool temp1 = ((A^B)&C);
  bool temp2 = A&B;
  bool carry = temp1|temp2;
  return carry;
}

void loop() {
//讀取開關
  for(int i=0;i<=5;i++){
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

  //乘法器
  output[0] = A[0]&B[0];

  sum = halfAdder_sum(A[1]&B[0], A[0]&B[1]);
  carrier = halfAdder_carry(A[1]&B[0], A[0]&B[1]);
  
  output[1] = sum;

  sum1 = halfAdder_sum(A[2]&B[0], A[1]&B[1]);
  carrier1 = halfAdder_carry(A[2]&B[0], A[1]&B[1]);

  sum2 = fullAdder_sum(sum1, A[0]&B[2], carrier);
  carrier2 = fullAdder_carry(sum1, A[0]&B[2], carrier);

  output[2] = sum2;

  sum3 = fullAdder_sum(A[2]&B[1], A[1]&B[2], carrier1);
  carrier3 = fullAdder_carry(A[2]&B[1], A[1]&B[2], carrier1);

  sum4 = halfAdder_sum(sum3, carrier2);
  carrier4 = halfAdder_carry(sum3, carrier2);

  output[3] = sum4;

  sum5 = fullAdder_sum(A[2]&B[2], carrier4, carrier3);
  carrier5 = fullAdder_carry(A[2]&B[2], carrier4, carrier3);

  output[4] = sum5;
  output[5] = carrier5;



  for(int i=0; i<=5; i++){
    if(output[i]==0) digitalWrite(LED_PIN[i], LOW);
    else digitalWrite(LED_PIN[i], HIGH);
  }

}

