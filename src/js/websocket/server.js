const express = require('express');
const app = express();
const server = app.listen(4434);
app.use(express.static('public'));

const socket = require('socket.io');
const io = socket(server);

io.sockets.on('connection', newConnection);

function newConnection(socket) {
    console.log(socket.id);

    socket.on('mouse', onMouseMessage);

    function onMouseMessage(data) {
        console.log(data);
        socket.broadcast.emit('mouse', data);
    }
}