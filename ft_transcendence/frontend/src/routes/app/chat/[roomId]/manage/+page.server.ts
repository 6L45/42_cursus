import { redirect, error } from "@sveltejs/kit";
import { HOSTNAME } from '$env/static/private'
export async function load({ cookies, params, fetch }) {
	const authToken = cookies.get('jwt_cookie');
	const roomId = params.roomId;
	// return {roomId: roomId}
	const url_api_remplacement_list = `http://${HOSTNAME}:8080/api/rooms/replacementList/${params.roomId}`;
	const url_api_room_info = `http://${HOSTNAME}:8080/api/rooms/info/${params.roomId}`;

	if (authToken === undefined) throw redirect(307, "/");

	const replacementList = await fetch(url_api_remplacement_list, {
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

	if (replacementList && replacementList.status)
		throw error(replacementList.status, { message: replacementList.statusText});

	const roomInfo = await fetch(url_api_room_info, {
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

	if (roomInfo && roomInfo.status)
		throw error(roomInfo.status, { message: roomInfo.statusText});

	return {
		roomId,
		replacementList: replacementList,
		roomInfo: roomInfo,
	}
}
