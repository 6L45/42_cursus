<script lang="ts">
	import { afterNavigate, goto, invalidateAll } from '$app/navigation';
	import ConnectStatus from '$lib/connectStatus.svelte';
	import { jwt_cookie, userId42, userId, clientName } from '$lib/stores';
	import { onMount, onDestroy } from 'svelte';
	import { socket } from '$lib/socketsbs';
	import Invite from '$lib/invitation.svelte';
	import { error, type AfterNavigate } from '@sveltejs/kit';
	import { Manager } from 'socket.io-client';

	// export let data: any;
	export let data: any;
	let roomId: string = data.roomId;
	let RoomsMessages: any = data.messages;
	let members: any = data.members;
	let user_message: string;
	let my_status: number = data.status;
	let blocked: any = data.blocked;
	let roomInfo: any = data.roomInfo;

	RoomsMessages = RoomsMessages.filter((msg: any) => {
		let found = false;
		blocked.forEach((el: any) => {
			if (
				(el.client1.name !== $clientName && el.client1.name === msg.sender) ||
				(el.client2.name !== $clientName && el.client2.name == msg.sender)
			)
				found = true;
		});
		return !found;
	});

	onMount(() => {
		if (!socket)
			setTimeout(function () {
				if (!socket)
					setTimeout(function () {
						if (socket) configSocket();
					}, 1000);
				else if (socket) configSocket();
			}, 1000);
		else if (socket) configSocket();
		else {
			console.error('socket is not initialised');
			goto('/app/chat');
		}
	});

	let configSocket = () => {
		socket.emit('joinChannel', String(roomId));
		socket.off('serverToChat', recieveMessage);
		socket.off('serverMessage', recieveServerMessage);
		socket.off('reloadMembers', reloadMembers);
		socket.on('serverToChat', recieveMessage);
		socket.on('serverMessage', recieveServerMessage);
		socket.on('reloadMembers', reloadMembers);
		// socket.on('reloadrooms', reloadRoom);
	};

	onDestroy(() => {
		if (socket) {
			socket.emit('leaveChannel', String(roomId));
			socket.off('serverToChat', recieveMessage);
			socket.off('serverMessage', recieveServerMessage);
			socket.off('reloadMembers', reloadMembers);
			// socket.off('reloadrooms', reloadRoom);
		}
	});

	// async function reloadRoom() {
	// 	invalidateAll();
	// }

	/**
	 * Socket functions handlers event
	 */

	let recieveMessage = (msg: any) => {
		let found: boolean = false;

		blocked.forEach((el: any) => {
			if (
				(el.client1.name !== $clientName && el.client1.name === msg.sender) ||
				(el.client2.name !== $clientName && el.client2.name == msg.sender)
			)
				found = true;
		});
		if (found) return;
		RoomsMessages = [{ sender: msg.sender, message: msg.message }, ...RoomsMessages];
	};

	let recieveServerMessage = (msg: any) => {
		RoomsMessages = [{ sender: msg.sender, message: msg.message }, ...RoomsMessages];
	};

	let sendMessage = () => {
		if (socket && user_message) {
			// RoomsMessages.push({sender: $userId42, message: user_message}) haha non merci
			// RoomsMessages = RoomsMessages
			socket.emit('chatToServer', { channel: roomId, message: user_message, sender_id: $userId42 });
			user_message = '';
		}
	};

	async function reloadMembers() {
		const url_api_members = `/api/chat/room/${roomId}`;

		const update_members = await fetch(url_api_members, {
			method: 'GET',
			headers: {
				Authorization: `Bearer ${$jwt_cookie}`
			}
		})
			.then(async (response) => {
				if (response.ok) return await response.json();
				else await goto('/app/chat');
			})
			.catch((err) => {
				throw error(err.status, { message: err.statusText });
			});
		members = update_members;
	}

	afterNavigate((navigation: AfterNavigate) => {
		user_message = '';
		roomId = data.roomId;
		RoomsMessages = data.messages;
		members = data.members;
		my_status = data.status;
		blocked = data.blocked;
		roomInfo = data.roomInfo;
		RoomsMessages = RoomsMessages.filter((msg: any) => {
			let found = false;
			blocked.forEach((el: any) => {
				if (
					(el.client1.name !== $clientName && el.client1.name === msg.sender) ||
					(el.client2.name !== $clientName && el.client2.name == msg.sender)
				)
					found = true;
			});
			return !found;
		});
		if (socket) {
			if (navigation.from?.params && navigation.from?.params.roomId)
				socket.emit('leaveChannel', String(navigation.from?.params.roomId));
			socket.emit('joinChannel', String(roomId));
		}
	});

	let sendQuitPost = async () => {
		await fetch(`/api/rooms/quit/${roomId}`, {
			method: 'POST',
			headers: {
				Authorization: `Bearer ${$jwt_cookie}`
			}
		})
			.then((res) => {
				if (!res.ok) console.error('failed to quit');
			})
			.catch(() => {
				console.error('failed to quit');
			});
	};

	let handleButton = () => {
		if (data.status != 0) {
			sendQuitPost();
			goto('/app/chat');
		} else goto(`/app/chat/${roomId}/manage`);
	};

	/**
	 * All functions related to admin/owner activity
	 * Kick/Ban/Mute/Promote/Demote
	 */
	async function updateClientStatus(clientId: number, status: number) {
		try {
			const response = await fetch(`/api/rooms/updateStatus/${roomId}/${clientId}/${status}`, {
				method: 'POST',
				headers: {
					Authorization: `Bearer ${$jwt_cookie}`
				}
			});

			if (!response.ok) {
				console.error(response.statusText);
				console.error('Failed to update status');
			}
		} catch (error) {
			console.error('An error occurred', error);
		}
	}

	async function kick(clientId: any) {
		try {
			const response = await fetch(`/api/rooms/kick/${roomId}/${clientId}`, {
				method: 'POST',
				headers: {
					Authorization: `Bearer ${$jwt_cookie}`
				}
			});

			if (!response.ok) {
				const errorText = await response.text();
				throw new Error(errorText);
			}
		} catch (error: any) {
			throw new Error(error.message);
		}
	}

	async function accept(clientId: any) {
		try {
			const response = await fetch(`/api/rooms/acceptNewMember/${roomId}/${clientId}`, {
				method: 'POST',
				headers: {
					Authorization: `Bearer ${$jwt_cookie}`
				}
			});

			if (!response.ok) {
				const errorText = await response.text();
				throw new Error(errorText);
			}
		} catch (error) {
			console.error(error);
		}
	}
