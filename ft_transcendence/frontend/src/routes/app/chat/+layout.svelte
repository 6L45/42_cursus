<script lang="ts">
	import { PUBLIC_HOSTNAME } from '$env/static/public';
	import { type Rooms, jwt_cookie, userId } from '$lib/stores';
	import { socket } from '$lib/socketsbs';
	import { onMount } from 'svelte';
	import { afterNavigate } from '$app/navigation';
	// import { reloadRooms, updateCount } from '$lib/socketsbs';
	import { page } from '$app/stores';
	import type { AfterNavigate } from '@sveltejs/kit';

	// let rooms_promise;
	let rooms: any = [];

	onMount(async () => {
		/**
		 * Reloading $rooms here is not mandatory but is recomended
		 * otherwise reload is trigered when some rooms changes are done on the backend and signaled trought the socket to the user if connected
		 */
		fetchRooms();
	});

	afterNavigate((navigation: AfterNavigate) => {
		fetchRooms();
	});

	async function fetchRooms() {
		try {
			const response = await fetch(`/api/chat`, {
				method: 'GET',
				headers: {
					Authorization: `Bearer ${$jwt_cookie}`
				}
			});
			if (response.status == 200) {
				let tmp_rooms = await response.json();
				rooms = tmp_rooms;
			} else console.error(response.status, response.statusText);
			return null;
		} catch (error) {
			console.error(error);
		}
	}

	async function getImageAndName(id: number) {
		try {
			const response = await fetch(
				`http://${PUBLIC_HOSTNAME}:8080/api/dashboard/imgandname/${id}`,
				{
					method: 'GET',
					headers: {
						Authorization: `Bearer ${$jwt_cookie}`
					}
				}
			);
			if (response.ok) {
				let client = await response.json();
				return client;
			} else console.error('img and name');
		} catch (error) {
			console.error('img and name', error);
		}
	}
</script>

<div class="container">
	<div class="list_box">
		<ul>
			<li class="one-room btn-manage-room">
				{#if $page.url.pathname === '/app/chat/rooms'}
					<a href="/app/chat">&lt;</a>
				{:else if $page.url.pathname === '/app/chat/create'}
					<a href="/app/chat/rooms">&lt;</a>
				{:else}
					<a href="/app/chat/rooms">+</a>
				{/if}
			</li>
			<!-- {#await rooms_promise then rooms} -->
			{#each rooms as room (room.roomId)}
				<!-- svelte-ignore a11y-no-noninteractive-element-interactions -->
				{#if room.secu !== 3}
					<li
						class="one-room"
						class:selected-room={$page.url.pathname === `/app/chat/${room.roomId}`}
					>
						{#if $page.url.pathname === `/app/chat/${room.roomId}`}
							<p>{room.roomName}</p>
						{:else}
							<a href="/app/chat/{room.roomId}">{room.roomName}</a>
						{/if}
					</li>
				{:else if room.secu === 3}
					{#if room.ownerid === $userId}
						<li
							class="one-room one-to-one"
							class:selected-room={$page.url.pathname === `/app/chat/${room.roomId}`}
						>
							{#await getImageAndName(room.client2Id)}
								<img src="/logo.jpeg" alt="logo" class="room-img" />
								<p>{room.client2.name}</p>
							{:then user}
								<img src={user.img} alt="logo" class="room-img" />
								{#if $page.url.pathname === `/app/chat/${room.roomId}`}
									<p>{room.client2.name}</p>
								{:else}
									<a href="/app/chat/{room.roomId}"> {room.client2.name}</a>
								{/if}
							{:catch}
								<img src="/logo.jpeg" alt="logo" class="room-img" />
								<p>Unknown</p>
							{/await}
						</li>
					{:else}
						<li
							class="one-room one-to-one"
							class:selected-room={$page.url.pathname === `/app/chat/${room.roomId}`}
						>
							{#await getImageAndName(room.ownerid)}
								<img src="/logo.jpeg" alt="logo" class="room-img" />
								<p>Loading...</p>
							{:then user}
								<img src={user.img} alt="logo" class="room-img" />
								{#if $page.url.pathname === `/app/chat/${room.roomId}`}
									<p>{user.name}</p>
								{:else}
									<a href="/app/chat/{room.roomId}"> {user.name}</a>
								{/if}
							{:catch}
								<img src="/logo.jpeg" alt="logo" class="room-img" />
								<p>Unknown</p>
							{/await}
						</li>
					{/if}
				{/if}
			{:else}
				<li class="one-room"><p>You don't have rooms</p></li>
			{/each}
			<!-- {/await} -->
		</ul>
	</div>
	<slot />
</div>

<style>
	.container {
		/* padding-top: 20px; */
		height: 70vh;
		display: flex;
		flex-direction: row;
		justify-content: flex-start;
		overflow: hidden;
	}

	.list_box {
		color: whitesmoke;
		background-color: #404040;
		width: 30vw;
		overflow: scroll;
	}

	.one-room {
		/* padding: 15px 20px; */
		text-align: center;
	}

	.one-to-one {
		display: flex;
		flex-direction: row;
		justify-content: center;
		align-items: center;
	}

	.selected-room {
		background-color: #3ab45c;
	}

	.one-room a {
		display: block;
		padding: 15px 0;
		text-decoration: none;
		color: white;
	}

	.one-room p {
		display: block;
		padding: 15px 0;
		text-decoration: none;
		color: white;
	}

	.btn-manage-room {
		color: white;
		background-color: #3ab45c;
	}

	/* .activeroom {
		background-color: #898f9f;
	} */

	ul {
		padding: 0;
		margin: 0;
	}

	li {
		list-style: none;
	}

	.room-img {
		width: 25px;
		height: 25px;
		border-radius: 50%;
		/* margin-right: 20px; */
		object-fit: cover;
		margin-right: 10px;
		/* box-shadow: 0 0 20px rgba(0, 255, 0, 0.5); */
	}
</style>
