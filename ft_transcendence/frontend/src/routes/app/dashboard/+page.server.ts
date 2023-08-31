import { redirect, error } from "@sveltejs/kit";
import { HOSTNAME } from '$env/static/private'

export async function load({ cookies , fetch }) {
	const authToken = cookies.get('jwt_cookie');
	const id42 = cookies.get('id42');
	// return {roomId: roomId}
	const url_api_history = `http://${HOSTNAME}:8080/api/dashboard/history/${id42}`;
	const url_api_stats = `http://${HOSTNAME}:8080/api/dashboard/stats/${id42}`;

	if (authToken === undefined) throw redirect(307, "/");
	const history = await fetch(url_api_history, {
				method: 'GET',
				headers: {
					'Authorization': `Bearer ${authToken}`
				}
			})
			.then(async (response) => {
				if (response.ok)
					return await response.json();
				else
					return response;
			})
			.catch((err) => {
				throw error(err.status, {
					message: err.message});
	});

	if (history && history.status)
		throw error(history.status, { message: history.statusText});

	const stats = await fetch(url_api_stats, {
			method: "GET",
			headers: {
				'Authorization': `Bearer ${authToken}`
			}
		}).then(async (res) => {
			if (res.ok)
				return await res.json()
			return res;
		}).catch((err) => {
			throw error(err.status, {
				message: err.message});
	})

	if (stats && stats.status)
		throw error(stats.status, { message: stats.statusText});

	return {
		history: history,
		stats: stats,
	}
}
