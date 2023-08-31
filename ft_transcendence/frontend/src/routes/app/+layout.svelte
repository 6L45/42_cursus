<script lang="ts">
	import { jwt_cookie, img_path, clientName, userId42, userId, rooms } from '$lib/stores';
	import { afterNavigate, goto, invalidate } from '$app/navigation';
	import { page } from '$app/stores';
	import { afterUpdate, onDestroy, onMount } from 'svelte';
	import { io } from 'socket.io-client';
	import { initializeSocket, socket } from '$lib/socketsbs.js';
	import { connectClientToColyseus } from '$lib/gamesocket';
	import Alert from '$lib/popupAlert.svelte';
	import type { AfterNavigate } from '@sveltejs/kit';
	import Invitation from '$lib/invitation.svelte';
	// import { redirect } from '@sveltejs/kit';

	export let data: any;
	/**
	 * Invitations
	 */
	let alertPopupOn = false;
	let invitationData = { player_id: 0, secret: '', name: '', img: '' };
	let Invitations: any = [];

	let setPopupToogleEvent = () => {
		socket.on('invitationGame', invitationHandler);
	};

	let invitationHandler = (invitData: any) => {
		alertPopupOn = true;
		invitationData = invitData;
		Invitations.push(invitationData);
	};

	/**
	 * La logique de ce Layout qui englobe tout App
	 * On fait un fetch 'test' et on recupere chaque info necessaire quon stock dans stores et dans le localStorage en consequent
	 * Si nok alors lacces a l'app est interdite et on renvoi sur la page de debut
	 */
	onMount(async () => {
		jwt_cookie.set(data.myJwtCookie);
		userId42.set(data.myid42);
		if ($jwt_cookie) {
			//--- Ici on va chercher la value de la DFA dans la BD
			try {
				const response = await fetch(`/api/auth/2fa`, {
					method: 'GET',
					headers: {
						Authorization: `Bearer ${$jwt_cookie}`
					}
				});
				if (response.ok) {
					let dfastatus = await response.json();
					if (dfastatus.dfa == true && dfastatus.dfaVerifies == false) goto('/2FA');
				}
			} catch {
				goto('/');
			}
			//---
			//si la value est true on goto /2FA
			//sinon rien

			try {
				const connect = await fetch(`/api/dashboard`, {
					method: 'GET',
					headers: {
						Authorization: `Bearer ${$jwt_cookie}`
					}
				});
				if (connect.status == 200) {
					const data = await connect.json();
					$img_path = data.img;
					$clientName = data.name;
					$userId = data.id;
					await initializeSocket();
					setPopupToogleEvent();
					connectClientToColyseus();
				} else {
					//connection refusee a cause dun mauvai/vieux/invalid/corrompu cookie
					console.error('invalid cookie');
					goto('/');
				}
			} catch (error) {
				console.error("fetching in '/app' :", error);
				goto('/');
			}
		} else goto('/');
	});

	onDestroy(() => {});

	afterNavigate(async (navigation: AfterNavigate) => {
		try {
			const connect = await fetch(`/api/dashboard`, {
				method: 'GET',
				headers: {
					Authorization: `Bearer ${$jwt_cookie}`
				}
			});
			if (connect.status == 200) {
				const data = await connect.json();
				$img_path = data.img;
				$clientName = data.name;
				$userId = data.id;
			} else {
				//connection refusee a cause dun mauvai/vieux/invalid/corrompu cookie
				console.error('invalid cookie');
				goto('/')
			}
		} catch (error) {
			console.error("fetching in '/app' :", error);
		}
	});

	/**
	 * La fonction handleLogOut est appelee lorsque le user click sur le bouton LogOut
	 * Ce qu'on doit faire cest supprimer tous les localStorage et les cookies de la session
	 * Puis renvoyer la session en "/"
	 */
	let handleLogOut = () => {
		goto('/logout');
	};

	/**
	 * Search Block
	 */
	let nameSearchInput = '';
	let id42NameInputNotEmpty: any;
	let searchRes: any = [];
	async function getSpecifiedClients() {
		const nameSearchInput = document.getElementById('id42-name-input').value;
		id42NameInputNotEmpty = nameSearchInput.trim() !== '';

		if (id42NameInputNotEmpty) {
			try {
				const response = await fetch(`/api/dashboard/name/${nameSearchInput}`, {
					method: 'GET',
					headers: {
						Authorization: `Bearer ${$jwt_cookie}`
					}
				});
				searchRes = await response.json();
			} catch (error) {
				console.error(error);
			}
		} else searchRes = [];
	}

	async function refreshInput(client: any) {
		document.getElementById('id42-name-input').value = '';
		searchRes = [];
		id42NameInputNotEmpty = null;
		await goto(`/app/dashboard/${client.name}`, { replaceState: true });
	}

	// $:{
	// 	$rooms;
	// 	local_count = msgCount;
	// }
</script>

