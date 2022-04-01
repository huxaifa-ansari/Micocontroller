#define x A0
#define y A1
#define z A2

int x_val;
int y_val;
int z_val;

void setup() {
  // put your setup code here, to run once:
  pinMode(x, INPUT);
  pinMode(y, INPUT);
  pinMode(z, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  x_val = analogRead(A0);
  y_val = analogRead(A1);
  z_val = analogRead(A2);
  Serial.print("X: ");
  Serial.println(x_val);
  Serial.print("Y: ");
  Serial.println(y_val);
  Serial.print("Z: ");
  Serial.println(z_val);
  Serial.println("--------------------------------");
}
