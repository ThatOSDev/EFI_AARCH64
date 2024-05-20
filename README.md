# Demo Code of booting ARM64 (AARCH64) with EFI  
  
# BIG THANK YOU TO THE FOLLOWING PEOPLE WHO HELPED ME TO MAKE THIS OS POSSIBLE
	- ANGEL  
	- QUESO  
	- JESTERJUNK  
	- STRYKER  
	- AND ALL OF MY YOUTUBE SUBSCRIBERS  
  
*NOTE* : This code will compile with CLANG on windows. No other dependancies needed. Currently, there is no way to compile this code with GCC. The GCC Team does have it planned this year to allow compiling for ARM64 for windows users. They are just slow about getting it done.  
  
*CLANG*  --  Get the 18.1.5 version  
https://github.com/llvm/llvm-project/releases  
NOTE :  It's the latest one with the EXE for windows at the time of writing this.  
  
*OSFMount*  -- To mount the drive.hdd file  
https://www.osforensics.com/tools/mount-disk-images.html  
  
*QEMU* -- Has an ARM64(AARCH64) Emulation built in. 
https://www.qemu.org/  
 
*BIOS FOR QEMU*   
The included "RELEASEAARCH64_QEMU_EFI.fd" file is like my BIOS64.BIN file in videos. These are used for QEMU to load EFI only. No other reason to need these files otherwise. If you ever need to update this file, you can get the QEMU BIOS-like files here. Rename them to BIOS^$.BIN if you want, like I did in my original videos. But make sure the BAT file has the correct name.  
https://github.com/retrage/edk2-nightly  
  

