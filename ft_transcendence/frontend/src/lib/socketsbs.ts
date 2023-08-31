import { io } from 'socket.io-client'
import { get, writable } from 'svelte/store';
import { userId42, rooms, userId, jwt_cookie, blockedUser} from '$lib/stores';
import { PUBLIC_HOSTNAME } from '$env/static/public';

// Socket chat
export let socket;//: Socket<DefaultEventsMap, DefaultEventsMap> | undefined = undefined;;

// value of not readed messages
// export let msgCount = 0;



// export let updateCount = () =>
// {
// 	let count = 0;
// 	get(rooms).forEach(element => {
// 			count += element.newMsgCount;
// 	});
// 	msgCount = count;
// }

export let initializeSocket = () => {
//   socketData = await data;
//   if (!socketData)
//   	return;
	socket = io(PUBLIC_HOSTNAME +':3000/chat', {path: '/chatsockets'});//, auth: {token: }});
  	socket.emit('whoAmI', get(userId));
//   socket.game = io(hostname+':3000/game', {path: '/gamesockets'});//, auth: {token: }});
	
  	// await reloadRooms();
	// socket.on('reloadrooms', reloadRooms);
	// defineSocketEvents();
}

// export async function reloadRooms() {
// 	console.log("reload here");
// 	let loadedRooms = await fetchRoomData();
// 	rooms.set(loadedRooms);
// 	console.log(loadedRooms);
// 	connectToRooms();
// 	fetchBlockedData();
// }

// export function getSocket() {
//   return socket;
// }

// export let defineSocketEvents = () =>
// {
// 	socket.on('serverAlertToChat', newMessage);
// 	// socket.on('clientRefreshRooms', reloadRooms);
	
// }

// export let deleteSocketEvents = () =>
// {
// 	socket.off('serverAlertToChat', newMessage);
// }

// export let defineGameSocketEvents = () =>
// {
// 	socket.game.on('testSeverToClient', (data) => {
// 	});
// 	socket.game.on('mvtpad', (data) => {

// 	});
// }

// let newMessage = (msg) =>
// {
// 	if (! isBlockedUser(msg.sender_id))
// 		add_alert_On(msg.channel);
// }

// export let isBlockedUser = (user_id) =>
// {
// 	let blocked = false;
// 	get(blockedUser).forEach((el) => {
// 		if (el.id == user_id)
// 			blocked = true;
// 	});
// 	return blocked;
// }

// export let add_alert_On = (id) =>
// {
// 	let trythis = get(rooms);
// 	trythis = trythis.map((item) => 
// 	{
// 		if (item.roomId == id)
// 			return { ...item, newMsgCount: item.newMsgCount + 1 };
// 		return (item);
// 	});
// 	rooms.set(trythis);
// 	updateCount()
// }

// // @ts-ignore
// export let deleteAlertOn = (roomId) =>
// {
// 	let roomsGet = get(rooms);
// 	roomsGet = roomsGet.map((item) => 
// 	{
// 		if (item.roomId == roomId)
// 			return { ...item, newMsgCount: 0 };
// 		return (item);
// 	});
// 	rooms.set(roomsGet);
// 	updateCount();
// }

// let connectToRooms = () => {
// 	get(rooms).forEach((room) => {
// 		socket.emit('joinChannel', String(room.roomId));
// 	});
// }

// async function fetchRoomData() {
// 	let curr_rooms = get(rooms);
// 	try {
// 		const response = await fetch(`/api/chat`, {
// 			method: 'GET',
// 			headers: {
// 				'Authorization': `Bearer ${get(jwt_cookie)}`
// 			}
// 		});
// 		if (response.status == 200)
// 		{
// 			let tmp_rooms = await response.json();
// 			tmp_rooms = tmp_rooms.map((el) => {
// 				let item = curr_rooms.find((room) => (room.roomId == el.roomId));
// 				if (item == undefined)
// 					return { ...el, newMsgCount: 0 };
// 				return (item);
// 			});
// 			return tmp_rooms;
// 		}
// 		else
// 			console.error(response.status, response.statusText);
// 		return null;
// 	}
// 	catch (error) {
// 		console.error(error);
// 	}
// }

// async function fetchBlockedData() {
// 	try {
// 		const response = await fetch(`/api/chat/blocked`, {
// 			method: 'GET',
// 			headers: {
// 				'Authorization': `Bearer ${get(jwt_cookie)}`
// 			}
// 		});
// 		if (response.status == 200)
// 		{
// 			let resjson = await response.json()
// 			// blocked_users.set(resjson);
// 			// // or
// 			// return blocked_users;
// 		}
// 		else
// 			console.error(response.status, response.statusText);
// 		return null;
// 	}
// 	catch (error) {
// 		console.error(error);
// 	}
// }
