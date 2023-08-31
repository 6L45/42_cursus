import { Client } from "colyseus.js";
import { socket } from '$lib/socketsbs';
import { userId } from "$lib/stores";
import { get, writable } from 'svelte/store';

export let client: any = null;

export let roomData: any;


export async function StartPlayProcess(opponent_id: number)
{
    //connectClientToColyseus();
    await createGame();
    inviteToPlay(opponent_id);
}

export let connectClientToColyseus = () =>
{
    client = new Client("ws://" + location.hostname + ":3001/ws");
}

async function createGame()
{
    roomData = await client?.create("my_room", {id: get(userId)});
}

export async function joinGame(secret: string)
{
    roomData = await client?.joinById(secret, {id: get(userId)});
}

export function resetroomData () {
    roomData = null;
}

let  inviteToPlay = (opponent_id: number) =>
{
    socket.emit('inviteToPlay', {player_id: get(userId), opponent_id: opponent_id, secret: roomData.id});
}