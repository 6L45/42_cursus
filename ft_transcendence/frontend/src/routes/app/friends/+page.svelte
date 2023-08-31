<script lang="ts">
	import ConnectStatus from '$lib/connectStatus.svelte';
	import Invitation from '$lib/invitation.svelte';

	export let data: any;
	let fl = data.fl;
</script>

<div class="fl-wrapper">
	{#if fl.length !== 0}
		<ul>
			{#each fl as friend}
				<li class="fl-friend">
					<div class="fl-data">
						<img src={friend.client.img} alt="logo" class="fl-img" />
						<a href="/app/dashboard/{friend.client.name}" class="fl-name">{friend.client.name}</a>
						<ConnectStatus userId={friend.client.id} />
					</div>
					<div class="btn-play-wrap">
						<Invitation opponent_id={friend.client.id} where="friendlist" />
					</div>
				</li>
			{/each}
		</ul>
	{:else}
		<p class="msg-void-fl">You don't have friends for the moment</p>
	{/if}
</div>

<style>
	.msg-void-fl {
		color: white;
		font-style: italic;
		text-align: center;
		font-weight: lighter;
		padding: 50px;
	}

	ul {
		margin: 0;
		padding: 40px 0;
	}

	li {
		text-decoration: none;
	}

	.fl-wrapper {
		max-width: 800px;
		margin: 0 auto;
	}

	.fl-friend {
		background-color: #404040;
		border-radius: 10px;
		display: flex;
		flex-direction: row;
		justify-content: space-between;
		margin: 20px;
		padding: 10px 40px;
	}

	.fl-data {
		display: flex;
		flex-direction: row;
		justify-content: space-between;
		min-width: 30%;
		color: white;
		align-items: center;
	}

	.fl-name {
		text-decoration: none;
		margin-right: 10px;
		color: white;
		cursor: pointer;
	}

	.fl-img {
		width: 50px;
		height: 50px;
		border-radius: 50%;
		object-fit: cover;
		margin-right: 10px;
	}

	.btn-play-wrap {
		display: flex;
		align-items: center;
	}
</style>
