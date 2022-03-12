const byte Startpin = 8;
const byte Fallpin = 9;
const byte Endpin = 10;
const byte buzzerpin = 5;

enum GameState{SUCCESS, IN_PLAYING, FAILED};
GameState gameState = GameState::FAILED;

void setup() {
  pinMode(Startpin, INPUT_PULLUP);
  pinMode(Fallpin, INPUT_PULLUP);
  pinMode(Endpin, INPUT_PULLUP);
  pinMode(buzzerpin, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  switch(gameState){
    case GameState::IN_PLAYING:
      if(!digitalRead(Endpin)){
        gameState = GameState::SUCCESS;
        Serial.println("Congratulation!");
        tone(buzzerpin, 440, 250);
        delay(200);
        tone(buzzerpin, 506, 250);
        delay(200);
     }
      else if(!digitalRead(Fallpin)){
        gameState = GameState :: FAILED;
        Serial.println("Try Again Next Time...");
        tone(buzzerpin, 490, 250);
        delay(200);
        tone(buzzerpin, 526, 250);
        delay(200);
      }
      break;
  case GameState::FAILED:
  case GameState::SUCCESS:
      if(!digitalRead(Startpin)){
        gameState = GameState :: IN_PLAYING;
        Serial.println("WELCOME CHALLENGER!");
        tone(buzzerpin, 440, 250);
        delay(200);
        tone(buzzerpin, 506, 250);
        delay(200);
      }
    break;
  }
}
