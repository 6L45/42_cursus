<script lang="ts">
	import { PUBLIC_HOSTNAME } from '$env/static/public';
	import { goto } from '$app/navigation';
	import { client } from '$lib/gamesocket';
	import { clientName, img_path, jwt_cookie, userId } from '$lib/stores';
	import { onMount } from 'svelte';

	// let blocked_users = [{block_id: 3, block_name: "LeGugusQuiMeSaoule"},
	// {block_id: 4, block_name: "LautreGus"},
	// {block_id: 5, block_name: "LeTricheur"},
	// {block_id: 6, block_name: "LeSpammeur"},
	// 					];
	export let data;
	let DfaInfo = data.DfaInfo;
	let qrCodeImageUrl = '';

	let badUpdate = false;
	let indexBadUpdate = 0;
	let new_img_data: any;
	let fileInput: any = null;
	let files: any;

	let blocked_users: any = [];

	onMount(() => {
		fetchBlockedUsers();
	});
	async function fetchBlockedUsers() {
		try {
			const response = await fetch(`/api/dashboard/blockedusers`, {
				method: 'GET',
				headers: {
					Authorization: `Bearer ${$jwt_cookie}`
				}
			});
			if (response.status == 200) {
				let block_list = await response.json();
				blocked_users = block_list;
			} else console.error(response.status, response.statusText);
			return null;
		} catch (error) {
			console.error(error);
		}
	}

	async function submitForm() {
		const nameInput = document.getElementById('input-name') as HTMLInputElement;
		const fileInput = document.getElementById('file-upload') as HTMLInputElement;
		let data = new FormData();
		data.append('file', fileInput.files[0]);

		if (fileInput && fileInput.files && fileInput.files[0]) {
			try {
				const response = await fetch(`http://${PUBLIC_HOSTNAME}:8080/api/dashboard/update/${$userId}`,
					{
						method: 'POST',
						body: data,
						headers: {
							Authorization: `Bearer ${$jwt_cookie}`
						},
					}
				);
				if (!response.ok) console.error('failed to update properly the avatar');
			} catch (error) {
				console.error(error);
			}
		}

		if (nameInput) {
			try {
				const response = await fetch(
					`http://${PUBLIC_HOSTNAME}:8080/api/dashboard/updateName/${$userId}`,
					{
						method: 'POST',
						body: nameInput.value,
						headers: {
							Authorization: `Bearer ${$jwt_cookie}`
						},
					}
				);
				if (!response.ok) console.log('failed to update the name');
			} catch (error) {
				console.error(error);
			}
		}
		goto('/app/dashboard');
	}

	//for previsualisation we extract file data
	function getBase64(image: any) {
		const reader = new FileReader();
		reader.readAsDataURL(image);
		reader.onload = (e) => {
			new_img_data = e.target.result;
		};
	}

	const unblockUser = async (unblockedId: number) => {
		const response = await fetch(`/api/chat/unblockUser`, {
			method: 'POST',
			headers: {
				'Content-Type': 'application/json',
				Authorization: `Bearer ${$jwt_cookie}`
			},
			body: JSON.stringify({
				unblockedId: unblockedId,
				iddata: $userId
			})
		});
		if (response.ok) {
			blocked_users = blocked_users.filter((user: any) => user.client2.id !== unblockedId);
		} else {
			console.error('Failed to unblock user');
		}
	};

	async function toggleDFAState() {
		DfaInfo.dfa = !DfaInfo.dfa;
		try {
			const response = await fetch(`/api/auth/2fa`, {
				method: 'POST',
				headers: {
					'Content-Type': 'application/json',
					Authorization: `Bearer ${$jwt_cookie}`
				},
				body: JSON.stringify({
					isDFAActive: DfaInfo.dfa
				})
			});
			if (response.ok) {
				data = await response.json();
				qrCodeImageUrl = data.qrCodeImageUrl;
			} else {
				console.error('Failed to get 2fa for the user');
			}
			// const response = await axios.post(`/api/auth/2fa/${$userId}`, { DfaInfo.dfa });
			// qrCodeImageUrl = response.data.qrCodeImageUrl;
		} catch (error) {
			console.error('Failed to update DFA status:', error);
		}
	}

	async function toggleDFAState2() {
		DfaInfo.dfa = !DfaInfo.dfa;
		qrCodeImageUrl = '';

		try {
			const response = await fetch(`/api/auth/2fastatus`, {
				method: 'POST',
				headers: {
					'Content-Type': 'application/json',
					Authorization: `Bearer ${$jwt_cookie}`
				},
				body: JSON.stringify({
					isDFAActive: DfaInfo.dfa
				})
			});
			if (response.ok) {
				return;
			} else {
				console.error('Failed to update 2fa for the user');
			}
		} catch (error) {
			console.error('Failed to update DFA status:', error);
		}
	}

	async function generateQrCode() {
		try {
			const response = await fetch(`/api/auth/2fa/code`, {
				method: 'GET',
				headers: {
					'Content-Type': 'application/json',
					Authorization: `Bearer ${$jwt_cookie}`
				}
			});
			if (response.ok) {
				data = await response.json();
				qrCodeImageUrl = data.qrCodeImageUrl;
			} else {
				console.error('Failed to get code for dfa');
			}
			// const response = await axios.post(`/api/auth/2fa/${$userId}`, { DfaInfo.dfa });
			// qrCodeImageUrl = response.data.qrCodeImageUrl;
		} catch (error) {
			console.error('Failed to get code for DFA:', error);
		}
	}
</script>

