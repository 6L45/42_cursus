import { Logger, ParseFloatPipe } from '@nestjs/common';
import {
  ConnectedSocket,
  MessageBody,
  SubscribeMessage,
  WebSocketGateway,
  WebSocketServer,
} from '@nestjs/websockets';
import { Server, Socket } from 'socket.io';

@WebSocketGateway({
  path: '/pongsockets',
  namespace: 'pong',
  cors: {
    origin: '*',
  },
})
export class PongGateway {
  @WebSocketServer()
  server: Server;

  private logger: Logger = new Logger('PongGateway');

  afterInit(server: Server) {
    this.logger.log('Initialized');
  }

  handleConnection(client: Socket, ...args: any[]) {
    this.logger.log(`Client connected : ${client.id}`);
  }

  async handleDisconnect(client: Socket) {
    this.logger.log(`Client disconnected : ${client.id}`);
  }

  @SubscribeMessage('test')
  async lobbyStatus(
    @MessageBody() data: string,
    @ConnectedSocket() client: Socket,
  ) {
    client.emit('testSeverToClient', 'success');
  }
}

// export class PongGateway {
//   @WebSocketServer() server;
//   private logger: Logger = new Logger('AppGateway');
//   private state: Record<string, any> = {};
//   private clientRooms: Record<string, string> = {};
//   private keystatusplayer1 = {keydown:0, keyup:0}; //
//   private keystatusplayer2 = {keydown:0, keyup:0};
//   private intervalId: any;

//   afterInit(server: Server) {
//     this.logger.log('Init');
//   }

//   handleDisconnect(client: Socket, ...args: any[]) {
//     this.logger.log(`Client disconnected: ${client.id}`);
//     const roomName = this.clientRooms[client.id];
//     let winner = 0;
//     if (roomName) {
//       winner = 2;
//       clearInterval(this.intervalId);
//       this.intervalId = null;
//       this.state[roomName] = null;
//       client.to(roomName).emit('gameOver', JSON.stringify({ winner }));
//       client.leave(roomName);
//     }
//   }

//   handleConnection(client: Socket, ...args: any[]) {
//     this.logger.log(`Client connected: ${client.id}`);
//   }

//   @SubscribeMessage('keydown')
//   handleKeydown(client: Socket, keyCode: any) {
//     const roomName = this.clientRooms[client.id];

//     if (!roomName) {
//       return;
//     }

//     try {
//       keyCode = parseInt(keyCode);
//     } catch (e) {
//       console.error(e);
//       return;
//     }

//     if (client.number == 1) {
//       if (keyCode === 38) {
//         if (this.state[roomName].user.y + 50 > 0) {
//           let i = 15;
//           while (i > 0) {
//             this.state[roomName].user.y--;
//             i--;
//           }
//         }
//       } else if (keyCode == 40) {
//         if (this.state[roomName].user.y + 50 < 400) {
//           let i = 15;
//           while (i > 0) {
//             this.state[roomName].user.y++;
//             i--;
//           }
//         }
//       }
//     } else if (client.number == 2) {
//       if (keyCode === 38) {
//         if (this.state[roomName].com.y + 50 > 0) {
//           let i = 15;
//           while (i > 0) {
//             this.state[roomName].com.y--;
//             i--;
//           }
//         }
//       } else if (keyCode == 40) {
//         if (this.state[roomName].com.y + 50 < 400) {
//           let i = 15;
//           while (i > 0) {
//             this.state[roomName].com.y++;
//             i--;
//           }
//         }
//       }
//     }
//   }

//   @SubscribeMessage('keyup')
//   handleKeyup(client: Socket, keyCode: any) {
//     const roomName = this.clientRooms[client.id];

//     if (!roomName) {
//       return;
//     }

//     try {
//       keyCode = parseInt(keyCode);
//     } catch (e) {
//       console.error(e);
//       return;
//     }

//     if (client.number == 1) {
//       if (keyCode === 38) {
//         if (this.state[roomName].user.y + 50 > 0) {
//           let i = 15;
//           while (i > 0) {
//             this.state[roomName].user.y--;
//             i--;
//           }
//         }
//       } else if (keyCode == 40) {
//         if (this.state[roomName].user.y + 50 < 400) {
//           let i = 15;
//           while (i > 0) {
//             this.state[roomName].user.y++;
//             i--;
//           }
//         }
//       }
//     } else if (client.number == 2) {
//       if (keyCode === 38) {
//         if (this.state[roomName].com.y + 50 > 0) {
//           let i = 15;
//           while (i > 0) {
//             this.state[roomName].com.y--;
//             i--;
//           }
//         }
//       } else if (keyCode == 40) {
//         if (this.state[roomName].com.y + 50 < 400) {
//           let i = 15;
//           while (i > 0) {
//             this.state[roomName].com.y++;
//             i--;
//           }
//         }
//       }
//     }
//   }

