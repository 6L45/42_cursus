<script lang="ts">
	import { browser } from '$app/environment';
	import { goto } from '$app/navigation';
	import { game_mode } from '$lib/stores';
	import { Client } from 'colyseus.js';
	// import { client, connectClientToGame } from '$lib/gamesocket'
	// import { onDistroy } from 'svelte';
	import { onDestroy, onMount } from 'svelte';

	let matches: any;
	//let width: any;
	//let height: any;
	let client: any;
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
	let changecolor: boolean = false;
	let gameOver = false;
	let gameResult: string = '';
	let leaved: boolean = false;

	if (browser) {
		client = new Client('ws://' + location.hostname + ':3001/ws');
	}

	// onMount(() => {
	// 	console.log("matc unde "	+ matchroom)
	// 	console.log("client id: " + client.id);

	// });

	// if (browser){
	// }

	// onDistroy(() => { // this will be called when the component is destroyed
	// 	room?.leave(); // leave the room when the component is destroyed
	// 	matchroom?.leave(); // leave the room when the component is destroyed
	// });
	async function leaveGame(room: any) {
		try {
			await room.leave();
			// console.log("Client left the room");
			// Effectuez d'autres actions après la déconnexion du client
		} catch (e) {
			console.error(e);
		}
	}

	onDestroy(() => {
		if (matchroom) {
			// deconnecter clent
			leaveGame(matchroom);
			//console.log("destroy match " + matchroom?.id + matchroom?.sessionId)
			//matchroom?.leave();
			//location.reload();
			leaved = true;
		}
	});

	// if(gameActive)
	// {
	// 	console.log("destroy " + gameActive);
	// // if (client && client.connection && client.connection.readyState === WebSocket.OPEN) {
	//  	// room?.onLeave();
	// 	// matchroom?.onleave();
	// 	//gameActive = false;
	// 	resetroomData();
	// 	console.log("destroy " + gameActive);
	//  }

	// });

	async function createGame() {
		try {
			// console.log(localstorage);
			if (browser) {
				const localstorage = localStorage.getItem('userId');
				room = await client?.joinOrCreate('my_room', { id: localstorage, roomName: 'my_room' }); // this will create "my_room" if it doesn't exist already or join it if it does exist
			}
			name = room.id;
			return room.id;
		} catch (e) {
			console.error(e);
		}
	}

	const handleCreateGame = () => {
		promise = createGame();
	};

	async function joinGame() {
		try {
			if (browser) {
				const localstorage = localStorage.getItem('userId');
				// input = (<HTMLInputElement>document.getElementById('gameCodeInput')).value;
				room = await client?.joinById(input, { id: localstorage, roomName: 'my_room' });
			}
		} catch (e) {
			console.error(e);
		}
	}

	const handleJoinGame = () => {
		promise = joinGame();
	};

	function init() {
		initialScreen.style.display = 'none';
		game.style.display = 'block';
		canvas = document.getElementById('pong');
		const { width, height } = canvas.getBoundingClientRect();
		canvas.width = width;
		canvas.height = height;
		ctx = canvas.getContext('2d');
		gameCode = document.getElementById('gameCode');
		if (gameCode) {
			gameCode.innerText = name;
		}
		gameResult = '';
		gameActive = true;
		document.addEventListener('keydown', keydown);
		document.addEventListener('keyup', keyup);
	}

	function keydown(e: any) {
		if (room && room.send) {
			if (e.keyCode === 38) {
				if (playerNumber == 1) room.send('keydown38player1');
				else room.send('keydown38player2');
			}
			if (e.keyCode === 40) {
				if (playerNumber == 1) room.send('keydown40player1');
				else room.send('keydown40player2');
			}
		}
	}

	function keyup(e: any) {
		if (room && room.send) {
			if (e.keyCode === 38) {
				if (playerNumber == 1) room.send('keyup38player1');
				else room.send('keyup38player2');
			}
			if (e.keyCode === 40) {
				if (playerNumber == 1) room.send('keyup40player1');
				else room.send('keyup40player2');
			}
		}
	}

	const initGame = () => {
		// room?.send("init");
		promise = init();
	};

	function drawMessage(message: string) {
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

	$: if (room) {
		room.onMessage('disconnect', () => goto('/app/dashboard'));
		room.onMessage('init', (j: number) => {
			playerNumber = j;
		});
		room.onMessage('gameState', (gameState: any) => {
			gameState = JSON.parse(gameState);
			requestAnimationFrame(() => trender(gameState));
		});
		room.onMessage('gameOver', (data: any) => {
			if (!gameOver) {
				let date = JSON.parse(data);
				if (date.winner === playerNumber) {
					drawMessage('GG Winner ');
				} else {
					drawMessage('You loooser');
				}
				gameOver = true;
			}
		});
		//room.send("canvas", 1000);
	}

	$: if (matchroom) {
		matchroom.onMessage('seat', (ticket: any) => {
			consumeticket(ticket);
		});
	}

	async function consumeticket(ticket: any) {
		try {
			room = await client?.consumeSeatReservation(ticket.ticket);
		} catch (e) {
			console.error('join error', e);
		}
	}

	/*
			faire changer la taille du canvas.
			envoyer dans le back tout le temps la taille du canvas !
			dans le back recuperer la taille du canvas et faire les calculs dynamique.
		*/

	//function setupMessageHandlers() {
	// room?.onMessage("gameState", handleGameState);
	// room?.onMessage("gameCode", handleGameCode);
	// room?.onMessage("unknownCode", handleUnknownCode);
	// room?.onMessage("tooManyPlayers", handleTooManyPlayers);
	// room?.onMessage("playerNumber", handlePlayerNumber);
	//}

	// room?.onMessage("init2", () => {
	// });

	// function drawRect(x: number, y: number, w: number, h: number, color: any) {
	//     ctx.fillStyle = color;
	//     ctx.fillRect(x, y, w, h);
	// }

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
		if (canvas === null) {
			return; // Sortir de la fonction si le canvas est nul
		}
		if (changecolor === true) drawRect(0, 0, canvas.width, canvas.height, '#000');
		else drawRect(0, 0, canvas.width, canvas.height, '#FFF');

		//if (changecolor === true)
		drawText(state.user.score, canvas.width / 4, canvas.height / 5, '#FF0000');
		//else

		drawText(state.com.score, (3 * canvas.width) / 4, canvas.height / 5, '#FF0000');
		if (changecolor === true) drawNet(state, '#FFF');
		else drawNet(state, '#000');

		if (changecolor === true)
			drawRect(state.user.x, state.user.y, state.user.width, state.user.height, '#FFF');
		else drawRect(state.user.x, state.user.y, state.user.width, state.user.height, '#000');

		//drawRect(state.user.x, state.user.y, state.user.width, state.user.height, state.user.color);

		if (changecolor === true)
			drawRect(state.com.x, state.com.y, state.com.width, state.com.height, '#FFF');
		else drawRect(state.com.x, state.com.y, state.com.width, state.com.height, '#000');

		if (changecolor === true) drawArc(state.ball.x, state.ball.y, state.ball.radius, '#FFF');
		else drawArc(state.ball.x, state.ball.y, state.ball.radius, '#000');

		// 	if (state.gameOver) {
		//     if (state.winner === playerNumber) {
		//         gameResult = "You win!";
		// 		console.log("?? " + room.id)
		// 		resetroomData()
		// 		console.log("?? " + room.id)
		//     } else {
		//         gameResult = "You lose!";
		// 		console.log("?? " + room.id)
		// 		resetroomData()
		// 		console.log("?? " + room.id)
		//     }
		//     drawMessage(gameResult);
		//     return; // Exit the function to stop rendering the game
		// }
	}

	function handleGameState(gameState: any) {
		if (!gameActive) {
			return;
		}
		gameState = JSON.parse(gameState);
		requestAnimationFrame(() => trender(gameState));
	}

	async function joinMatchMaking() {
		try {
			if (browser) {
				const localstorage = localStorage.getItem('userId');
				matchroom = await client?.joinOrCreate('matchMaking', {
					id: localstorage,
					roomName: 'matchMaking'
				}); // this will create "my_room" if it doesn't exist already or join it if it does exist
				return matchroom;
			}
		} catch (e) {
			console.error(e);
		}
	}

	function matchMaking() {
		promise = joinMatchMaking();
		initGame();
	}

	function changeColor() {
		changecolor = true;
	}

	// function quitGame() {
	// 	room?.leave();
	// 	matchroom?.leave();
	// 	gameActive = false;
	// 	goto('/');
	// }

	function reconnectToRunningGame() {
		const gameCodeInput = document.getElementById('gameCodeInput') as HTMLInputElement;
		gameCodeInput.value = room.id;
		initialScreen.style.display = 'none';
		game.style.display = 'block';
		canvas = document.getElementById('pong');
		const { width, height } = canvas.getBoundingClientRect();
		canvas.width = width;
		canvas.height = height;
		ctx = canvas.getContext('2d');
		gameCode = document.getElementById('gameCode');
		if (gameCode) {
			gameCode.innerText = room.id;
		}
		gameActive = true;
		document.addEventListener('keydown', keydown);
		document.addEventListener('keyup', keyup);
		room.onMessage('gameState', handleGameState);
		room.onMessage('gameOver', handleGameOver);
	}

	function handleGameOver(data: any) {
		document.removeEventListener('keyup', keyup);
		document.removeEventListener('keydown', keydown);
		room?.leave();
		matchroom?.leave();
		gameActive = false;
		let date = JSON.parse(data);
		if (date.winner === playerNumber) {
			drawMessage('GG Winner ');
			resetroomData();
		} else {
			drawMessage('You loooser');
			resetroomData();
		}
	}

	function resetroomData() {
		room = null;
		matchroom = null;
		gameActive = false;
		gameCode = null;
		playerNumber = 0;
	}
