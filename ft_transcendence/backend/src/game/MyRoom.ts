import { Room, Client, Delayed } from "colyseus";
import { createGameState, gameLoop } from "./MyGame";
import fetch from 'node-fetch';
import { captureRejectionSymbol } from "events";


const state: Record<string, any> = {};
let intervalId: NodeJS.Timer = null;


export class MyRoom extends Room<any> {
  maxClients = 2;
  clients: any;
  keystatusplayer1 = { keydown: 0, keyup: 0 };
  keystatusplayer2 = { keydown: 0, keyup: 0 };
  joueur1: string;
  joueur2: string;
  //public delayedInterval!: Delayed;
  // When room is initialized
  onCreate(options: any) {
    state[this.roomId] = createGameState();
    //this.setState(createGameState());
  }

  // Authorize client based on provided options before WebSocket handshake is complete
  /*onAuth (client: Client, options: any, request: http.IncomingMessage) { }*/

  // When client successfully join the room
  onJoin(client: Client, options: any, auth: any) {
    if(options.roomName == "matchMaking" || options.roomName == "my_room") {
      if (this.clients.length === 1) {
        state[this.roomId].user.id = +options.id;
        client.send("init", 1);
      }
      if (this.clients.length === 2) {
        // this.joueur2 = client.id;
        state[this.roomId].com.id = +options.id;
        client.send("init", 2);
        // client.send("init", 1); 
        this.emitgamestate();
      }
      this.onMessage("keydown38player1", () => {
        this.keystatusplayer1.keydown = 1;
      });
      this.onMessage("keydown38player2", () => {
        this.keystatusplayer2.keydown = 1;
      });
      this.onMessage("keydown40player1", () => {
        this.keystatusplayer1.keyup = 1;
      });
      this.onMessage("keydown40player2", () => {
        this.keystatusplayer2.keyup = 1;
      });
      this.onMessage("keyup38player1", () => {
        this.keystatusplayer1.keydown = 0;
      });
      this.onMessage("keyup38player2", () => {
        this.keystatusplayer2.keydown = 0;
      });
      this.onMessage("keyup40player1", () => {
        this.keystatusplayer1.keyup = 0;
      });
      this.onMessage("keyup40player2", () => {
        this.keystatusplayer2.keyup = 0;
      });
  }
  else {
    if (this.clients.length === 1) {
      state[this.roomId].user.id = +options.id;
      // client.send("init", 1);
    }
    if (this.clients.length === 2) {
      // this.joueur2 = client.id;
      state[this.roomId].com.id = +options.id;
      client.send("init", 1); 
      client.send("init", 2);
      this.emitgamestate();
    }
    this.onMessage("keydown38player1", () => {
      this.keystatusplayer1.keydown = 1;
    });
    this.onMessage("keydown38player2", () => {
      this.keystatusplayer2.keydown = 1;
    });
    this.onMessage("keydown40player1", () => {
      this.keystatusplayer1.keyup = 1;
    });
    this.onMessage("keydown40player2", () => {
      this.keystatusplayer2.keyup = 1;
    });
    this.onMessage("keyup38player1", () => {
      this.keystatusplayer1.keydown = 0;
    });
    this.onMessage("keyup38player2", () => {
      this.keystatusplayer2.keydown = 0;
    });
    this.onMessage("keyup40player1", () => {
      this.keystatusplayer1.keyup = 0;
    });
    this.onMessage("keyup40player2", () => {
      this.keystatusplayer2.keyup = 0;
    });
  }
    /*setInterval(() => {
      gameLoop(state[this.roomId]);
      if (this.keystatusplayer1.keydown == 1) {
        if (state[this.roomId].user.y > 0) {
          state[this.roomId].user.y -= 10;
        }
      }
      if (this.keystatusplayer1.keyup == 1) {
        if (state[this.roomId].user.y + 100 < 400) {
          state[this.roomId].user.y += 10;
        }
      }
      if (this.keystatusplayer2.keydown == 1) {
        if (state[this.roomId].com.y > 0) {
          state[this.roomId].com.y -= 10;
        }
      }
      if (this.keystatusplayer2.keyup == 1) {
        if (state[this.roomId].com.y + 100 < 400) {
          state[this.roomId].com.y += 10;
        }
      }
      this.broadcast("gameState", JSON.stringify(state[this.roomId]));
    }, 1000 / 50);*/
}

  emitgamestate() {
      intervalId = setInterval(() => {
      /*this.onMessage("canvas", (canvas: number) => {
          console.log(canvas);
      });*/
      const winner = gameLoop(state[this.roomId]);
      if (!winner) {
        if (this.keystatusplayer1.keydown == 1) {
          if (state[this.roomId].user.y > 0) {
            state[this.roomId].user.y -= 10;
          }
        }
        if (this.keystatusplayer1.keyup == 1) {
          if (state[this.roomId].user.y + 100 < 400) {
            state[this.roomId].user.y += 10;
          }
        }
        if (this.keystatusplayer2.keydown == 1) {
          if (state[this.roomId].com.y > 0) {
            state[this.roomId].com.y -= 10;
          }
        }
        if (this.keystatusplayer2.keyup == 1) {
          if (state[this.roomId].com.y + 100 < 400) {
            state[this.roomId].com.y += 10;
          }
        }
        this.broadcast("gameState", JSON.stringify(state[this.roomId]));
      } else {

        this.broadcast("gameOver", JSON.stringify({ winner }));

        fetch(`http://localhost:3000/api/game/saveScore?data=${ 
          encodeURIComponent(JSON.stringify(state[this.roomId]))
        }`, {
          method: 'POST'
        });


        state[this.roomId] = null;
        clearInterval(intervalId);

      }
    }, 1000 / 50);
  }

  // When a client leaves the room
  onLeave(client: Client, consented: boolean) {
    this.broadcast("disconnect")
    state[this.roomId] = null;
    // client.send("quitGame")
    if(intervalId)
      clearInterval(intervalId);


    this.disconnect();
   
  }

  // Cleanup callback, called after there are no more clients in the room. (see `autoDispose`)
  onDispose() { 

  }
}
