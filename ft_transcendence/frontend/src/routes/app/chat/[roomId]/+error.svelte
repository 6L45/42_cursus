<script>
	import { page } from '$app/stores';
</script>

<div class="error">
	<h1>{$page.status}</h1>
	{#if $page.error}
		<h2>{$page.error.message}</h2>
	{/if}
	<a href="/app/chat">go back</a>
</div>
<div class="chat-users-content" />

<style>
	.chat-users-content {
		background-color: #404040;
		width: 30vw;
	}

	.error {
		width: 100%;
		/* max-height: 60vh; */
		margin: 30px 0;
		text-align: center;
	}

	h1 {
		color: white;
		font-weight: bold;
		font-size: 25px;
	}

	h2 {
		color: lightgrey;
		font-weight: lighter;
		font-size: 15px;
		font-style: italic;
	}

	a {
		color: white;
		text-decoration: none;
		cursor: pointer;
	}
</style>
