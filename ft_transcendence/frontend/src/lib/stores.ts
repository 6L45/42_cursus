import { writable } from 'svelte/store';
import { browser } from '$app/environment';

interface User {
	name: string,
	id: number,	//id db
}

  interface Room {
	roomId: number;
	roomName: String;
  }
export let rooms = writable<Room[]>([]);
export let blockedUser = writable<User[]>([]);

/*
	pour set la value il faudras juste faire imgUser.set(value); au moment voulus
	bon site qui explique un peut la chose: https://rodneylab.com/using-local-storage-sveltekit/
*/
//----------------------------------------------------------------//
const persitedImg_path: string = browser ? localStorage.getItem('img_path') ?? "" : "";
export const img_path = writable(persitedImg_path);

img_path.subscribe((value: string) => {
	if (browser) {
		window.localStorage.setItem('img_path', value);
	}
})

// if initially img_path was not defined we define a default value
if (browser && window.localStorage.getItem('img_path') === undefined)
	img_path.set("/logo.jpeg")

//----------------------------------------------------------------//
const persitedUserId42: number = browser ? parseInt(localStorage.getItem('userId42') ?? 0, 10) : 0;
export const userId42 = writable(persitedUserId42);

userId42.subscribe((value: number) => {
    if (browser) {
        window.localStorage.setItem('userId42', value);
	}
})

//----------------------------------------------------------------//
const persitedUserId: number = browser ? parseInt(localStorage.getItem('userId') ?? 0, 10) : 0;
export const userId = writable(persitedUserId);

userId.subscribe((value: number) => {
    if (browser) {
        window.localStorage.setItem('userId', value);
	}
})
//----------------------------------------------------------------//
const persitedPage_shown: string = browser ? localStorage.getItem('page_shown') ?? "/" : "/";
export const page_shown = writable(persitedPage_shown);

page_shown.subscribe((value: string) => {
    if (browser) {
        window.localStorage.setItem('page_shown', value);
	}
})
//----------------------------------------------------------------//
const persitedClientName: string = browser ? localStorage.getItem('clientName') ?? "" : "";
export const clientName = writable(persitedClientName);

clientName.subscribe((value: string) => {
    if (browser) {
        window.localStorage.setItem('clientName', value);
	}
})
//----------------------------------------------------------------//
const persitedJwt_cookie: string = browser ? localStorage.getItem('jwt_cookie') ?? "" : "";
export const jwt_cookie = writable(persitedJwt_cookie);

jwt_cookie.subscribe((value: string) => {
    if (browser) {
        window.localStorage.setItem('jwt_cookie', value);
	}
})
//----------------------------------------------------------------//
const persistedGame_mode: string = browser ? localStorage.getItem('game_mode') ?? "" : "";
export const game_mode = writable(persistedGame_mode);

game_mode.subscribe((value: string) => {
    if (browser) {
        window.localStorage.setItem('game_mode', value);
	}
})
//----------------------------------------------------------------//