<header>
	<div class="search-bar">
		<input
			class="input"
			type="text"
			placeholder="search ..."
			id="id42-name-input"
			on:input={() => getSpecifiedClients()}
			bind:value={nameSearchInput}
		/>
		{#if id42NameInputNotEmpty}
			<div class="popup">
				{#each searchRes as client}
					<div class="link">
						<button on:click={() => refreshInput(client)}>{client.name}</button>
					</div>
				{/each}
			</div>
		{/if}
	</div>
	<div class="content">
		<h1>The Pong</h1>
		<div class="panel">
			<div class="controls">
				<p class="controls-one">{$clientName}</p>
				<button
					on:click={() => goto('/app/settings')}
					class:settings-select={$page.url.pathname === '/app/settings'}
					class="controls-one">settings</button
				>
				<button class="controls-one" on:click={handleLogOut}>log out</button>
			</div>
			{#if $img_path}
				<img src={$img_path} alt="logo" class="rick" />
			{:else}
				<img src="/logo.jpeg" alt="logo" class="rick" />
			{/if}
		</div>
	</div>
</header>
<nav class="navbar">
	<button
		on:click={() => goto('/app/dashboard')}
		class:selected={$page.url.pathname === '/app/dashboard'}>DashBoard</button
	>
	<button
		on:click={() => goto('/app/friends')}
		class:selected={$page.url.pathname === '/app/friends'}>Friends</button
	>
	<button on:click={() => goto('/app/game')} class:selected={$page.url.pathname === '/app/game'}
		>Game</button
	>
	<button on:click={() => goto('/app/chat')} class:selected={$page.url.pathname === '/app/chat'}
		>Chat</button
	>
</nav>

<main>
	{#if alertPopupOn}
		<Alert
			{invitationData}
			on:refuseInvitation={() => {
				alertPopupOn = false;
			}}
		/>
	{/if}
	<!-- {#each Invitations as invitation}
		<Alert invitationData={invitation} on:refuseInvitation={ () => {
			Invitations = Invitations.filter((el) => {
			el.player_id !== invitation.id;
			});
		}}/>
	{/each} -->
	<slot class="main_body" />
</main>

<style>
	header {
		/* background: no-repeat center/100% url('https://profile.intra.42.fr/assets/background_login-a4e0666f73c02f025f590b474b394fd86e1cae20e95261a6e4862c2d0faa1b04.jpg'); */
		height: 25vh;
		min-height: 160px;
		color: white;
		padding: 0 100px;
	}

	h1 {
		text-transform: uppercase;
		font-weight: normal;
	}

	.content {
		display: flex;
		flex-direction: row;
		justify-content: space-between;
		align-items: center;
		height: 100%;
		max-width: 1000px;
		margin: auto;
		padding: auto;
	}

	.panel {
		align-items: center;
		display: flex;
	}

	.controls {
		float: left;
		display: flex;
		justify-content: space-around;
		flex-direction: column;
		font-size: 15px;
		margin-right: 15px;
		font-weight: lighter;
		text-align: center;
	}

	button {
		text-decoration: none;
		border: none;
		background: none;
		font-weight: normal;
		font-family: 'Oxanium';
	}

	.controls button {
		margin-top: 5px;
		text-decoration: none;

		border: none;
		background: none;
		font-size: 15px;
		font-weight: lighter;
		font-family: 'Oxanium';
	}

	.controls-one {
		color: white;
	}

	.settings-select {
		color: #05e300;
	}

	.controls button:hover {
		text-decoration: underline;
		cursor: pointer;
	}

	.rick {
		width: 90px;
		height: 90px;
		border-radius: 50%;
		/* margin-right: 20px; */
		object-fit: cover;
		/* box-shadow: 0 0 20px rgba(0, 255, 0, 0.5); */
	}

	.search-bar {
		text-align: left;
	}

	.input {
		width: 150px;
		height: 20px;
		padding-left: 20px;
		font-family: 'Oxanium';
		border: none;
	}

	.navbar {
		padding: 0 100px;
		background-color: #404040;
		display: flex;
		justify-content: space-around;
	}

	.navbar button {
		padding: 8px 30px;
		color: white;
		font-size: 12px;
		font-weight: 200;
	}

	.navbar button:hover {
		cursor: pointer;
	}

	.selected {
		background-color: #3ab45c;
	}

	/* .tabs{
		display: flex;
		justify-content: space-around;
		padding: 0 150px;
		margin: 0;
		background-color: #292d39;
		color: lightgray
	}

	.newMessage::after {
		content: attr(number);
		position: absolute;
		top: -10px;
		right: -10px;
		width: 20px;
		height: 20px;
		background-color: red;
		color: white;
		border-radius: 50%;
		text-align: center;
		line-height: 20px;
		font-size: 12px;
	} */
	.link {
		text-decoration: none;
		background-color: white;
		height: 20px;
		width: 150px;
		padding-left: 20px;
		transition: background-color 0.3s ease;
		transition: color 0.3s ease;
	}
	.link:hover {
		color: #3ab45c;
		cursor: pointer;
	}
	.link button:hover {
		color: #3ab45c;
		cursor: pointer;
	}

	.popup {
		position: absolute;
	}

	/* .popup_container {
		position: relative;
		width: 7vw;
		left: 50%;
		transform: translateX(-50%);
	}
	.popup {
		position: absolute;
		top: calc(100% + 10px);
		left: 0;
		width: 100%;
		max-height: 200px;
		overflow-y: auto;
		background-color: #fff;
		border: 1px solid #ccc;
		border-radius: 4px;
		padding: 8px;
		box-shadow: 0 2px 4px rgba(0, 0, 0, 0.1);
		z-index: 1;
	} */

	input:disabled {
		color: #ccc;
	}
</style>