</script>

<div class="room_wrap">
	<!-- rajouter un link bouton fermer qui retourne sur /chat -->
	<ul class="messages">
		{#each RoomsMessages as message}
			<li
				class="one_message"
				class:servermsg={message.sender === 'server'}
				class:myMessage={message.sender === $clientName}
			>
				{message.sender}: {message.message}
			</li>
		{:else}
			<p class="info">no messages, be the first one</p>
		{/each}
	</ul>
	<form on:submit|preventDefault={sendMessage} class="component_send_box">
		<input type="text" placeholder="Type something ..." maxlength="500" bind:value={user_message} />
		<button>send</button>
	</form>
</div>
<div class="members">
	{#if roomInfo.secu !== 3}
		<ul>
			{#each members as member}
				<li class="one_member">
					{#if my_status === 0 || my_status === 1}
						<div class="owner-admin-block">
							{#if member.status === 6}
								<button
									class="hovertext"
									data-hover="accept"
									on:click={() => accept(member.member.id)}>✅</button
								>
								<button
									class="hovertext"
									data-hover="refuse access"
									on:click={() => kick(member.member.id)}>❌</button
								>
							{:else if member.status === 5}
								<button class="hovertext" data-hover="unban" on:click={() => kick(member.member.id)}
									>❌</button
								>
							{:else if member.status !== 0 && member.status !== 1}
								<button class="hovertext" data-hover="kick" on:click={() => kick(member.member.id)}
									>🚪</button
								>
								<button
									class="hovertext"
									data-hover="ban"
									on:click={() => updateClientStatus(member.member.id, 5)}>❌</button
								>
								<button
									class="hovertext"
									data-hover="toggle mute"
									on:click={() => {
										if (member.status === 3) updateClientStatus(member.member.id, 2);
										else updateClientStatus(member.member.id, 3);
									}}>🔇</button
								>
							{/if}
						</div>
					{/if}
					{#if my_status === 0}
						<div class="owner-block">
							{#if member.status === 1}
								<button
									class="hovertext"
									data-hover="demote"
									on:click={() => updateClientStatus(member.member.id, 2)}>⬇️</button
								>
							{:else if member.status === 2}
								<button
									class="hovertext"
									data-hover="promote"
									on:click={() => updateClientStatus(member.member.id, 1)}>⬆️</button
								>
							{/if}
						</div>
					{/if}
					<a href="/app/dashboard/{member.member.name}">
						{#if member.status === 0}
							👑
						{:else if member.status === 1}
							💂
						{:else if member.status === 3}
							🤐
						{/if}
						{member.member.name}
					</a>
					<div class="member-status-block">
						{#if member.member.id != $userId && member.status !== 6 && member.status !== 5}
							<Invite opponent_id={member.member.id} where="" />
						{/if}
						<ConnectStatus userId={member.member.id} />
					</div>
				</li>
			{/each}
		</ul>
		<button on:click={handleButton} class="btn-room-quit">
			{#if my_status === 0}
				Manage
			{:else}
				Quit
			{/if}
		</button>
	{:else}
		<ul>
			{#each members as member}
				<li class="one_member">
					<a href="/app/dashboard/{member.member.name}">
						{member.member.name}
					</a>
					<div class="member-status-block">
						{#if member.member.id != $userId && member.status !== 6 && member.status !== 5}
							<Invite opponent_id={member.member.id} where="" />
						{/if}
						<ConnectStatus userId={member.member.id} />
					</div>
				</li>
			{/each}
		</ul>
	{/if}
</div>

<style>
	.members {
		width: 30vw;
		background-color: #404040;
		display: flex;
		flex-direction: column;
		justify-content: space-between;
		align-items: center;
	}

	.room_wrap {
		width: 100%;
		margin: 30px 0;
		display: flex;
		flex-direction: column;
		justify-content: end;
	}

	a {
		color: rgb(0, 100, 200);
		text-decoration: none;
	}

	li {
		list-style: none;
	}

	.room_wrap {
		width: 100%;
		/* max-height: 60vh; */
		display: flex;
		flex-direction: column;
		justify-content: space-between;
		color: #ffffff;
		padding: 5px;
		max-height: 60vh;
	}

	.component_send_box {
		background-color: #ffffff;
		overflow: hidden;
		display: flex;
		flex-direction: row;
		justify-content: space-between;
		align-items: baseline;
		padding: 5px 10px;
		min-height: 30px;
	}

	.component_send_box input {
		border: none;
		width: 100%;
		max-width: 80%;
		font-family: 'Oxanium';
	}

	input:focus {
		outline: none;
	}

	.component_send_box button {
		border: none;
		border-radius: 10px;
		width: 80px;
		height: 30px;
		background: #dbdbdb;
		font-family: 'Oxanium';
	}

	.messages {
		display: flex;
		flex-direction: column-reverse;
		max-height: 60vh;
		overflow: auto;
	}

	.one_message {
		background-color: #404040;
		max-width: 50%;
		border-radius: 5px;
		margin: 10px 0;
		padding: 15px 20px;
		font-size: 12px;
	}

	.myMessage {
		background-color: #3ab45c;
		align-self: flex-end;
	}

	.servermsg {
		color: gray;
	}

	.info {
		width: 100%;
		color: gray;
		text-align: center;
	}

	/* Member Block */

	.members ul {
		padding: 0;
		margin: 0;
	}

	.one_member {
		display: flex;
		flex-direction: row;
		margin: 0 10px;
		max-width: 100%;
		justify-content: space-between;
		align-items: center;
		margin-top: 15px;
		font-size: 12px;
	}

	.owner-admin-block {
		max-width: 77px;
		width: 77px;
		display: flex;
		flex-direction: row;
		align-items: center;
	}

	.owner-admin-block button {
		border: none;
		background: none;
		cursor: pointer;
	}

	.owner-block button {
		border: none;
		background: none;
		cursor: pointer;
	}

	.one_member a {
		text-decoration: none;
		color: white;
		font-size: 12px;
	}

	.member-status-block {
		max-width: 40px;
		width: 40px;
		display: flex;
		flex-direction: row;
		justify-content: end;
		align-items: center;
	}

	.btn-room-quit {
		border: none;
		background-color: #939393;
		color: white;
		font-family: 'Oxanium';
		padding: 15px 60px;
		margin: 10px 10px;
		text-transform: uppercase;
		cursor: pointer;
		transition: all ease-in-out 0.3s;
	}

	.btn-room-quit:hover {
		background-color: #3ab45c;
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
