import { error, redirect } from "@sveltejs/kit";
import { HOSTNAME } from "$env/static/private";

export async function load({ cookies, fetch, params }) {
	const authToken = cookies.get('jwt_cookie');
	const id42 = cookies.get('id42');

	const url_api_target = `http://${HOSTNAME}:8080/api/dashboard/getTargetWithRelation/${params.userName}`;
	
	if (authToken === undefined) throw redirect(307, "/");
	
	const target =  await fetch(url_api_target, {
		method: "GET",
		headers: {
			'Authorization': `Bearer ${authToken}`
		}
	}).then(async (res) => {
		if (res.ok)
			return await res.json();
		else
			return res;
	}).catch((err) => {
		throw error(err.status, {
			message: err.message});
	});
	//if fetch failed
	if (target && target.status)
		throw error(target.status, { message: target.statusText});
		
	if (Number(target.id42) === Number(id42))
		throw redirect(307, "/app/dashboard");
	
	if (target && (target.client1.length != 0 && target.client1[0].status == 1) 
		|| (target.client2.length != 0 && target.client2[0].status == 1))
		throw redirect(307, "/app/dashboard");

	const url_api_history = `http://${HOSTNAME}:8080/api/dashboard/history/${target.id42}`;
	const url_api_stats = `http://${HOSTNAME}:8080/api/dashboard/stats/${target.id42}`;
		
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
				return await res.json();
			else
				return res;
		}).catch((err) => {
			throw error(err.status, {
				message: err.message});
	})

	if (stats && stats.status)
		throw error(stats.status, { message: stats.statusText});

	return {
		target: target,
		stats: stats,
		history: history,
	}
}