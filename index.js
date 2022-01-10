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
    ctx.fillStyle = "#" + rgb;
    ctx.fillRect(col * CELL_SIZE + 1, row * CELL_SIZE + 1, CELL_SIZE - 2, CELL_SIZE - 2)
    ctx.stroke();
}

function draw(array, queue) {
    ctx.beginPath();

    ctx.fillStyle = "#FFFFFF";
    ctx.fillRect(0, 0, 280, 400);
    ctx.stroke();
    ctx.fillStyle = "#000000";
    ctx.fillRect(1, 1, 278, 398);
    ctx.stroke();

    for (let row = 4; row < 24; row++) {
        for (let col = 0; col < 10; col++) {
            let idx = row * 10 + col;
            if (array[idx] > 0) {
                let rgb = array[idx].toString(16).toUpperCase();
                rgb = rgb.padStart(6, '0');
                drawCell(ctx, col, row - 4, rgb);
            }
        }
    }


    ctx.fillStyle = "#FFFFFF";
    ctx.fillRect(10*CELL_SIZE, 0, 1, 400);
    ctx.stroke();

    for (let row = 0; row < 20; row++) {
        for (let col = 0; col < 3; col++) {
            let idx = row * 10 + col;
            if (queue[idx] > 0) {
                let rgb = queue[idx].toString(16).toUpperCase();
                rgb = rgb.padStart(6, '0');
                drawCell(ctx, col+10, row, rgb);
            }
        }
    }
    ctx.stroke();
}


function setScore(score) {
    document.getElementById("score").innerText = "Rows Cleared: " + score;
}

async function run() {
    const prog = await WebAssembly.instantiateStreaming(fetch('tetris.wasm'), {});

    var time = +Date.now();
    prog.instance.exports.initGame(time);
    while (true) {
        time = +Date.now();
        let ptr = prog.instance.exports.updateGame(time, move, down, rotate);
        let scorePtr = prog.instance.exports.getScore();
        let queuePtr = prog.instance.exports.getQueue();

        const scoreArr = new Int32Array(prog.instance.exports.memory.buffer, scorePtr, 3);
        const queueArr = new Int32Array(prog.instance.exports.memory.buffer, queuePtr, 240);
        let gameOver = scoreArr[2];
        if (gameOver == 1) {
            setScore("GAME OVER");
        }
        else {
            setScore(scoreArr[0]);
        }


        const array = new Int32Array(prog.instance.exports.memory.buffer, ptr, 240);

        draw(array, queueArr);
        move = 0;
        rotate = 0;
        down = 0;

        await sleep(50);
    }
};
run();