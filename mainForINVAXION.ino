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

int s, a, b, c, d, l, r;
int vll, vlr, vrl, vrr;
int vlp = 0, vrp = 0, vrhp = 0;
const int vls = 10, vrs = 7, vrh = 500;

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
  int dl = GetVolL();
  int dr = GetVolR();
  if(dl < 0){
    if(!vll){
      Keyboard.press(KEY_LEFT_ARROW);
      vll = 1;
    }
  }
  else if(vll){
    Keyboard.release(KEY_LEFT_ARROW);
    vll = 0;
  }
  if(dl > 0){
    if(!vlr){
      Keyboard.press(KEY_RIGHT_ARROW);
      vlr = 1;
    }
  }
  else if(vlr){
    Keyboard.release(KEY_RIGHT_ARROW);
    vlr = 0;
  }
  if(dr < 0){
    if(!vrl){
      Keyboard.press(KEY_UP_ARROW);
      vrl = 1;
    }
  }
  else if(vrl){
    Keyboard.release(KEY_UP_ARROW);
    vrl = 0;
  }
  if(dr > 0){
    if(!vrr){
      Keyboard.press(KEY_DOWN_ARROW);
      vrr = 1;
    }
  }
  else if(vrr){
    Keyboard.release(KEY_DOWN_ARROW);
    vrr = 0;
  }
  
  if(digitalRead(START)){
    if(!s){
      Keyboard.press('\n');
      s = 1;
    }
  }
  else if(s){
    Keyboard.release('\n');
    s = 0;
  }
  if(digitalRead(BT_A)){
    if(!a){
      Keyboard.press('d');
      a = 1;
    }
  }
  else if(a){
    Keyboard.release('d');
    a = 0;
  }
  if(digitalRead(BT_B)){
    if(!b){
      Keyboard.press('f');
      b = 1;
    }
  }
  else if(b){
    Keyboard.release('f');
    b = 0;
  }
  if(digitalRead(BT_C)){
    if(!c){
      Keyboard.press('j');
      c = 1;
    }
  }
  else if(c){
    Keyboard.release('j');
    c = 0;
  }
  if(digitalRead(BT_D)){
    if(!d){
      Keyboard.press('k');
      d = 1;
    }
  }
  else if(d){
    Keyboard.release('k');
    d = 0;
  }
  if(digitalRead(FX_L)){
    if(!l){
      Keyboard.press('s');
      l = 1;
    }
  }
  else if(l){
    Keyboard.release('s');
    l = 0;
  }
  if(digitalRead(FX_R)){
    if(!r){
      Keyboard.press('l');
      r = 1;
    }
  }
  else if(r){
    Keyboard.release('l');
    r = 0;
  }
}

int GetVolL(){
  int n = GetStep(digitalRead(Vol_L_A), digitalRead(Vol_L_B));
  int delta = GetEncDelta(encStatL, n, &lsL);
  encStatL = n;
  vlp += delta;
  if(vlp < -vls){
    vlp = 0;
    return -1;
  }
  if(vlp > vls){
    vlp = 0;
    return 1;
  }
  return 0;
}

int GetVolR(){
  int n = GetStep(digitalRead(Vol_R_A), digitalRead(Vol_R_B));
  int delta = GetEncDelta(encStatR, n, &lsR);
  encStatR = n;
  vrp += delta;
  if(vrp < -vrs){
    vrp = 0;
    vrhp = -vrh;
    return -1;
  }
  if(vrp > vrs){
    vrp = 0;
    vrhp = vrh;
    return 1;
  }
  if(vrhp < 0){
    vrhp++;
    return -1;
  }
  if(vrhp > 0){
    vrhp--;
    return 1;
  }
  return 0;
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
