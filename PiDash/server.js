const express = require('express');
const http = require('http');
const WebSocket = require('ws');
const path = require('path');
require('dotenv').config();

const app = express();
const server = http.createServer(app);
const wss = new WebSocket.Server({ server });

const COMPANION_APP_IP = process.env.COMPANION_APP_IP;
const COMPANION_APP_PORT = process.env.COMPANION_APP_PORT;
const COMPANION_APP_WS_URL = `ws://${COMPANION_APP_IP}:${COMPANION_APP_PORT}`;

app.use(express.static(path.join(__dirname, 'public')));

app.get('/', (req, res) => {
    res.sendFile(path.join(__dirname, 'public', 'index.html'));
});

wss.on('connection', (ws) => {
    ws.on('message', (message) => {
        console.log(`Received message: ${message}`);
        const companionAppWs = new WebSocket(COMPANION_APP_WS_URL);
        companionAppWs.on('open', () => {
            console.log(`Forwarding message to CompanionApp: ${message}`);
            companionAppWs.send(message);
        });
        companionAppWs.on('error', (error) => {
            console.error(`WebSocket error: ${error.message}`);
        });
    });
});

server.listen(3000, () => {
    console.log('Server is listening on port 3000');
});
