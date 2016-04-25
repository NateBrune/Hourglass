# Hourglass
Sumon the power of Chronos to keep your files encrypted for as long as you like. 

![](https://u.pomf.is/asshps.gif "Screencast")

> This project is still under active development
> 
> The algorythm in this software is http://wiki.qt.io/Simple_encryption [!]

### What
---
Hourglass is a program that encrypts files for a predetermined amount of time. When someone wishes to view the contents of the file, they must wait the aformentioned predetermined amount of time before it can be decrypted.

### Why
---
There are a quite a few...

- If someone wanted insurance
- Leave a message for someone to read later
- If you wish for there to be a gap of time between the handoff and reading
- Increase barrier of entry to decrypt data

### How
---
The methodology used in this program has many similarities with bitcoin. 
When you designate a file to be encrypted with Hourglass you also select the designated amount of hashes. This dictates how long the file will need to be kept encrypted for. When you click encrypt the computer hashes the `seed` value the designated amount of times. This is similar to the proof of work algorythm used in bitcoin. After the hashes is done it encrypts the file with the truncated hash and the Qt Simple Encryption algorythm.

### Contact
--- 
[natebrune@gmail.com](mailto:natebrune@gmail.com)  
https://keybase.io/natebrune
