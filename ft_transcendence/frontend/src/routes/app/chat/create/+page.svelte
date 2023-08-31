<script lang="ts">
	import { goto } from '$app/navigation';
	import { jwt_cookie, userId42 } from '$lib/stores';

	let roomName: string = '';
	let roomType: string = 'public';
	let password: string = '';

	const handleSubmit = async (event: any) => {
		if (password === '' && roomType == 'protected') {
			alert('Please enter a password');
			return;
		}
		event.preventDefault();
		if (roomType !== 'protected') password = '';
		if (roomName === '') {
			alert('Please enter a name');
			return;
		}
		/*
		 * Appel au Post du controller Chat qui va creer la Room dans la Db
		 */
		try {
			const response = await fetch(`/api/chat`, {
				method: 'POST',
				headers: {
					Authorization: `Bearer ${$jwt_cookie}`,
					'Content-Type': 'application/json'
				},
				body: JSON.stringify({
					roomName,
					roomType,
					password,
					iddata: $userId42
				})
			});
			if (response.ok) {
				roomName = '';
				roomType = 'public';
				password = '';
				goto('/app/chat');
			} else {
				console.error('Failed to create room');
				// handle error
			}
			// Reset les valeurs du formulaure
		} catch {
			console.error('Failed to create Room');
		}
		//ici rediriger vers /chat/room_id?
		// toggleForm();
		// fetchRooms();
		// fetchOwnedRoom();
	};
</script>

<div class="rooms-create-content">
	<form on:submit={handleSubmit}>
		<div class="inputs">
			<label for="room-name"
				><h4>Room Name:</h4>
				<input type="text" id="room-name" bind:value={roomName} class="input-box" />
			</label>
		</div>
		<div class="inputs">
			<label for="room-type"
				><h4>Room Type:</h4>
				<select id="room-type" bind:value={roomType} class="input-box">
					<option value="public">Public</option>
					<option value="private">Private</option>
					<option value="protected">Protected</option>
				</select>
				{#if roomType === 'protected'}
					<br />
					<label for="password"
						><h4>Password:</h4>
						<input type="password" id="password" bind:value={password} class="input-box" />
					</label>
				{/if}
			</label>
		</div>
		<div class="btn-submit-room-wrapper">
			<button type="submit" class="btn-submit">Create</button>
		</div>
	</form>
</div>
<div class="void-content" />

<style>
	.rooms-create-content {
		width: 100%;
		background-color: #efefef;
		color: black;
	}

	form {
		padding: 30px 100px;
	}

	h4 {
		text-align: left;
		font-weight: normal;
		font-size: 18px;
		text-transform: capitalize;
		margin-bottom: 10px;
	}

	.btn-submit-room-wrapper {
		text-align: center;
		margin: 30px 0;
	}

	.btn-submit {
		background-color: #3ab45c;
		border: none;
		color: white;
		padding: 15px 30px;
		text-decoration: none;
		font-size: larger;
		cursor: pointer;
		text-align: center;
		font-family: 'Oxanium';
	}

	.inputs {
		margin-bottom: 20px;
	}

	.input-box {
		padding: 5px 10px;
		border-radius: 0%;
		border: #dcdcdc 1px solid;
	}

	select {
		font-family: 'Oxanium';
	}

	.void-content {
		background-color: #404040;
		width: 30vw;
	}
</style>
