import time

import Jetson.GPIO as GPIO

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

def main():
    thresh = 300
    is_light = False 
    counter = 0
    long_signal_thresh = 5
    result = ""
    init()
    while True:
        adc_value = readadc(photo_ch, SPICLK, SPIMOSI, SPIMISO, SPICS)
        print(adc_value)
        if (adc_value > thresh):
            is_light = True
        else:
            is_light = False

        if (is_light == True):
            counter += 1
        else:
            if counter > long_signal_thresh:
                result += "1"
            elif counter > 0:
                result += "0"
            counter = 0
        time.sleep(0.5)


if __name__ == '__main__':
    try:
        main()
    except:
        pass
