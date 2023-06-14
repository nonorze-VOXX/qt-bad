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
    mores=""
    with open("text.txt","r") as f:
        mores= f.read()

    print("mores!",mores)
    socketio.emit('update', {'led1': "0","sen":"500","mores":mores})
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
        child=pexpect.spawnu(f"sudo python3 run.py {msg}",timeout=3000)
        child.expect('sudo] password for nvidia:')
        child.sendline('nvidia')
        # child.expect('password:')
        # child.sendline('nvidia')
if __name__ == '__main__':
    # light=pexpect.spawnu(f"sudo python3 run.py 1",timeout=3000)
    light=pexpect.spawnu("sudo python3 light_to_morse.py")
    light.expect('[sudo] password for nvidia:')
    light.sendline('nvidia')
    app.run(host='0.0.0.0',port=8000,debug=False)


