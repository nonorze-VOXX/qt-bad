import time

import send_email
import Jetson.GPIO as GPIO
from multiprocessing import Process, Value
from ctypes import c_char_p

# change these as desired - they're the pins connected from the
# SPI port on the ADC to the Cobbler


def init():
    # GPI0. BOARD
    GPIO.setmode(GPIO.BOARD)
    GPIO.setup(output_pin, GPIO.OUT, initial=GPIO.HIGH)
    GPIO.setwarnings(False)
    GPIO.cleanup()
    GPIO.setmode(GPIO.BCM)
    # set up the SPI interface pins
    GPIO.setup(SPIMOSI, GPIO.OUT)
    GPIO.setup(SPIMISO, GPIO.IN)
    GPIO.setup(SPICLK, GPIO.OUT)
    GPIO.setup(SPICS, GPIO.OUT)
    # GPIO.setup(led1_code, GPIO.OUT)
    # GPIO.setup(led2_code, GPIO.OUT)
    # GPIO.output(led1_code, 0)
    # GPIO.output(led2_code, 0)


def readadc(adcnum, clockpin, mosipin, misopin, cspin):
    if (adcnum > 7) or (adcnum < 0):
        return -1
    GPIO. output(cspin, True)

    GPIO.output(clockpin, False)  # start clock low
    GPIO.output(cspin, False)  # bring CS low

    commandout = adcnum
    commandout |= 0x18  # start bit + single-ended bit
    commandout <<= 3  # we only need to send 5 bits here
    for i in range(5):
        if (commandout & 0x80):
            GPIO.output(mosipin, True)
        else:
            GPIO.output(mosipin, False)
        commandout <<= 1
        GPIO.output(clockpin, True)
        GPIO.output(clockpin, False)

    adcout = 0
    # read in one empty bit, one null bit and 10 ADC bits
    for i in range(12):
        GPIO.output(clockpin, True)
        GPIO.output(clockpin, False)
        adcout <<= 1
        if (GPIO.input(misopin)):
            adcout |= 0x1

    GPIO.output(cspin, True)

    adcout >>= 1
    return adcout


SPICLK = 11
SPIMISO = 9
SPIMOSI = 10
SPICS = 8

output_pin = 7

# led1_thresh = 300
# led2_thresh = 600
# led1_code = 4
# led2_code = 17

# photoresistor connected to adc #0

photo_ch = 0

def decode(result):
    MORSE_CODE_DICT = { 'A':'.-', 'B':'-...',
	'C':'-.-.', 'D':'-..', 'E':'.',
	'F':'..-.', 'G':'--.', 'H':'....',
	'I':'..', 'J':'.---', 'K':'-.-',
	'L':'.-..', 'M':'--', 'N':'-.',
	'O':'---', 'P':'.--.', 'Q':'--.-',
	'R':'.-.', 'S':'...', 'T':'-',
	'U':'..-', 'V':'...-', 'W':'.--',
	'X':'-..-', 'Y':'-.--', 'Z':'--..',
	'1':'.----', '2':'..---', '3':'...--',
	'4':'....-', '5':'.....', '6':'-....',
	'7':'--...', '8':'---..', '9':'----.',
	'0':'-----', ', ':'--..--', '.':'.-.-.-',
	'?':'..--..', '/':'-..-.', '-':'-....-',
	'(':'-.--.', ')':'-.--.-'}
    
    text = ""
    for k, v in MORSE_CODE_DICT.items():
        if result == v:
                text = k
    return text
    
def test():
    code = "... --- ..."
    result = decode(code)
    print(result)


def main():
    thresh = 400
    is_light = False 
    pre_light = False
    counter = 0
    now_time = 0
    result = ""
    text = ""
    start_flag = False
    long_signal_thresh = 0.7
    init()

    print("start")
    base_time = time.time()
    while True:
        adc_value = readadc(photo_ch, SPICLK, SPIMOSI, SPIMISO, SPICS)
        print(adc_value)
        if (adc_value > thresh):
            is_light = True
        else:
            is_light = False

        now_time = time.time()
        if(now_time-base_time>60):
            text=""
            result = ""
        elif(now_time-base_time>5):
            text += decode(result)
            result = ""
            with open("./score") as file:
                score=file.read()
                if(int(score)>30):
                    mailtext="score: "+score
                    print(score)
                    send_email.sendMail(text+'\n'+mailtext)
                    # exit(1)

        if pre_light != is_light:  # light switch            
            # now_time = time.time()
            bias = now_time - base_time
            # print("bias " , bias)
            if bias > long_signal_thresh:
                if is_light == False:
                    text += decode(result)
                    print(text)
                    result = ""
                elif is_light == True:
                    result += "-"
            elif bias > 0:
                if is_light == True:
                    result += "."

            pre_light = is_light
            base_time = time.time()
        #result = decode(result)
        print(result)
        print(text)
        with open('text.txt', 'w') as f:
            f.write(text)
        with open('morse-code.txt', 'w') as f:
            f.write(result)
        time.sleep(0.03)


if __name__ == '__main__':
    try:
        main()
    except:
        pass