<div class="settings-wrap">
	<div class="settings-data">
		<div class="inputs">
			<label
				><h4>Name :</h4>
				<input id="input-name" name="input-name" type="text" placeholder={$clientName} />
			</label>
		</div>
		<div class="inputs inputs-avatar">
			<h4>Avatar :</h4>
			<label>
				{#if fileInput && fileInput.value != ''}
					<div class="selected-img">
						<img src={new_img_data} alt="logo" class="rick" /><button
							class="btn-image-delete-selected"
							on:click={() => (fileInput.value = '')}>x</button
						>
					</div>
				{:else if $img_path}
					<img src={$img_path} alt="logo" class="rick" />
				{:else}
					<img src="/logo.jpeg" alt="logo" class="rick" />
				{/if}
				<p>
					<input
						type="file"
						accept=".png,.jpg"
						id="file-upload"
						name="file-upload"
						bind:this={fileInput}
						bind:files
						on:change={() => getBase64(files[0])}
					/>
				</p>
				<!-- <input type="file" name="file-upload" id="file-upload"> -->
			</label>
		</div>
		<div class="btn-wrap"><button class="btn-save" on:click={submitForm}>SAVE</button></div>
		<!-- <div class="inputs">
			<h4>Dfa</h4>
			{#if DfaInfo.dfa}
				<p>On</p>
				<label class="switch">
					<input type="checkbox" on:click={toggleDFAState} checked/>
					<span class="slider round"></span>
				</label>
			{:else}
				<p>Off</p>
				<label class="switch">
					<input type="checkbox" on:click={toggleDFAState} />
					<span class="slider round"></span>
				</label>
			{/if}
			{#if qrCodeImageUrl}
				<div class="qrcode-wrapper">
					<img class="img-qrcode" src={qrCodeImageUrl} alt="QR Code" />
				</div>
			{/if}
		</div> -->
		<div class="inputs">
			<h4>Dfa :</h4>
			<p>Using Google - Autheticator</p>
			{#if DfaInfo.dfa}
				<p>On</p>
				<div class="btn-wrap">
					<button class="btn-save" on:click={toggleDFAState2}> Desactivate </button>
				</div>
			{:else if !DfaInfo.dfa && qrCodeImageUrl === ''}
				<p>Off</p>
				<div class="btn-wrap">
					<button class="btn-save" on:click={generateQrCode}> Generate Code </button>
				</div>
			{:else}
				<p>Off</p>
				<div class="qrcode-wrapper">
					<img class="img-qrcode" src={qrCodeImageUrl} alt="QR Code" />
				</div>
				<p class="warning-text">
					<strong
						>do not activate dfa if you didn't took the qrCode otherwise you will never be able to
						connect.</strong
					>
				</p>
				<div class="btn-wrap">
					<button class="btn-save" on:click={toggleDFAState2}> Activate </button>
					<button class="btn-save" on:click={() => (qrCodeImageUrl = '')}> Abort </button>
				</div>
			{/if}
		</div>
	</div>
	<div class="block-list">
		<h3>Blocked Users :</h3>
		<ul>
			{#each blocked_users as blocked_user}
				<li>
					<button class="btn-unblock" on:click={() => unblockUser(blocked_user.client2.id)}
						>Unblock</button
					>
					{blocked_user.client2.name}
				</li>
			{/each}
		</ul>
	</div>
</div>

<style>
	.settings-wrap {
		background-color: #efefef;
		margin: 30px 100px;
		padding: 50px;
		display: flex;
		flex-direction: row;
		justify-content: space-evenly;
	}

	.settings-data {
		width: 50%;
	}

	h4 {
		font-weight: normal;
		font-size: 18px;
		text-transform: capitalize;
		margin-bottom: 10px;
	}

	.inputs {
		margin-bottom: 20px;
	}

	#input-name {
		padding: 5px 10px;
		border-radius: 0%;
		border: #dcdcdc 1px solid;
		text-align: end;
	}
	#input-name::placeholder {
		text-align: end;
	}

	.inputs-avatar {
		text-align: center;
	}

	h4 {
		text-align: left;
	}

	.rick {
		width: 90px;
		height: 90px;
		border-radius: 50%;
		/* margin-right: 20px; */
		object-fit: cover;
		/* box-shadow: 0 0 20px rgba(0, 255, 0, 0.5); */
	}

	.selected-img {
		position: relative;
	}

	.btn-image-delete-selected {
		position: absolute;
		top: 0;
		right: 0;
		border: none;
		background-color: #df0000;
		border-radius: 50%;
		color: white;
		cursor: pointer;
		font-size: 8px;
		font-weight: bold;
		font-family: 'Oxanium';
		width: 20px;
		height: 20px;
		padding: 5px;
	}

	.btn-wrap {
		text-align: center;
	}

	.btn-save {
		background-color: #3ab45c;
		padding: 15px 25px;
		color: white;
		border: none;
		cursor: pointer;
		text-transform: uppercase;
	}

	.block-list {
		border-left: #df0000;
	}

	.block-list h3 {
		font-weight: normal;
		font-size: 20px;
		text-align: center;
	}

	.block-list ul {
		list-style: none;
	}

	.block-list ul li {
		font-size: larger;
		margin-top: 15px;
	}

	.block-list ul li button {
		font-family: 'Oxanium';
		border: none;
		font-weight: lighter;
		background-color: #df0000;
		color: white;
		padding: 10px 20px;
		margin-right: 10px;
		cursor: pointer;
	}
	
	.warning-text {
		color: red;
	}

	.qrcode-wrapper {
		text-align: center;
		padding: 15px;
	}
</style>
