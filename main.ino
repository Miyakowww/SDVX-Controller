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
const int rotateSpeed = 3;

int s, a, b, c, d, l, r;

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
  pinMode(LED_BUILTIN, OUTPUT);

  encStatL = GetStep(digitalRead(Vol_L_A), digitalRead(Vol_L_B));
  encStatR = GetStep(digitalRead(Vol_R_A), digitalRead(Vol_R_B));

  Mouse.begin();
  Keyboard.begin();
}

void loop() {
  Mouse.move(GetVolL() * rotateSpeed, GetVolR() * rotateSpeed);
  
  if(digitalRead(START)){
    if(!s){
      Keyboard.press('6');
      s = 1;
    }
  }
  else if(s){
    Keyboard.release('6');
    s = 0;
  }
  if(digitalRead(BT_A)){
    if(!a){
      Keyboard.press('a');
      a = 1;
    }
  }
  else if(a){
    Keyboard.release('a');
    a = 0;
  }
  if(digitalRead(BT_B)){
    if(!b){
      Keyboard.press('b');
      b = 1;
    }
  }
  else if(b){
    Keyboard.release('b');
    b = 0;
  }
  if(digitalRead(BT_C)){
    if(!c){
      Keyboard.press('c');
      c = 1;
    }
  }
  else if(c){
    Keyboard.release('c');
    c = 0;
  }
  if(digitalRead(BT_D)){
    if(!d){
      Keyboard.press('d');
      d = 1;
    }
  }
  else if(d){
    Keyboard.release('d');
    d = 0;
  }
  if(digitalRead(FX_L)){
    if(!l){
      Keyboard.press('l');
      l = 1;
    }
  }
  else if(l){
    Keyboard.release('l');
    l = 0;
  }
  if(digitalRead(FX_R)){
    if(!r){
      Keyboard.press('r');
      r = 1;
    }
  }
  else if(r){
    Keyboard.release('r');
    r = 0;
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
