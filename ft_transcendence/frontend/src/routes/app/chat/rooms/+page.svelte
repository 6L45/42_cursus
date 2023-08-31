<script lang="ts">
	import { goto } from '$app/navigation';
	import { jwt_cookie } from '$lib/stores';

	async function fetchAvailableRooms() {
		// ici demander throw catch error comme ailleurs
		const response = await fetch(`/api/rooms/valideRooms`, {
			method: 'GET',
			headers: {
				Authorization: `Bearer ${$jwt_cookie}`
			}
		});
		if (response.status == 200) {
			let rooms = await response.json();
			return rooms;
		} else {
			console.error('Failed to fetch rooms');
		}
	}

	const join = async (room: any) => {
		let password: string = '';
		if (room.secu == 1) {
			const placeholder = prompt('Enter the password:');
			if (placeholder === null) return;
			else if (placeholder === '') {
				alert('Please enter a password');
				return;
			} else if (placeholder) password = placeholder;
		}
		const response = await fetch(`/api/rooms/join/${room.id}`, {
			method: 'POST',
			headers: {
				'Content-Type': 'application/json',
				Authorization: `Bearer ${$jwt_cookie}`
			},
			body: JSON.stringify({ password })
		});
		if (response.ok) {
			goto('/app/chat/');
		} else if (response.status === 401) {
			alert('wrong password');
		} else {
			console.error('Failed to join room:', room.name);
		}
	};
</script>

<div class="rooms-list-content">
	<div class="btn-create-room-wrapper">
		<a class="btn-create-room" href="/app/chat/create">Create Room</a>
	</div>
	{#await fetchAvailableRooms()}
		<p>Loading available rooms ...</p>
	{:then availableRooms}
		<ul>
			{#each availableRooms as room}
				<li>
					<div class="room-left-content">
						<button class="btn-join-room" on:click={() => join(room)}>Join</button>{room.name}
						{#if room.secu == 1 || room.secu == 2}
							🔒
						{/if}
					</div>
					<div class="room-info">{room.quantity}👤</div>
				</li>
			{/each}
		</ul>
	{/await}
</div>
<div class="void-content" />

<style>
	.rooms-list-content {
		width: 100%;
		background-color: #efefef;
		color: black;
		overflow: scroll;
	}

	ul {
		margin: 20px 40px;
		padding: 0;
	}

	li {
		display: flex;
		flex-direction: row;
		justify-content: space-between;
		align-items: center;
		background-color: #d9d9d9;
		padding: 10px 15px;
		border-radius: 8px;
		margin-bottom: 15px;
	}

	.btn-join-room {
		border: none;
		background-color: #3ab45c;
		color: white;
		font-family: 'Oxanium';
		font-weight: lighter;
		padding: 4px 25px;
		margin-right: 10px;
		cursor: pointer;
	}

	.void-content {
		background-color: #404040;
		width: 30vw;
	}

	.btn-create-room-wrapper {
		text-align: center;
		margin: 30px 0;
	}

	.btn-create-room {
		background-color: #3ab45c;
		color: white;
		padding: 15px 20px;
		text-decoration: none;
		cursor: pointer;
		text-align: center;
	}

</style>
