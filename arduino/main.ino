#include <Keyboard.h>

const int NUM_SLIDERS = 5;
const int analogInputs[NUM_SLIDERS] = {A0, A1, A2, A3, A4};
int analogSliderValues[NUM_SLIDERS];

const int NUM_BUTTONS = 6;
const int buttonPins[NUM_BUTTONS] = {2, 3, 4, 5, 6, 7};
bool buttonStates[NUM_BUTTONS] = {false, false, false, false, false, false};
bool lastButtonStates[NUM_BUTTONS] = {false, false, false, false, false, false};

void updateSliderValues();
void sendSliderValues();
void executeMacro(int buttonIndex);

void previousTrack();
void playPause();
void nextTrack();
void copy();
void paste();
void cut();

void setup() {
  for (int i = 0; i < NUM_SLIDERS; i++) {
    pinMode(analogInputs[i], INPUT);
  }

  for (int i = 0; i < NUM_BUTTONS; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);
  }

  Serial.begin(9600);
  Keyboard.begin();
}

void loop() {
  updateSliderValues();
  sendSliderValues();

  for (int i = 0; i < NUM_BUTTONS; i++) {
    buttonStates[i] = digitalRead(buttonPins[i]) == LOW;

    if (buttonStates[i] && !lastButtonStates[i]) {
      executeMacro(i);
    }

    lastButtonStates[i] = buttonStates[i];
  }

  delay(10);
}

void updateSliderValues() {
  for (int i = 0; i < NUM_SLIDERS; i++) {
    analogSliderValues[i] = analogRead(analogInputs[i]);
  }
}

void sendSliderValues() {
  String builtString = String("");
  for (int i = 0; i < NUM_SLIDERS; i++) {
    builtString += String(analogSliderValues[i]);
    if (i < NUM_SLIDERS - 1) {
      builtString += "|";
    }
  }
  Serial.println(builtString);
}

void executeMacro(int buttonIndex) {
  switch (buttonIndex) {
    case 0: previousTrack(); break;
    case 1: playPause(); break;
    case 2: nextTrack(); break;
    case 3: copy(); break;
    case 4: paste(); break;
    case 5: cut(); break;
    default: break;
  }
}

void previousTrack() {
  Keyboard.press(KEY_MEDIA_PREVIOUS_TRACK);
  Keyboard.releaseAll();
  Serial.println("Macro: Previous Track");
}

void playPause() {
  Keyboard.press(KEY_MEDIA_PLAY_PAUSE);
  Keyboard.releaseAll();
  Serial.println("Macro: Play/Pause");
}

void nextTrack() {
  Keyboard.press(KEY_MEDIA_NEXT_TRACK);
  Keyboard.releaseAll();
  Serial.println("Macro: Next Track");
}

void copy() {
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press('c');
  Keyboard.releaseAll();
  Serial.println("Macro: Copy");
}

void paste() {
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press('v');
  Keyboard.releaseAll();
  Serial.println("Macro: Paste");
}

void cut() {
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press('x');
  Keyboard.releaseAll();
  Serial.println("Macro: Cut");
}
