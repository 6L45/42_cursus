<script lang="ts">
	import { onMount } from 'svelte';
	import { img_path, jwt_cookie, clientName, userId } from '$lib/stores';
	import { goto } from '$app/navigation';
	import Invitation from '$lib/invitation.svelte';
	import { PUBLIC_HOSTNAME } from '$env/static/public';

	export let data: any;
	let target = data.target;
	let stats = data.stats;
	let match_history = data.history;

	onMount(() => {});

	async function getImage(id: number) {
		try {
			const response = await fetch(`http://${PUBLIC_HOSTNAME}:8080/api/dashboard/avatar/${id}`, {
				method: 'GET',
				headers: {
					Authorization: `Bearer ${$jwt_cookie}`
				}
			});
			if (response.ok) {
				let client = await response.json();
				return client;
			} else console.error('avatar');
		} catch (error) {
			console.error('avatar', error);
		}
	}

	const blockUser = async () => {
		const response = await fetch(`/api/chat/blockUser`, {
			method: 'POST',
			headers: {
				'Content-Type': 'application/json',
				Authorization: `Bearer ${$jwt_cookie}`
			},
			body: JSON.stringify({
				blockedId: target.id,
				iddata: $userId
			})
		});
		if (response.ok) {
			goto('/app/dashboard');
		} else {
			console.error('Failed to block user');
		}
	};

	const addFriend = async () => {
		const response = await fetch(`/api/chat/addFriend`, {
			method: 'POST',
			headers: {
				'Content-Type': 'application/json',
				Authorization: `Bearer ${$jwt_cookie}`
			},
			body: JSON.stringify({
				newFriendId: target.id,
				iddata: $userId
			})
		});
		if (response.ok) {
			target.client1 = [{ status: 0 }];
			target.client2 = [{ status: 0 }];
		} else console.error(response.status, response.statusText);
	};

	async function deleteFriendship() {
		try {
			const response = await fetch(`/api/dashboard/supprFriendship/${target.id}`, {
				method: 'POST',
				headers: {
					Authorization: `Bearer ${$jwt_cookie}`
				}
			});
			if (response.ok) {
				target.client1 = [];
				target.client2 = [];
			} else {
				console.error('failed to erase friendshipe you re in forever');
			}
		} catch (error) {
			console.error(error);
		}
	}

	const sendMsg = async () => {
		try {
			const response = await fetch(`/api/chat/sendMsg`, {
				method: 'POST',
				headers: {
					'Content-Type': 'application/json',
					Authorization: `Bearer ${$jwt_cookie}`
				},
				body: JSON.stringify({
					newFriendId: target.id,
					iddata: $userId
				})
			});
			if (response.ok) {
				const resolve = await response.json();
				goto(`/app/chat/${resolve.roomId}`);
			} else {
				console.error('Failed to create one to one room');
			}
		} catch (err) {
			console.error('Failed to create one to one room');
		}
	};
</script>

