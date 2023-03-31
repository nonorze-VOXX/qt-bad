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

    // data = JSON.parse(data)
    console.log("1")
    // res.end("")
    res.sendFile("/home/lag/code/micro-computer/lab4/lab4.html");


});
let data = { "ON": "", "OFF": "" };
app.post('/led', function (req, res) {
    const form = new formidable.IncomingForm();
    form.parse(req, function (err, fields, files) {
        if (err) {
        }
        data['ON'] = fields['ON'];
        data['OFF'] = fields['OFF'];
        data['led1'] = fields['led1']
        data['led2'] = fields['led2']
        data['led3'] = fields['led3']
        data['led4'] = fields['led4']

        if (fields['led4'] == 'on') {
            exec("./onoff.out LED4 " + fields['led4'])
        } else {
            exec("./onoff.out LED4 off")

        }

        res.end("i have " + JSON.stringify(data))
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
