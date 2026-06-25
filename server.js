const { SerialPort } = require("serialport");
const { ReadlineParser } = require("@serialport/parser-readline");
const { Server } = require("socket.io");
const http = require("http");
const express = require("express");

const app = express();
const server = http.createServer(app);
const io = new Server(server);

app.use(express.json());

app.get("/", (req, res) => {
    res.sendFile(__dirname + "/views/index.html");
});

io.on("connection", (socket) => {
    console.log("Client connected...");
    socket.on("disconnect", () => {
        console.log("Client disconnected");
    });
});

server.listen(5000, () => {
    console.log("Server running on port 5000!");
});

// Konektifitas Serial Arduino
const port = new SerialPort({
    path: "COM3", // Sesuaikan dengan port Arduino Anda (COM3, COM4, COM5, dst)
    baudRate: 19200,
});

const parser = port.pipe(new ReadlineParser({ delimiter: "\r\n" }));

// 1. TERIMA DATA SERIAL DARI TONGKAT ARDUINO KE WEB DASHBOARD
parser.on("data", (result) => {
    // Bersihkan data dari spasi, enter, atau karakter aneh \r \n
    const cleanData = result.toString().replace(/[\r\n\t]/g, "").trim();
    
    console.log("Data asli dari Arduino -> [", cleanData, "]");

    // VALIDASI KETAT: Cek jika data murni angka 4 tunggal dari tombol fisik tongkat
    if (cleanData === "4") {
        console.log("⚠️ ALARM AKTIF: Mode Tersesat Diaktifkan!");
        io.emit("tersesatAlert", { message: "Mode Tersesat Diaktifkan" });
    } 
    // Cek jika data berupa angka jarak ultrasonik murni yang valid
    else if (cleanData !== "" && !isNaN(cleanData)) {
        io.emit("dataSensor", { data: cleanData });
    } else {
        console.log("Data diabaikan:", cleanData);
    }
});

// 2. PERBAIKAN UTAMA: API Endpoint Menerima Klik Tombol Web Lalu Dikirim ke Kabel Arduino
app.post("/arduinoApi", (req, res) => {
    const data = req.body.data; 

    // Tulis data angka "4" ke kabel USB Arduino
    port.write(data, (err) => {
        if (err) {
            console.log('Error saat menulis data ke Serial Port: ', err);
            return res.status(500).json({ error: "Write data error!" });
        }
        console.log("Tombol Web Diklik -> Sinyal [" + data + "] sukses dikirim ke Arduino via USB!");
        
        // Kirim sinyal lewat Socket.io agar box merah di halaman web langsung muncul
        io.emit("tersesatAlert", { message: "Mode Tersesat Diaktifkan" });
        res.json({ status: "success", message: "Data berhasil diteruskan ke Arduino" });
    });
});