<main class="main_body">
	<div class="profile-container">
		{#if target}
			<img src={target.img} alt="logo" class="rick" />
			{#if target.client1.length !== 0 && target.client1[0].status === 0}
				<p class="friend-info">Friend</p>
			{/if}
			<h2>{target.name}</h2>
			<div class="stats">
				{#if stats}
					<p>victory - {stats.won}</p>
					<p>loses - {stats.played - stats.won}</p>
					{#if stats.played !== 0}
						<p>ratio - {(stats.won * 100) / stats.played}%</p>
					{/if}
					<p>game points - {stats.won * 5}</p>
				{/if}
			</div>
			<div class="control-panel">
				{#if target.client1.length !== 0 && target.client1[0].status === 0}
					<button class="hovertext" data-hover="remove friendship" on:click={deleteFriendship}
						>🙏</button
					>
				{:else}
					<button class="hovertext" data-hover="add to friendlist" on:click={addFriend}>🙏</button>
				{/if}
				<button class="hovertext" data-hover="block" on:click={blockUser}>❌</button>
				<button class="hovertext" data-hover="send a message" on:click={sendMsg}>💬</button>
				<Invitation opponent_id={target.id} where="" />
			</div>
		{/if}
	</div>
	<div class="list-container">
		<h3>Match History</h3>
		{#if match_history.length !== 0}
			<ul>
				{#each match_history as match}
					<li class="mh-list">
						<div class="mh-opponent">
							{#if match.client1.id === target.id}
								<img src={target.img} alt="logo" class="mh-img" />
							{:else}
								{#await getImage(match.client1.id)}
									<img src="/logo.jpeg" alt="logo" class="mh-img" />
								{:then user}
									<img src={user.img} alt="logo" class="mh-img" />
								{/await}
							{/if}
							<p>{match.client1.name}</p>
						</div>
						<div class="mh-score">
							<p
								class:winScore={match.persScore === 4 && match.client1.id === target.id}
								class:looseScore={match.persScore !== 4 && match.client1.id === target.id}
							>
								{match.persScore}
							</p>
							<p>-</p>
							<p
								class:winScore={match.vsScore === 4 && match.client2.id === target.id}
								class:looseScore={match.vsScore !== 4 && match.client2.id === target.id}
							>
								{match.vsScore}
							</p>
						</div>
						<div class="mh-opponent">
							<p>{match.client2.name}</p>
							{#if match.client2.id === target.id}
								<img src={target.img} alt="logo" class="mh-img" />
							{:else}
								{#await getImage(match.client2.id)}
									<img src="/logo.jpeg" alt="logo" class="mh-img" />
								{:then user}
									<img src={user.img} alt="logo" class="mh-img" />
								{/await}
							{/if}
						</div>
					</li>
				{/each}
			</ul>
		{:else}
			<p class="msg-void-mh">You didn't play any game for the moment</p>
		{/if}
	</div>
</main>

<style>
	.main_body {
		width: 100%;
		padding: 20px 0;
		display: flex;
		flex-direction: column;
		align-items: center;
	}

	.profile-container {
		padding: 30px 50px;
		background-color: #404040;
		max-width: 300px;
		border-radius: 8px;
		display: flex;
		flex-direction: column;
		justify-content: center;
		align-items: center;
		text-align: center;
		color: white;
		font-size: 20px;
	}

	.friend-info {
		color: #30ef00;
		text-transform: lowercase;
		font-size: 15px;
	}

	.control-panel {
		text-align: center;
	}

	.control-panel button {
		text-align: center;
		border: none;
		cursor: pointer;
		background: none;
	}

	.hovertext {
		position: relative;
		border-bottom: 1px dotted black;
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

	h2 {
		font-weight: normal;
		font-size: 20px;
	}

	.rick {
		width: 150px;
		height: 150px;
		border-radius: 50%;
		/* margin-right: 20px; */
		object-fit: cover;
		/* box-shadow: 0 0 20px rgba(0, 255, 0, 0.5); */
	}

	.list-container {
		padding: 50px 50px;
		border-radius: 8px;
		color: white;
		width: 100%;
		max-width: 800px;
	}

	.list-container h3 {
		font-weight: normal;
		font-size: 20px;
		text-align: center;
	}

	.list-container ul {
		margin: 0;
		padding: 0;
	}

	.msg-void-mh {
		color: white;
		font-style: italic;
		text-align: center;
		font-weight: lighter;
		padding: 50px;
	}

	.mh-list {
		background-color: #404040;
		text-decoration: none;
		list-style: none;
		display: flex;
		flex-direction: row;
		justify-content: space-between;
		margin: 15px 50px;
		padding: 10px 30px;
		border-radius: 5px;
	}

	.mh-img {
		width: 25px;
		height: 25px;
		border-radius: 50%;
		/* margin-right: 20px; */
		object-fit: cover;
		/* box-shadow: 0 0 20px rgba(0, 255, 0, 0.5); */
	}

	.mh-opponent {
		display: flex;
		flex-direction: row;
		align-items: center;
	}

	.mh-opponent p {
		margin: 0 20px;
	}

	.mh-score {
		display: flex;
		flex-direction: row;
		justify-content: space-around;
		align-items: center;
		width: 30%;
	}

	.winScore {
		color: #30ef00;
	}

	.looseScore {
		color: #ef0000;
	}

</style>