//   @SubscribeMessage('createGame')
//   handleCreateGame(client: Socket, data: any) {
//     const roomName = Math.random().toString(36).substring(2, 7);
//     this.clientRooms[client.id] = roomName;
//     client.emit('gameCode', roomName);
//     client.join(roomName);
//     client.number = 1;
//     client.emit('init', 1);
//     this.state[roomName] = createGameState();
//     this.intervalId = setInterval(() => this.updateGameState(roomName), 1000 / 60);
//   }

//   @SubscribeMessage('joinGame')
//   handleJoinGame(client: Socket, roomName: string) {
//     const room = this.server.sockets.adapter.rooms[roomName];
//     let allUsers;
//     if (room) {
//       allUsers = room.sockets;
//     }
//     let numClients = 0;
//     if (allUsers) {
//       numClients = Object.keys(allUsers).length;
//     }
//     if (numClients === 0) {
//       client.emit('unknownGame');
//       return;
//     } else if (numClients > 1) {
//       client.emit('tooManyPlayers');
//       return;
//     }
//     this.clientRooms[client.id] = roomName;
//     client.join(roomName);
//     client.number = 2;
//     client.emit('init', 2);
//     this.startGameInterval(roomName);
//   }

//   startGameInterval(roomName: string) {
//     this.intervalId = setInterval(() => this.updateGameState(roomName), 1000 / 60);
//   }

//   updateGameState(roomName: string) {
//     const pack = [];
//     if (!this.state[roomName]) {
//       return;
//     }
//     this.state[roomName].ball.x += this.state[roomName].ball.velocityX;
//     this.state[roomName].ball.y += this.state[roomName].ball.velocityY;

//     if (this.state[roomName].ball.y + 10 > 500 || this.state[roomName].ball.y < 0) {
//       this.state[roomName].ball.velocityY = -this.state[roomName].ball.velocityY;
//     }

//     if (this.state[roomName].ball.x + 10 > 500 || this.state[roomName].ball.x < 0) {
//       this.state[roomName].ball.velocityX = -this.state[roomName].ball.velocityX;
//     }

//     if (this.state[roomName].ball.x < 0) {
//       this.state[roomName].ball.x = 250;
//       this.state[roomName].ball.y = 250;
//       this.state[roomName].ball.velocityX = 3;
//       this.state[roomName].ball.velocityY = 3;
//       this.state[roomName].user.score++;
//     }

//     if (this.state[roomName].ball.x > 500) {
//       this.state[roomName].ball.x = 250;
//       this.state[roomName].ball.y = 250;
//       this.state[roomName].ball.velocityX = -3;
//       this.state[roomName].ball.velocityY = -3;
//       this.state[roomName].com.score++;
//     }

//     if (this.state[roomName].ball.x < 500 && this.state[roomName].ball.x > 0) {
//       if (this.state[roomName].ball.y < this.state[roomName].user.y + 50 && this.state[roomName].ball.y > this.state[roomName].user.y) {
//         this.state[roomName].ball.velocityX = -this.state[roomName].ball.velocityX;
//       }
//       if (this.state[roomName].ball.y < this.state[roomName].com.y + 50 && this.state[roomName].ball.y > this.state[roomName].com.y) {
//         this.state[roomName].ball.velocityX = -this.state[roomName].ball.velocityX;
//       }
//     }

//     pack.push(this.state[roomName].user);
//     pack.push(this.state[roomName].com);
//     pack.push(this.state[roomName].ball);
//     this.server.to(roomName).emit('update', pack);
//   }

//   // @SubscribeMessage('disconnect')
//   // handleDisconnect(client: Socket) {
//   //   const roomName = this.clientRooms[client.id];
//   //   let winner = 0;
//   //   if (roomName) {
//   //     if (this.state[roomName].user.score > this.state[roomName].com.score) {
//   //       winner = 1;
//   //     } else {
//   //       winner = 2;
//   //     }
//   //     this.server.to(roomName).emit('gameOver', winner);
//   //     clearInterval(this.intervalId);
//   //     delete this.state[roomName];
//   //   }
//   // }

// }
