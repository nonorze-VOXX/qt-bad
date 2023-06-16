# import requests
from flask import Flask, request, abort, render_template, jsonify
from flask_socketio import SocketIO, emit
import subprocess
import pexpect
import os
import logging

log = logging.getLogger('werkzeug')
log.setLevel(logging.ERROR)

APP_PATH = ""+os.path.dirname(os.path.abspath(__file__))

app = Flask(__name__)
app.config['SECRET_KEY'] = 'secret!'
socketio = SocketIO(app)
socketio.init_app(app, cors_allowed_origins="*")


@app.route("/")
def home():

    return render_template("final.html", async_mode=socketio.async_mode)
        
    


@app.route("/status")
@socketio.on('status')
def upload(msg):
    # d = request
    # print("receive data:{}".format(d))
    # do something


    # socketio.emit('status_response', {'data': "hi "})
    text="error"
    mores="0"
    value="0"
    led1="0"
    with open("text.txt","r") as f:
        text= f.readline()
        mores= f.readline()
        value= f.readline()
    with open("/sys/class/gpio/gpio466/value","r") as f:
        led1=f.read()


    print("text!",text)
    print("mores!",mores)
    print("value!",value)
    socketio.emit('update', {'led1': led1,"sen":value,"mores":mores,"text":text})
    return jsonify(
        {"response": "ok"}
    )


# mores="sos"
child=""
@app.route("/send")
@socketio.on('send')
def getdata(msg):
    if(isinstance(msg,str)==True):
        print("++++++++++++++++++++")
        global child
        if(child!=""):
            child.close()
        child=pexpect.spawnu(f"sudo python3 run.py /{msg}",timeout=30000)
        #child.expect('sudo] password for nvidia:')
        child.sendline('nvidia')
        # child.expect('password:')
        # child.sendline('nvidia')
if __name__ == '__main__':
    # light=pexpect.spawnu(f"sudo python3 run.py 1",timeout=3000)
    # light=pexpect.spawnu("sudo python3 light_to_morse.py",timeout=30000)
    # light.expect('[sudo] password for nvidia:')
    # light.sendline('nvidia')
    app.run(host='0.0.0.0',port=8000,debug=False)


