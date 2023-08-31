<script lang="ts">
	import { goto } from '$app/navigation';
	import { socket } from './socketsbs';
	import { createEventDispatcher, onMount } from 'svelte';
	const dispatch = createEventDispatcher();

	export let invitationData: any;

	let hanndleRefuse = () => {
		socket.emit('refuse', invitationData);
		dispatch('refuseInvitation');
	};
</script>

<div class="popup">
	<img src={invitationData.img} alt="logo" class="invit-img" />
	<p>You got an invitation to a game from {invitationData.name}</p>
	<div class="buttons">
		<button
			on:click={() => {
				dispatch('refuseInvitation');
				goto(`/app/game/${invitationData.secret}`);
			}}
			class="accept-button">Accept</button
		>
		<button class="decline-button" on:click={hanndleRefuse}>Decline</button>
	</div>
</div>

<style>
	.popup {
		position: fixed;
		bottom: 20px;
		right: 20px;
		width: 300px;
		padding: 20px;
		background-color: #f0f0f0;
		border: 1px solid #ccc;
		box-shadow: 0 2px 4px rgba(0, 0, 0, 0.2);
		text-align: center;
	}

	.popup p {
		margin: 0;
	}

	.buttons {
		margin-top: 20px;
	}

	.buttons button {
		margin: 0 5px;
		padding: 10px 20px;
		background-color: #007bff;
		color: #fff;
		border: none;
		border-radius: 4px;
		cursor: pointer;
	}

	.buttons button:hover {
		background-color: #0056b3;
	}

	.invit-img {
		width: 50px;
		height: 50px;
		border-radius: 50%;
		/* margin-right: 20px; */
		object-fit: cover;
		/* box-shadow: 0 0 20px rgba(0, 255, 0, 0.5); */
	}
</style>
