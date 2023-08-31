import {
  OnGatewayConnection,
  OnGatewayDisconnect,
  OnGatewayInit,
  SubscribeMessage,
  WebSocketGateway,
  WebSocketServer,
  WsResponse,
} from '@nestjs/websockets';
import { Injectable, Logger } from '@nestjs/common';
import { Server, Socket } from 'socket.io';
import { DatabaseService } from 'src/database/database.service';
import { UserConnectedService } from './user-connected-service.service';

@Injectable()
@WebSocketGateway({
  path: '/chatsockets',
  namespace: '/chat',
  cors: {
    origin: '*',
  },
})
export class ChatGateway
  implements OnGatewayInit, OnGatewayConnection, OnGatewayDisconnect
{
  @WebSocketServer() wss: Server;
  constructor(
    private db: DatabaseService,
    private usersConnected: UserConnectedService,
  ) {}

  private logger: Logger = new Logger('ChatGateway');

  afterInit(server: Server) {
    this.logger.log('Initialized');
  }
  handleConnection(client: Socket, ...args: any[]) {
    this.logger.log(`Client connected : ${client.id}`);
  }
  handleDisconnect(client: Socket) {
    this.logger.log(`Client disconnected : ${client.id}`);
    this.usersConnected.deleteUser(client);
  }

  @SubscribeMessage('whoAmI')
  addToUsers(user: Socket, id: number) {
    this.usersConnected.addUser(user, id);
  }

  // @SubscribeMessage('setUsername')
  // handleSetUsername(socket: Socket, username: string) {
  // 	this.logger.log(`Received username: ${username}`);
  // 	socket.username = username; // Store the username in the socket object
  // }

  @SubscribeMessage('chatToServer')
  async handleMessage(
    client: Socket,
    message: {
      channel: string;
      message: string;
      sender_id: string;
    },
  ) {
    this.logger.log(
      `A message was send by id ${message.sender_id} --content--> ${message.message}`,
    );
    const client_id = await this.db.getClientById42(Number(message.sender_id));
    const room_exist = await this.db.getRoomById(Number(message.channel));
    if (room_exist == null) return;
    // if (! this.db.userIsMemberOfRoom()) return ;
    let status = await this.db.roomUserCheck(room_exist.id, client_id.id);
    if (status == null || status.status == 3 || status.status == 4 || status.status == 5 || status.status == 6)
    {
      return ;
    }
	if (! this.areWordsLessThanLength(message.message, 15))
		return ;
    await this.addMessageToRoom({
      id: Number(message.channel),
      sender: client_id.id,
      msg: message.message,
    });
    this.wss.to(message.channel).emit('serverToChat', { ...message, sender: client_id.name});
    this.wss.to(message.channel).emit('serverAlertToChat', { ...message, sender: client_id.name});
    // WsResponse<string>
    // return { event: 'msgToClient', data: text};
  }

  @SubscribeMessage('inviteToPlay')
  async handleInvitation(
    client: Socket,
    data: { player_id: number; opponent_id: number, secret: string},
  ) {
    //utiliser le id via le token sinon on peux creer des invitations entre deux users sans leurs consantement
    this.logger.log(`A invitation to play was send to opponent_id`);
    const socket_id = this.usersConnected.findSocketId(data.opponent_id);
    if (socket_id == '') return;
    let user = await this.db.getClientById(data.player_id);
    this.logger.log(`FOUND`);
    this.wss.to(socket_id).emit('invitationGame', {player_id: data.player_id, secret: data.secret, name: user.name, img: user.img});
    //   let client_id = await this.db.getClientById42(message.sender_id);
    //   await this.addMessageToRoom({ id: message.channel, sender: client_id.id, msg: message.message});
    //   this.wss.to(message.channel).emit('serverToChat', message);
    //   this.wss.to(message.channel).emit('serverAlertToChat', message);
    // WsResponse<string>
    // return { event: 'msgToClient', data: text};
  }

  @SubscribeMessage('refuse')
  handleRefuse(client: Socket, data: any) {
    const socket_id = this.usersConnected.findSocketId(data.player_id);
    if (socket_id != '')
      client.to(socket_id).emit('refused');
  }

  @SubscribeMessage('joinChannel')
  async handleJoinChannel(client: Socket, channel: string) {
	let room = await this.db.getRoomById(Number(channel));
	if (null)
		return ;
	let id = this.usersConnected.findId(client.id);
	if (id === null)
		return ;
	let status = await this.db.roomUserCheck(Number(channel), id);
	if (status !== null && status.status != 5 && status.status != 6)
	{
		client.join(channel);
		client.emit('joinedChannel', channel);
	}
  }

  @SubscribeMessage('leaveChannel')
  handleLeaveChannel(client: Socket, channel: string) {
    // check if channel id is existing if not do nothing
    // check if client is a member of channel then proceed
    // ask the chat service to delete the user from members
    client.leave(channel);
    client.emit('leavedChannel', channel);
  }

  /**
   * 
   * Socket event In Game story
   * 
   */
   @SubscribeMessage('startGame')
   userIsInGame(user: Socket) {
      this.usersConnected.addInGame(user);
   }

   @SubscribeMessage('endGame')
   userIsNotInGame(user: Socket, id: number) {
    this.usersConnected.deleteInGame(user);
   }


  async addMessageToRoom(data: any) {
    this.db.addMessageToRoom(data.id, data.sender, data.msg);
  }

  async sendServerMsg(roomid: number, msg: any) {
    this.wss.to(`${roomid}`).emit('serverMessage', {
      channel: roomid,
      sender: 'server',
      message: msg,
      sender_id: 0,
    });
  }

  async sendReloadRequest(target_id: any)
  {
    let socket_id = this.usersConnected.findSocketId(target_id);
    if (socket_id != '')
    {
      this.wss.to(socket_id).emit('reloadrooms');
    }
  }

  async sendReloadRoomToAllMembers(roomId: any)
  {
	this.wss.to(roomId).emit('reloadrooms');
  }


  async emitMemberReload(roomId: number)
  {
	this.wss.to(`${roomId}`).emit("reloadMembers");
  }

  areWordsLessThanLength(inputString: string, maxLength: number) 
  {
    const words = inputString.split(' ');
    for (let i = 0; i < words.length; i++) {
        if (words[i].length > maxLength) {
            return false;
        }
    }
    return true;
  }
}
