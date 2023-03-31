// import express from 'express';
// import fs from 'fs';


const { exec } = require('child_process');
const express = require('express')
const formidable = require('formidable')
const fs = require('fs')
const JSON = require('JSON')

let app = express();
app.get('/', function (req, res) {

    //post data 
    var add_data = req.body
    console.log("1")
    // data = JSON.parse(data)
    // res.end("")
    // res.sendFile("/home/nvidia/code/lab4/lab4.html");
    res.sendFile("/home/lag/code/micro-computer/lab4/lab4.html");


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
            if (data['led' + i] == 'on') {
                exec("./onoff.out LED" + i + " " + onoff)
                poutput += "./onoff.out LED" + i + " " + onoff + "<br>";
            }
        }
        res.end("i have " + JSON.stringify(poutput))
    })
});
app.post('/times', function (req, res) {
    const form = new formidable.IncomingForm();
    form.parse(req, function (err, fields, files) {
        let initLedstate = [1, 1, 0, 0];
        let ledstate = [1, 1, 0, 0];
        let counter = 0;
        let times = 0;

        function myAlert() {
            counter += 1;
            if (counter > times) {
                setTimeout();
            }
            for (let i = 0; i < 4; i++) {
                if (ledstate == 1) {
                    exec("./onoff.out LED" + i + " on");
                } else {
                    exec("./onoff.out LED" + i + " off");
                }
                ledstate[i] = 1 - ledstate[i];
            }
        }
        if (err) {
        }
        times = fields['times'];
        counter = 0;
        ledstate = initLedstate
        var timeoutID = setTimeout(myAlert, 1000);
    })
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
