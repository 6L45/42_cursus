import { redirect, error } from "@sveltejs/kit";
import { HOSTNAME } from "$env/static/private";

export async function load({ cookies, fetch }) {
	const authToken = cookies.get('jwt_cookie');
	// return {roomId: roomId}
	const url_api_2fa = `http://${HOSTNAME}:8080/api/auth/2fa`;

	if (authToken === undefined) throw redirect(307, "/");
	const DfaInfo = await fetch(url_api_2fa, {
				method: 'GET',
				headers: {
					'Authorization': `Bearer ${authToken}`
				}
			})
			.then(async (response) => {
				if (response.ok)
				{
					let resolve = await response.json();
					return resolve;
				}
				else
					return response;
			})
			.catch((err) => {
				throw error(err.status, {
					message: err.message});
	});

	if (DfaInfo.status)
		throw error(DfaInfo.status, { message: DfaInfo.statusText});

	return {
		DfaInfo: DfaInfo,
	}
}
