#define x A0
#define y A1
#define z A2

int x_val;
int y_val;
int z_val;
int x_val2;
int y_val2;
int z_val2;

void setup() {
  // put your setup code here, to run once:
  pinMode(x, INPUT);
  pinMode(y, INPUT);
  pinMode(z, INPUT);
  x_val = analogRead(A0);
  y_val = analogRead(A1);
  z_val = analogRead(A2);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  x_val2 = analogRead(A0);
  y_val2 = analogRead(A1);
  z_val2 = analogRead(A2);
  int xval = x_val-x_val2;
  int yval = y_val-y_val2;
  int zval = z_val-z_val2;
  if(yval>=60){
    Serial.println("Forward");
  }
  else if(yval<=-60){
    Serial.println("Backward");
  }
  else if(xval>=60){
    Serial.println("Right");
  }
  else if(xval<=-60){
    Serial.println("Left");
  }
  else{
    Serial.println("Stop");
  }
}
