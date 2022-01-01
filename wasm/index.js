var canvas = document.getElementById("canvas");
var ctx = canvas.getContext("2d");
let CELL_SIZE = 20;

let move = 0;
let rotate = 0;
let down = 0;

function sleep(time) {
    return new Promise((resolve) => setTimeout(resolve, time));
}

function keyDown(event) {
    var key = event.key;
    if (key == "ArrowRight") {
        move = 1;
    }
    if (key == "ArrowLeft") {
        move = -1;
    }
    if (key == "ArrowUp") {
        rotate = 1;
    }
    if (key == "ArrowDown") {
        down = 1;
    }
}

function drawCell(ctx, col, row, rgb) {
    ctx.fillStyle = "#FFFFFF";
    ctx.fillRect(col * CELL_SIZE, row * CELL_SIZE, CELL_SIZE, CELL_SIZE)
    ctx.stroke();
    ctx.fillStyle = "#" + rgb;
    ctx.fillRect(col * CELL_SIZE + 1, row * CELL_SIZE + 1, CELL_SIZE - 2, CELL_SIZE - 2)
    ctx.stroke();
}

function draw(array) {
    ctx.beginPath();

    ctx.fillStyle = "#FFFFFF";
    ctx.fillRect(0, 0, 400, 400);
    ctx.stroke();
    ctx.fillStyle = "#000000";
    ctx.fillRect(2, 2, 396, 396);
    ctx.stroke();

    for (let row = 0; row < 40; row++) {
        for (let col = 0; col < 10; col++) {
            let idx = row * 10 + col;
            if (array[idx] > 0) {
                let rgb = array[idx].toString(16).toUpperCase();
                rgb = rgb.padStart(8 - rgb.length, '0');
                drawCell(ctx, col, row, rgb);
                console.log(rgb);
            }
        }
    }
    ctx.stroke();
}

(async () => {
    const prog = await WebAssembly.instantiateStreaming(fetch('tetris.wasm'), {});

    var time = +Date.now();
    prog.instance.exports.initGame(time);
    for (let i = 0; i < 10000; i++) {

        time = +Date.now();
        let ptr = prog.instance.exports.updateGame(time, move, down, rotate);
        const array = new Int32Array(prog.instance.exports.memory.buffer, ptr, 400);

        draw(array);
        move = 0;
        rotate = 0;
        down = 0;


        await sleep(50);
        console.log(i);

    }
})();