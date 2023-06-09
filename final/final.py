# import requests
from flask import Flask, request, abort, render_template, jsonify
from flask_socketio import SocketIO, emit
import subprocess
import pexpect

import os
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
@app.route("/send")
@socketio.on('send')
def getdata(msg):
    if(msg==)
    socketio.emit('update', {'led1': "0","sen":"500","mores":"hi"})
    tm=[i for i in range(10000)]
    pass
    # print("#",msg)

if __name__ == '__main__':
    # os.system("some_command &")
    # os.system( 'python light_to_morse.py')
    # subprocess.Popen(["python3","light_to_morse.py"])
    # subprocess.run("python light_to_morse.py", shell=False, check=True)
    pexpect.spawnu("python3 light_to_morse.py")
    app.run(host='0.0.0.0',port=8000)


