#define START 2

#define BT_A 3
#define BT_B 4
#define BT_C 5
#define BT_D 6

#define FX_L 7
#define FX_R 8

#define Vol_L_A A0
#define Vol_L_B A1
#define Vol_R_A A2
#define Vol_R_B A3

#include <Mouse.h>
#include <Keyboard.h>

int encStatL, encStatR;
int lsL, lsR;
int rotateSpeed = 3;

void setup() {
  pinMode(START, INPUT);
  pinMode(BT_A, INPUT);
  pinMode(BT_B, INPUT);
  pinMode(BT_C, INPUT);
  pinMode(BT_D, INPUT);
  pinMode(FX_L, INPUT);
  pinMode(FX_R, INPUT);
  pinMode(Vol_L_A, INPUT);
  pinMode(Vol_L_B, INPUT);
  pinMode(Vol_R_A, INPUT);
  pinMode(Vol_R_B, INPUT);

  encStatL = GetStep(digitalRead(Vol_L_A), digitalRead(Vol_L_B));
  encStatR = GetStep(digitalRead(Vol_R_A), digitalRead(Vol_R_B));

  Mouse.begin();
  Keyboard.begin();
}

void loop() {
  Mouse.move(GetVolL() * rotateSpeed, GetVolR() * rotateSpeed);

  TestKey(START, '6');
  TestKey(BT_A, 'a');
  TestKey(BT_B, 'b');
  TestKey(BT_C, 'c');
  TestKey(BT_D, 'd');
  TestKey(FX_L, 'l');
  TestKey(FX_R, 'r');
}

void TestKey(int pin, char key){
  if(digitalRead(pin)){
    Keyboard.press(key);
  }
  else{
    Keyboard.release(key);
  }
}

int GetVolL(){
  int n = GetStep(digitalRead(Vol_L_A), digitalRead(Vol_L_B));
  int delta = GetEncDelta(encStatL, n, &lsL);
  encStatL = n;
  return delta;
}

int GetVolR(){
  int n = GetStep(digitalRead(Vol_R_A), digitalRead(Vol_R_B));
  int delta = GetEncDelta(encStatR, n, &lsR);
  encStatR = n;
  return delta;
}

int GetEncDelta(int l, int n, int *ls){
  if(l == n){
    *ls = 0;
    return 0;
  }
  if((l < 3 && n == l + 1) || (l == 3 && n == 0)){
    *ls = 1;
    return 1;
  }
  else if((l > 0 && n == l - 1) || (l == 0 && n == 3)){
    *ls = -1;
    return -1;
  }
  else{
    return *ls * 2;
  }
}

int GetStep(int A, int B){
  if(A){
    if(B)
      return 2;
    else
      return 1;
  }
  else{
    if(B)
      return 3;
    else
      return 0;
  }
}
