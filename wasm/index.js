var canvas = document.getElementById("canvas");
var ctx = canvas.getContext("2d");
let CELL_SIZE = 10;

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

function draw(array) {
    ctx.beginPath();

    ctx.fillStyle = "#000000";
    ctx.fillRect(0, 0, 400, 400);
    ctx.stroke();

    for (let row = 0; row < 40; row++) {
        for (let col = 0; col < 10; col++) {
            let idx = row * 10 + col;
            ctx.fillStyle = "#FF0000";
            if (array[idx] > 0) {
                ctx.fillRect(col * CELL_SIZE, row * CELL_SIZE, CELL_SIZE, CELL_SIZE)
            }
        }
    }
    ctx.stroke();
}

(async () => {
    const prog = await WebAssembly.instantiateStreaming(fetch('tetris.wasm'), {});


    prog.instance.exports.initGame();
    for (let i = 0; i < 100; i++) {


        if(move != 0 || rotate == 1 || down == 1)
        {
            prog.instance.exports.moveCurrentBlock(move, down, rotate);
            move = 0;
            rotate = 0;
            down = 0;
        }
        let row = prog.instance.exports.updateGame();
        let ptr = prog.instance.exports.getGame();
        const array = new Int32Array(prog.instance.exports.memory.buffer, ptr, 400);

        draw(array);

        await sleep(100);
        console.log(i);

    }
})();