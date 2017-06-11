Readme:
Notice, the programming language is python, so we just need to follow the following steps to run the program. we don¡¯t need another makefile for this python file.

Also, the python version in my laptop is 2.7, by running a python application, we can type like this: ¡°python ¡­¡± or ¡°python2.7 ¡­¡± if you not sure your python version, please use ¡°python --version¡±
python 2 and 3 have big difference, please run the application under python 2
I also attach the picture which I generate from the application, it¡¯s name google.jpg

Another, if you input the secret key, for example you get the secret key from google: ¡°bitg g3cc vv5j c2fa czfy l6ks gqit mkct¡±, please remove all the blank space and turn it into ¡°bitgg3ccvv5jc2faczfyl6ksgqitmkct¡±, then use this to do the test.

Install steps:

1. Install python libs
make sure to update your pip tools as the newest version: pip install --upgrade pip
if you don¡¯t have image library, please install it: pip install image
then:
a. Run "pip install qrcode"
b. Run "pip install pyotp"

2. Test generate qrcode
a. Run "python submission.py --generate-qr"
b. Enter your google account
c. Enter your secret key
d. Check the file "google.jpg" in current directory

3. Test get otp
a. Run "python submission.py --get-otp"
b. Enter your google account
c. Enter your secret key
d. Check the 6-digit code

The implement idea:
the programming language is Python. I choose it because it has many libraries, and can easily handle qrcode and otp. First, we need the user have a google account and the security key. Then we can run the application to get a uri, which can help us generate a qrcode. When we use google authenticator to scan the qrcode, the app can recognise the security key in the uri and use otp algorithm to generate a 6 digit token.Because the valid date for generating a token is 30 seconds, so every 30 seconds there will be a new token shows in the command line. 
