<!-- <svelte:window on:load={onload} on:unload={onunload} /> -->

<script lang="ts">
	import { browser } from '$app/environment';
	import { goto } from '$app/navigation';
	import {
		client,
		connectClientToColyseus,
		joinGame,
		roomData,
		resetroomData
	} from '$lib/gamesocket.js';
	import { socket } from '$lib/socketsbs.js';
	import { onDestroy, onMount } from 'svelte';
	import { game_mode, userId } from '$lib/stores';

	export let data;

	/**
	 * GameStates
	 */
	let name: any;
	let input: string;
	let initialScreen: any;
	let canvas: any;
	let ctx: any;
	let game: any;
	let pong: any;
	let room: any;
	let matchroom: any;
	let gameActive: boolean = false;
	let promise: any;
	let gameCode: any;
	let playerNumber: number;
	let gameResult: string = '';
	let leaved: boolean = false;
	let changecolor: boolean = false;
	let quitGame = () => {
		goto('/app/game');
	};

	// let onload = async () =>
	onMount(async () => {
		// window.onbeforeunload = function() {
		//     console.log('reload')
		//     goto("/");
		// }
		
		if (!roomData) {
			// si
			//connectClientToColyseus();
			await joinGame(data.gameId); // join room permet de
			playerNumber = 2;
		} else playerNumber = 1;

		if (!roomData)
		{
			goto('/app/game');
		}
		// if (roomData)
		// {
		//     roomData.onMessage("init", (j: number) => {
		//         playerNumber = j;
		//         console.log(playerNumber);
		//         //console.log('test init22! ' + name + ' ' + roomData.id);
		//         //console.log("client id: " + client.id);
		//         console.log('init');
		//     });

		// }
		// roomData.onMessage("quitGame", quitGame);
		if (socket) {
			socket.emit('startGame');
			socket.on('refused', quitGame);
		}
		try {
			init();
			createHandlers();
		} catch (error) {
			goto('/app/game');
		}
	});

	// let onunload = () =>
	onDestroy(() => {
		if (browser) {
			document.removeEventListener('keyup', keyup);
			document.removeEventListener('keydown', keydown);
		}
		if (socket) {
			socket.emit('endGame');
		}
		resetroomData();
		// client.close();
	});

	function drawMessage(message: string) {
		if (browser) {
			const canvas = document.getElementById('pong') as HTMLCanvasElement;
			const ctx = canvas?.getContext('2d');
			if (ctx) {
				ctx.clearRect(0, 0, canvas.width, canvas.height);
				ctx.font = '48px Arial';
				ctx.fillStyle = 'black';
				ctx.textAlign = 'center';
				ctx.fillText(message ?? '', canvas.width / 2, canvas.height / 2);
			}
		}
	}

	let createHandlers = () => {
		roomData.onMessage('disconnect', quitGame);
		roomData.onMessage('init', (j: number) => {
			// Handle 'init' message here
			init();
		});
		roomData.onMessage('gameState', (gameState: any) => {
			gameState = JSON.parse(gameState);
			requestAnimationFrame(() => trender(gameState));
		});
		roomData.onMessage('gameOver', (data: any) => {
			if (browser) {
				document.removeEventListener('keyup', keyup);
				document.removeEventListener('keydown', keydown);
			}
			if (socket) {
				socket.emit('endGame');
			}
			let date = JSON.parse(data);
			if (date.winner === playerNumber) {
				drawMessage('GG Winner ');
				resetroomData();
				//quitGame();
			} else {
				drawMessage('You loooser');
				resetroomData();
				//quitGame();
			}
		});
	};

	function init() {
		//initialScreen.style.display = "none";
		//game.style.display = "block";
		canvas = pong;
		// const { width, height } = canvas.getBoundingClientRect();
		// canvas.width = width;
		// canvas.height = height;
		// console.log(canvas.width);
		// console.log(canvas.height);
		ctx = canvas.getContext('2d');
		// gameCode = document.getElementById('gameCode');
		// gameCode.innerText = name;
		gameActive = true;
		// console.log(gameCode);
		gameResult = '';
		if (browser) {
			document.addEventListener('keydown', keydown);
			document.addEventListener('keyup', keyup);
		}
		//gameActive = true;
	}

	function keydown(e: any) {
		if (e.keyCode === 38) {
			if (playerNumber == 1) roomData.send('keydown38player1');
			else roomData.send('keydown38player2');
		}
		if (e.keyCode === 40) {
			if (playerNumber == 1) roomData.send('keydown40player1');
			else roomData.send('keydown40player2');
		}
	}

	function keyup(e: any) {
		if (e.keyCode === 38) {
			if (playerNumber == 1) roomData.send('keyup38player1');
			else roomData.send('keyup38player2');
		}
		if (e.keyCode === 40) {
			if (playerNumber == 1) roomData.send('keyup40player1');
			else roomData.send('keyup40player2');
		}
	}
	/**
	 *
	 * GAME RENDER
	 *
	 */

	function drawRect(x: number, y: number, w: number, h: number, color: any) {
		if (ctx) {
			ctx.fillStyle = color;
			ctx.fillRect(x, y, w, h);
		}
	}

	function drawArc(x: number, y: number, r: number, color: any) {
		if (ctx) {
			ctx.fillStyle = color;
			ctx.beginPath();
			ctx.arc(x, y, r, 0, Math.PI * 2, true);
			ctx.closePath();
			ctx.fill();
		}
	}

	function drawNet(statenet: any, color: any) {
		for (let i = 0; i <= canvas.height; i += 15) {
			//        drawRect(statenet.net.x, statenet.net.y + i, statenet.net.width, statenet.net.height, statenet.net.color);
			drawRect(statenet.net.x, statenet.net.y + i, statenet.net.width, statenet.net.height, color);
		}
	}

	function drawText(text: string, x: number, y: number, color: any) {
		if (ctx) {
			//ctx.fillStyle = "#FFF";
			ctx.fillStyle = color;
			ctx.font = '75px fantasy';
			ctx.fillText(text, x, y);
		}
	}

	function trender(state: any) {
		if (changecolor === false) drawRect(0, 0, canvas.width, canvas.height, '#000');
		else drawRect(0, 0, canvas.width, canvas.height, '#FFF');

		drawText(state.user.score, canvas.width / 4, canvas.height / 5, '#FF0000');

		drawText(state.com.score, (3 * canvas.width) / 4, canvas.height / 5, '#FF0000');
		if (changecolor === false) drawNet(state, '#FFF');
		else drawNet(state, '#000');

		if (changecolor === false)
			drawRect(state.user.x, state.user.y, state.user.width, state.user.height, '#FFF');
		else drawRect(state.user.x, state.user.y, state.user.width, state.user.height, '#000');

		if (changecolor === false)
			drawRect(state.com.x, state.com.y, state.com.width, state.com.height, '#FFF');
		else drawRect(state.com.x, state.com.y, state.com.width, state.com.height, '#000');

		if (changecolor === false) drawArc(state.ball.x, state.ball.y, state.ball.radius, '#FFF');
		else drawArc(state.ball.x, state.ball.y, state.ball.radius, '#000');
	}

	//------------------------------------------------------------------------------------------------
</script>

<!-- <p>{data.gameId} $$$ {playerNumber}</p> -->
<canvas bind:this={pong} id="pong" width="600" height="400" />

<style>
	/* #pong {
        border: 2px solid #FFF;
        position: relative;
        margin: auto;
        top: 0;
        right: 0;
        left: 0;
        bottom: 0;
    } */

	#pong {
		border: 2px solid rgb(32, 31, 31);
		position: relative;
		margin: auto;
		/* top: 0;
        right: 0;
        left: 0;
        bottom: 0; */
		display: flex;
		justify-content: center;
		align-items: center;
	}
</style>
