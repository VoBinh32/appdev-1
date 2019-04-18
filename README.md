Application Development I-IT-1N4
================================
* This project is to run a Raspberry Pi as an audio device. The device is able to do 2 functions: as a sound collector and as a test-tone generator.

## Table of Content
    1. Configuration Instructions
    2. Installation Instructions
    3. Operating Instructions
    4. File list (Manifest)
    5. Copyright / Copyleft
    6. Contact Information
    7. Credits and Acknowledgements

## 1. Configuration Instructions

* The application is running on a Raspberry Pi 3 model B. This Pi should come with a USB sound card, a network connection, a microphone.

1.1. Configure USB sound card as default audio device

* Raspberry Pi onboard sound card doesn’t have microphone interface. We have to change the default audio device to be USB sound card.
* Boot up RPi, and apply the USB sound card. Use “lsusb” command to check if your USB sound card is mounted
* Use “sudo nano /etc/asound.conf” command and put following content to the file:

pcm.!default {
  type plug
  slave {
    pcm "hw:1,0"
  }
}
ctl.!default {
    type hw
    card 1
}

* Go to your home directory. Use _“nano .asoundrc”_ command and put the same content to the file.
* Run “alsamixer” you should be able to see that USB sound card is the default audio device. For a more sensitive sound detection, it is better to maximize the volume of “Mic”.

1.2. Install Libcurl library

* First use command "ls /usr/include/curl" or "ls /usr/include/arm-linux-gnueabihf/curl" to identify that libcurl library is installed.
* If the folder doesn’t exist. Run “sudo apt-get update” to update the application list.
* Run “sudo apt-get install libcurl3” to install the libcurl3.
* Run “sudo apt-get install libcurl4-openssl-dev” to install the development API of libcurl4.

## 2. Installation Instructions

* Clone the project.
* Make.
* Now sound.out should be built in the same folder.

## 3. Operating Instructions

* ./sound.out to without any arguments to generate a decibel barchart of captured sound.
* ./sound.out <sound frequecy>: generate a testTone.wav with specified options.

## 4. File list (Manifest)

* Source: comm.c comm.h main.c makefile screen.c screen.h sound.c sound.h
* Runtime files: test.wav testTone.wav

## 5. Copyright / Copyleft

* This project is licensed under the MIT License.

## 6. Contact Information

* Hai Vu - andreehai1011@gmail.com

## 7. Credits and Acknowledgements

* Thanks Dr. Gao Chao for instructions in making this project.
