# Arduino for PRisme2

![Alt text](http://robopoly.epfl.ch/files/content/sites/robopoly/files/web/prisme/IMG_20120614_183432.jpg)

These files contain the necessary to make the PRisme2, compatible with [Arduino IDE](http://arduino.cc/en/Main/Software).

## Bootloader
The bootloader is an adaptation of [Optiboot](http://code.google.com/p/optiboot/): an STK500 compatible, under 512 bytes bootloader. The adaptation is straight forward only needing minor registry modifications and some new definitions for the ATmega8535. Files for the [modified bootloader](https://github.com/Robopoly/prisme2-bootloader) are available at Github.

## Files
To make a new board compatible with Arduino one must add board definitions in _/hardware/Prisme2/boards.txt_ file, containing  baud speed, fuse bits, microcontroller definition, bootloader...

Other files, such as the compiled bootloader file go inside _/hardware/Prisme2/bootloader/optiboot/_ (it must have the same name as in the _boards.txt_ file).

The most important file is _pins\_arduino.h_ file, located in _/hardware/Prisme2/variants/prisme2/_, which makes the board compatible with Arduino libraries. There are the pin definitions, input and output register addresses, timer addresses...

## Installation
The installation consists of copying the files in the right place, Arduino will check the relevant locations for new board definitions.

On different systems it is done differently: as of Arduino 1.0.1 on Windows one must copy the contents of _/hardware_ and _/libraries_ in the respective folders where the Arduino files were extracted.

On Mac the folders must be copied in the users documents under _/Arduino_ directory, so under _[user]/Documents/Arduino/_.

## Bootloader uploading
To upload the bootloader with Arduino IDE one must use an ISP programmer, choose the correct board in the Tools menu, choose the correct ISP programmer in the same menu and finally click on the _Upload bootloader_ still in the same menu.

## Programming via UART
UART programming can only be done once the bootloader has been uploaded. After writing a program, or selecting one from the examples, one must click on the upload button in the top menu. Arduino will compile the program and will try to upload it, then the user must quickly click the reset button to allow the uploading to start.

More information can be had from [Robopoly's R&D wiki](http://wiki.robopoly.ch/w/Arduino) (in French).
