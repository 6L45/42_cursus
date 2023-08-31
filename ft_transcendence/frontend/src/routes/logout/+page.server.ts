/**
	load fonction ici va nous permettre de recuperer le cookie de lutilisateur.
	Le return permet de le recuperer en props dans page.svelte en route "/"
 */

import { error } from "@sveltejs/kit";

export async function load({ cookies }) {
	const authToken = cookies.get('jwt_cookie');

	const url_api_switchDfa = `http://localhost:8080/api/auth/2fa/logout`;

	const switchDfa = await fetch(url_api_switchDfa, {
			method: 'POST',
			headers: {
				'Authorization': `Bearer ${authToken}`
			}
		})
		.then(async (response) => {
			if (response.ok)
				return null;
			else
				return response;
		})
		.catch((err) => {
			throw error(err.status, {
				message: err.message});
	});

	if (switchDfa && switchDfa.status)
		throw error(switchDfa.status, { message: switchDfa.statusText});
	cookies.set('jwt_cookie', "");
	cookies.set('id42', "");
	// cookies.set('_intra_42_session_production', null);
	// cookies.set('user.id', null);
}
