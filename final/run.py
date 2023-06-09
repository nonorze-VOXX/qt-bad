import time
import sys

def text_to_morse(text):
    MORSE_CODE_DICT = { 'A':'.-', 'B':'-...',
                    'C':'-.-.', 'D':'-..', 'E':'.',
                    'F':'..-.', 'G':'--.', 'H':'....',
                    'I':'..', 'J':'.---', 'K':'-.-',
                    'L':'.-..', 'M':'--', 'N':'-.',
                    'O':'---', 'P':'.--.', 'Q':'--.-',
                    'R':'.-.', 'S':'...', 'T':'-',
                    'U':'..-', 'V':'...-', 'W':'.--',
                    'X':'-..-', 'Y':'-.--', 'Z':'--..',
                    'a':'.-', 'b':'-...',
                    'c':'-.-.', 'd':'-..', 'e':'.',
                    'f':'..-.', 'g':'--.', 'h':'....',
                    'i':'..', 'j':'.---', 'k':'-.-',
                    'l':'.-..', 'm':'--', 'n':'-.',
                    'o':'---', 'p':'.--.', 'q':'--.-',
                    'r':'.-.', 's':'...', 't':'-',
                    'u':'..-', 'v':'...-', 'w':'.--',
                    'x':'-..-', 'y':'-.--', 'z':'--..',
                    '1':'.----', '2':'..---', '3':'...--',
                    '4':'....-', '5':'.....', '6':'-....',
                    '7':'--...', '8':'---..', '9':'----.',
                    '0':'-----', ', ':'--..--', '.':'.-.-.-',
                    '?':'..--..', '/':'-..-.', '-':'-....-',
                    '(':'-.--.', ')':'-.--.-'}
    morse = ""
    for t in text:
            morse += MORSE_CODE_DICT[t]
            morse += " "
    print(morse)
    return morse

def pass_morse(morse):
    led_code = "466"
    status = "0"
    path = "/dev/lab6-2"
    # path = "tmp.txt"
    print(morse)
    
    for m in morse:
        if m == '.':
            with open(path, 'w') as f:
                f.write(led_code + " " + "1")
            time.sleep(0.3)
            with open(path, 'w') as f:
                f.write(led_code + " " + "0")
        if m == '-':
            with open(path, 'w') as f:
                f.write(led_code + " " + "1")
            time.sleep(1)
            with open(path, 'w') as f:
                f.write(led_code + " " + "0")
        if m == ' ':
            time.sleep(1)
        time.sleep(0.3)
        
if __name__=="__main__":
    arg=sys.argv[1:]
    morse = text_to_morse(arg[0])
    pass_morse(morse)