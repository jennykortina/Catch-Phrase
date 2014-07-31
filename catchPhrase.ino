#include <LiquidCrystal.h>  // include the library code:
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);  // initialize the library with the numbers of the interface pins

//counting vars
int newGame = 0;  
int timerCounter = 0;
int timerMaxCount = 60;
int teamOneReadScore = 0;
int teamTwoReadScore = 0;
int teamOneWins = 0;
int teamTwoWins = 0;

//setting up the buzzer
const int buzzerPin =  10;      // the number of the buzzer pin
int buzzerState = LOW;             // buzzerState used to set the buzzer
long previousMillis = 0;        // will store last time buzzer was updated
long buzzerInterval = 300;           // buzzerInterval (milliseconds)


// setting up start button
int startButtonPin = 9;  
int startButtonPushCounter = 0;   // counter for the number of button presses
int startButtonState = 0;         // current state of the button
int startButtonLastestState = 0;     // previous state of the button

// setting up next button
int nextButtonPin = 8;  
int nextButtonPushCounter = 0;  
int nextButtonState = 0;         
int nextButtonLastestState = 0;     

// setting up teamOne button
int teamOneButtonPin = 7;  
int teamOneButtonPushCounter = 0;  
int teamOneButtonState = 0;         
int teamOneButtonLastestState = 0; 

// setting up teamTwo button
int teamTwoButtonPin = 6;  
int teamTwoButtonPushCounter = 0;  
int teamTwoButtonState = 0;         
int teamTwoButtonLastestState = 0;   

String words[] = { 
  "Mona Lisa","kitchen","wig","tree house","java script","grover","orange","fun","asha","hotdog","canada","wrist","red","apple","ape","mom","love","fart","kortina","lcd"}; // an array of words for catchphrase
int maxSize = sizeof(words)/sizeof(String);
int interval = 0;

void setup() {
  lcd.begin(2,16);
  shuffle(); 
  pinMode(startButtonPin, INPUT);    // button as input
  digitalWrite(startButtonPin, HIGH); // turns on pull-up resistor after input
  pinMode(nextButtonPin, INPUT);   
  digitalWrite(nextButtonPin, HIGH); 
  pinMode(teamOneButtonPin, INPUT);   
  digitalWrite(teamOneButtonPin, HIGH); 
  pinMode(teamTwoButtonPin, INPUT);   
  digitalWrite(teamTwoButtonPin, HIGH); 
  pinMode(buzzerPin, OUTPUT);  //buzzer setup
  lcd.print("Press Start!");
}

void loop() {
  printScore();
  timerTone(); 
   
  startButtonState = digitalRead(startButtonPin);	
  if (startButtonState != startButtonLastestState) { 
    if(digitalRead(startButtonPin) == LOW){
       if(timerCounter == 0){      
           startGame();
       }
       else {
         digitalWrite(buzzerPin, LOW); 
         timerCounter = 0;
       }
     }         
      
     
            
}
  startButtonLastestState = startButtonState;


  nextButtonState = digitalRead(nextButtonPin);	
  if (nextButtonState != nextButtonLastestState) { 
    if(digitalRead(nextButtonPin) == LOW){
                printWord();
	    }  
            
}
  nextButtonLastestState = nextButtonState;
  
  teamOneButtonState = digitalRead(teamOneButtonPin);	
  if (teamOneButtonState != teamOneButtonLastestState) { 
    if(digitalRead(teamOneButtonPin) == LOW){
                teamOneScore();
	    }  
            
}
  teamOneButtonLastestState = teamOneButtonState;  
  
teamTwoButtonState = digitalRead(teamTwoButtonPin);	
  if (teamTwoButtonState != teamTwoButtonLastestState) { 
    if(digitalRead(teamTwoButtonPin) == LOW){
                teamTwoScore();
	    }  
            
}
  teamTwoButtonLastestState = teamTwoButtonState; 
  
  
}

// shuffle the list of words
void shuffle(){
  for (int a=0; a<maxSize; a++){
    int r = random(a+1);
    String temp = words[a];
    words[a] = words[r];
    words[r] = temp;
  } 
}

//start the game
void startGame() {  
  lcd.clear();   
  lcd.print(words[interval]);
  interval++;
  newGame++;
  timerCounter ++;
  if (interval == maxSize) {
    interval = 0;
    shuffle();    
  } 
 }

//print the word
void printWord() { 
      if (timerCounter !=0) {
        lcd.clear();   
        lcd.print(words[interval]);
        interval++;
        if (interval == maxSize) {
          interval = 0;
          shuffle();    
        } 
     } 
  } 

//timer with buzzer
void timerTone() {
  unsigned long currentMillis = millis();
  if (timerCounter > 0) {  
    if (timerCounter < timerMaxCount) { 
      if(currentMillis - previousMillis > buzzerInterval) {
          previousMillis = currentMillis;   
          if (buzzerState == LOW){
              buzzerState = HIGH;
          }
          else{
              buzzerState = LOW;
          }    
        digitalWrite(buzzerPin, buzzerState); 
        timerCounter++;
      }
    } 
  }  
  if (timerCounter == timerMaxCount) { 
     digitalWrite(buzzerPin, LOW); 
     timerCounter = 0;
  }
}

//teamOne score
void teamOneScore() {  
  if (newGame != 0) { 
      teamOneReadScore++;
      lcd.setCursor(0, 1); // bottom left
      lcd.print("One: ");
      lcd.print(teamOneReadScore);  
    if (teamOneReadScore > 10) {
      lcd.clear();   
      lcd.setCursor(0, 0);
      lcd.print("Team One wins!");
      newGame = 0;
      teamOneReadScore = 0;
      teamTwoReadScore = 0;
      teamOneWins = 1;
      timerCounter = 0; 
      digitalWrite(buzzerPin, LOW); 
    } 
   } 
 }

//teamTwo score
void teamTwoScore() { 
  if (newGame != 0) {  
      teamTwoReadScore++;
      lcd.setCursor(9, 1); // bottom right
      lcd.print("Two: ");
      lcd.print(teamTwoReadScore);
    if (teamTwoReadScore > 10) {
      lcd.clear();   
      lcd.setCursor(0, 0);
      lcd.print("Team Two wins!");
      newGame = 0;  
      teamOneReadScore = 0;
      teamTwoReadScore = 0;
      teamTwoWins = 1;
      timerCounter = 0;
      digitalWrite(buzzerPin, LOW); 
    } 
  } 
 }
 
 //print score
void printScore() { 
  if (newGame > 0) {
    lcd.setCursor(0, 1); // bottom left
    lcd.print("One: ");
    lcd.print(teamOneReadScore);
    lcd.setCursor(9, 1); // bottom right
    lcd.print("Two: ");
    lcd.print(teamTwoReadScore);
    }
 }

