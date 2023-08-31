<script>
	import { page } from '$app/stores';
</script>

<div class="error">
	<h1>{$page.status}</h1>
	{#if $page.error}
		<h2>{$page.error.message}</h2>
	{/if}
</div>

<style>
	.error {
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
</style>
