<script lang="ts">
	import { jwt_cookie, img_path, userId42 } from '$lib/stores';
	import { onMount } from 'svelte';
	import { goto } from '$app/navigation';
	// import { error } from '@sveltejs/kit';

	export let data: any; //exported data is the cookie

	onMount(async () => {
		//on stock le cookie dans un local Storage pour y avoir plus facilement acces
		jwt_cookie.set(data.myJwtCookie);
		userId42.set(data.myid42);

		// Premier cas : on a pas de cookie le local Storage est undefined et on attent que le User clique sur SignIn qui va lui permettre de faire la procedure d'auth et de recuperer un cookie

		// Deuxieme cas : on a un cookie. On verifie que la connexion a l.api fonctionne grace a ce cookie
		//                  Si le retour est ok on redirige le user dans l'application
		//                  Si le retour est ko cela veut dire qu'on a un mauvais cookie (expire ou bien un pirate que sait-je) et donc on attend quil sign in pour reprendre un nouveau cookie
		if ($jwt_cookie && $jwt_cookie != null && $jwt_cookie != 'null') {
			try {
				const connect = await fetch(`/api/dashboard`, {
					method: 'GET',
					headers: {
						Authorization: `Bearer ${$jwt_cookie}`
					}
				});
				if (connect.status == 200) {
					goto('/app/dashboard');
				} else {
					//connection refusee a cause dun mauvai/vieux/invalid/corrompu cookie
					console.error('Invalid cookie');
					goto('/');
				}
			} catch (error) {
				console.error("fetching in '/' :", error);
			}
		}
	});
</script>

<div class="screen">
	<h1>THE PONG</h1>
	<!-- <h2>Hello traveler, to start you pong journey please use the button bellow</h2> -->
	<a href={data.url} class="login-button"> Sign in </a>
</div>

<style>
	.screen {
		height: 100vh;
		width: 100vw;
		background: rgb(23, 23, 23);
		background: linear-gradient(135deg, rgba(23, 23, 23, 1) 0%, rgba(23, 23, 23, 0) 100%);
		display: flex;
		flex-direction: column;
		justify-content: center;
	}

	h1 {
		text-align: center;
		margin-bottom: 20px;
		text-transform: uppercase;
		font-size: 64px;
		color: #fff;
	}

	.login-button {
		display: block;
		width: 100%;
		max-width: 240px;
		padding: 16px;
		font-size: 16px;
		font-weight: bold;
		text-align: center;
		text-decoration: none;
		color: #fff;
		background-color: #df0000;
		/* border-radius: 8px; */
		transition: background-color 0.2s ease-in-out;
		margin: 30px auto;
	}

	.login-button:hover {
		background-color: #00cc1b;
	}
</style>