</script>

{#await promise}
	<p>attente</p>
{:then test}
	<!--<button on:click={initGame}>init game</button>-->
{:catch err}
	<p>error: {err}</p>
{/await}

<main>
	<div class="wrap">
		<div bind:this={initialScreen} class="h-100 center-div">
			<div class="d-flex flex-column align-items-center justify-content-center h-100">
				<h1>Multiplayer Pong Game</h1>
				<!-- <button on:click={handleCreateGame} class="btn btn-success" id="newGameBtn">
                Create New Game
            </button>
            <div>OR</div>
            <div class="form-group">
				<input bind:value={input} placeholder="enter your name" />
            </div>
            <button on:click={handleJoinGame} class="btn btn-success" id="joinGameBtn">
                Join Game
            </button> -->
				<button on:click={matchMaking} class="btn btn-success" id="matchMaking">
					Match Making
				</button>
				<form method="post" id="form">
					<input type="radio" on:click={changeColor} /> night mode
				</form>
			</div>
		</div>
		<div bind:this={game} id="game">
			<!-- <h1>Your game code is: <span id="gameCode"></span></h1> -->

			<canvas bind:this={canvas} id="pong" width="600" height="400" />
			<!-- <canvas id="resultCanvas"></canvas> -->
			<!-- <button on:click={quitGame}>quit</button> -->
		</div>
	</div>
</main>

<!-- 
	EXPLICATION DANS LE DETAIL DU CODE DE LA PAGE :

	1. On importe les librairies dont on a besoin pour la page
	2. On déclare les variables dont on a besoin pour la page :
		- matches : contient les matchs
		- width : largeur du canvas
		- height : hauteur du canvas
		- client : client pour se connecter au serveur
		- name : nom du joueur
		- input : input du joueur
		- initialScreen : écran d'attente
		- canvas : canvas du jeu
		- ctx : contexte du canvas
		- game : écran du jeu
		- pong : jeu
		- room : room du jeu
		- matchroom : room du matchmaking
		- gameActive : booléen pour savoir si le jeu est actif
		- promise : promesse pour attendre la réponse du serveur
		- gameCode : code du jeu
		- playerNumber : numéro du joueur
		- changecolor : booléen pour savoir si on est en mode nuit ou jour

	3. On crée la fonction createGame qui permet de créer une room :
		- On essaie de créer une room
		- On récupère l'id de la room
		- On retourne l'id de la room
	
	4. On crée la fonction handleCreateGame qui permet de créer une room :
		- On appelle la fonction createGame

	5. On crée la fonction joinGame qui permet de rejoindre une room :
		- On essaie de rejoindre une room
		- On retourne l'id de la room

	6. On crée la fonction handleJoinGame qui permet de rejoindre une room :
		- On appelle la fonction joinGame

	7. On crée la fonction init qui permet d'initialiser le jeu :
		- On cache l'écran d'attente
		- On affiche l'écran du jeu
		- On récupère le canvas
		- On récupère la largeur et la hauteur du canvas
		- On initialise le contexte du canvas
		- On affiche le code du jeu
		- On initialise le jeu
		- On ajoute les évènements clavier

	8. On crée la fonction keydown qui permet de gérer les évènements clavier :
		- Si la touche pressée est la touche du haut
			- Si le joueur est le joueur 1
				- On envoie un message au serveur pour dire que le joueur 1 a appuyé sur la touche du haut
			- Sinon
				- On envoie un message au serveur pour dire que le joueur 2 a appuyé sur la touche du haut
		- Si la touche pressée est la touche du bas
			- Si le joueur est le joueur 1
				- On envoie un message au serveur pour dire que le joueur 1 a appuyé sur la touche du bas
			- Sinon
				- On envoie un message au serveur pour dire que le joueur 2 a appuyé sur la touche du bas
	
	9. On crée la fonction keyup qui permet de gérer les évènements clavier :
		- Si la touche pressée est la touche du haut
			- Si le joueur est le joueur 1
				- On envoie un message au serveur pour dire que le joueur 1 a relaché la touche du haut
			- Sinon
				- On envoie un message au serveur pour dire que le joueur 2 a relaché la touche du haut
		- Si la touche pressée est la touche du bas
			- Si le joueur est le joueur 1
				- On envoie un message au serveur pour dire que le joueur 1 a relaché la touche du bas
			- Sinon
				- On envoie un message au serveur pour dire que le joueur 2 a relaché la touche du bas
	
	10. On crée la fonction initGame qui permet d'initialiser le jeu :
		- On envoie un message au serveur pour dire qu'on initialise le jeu

	11. On crée la fonction handleGameState qui permet de gérer l'état du jeu :
		- Si le jeu n'est pas actif
			- On sort de la fonction
		- On parse l'état du jeu
		- On demande au serveur de mettre à jour l'état du jeu

	12. On crée la fonction joinMatchMaking qui permet de rejoindre le matchmaking :
		- On essaie de rejoindre le matchmaking
		- On retourne le matchmaking

	13. On crée la fonction matchMaking qui permet de rejoindre le matchmaking :
		- On appelle la fonction joinMatchMaking
		- On initialise le jeu
	
	14. On crée la fonction changeColor qui permet de changer la couleur du jeu :
		- On passe le booléen changecolor à true

	15. On crée la fonction drawRect qui permet de dessiner un rectangle :
		- On récupère le contexte du canvas
		- On dessine un rectangle

	16. On crée la fonction drawArc qui permet de dessiner un cercle :
		- On récupère le contexte du canvas
		- On dessine un cercle

	17. On crée la fonction drawNet qui permet de dessiner le filet :
		- On récupère le contexte du canvas
		- On dessine le filet

	18. On crée la fonction drawText qui permet de dessiner du texte :
		- On récupère le contexte du canvas
		- On dessine du texte

	19. On crée la fonction trender qui permet de dessiner le jeu :
		- Si le canvas est nul
			- On sort de la fonction
		- On dessine le fond du jeu
		- On dessine le score du joueur 1
		- On dessine le score du joueur 2
		- On dessine le filet
		- On dessine le joueur 1
		- On dessine le joueur 2
		- On dessine la balle
	
 -->

<style>
	#game {
		display: none;
	}
	.wrap {
		background-color: rgb(126, 123, 123);
	}

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
	h1 {
		color: rgb(180, 48, 64);
		position: center;
		display: flex;
		justify-content: center;
		align-items: center;
	}
	button {
		display: flex;
		justify-content: center;
		align-items: center;
		border: none;
		background-color: #9e9c9c;
		border-radius: 20px;
		color: white;
		font-size: 16px;
		font-weight: bold;
		cursor: pointer;
		outline: none;
		padding: 10px 20px;
		margin: 0 auto;
		transition: background-color 0.3s ease;
	}

	#form {
		margin: 40px;
		display: flex;
		justify-content: center;
		align-items: center;
	}

	.center-div {
		display: flex;
		justify-content: center;
		align-items: center;
	}

	/*@media (min-width: 1px) and (max-width: 1000px) {
			canvas {
				width: 600px;
				height: 400px;
			}
		}

		@media(min-width: 1001px) {
			canvas {
				width: 1200px;
				height: 800px;
			}
		}*/
</style>
