<script>
	/*
		This is just a default page when no chat is selected
	*/
	import { onMount } from 'svelte';

	let messages = [];

	onMount(async () => {
		// const response = await fetch('/api/chat/messages/1');
		// messages = await response.json();
	});
</script>

<div class="chat-content">
	<p class="info">no room selected</p>
</div>
<div class="chat-users-content" />

<style>
	.chat-content {
		width: 100%;
		/* max-height: 60vh; */
		margin: 30px 0;
	}

	.chat-users-content {
		background-color: #404040;
		width: 30vw;
	}

	.info {
		width: 100%;
		color: gray;
		text-align: center;
	}
</style>
