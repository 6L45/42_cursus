import { error, redirect } from '@sveltejs/kit'; 
import { HOSTNAME } from '$env/static/private'

let hostname = process.env.HOSTNAME
	// @ts-ignore
	async function fetchAllRoomMembers(id42, roomName, fetch, authToken)
	{
		try
		{
			const response = await fetch(`http://${HOSTNAME}:8080/api/rooms/allMemberwithStatus/${id42}/${roomName}`, {
				method: 'GET',
				headers: {
					Authorization: `Bearer ${authToken}`
				}
			});
			if (response.ok) {
				let res =  await response.json();
				return res;
			}
			else {
				return response;
			}
		}
		catch (error) {
			console.error(error);
		}
	}

	async function fetchRoomId(roomName, fetch, authToken)
	{
		try {
			const response = await fetch(`http://${HOSTNAME}:8080/api/rooms/getRoomId/${roomName}`, {
				method: 'GET',
				headers: {
					Authorization: `Bearer ${authToken}`
				}
			});
			if (response.ok){
				let res =  await response.json();
				return res;
			}
			else {
				return response;
			}
		}
		catch (error) {
			console.error(error);
		}
	}

export async function load( {cookies, fetch, params} ) {
	const authToken = cookies.get('jwt_cookie');
	
	if (authToken === undefined)
		throw redirect(307, "/login");

	const id42 = cookies.get('id42');
	const roomName = params.salon;
	let ret = await fetchAllRoomMembers(id42, roomName, fetch, authToken)
	let roomid = await fetchRoomId(roomName, fetch, authToken);
	if (ret instanceof Response)
	{
		throw error(ret.status, {
			message: ret.statusText
		});
	}
	if (roomid instanceof Response)
	{
		throw error(roomid.status, {
			message: roomid.statusText
		})
	}

	return {
		members: ret,
		room: params.salon,
		authToken
	}
}