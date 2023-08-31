<script lang="ts">
	import { goto } from '$app/navigation';
	import { socket } from '$lib/socketsbs';
	import { userId } from '$lib/stores';
	import { StartPlayProcess, roomData } from '$lib/gamesocket';

	export let opponent_id: number;
	export let where: string;

	async function sendInvitation() {
		// socket.chat.emit('inviteToPlay', {player_id: $userId, opponent_id: opponent_id, secret: secret});
		// goto(`/app/game/${secret}`);
		await StartPlayProcess(opponent_id);
		goto(`/app/game/${roomData.id}`);
	}
</script>

{#if where === 'friendlist'}
	<button class="btn-blue" on:click={sendInvitation}>Play</button>
{:else}
	<button class="btn-emoji hovertext" data-hover="play" on:click={sendInvitation}>🕹️</button>
{/if}

<style>
	.btn-emoji {
		border: none;
		background: none;
		cursor: pointer;
	}

	.btn-blue {
		border: none;
		cursor: pointer;
		background-color: #17acff;
		color: white;
		font-family: 'Oxanium';
		padding: 10px 30px;
	}

	.hovertext {
		position: relative;
	}

	.hovertext:before {
		content: attr(data-hover);
		visibility: hidden;
		opacity: 0;
		background-color: black;
		color: #fff;
		text-align: center;
		border-radius: 5px;
		padding: 5px 5px;
		transition: opacity 1s ease-in-out;

		position: absolute;
		z-index: 1;
		left: 0;
		top: 110%;
	}

	.hovertext:hover:before {
		opacity: 1;
		visibility: visible;
	}
</style>
