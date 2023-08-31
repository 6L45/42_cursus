import { redirect, error } from "@sveltejs/kit";
import { HOSTNAME } from '$env/static/private'

export async function load({ cookies, params, fetch }) {
	const authToken = cookies.get('jwt_cookie');
	const roomId = params.roomId;
	// return {roomId: roomId}
	const url_api_message = `http://${HOSTNAME}:8080/api/chat/messages/${params.roomId}`;
	const url_api_members = `http://${HOSTNAME}:8080/api/chat/room/${params.roomId}`;
	const url_api_status = `http://${HOSTNAME}:8080/api/chat/room/${params.roomId}/status`;
	const url_api_blocked = `http://${HOSTNAME}:8080/api/chat/blocked`;
	const url_api_room_info = `http://${HOSTNAME}:8080/api/rooms/info/${params.roomId}`;

	if (authToken === undefined) throw redirect(307, "/");
	const members = await fetch(url_api_members, {
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

	if (members.status)
		throw error(members.status, { message: members.statusText});

	const status = await fetch(url_api_status, {
			method: 'GET',
			headers: {
				'Authorization': `Bearer ${authToken}`
			}
		})
		.then(async (response) => {
			if (response.ok)
				return await response.json();
			else
				return null;
		})
		.catch((err) => {
			throw error(err.status, {
				message: err.message});
	});

	if (status === null)
		throw error(401, { message: 'Unauthorized'});

	const messages = await fetch(url_api_message, {
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

	if (messages.status)
		throw error(messages.status, { message: messages.statusText});

	const blocked = await fetch(url_api_blocked, {
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

	if (blocked.status)
		throw error(blocked.status, { message: blocked.statusText});

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

	messages.reverse();

	return {
		roomId,
		messages: messages, 
		members: members,
		status : status.status,
		blocked: blocked,
		roomInfo: roomInfo,
	}
}
