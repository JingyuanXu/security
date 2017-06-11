import qrcode
import sys
import pyotp
import time


def gen_uri(account, key):
    uri = 'otpauth://totp/' + str(account) + '?secret=' + str(key)
    return uri

def print_usage():
    print('USAGE OF GENERATE QRCODE: python submission.py --generate-qr')
    print('USAGE OF GET OTP: python submission.py --get-otp')

def get_account():
    account = raw_input('Enter google account: ')
    return account

def get_key():
    key = raw_input('Enter google secret key: ')
    return key

if __name__ == '__main__':
    if len(sys.argv) != 2:
        print_usage()
        sys.exit(1)
    option = sys.argv[1]
    if option == '--generate-qr':
        account = get_account()
        key = get_key()
        uri = gen_uri(account, key)
        img = qrcode.make(uri)
        img.save('google.jpg')
        sys.exit(0)
    elif option == '--get-otp':
        account = get_account()
        key = get_key()
        totp = pyotp.TOTP(key)
        while True:
            print(totp.now())
            time.sleep(30)
        sys.exit(0)
    print_usage()
    sys.exit(1)
