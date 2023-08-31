<script lang="ts">
	import { goto } from '$app/navigation';
	import { jwt_cookie, img_path, clientName, userId, userId42 } from '$lib/stores.js';

	$jwt_cookie = '';
	$img_path = '';
	$clientName = '';
	$userId42 = 0;
	$userId = 0;
</script>

<center>
	<div>
		<center><h1 style="color: white;">Goodbye :'&#40;</h1></center>
		<center><h3 style="color: white;">We gonna miss U</h3></center>
		<center><h3 style="color: white;">My heart Just Broke</h3></center>
		<center><h3 style="color: white;">But OK, i understand</h3></center>
		<center><h3 style="color: white;">It's not you, it's me...</h3></center>
		<center><h3 style="color: white;">I hope we can still be friends</h3></center>
		<center><h3 style="color: white;">(ㅠ﹏ㅠ)</h3></center>
	</div>
	<br />
	<br />
	<br />
	<br />
	<center>
		<button class="round-button" on:click={() => goto('/')}
			>Ok I'm sorry<br />I miss u. I'm coming back<br />Please forgive me</button
		>
	</center>
</center>

<style>
	.round-button {
		border: none;
		background-color: #2ccc00;
		border-radius: 20px;
		color: white;
		font-size: 16px;
		font-weight: bold;
		cursor: pointer;
		outline: none;
		padding: 10px 20px;
		margin: 10px;
		transition: background-color 0.3s ease;
	}
</style>
