<script lang="ts">
	import { goto } from '$app/navigation';
	import { jwt_cookie } from '$lib/stores';
	import { error } from '@sveltejs/kit';
	import { onMount, afterUpdate } from 'svelte';

	export let data: any;
	// export let id: number;
	// export let delTab: string;
	// export let roomId: number;

	let admins: any = data.replacementList.admins;
	let members: any = data.replacementList.members;
	let roomName: string = ''; //importer tout ça depuis le load (info-rooms)
	let roomType: string = 'public';
	let password: string = '';
	let owner_choice: any;
	let successor_id: number;

	if (data.roomInfo.secu === 1) roomType = 'protected';
	else if (data.roomInfo.secu === 2) roomType = 'private';

	onMount(async () => {});

	afterUpdate(() => {});

	let stayOption = 'stay'; // Default option is "and stay"

	async function resign(stay: boolean) {
		try {
			const response = await fetch(
				`/api/rooms/resign/${data.roomInfo.id}/${successor_id}/${stay}`,
				{
					method: 'POST',
					headers: {
						Authorization: `Bearer ${$jwt_cookie}`
					}
				}
			);
			if (response.ok) {
				return;
			} else {
				console.error('failed on resign');
			}
		} catch (error: any) {
			console.error('ERROR: falied on resign', error.message);
		}
	}

	async function eraseRoom() {
		let res = await fetch(`/api/rooms/delete/${data.roomInfo.id}`, {
			method: 'POST',
			headers: {
				Authorization: `Bearer ${$jwt_cookie}`
			}
		})
			.then(async (response) => {
				if (response.ok) await goto('/app/chat');
				else console.error('Unauthorised');
			})
			.catch((err) => {
				throw error(err.status, { message: err.statusText });
			});
	}

	const roomTypeDict: { [key: string]: number } = {
		public: 0,
		protected: 1,
		private: 2
	};

	const handleSubmit = async (event: any) => {
		let type: number = roomTypeDict[roomType];
		if (password === '' && roomType == 'protected' && data.roomInfo.secu !== 1) {
			alert('Please enter a password');
			return;
		}
		event.preventDefault();
		if (roomType !== 'protected') password = '';
		if (roomName === '') roomName = data.roomInfo.name;
		/*
		 * Appel au Post du controller Chat qui va creer la Room dans la Db
		 */
		// let roomDto = {name: roomName, secu: type, password}
		const response = await fetch(`/api/rooms/updateRoom/${data.roomInfo.id}`, {
			method: 'POST',
			headers: {
				Authorization: `Bearer ${$jwt_cookie}`,
				'Content-Type': 'application/json'
			},
			body: JSON.stringify({
				name: roomName,
				secu: type,
				password
			})
		});
		if (!response.ok) {
			alert('Failed to update room');
		}
		goto(`/app/chat/${data.roomInfo.id}`);
	};

	const handleOwnerSubmit = async (event: any) => {
		event.preventDefault();
		if (owner_choice == '') return;
		if (owner_choice === 'deleteroom') return eraseRoom();
		let stay = true;
		if (owner_choice === 'resignquit') stay = false;
		resign(stay);
		if (stay) goto(`/app/chat/${data.roomInfo.id}`);
		else goto(`/app/chat`);
	};
</script>

<div class="manage-wrapper">
	<div class="manage-block">
		<h3>Update your Room</h3>
		<form on:submit={handleSubmit}>
			<div class="inputs">
				<label for="room-name"
					><h4>Room Name:</h4>
					<input
						type="text"
						id="room-name"
						bind:value={roomName}
						placeholder={data.roomInfo.name}
						class="input-box"
					/>
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
				<button type="submit" class="btn-submit">Update</button>
			</div>
		</form>
	</div>
	<div class="manage-block">
		<form on:submit={handleOwnerSubmit}>
			<h3>Owner Option</h3>
			<label for="owner-choice">
				<select id="owher-choice" bind:value={owner_choice} class="input-box">
					<option disabled selected value> -- select an option -- </option>
					{#if (admins && admins.length !== 0) || (members && members.length !== 0)}
						<option value="resign">resign</option>
						<option value="resignquit">resign and quit</option>
					{/if}
					<option value="deleteroom">delete room</option>
				</select>
			</label>
			{#if owner_choice === 'resign' || owner_choice === 'resignquit'}
				<h3>Select the successor</h3>
				<label for="successor">
					<select id="successor" bind:value={successor_id} class="input-box">
						<option disabled selected value> -- select a successor -- </option>
						{#each admins as admin}
							<option value={admin.id}>💂{admin.name}</option>
						{/each}
						{#each members as member}
							<option value={member.id}>{member.name}</option>
						{/each}
					</select>
				</label>
			{/if}
			<div class="btn-submit-room-wrapper">
				<button type="submit" class="btn-submit">Confirm</button>
			</div>
		</form>
	</div>
</div>

<div class="chat-users-content" />

<style>
	.chat-users-content {
		background-color: #404040;
		width: 30vw;
	}

	.manage-wrapper {
		width: 100%;
		background-color: #efefef;
		color: black;
		text-align: center;
		padding: 30px 50px;
		overflow: scroll;
	}

	h3 {
		font-weight: normal;
	}

	form {
		text-align: center;
	}

	h4 {
		/* text-align: left; */
		font-weight: normal;
		font-size: 15px;
		text-transform: capitalize;
		margin-bottom: 8px;
	}

	.btn-submit-room-wrapper {
		text-align: center;
		margin: 30px 0;
	}

	.btn-submit {
		background-color: #3ab45c;
		border: none;
		color: white;
		padding: 10px 30px;
		text-decoration: none;
		font-size: 15px;
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
</style>
