// import express from 'express';
// import fs from 'fs';


const { exec } = require('child_process');
const express = require('express')
const formidable = require('formidable')
const fs = require('fs')
const JSON = require('JSON')

// const path="/home/nvidia/code/qt-bad/"
const path="/home/green-rider/code/university/qt-bad/"
let app = express();
app.get('/', function (req, res) {

    //post data 
    var add_data = req.body
    console.log("1")
    // data = JSON.parse(data)
    // res.end("")
    res.sendFile(path+"lab4.html");
    // res.sendFile("/home/lag/code/micro-computer/lab4/lab4.html");


});
let data = { "ON": "", "OFF": "" };
let poutput = "";

app.post('/led', function (req, res) {
    const form = new formidable.IncomingForm();
    form.parse(req, function (err, fields, files) {
        if (err) {
        }
        let onoff = '';
        data['ON'] = fields['ON'];
        data['OFF'] = fields['OFF'];
        if (data['ON']) {
            onoff = 'on';
        } else if (data['OFF']) {
            onoff = 'off';

        }
        data['led1'] = fields['led1']
        data['led2'] = fields['led2']
        data['led3'] = fields['led3']
        data['led4'] = fields['led4']
        for (let i = 0; i < 4; i++) {
            if (data['led' + (i + 1)] == 'on') {
                exec("./onoff.out LED" + (i + 1) + " " + onoff)
                console.log(i + onoff)
                poutput += "./onoff.out LED" + (i + 1) + " " + onoff + "<br>";
            }
        }
        res.sendFile(path+"lab4.html");
        // res.sendFile("/home/lag/code/micro-computer/lab4/lab4.html")
    })
});

let initLedstate = [1, 1, 0, 0];
let ledstate = [1, 1, 0, 0];
let counter = 0;
let times = 0;
let timeoutID = '';

function myAlert() {
    counter += 1;
    if (counter > times) {
        return 0;
    }
    console.log(ledstate)
    for (let i = 0; i < 4; i++) {
        if (ledstate[i] == 1) {
            console.log(i + 'on')
            exec("./onoff.out LED" + (i + 1) + " on");
        } else {
            console.log(i + 'off')
            exec("./onoff.out LED" + (i + 1) + " off");
        }
        ledstate[i] = 1 - ledstate[i];
    }
    setTimeout(myAlert, 1000);
}
app.post('/times', function (req, res) {
    const form = new formidable.IncomingForm();
    form.parse(req, function (err, fields, files) {
        if (err) {
        }
        times = fields['times'] * 2;
        counter = 0;
        ledstate = initLedstate
        timeoutID = setTimeout(myAlert, 1000);

        res.sendFile(path+"lab4.html");
        // res.sendFile("/home/lag/code/micro-computer/lab4/lab4.html")
    })
});
app.get('/lightSense', function (req, res) {
    var exec = require('child_process').exec;
    // function execute(command, callback){
    var output ="";
    // exec("python lab5.py", function(error, stdout, stderr){ 
    //     console.log(stdout);
    //     output = stdout;
    // });
    // };
    // console.log("13")
    // res.end(output)
    res.end("123")
});
app.listen(8000)
// function writeFile() {
//     fs.writeFile('TestFile.txt', function (err, data) {
//         if (err) throw err;

//         console.log(data.toString());
//     });

// }
// function ledSwitch() {
//     let exp = 0;


// }
