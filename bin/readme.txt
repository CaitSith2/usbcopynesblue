USBCopyNESBlue v5.0.4
Released by Brad Smith, ?????

This is a fork of the USBCopyNES client originally released by
Brian Parker (RetroUSB). This was in turn based on CopyNESW by
Quietust, which was in turn based on CopyNES by Kevin Horton.

http://www.retrousb.com/product_info.php?products_id=36
http://www.qmtpro.com/~nes/copynes/
http://kevtris.org/Projects/copynes/index.html

This project is publicly maintained on Google Code. The latest version,
as well as source code is available at:

http://code.google.com/p/usbcopynesblue/


Known Bugs:

 - CopyNES BIOS 4 NSF player copies song number into X and Y registers,
   causing dual NTSC/PAL NSFs to play at incorrect speed.


Changes:

v5.0.4 - ?????
 - Glider cart now usable as an NSF cart.
 - Parallel port support added. (there may still be bugs with that.)
 - Mapper.dat format updated. (Now easier to add a plugin.)

v5.0.3 - 4/30/2013
 - Fixed bugs with Glider flasher
 - Created RET-CUFROM plugin (dumps Glider)

v5.0.2 - 4/29/2013
 - Lots of bug fixes
 - Added NES 2.0 support
 - Updated U5ROM plugin to handle carts that do more than oversized UxROM, like flash saving, etc... (Mapper 30
 - Added UNROM-512 flasher unde RAM-Cart
 - Created NSF log player (created with NSFPlay)

v5.0.1 - 5/10/2013
 - NSF player now works with common RAM carts. (Cancel RAM cart plugin dialog for old NSF cart behaviour.)
 - RAM cart code refactoring to allow use with other program functions.
 - Created U5ROM oversized UxROM plugin.
 - Fixed misnamed MMC6 WRAM writer in MAPPERS.DAT
 - New, more accurate set of VRC7 patches.
 - Fixed VRC7 patch tuner stop button (now releases note).
 - Fixed VRC7 patch tuner bug with saving patches.
 - Added VRC7 patch tuner keyboard function Q/W/E for Custom/Builtin/Stop.
 
v5.0.0 - 7/24/2012
 - Fixed bug in PowerPak Lite mapper selection.
 - Fixed bug in serial device initialization, now works on Windows 7.
 - Replaced C++ code in C files with valid C code.
 - Various source cleanup.
 