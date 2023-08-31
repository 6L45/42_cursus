import {
  Controller,
  Delete,
  Get,
  Post,
  ParseIntPipe,
  Put,
  Param,
  Body,
  HttpException,
  HttpStatus,
  BadRequestException,
  UseGuards,
  Request,
  UnauthorizedException,
} from '@nestjs/common';
import { DatabaseService } from 'src/database/database.service';
import { createRoomDto } from '../dashboard/dashboardDtos/createsTablesDtos';
import * as bcrypt from 'bcrypt';
import { UserConnectedService } from './user-connected-service.service';
import { ChatGateway } from './chat.gateway';
import { AuthGuard } from 'src/auth/auth.guard';
import IJWT from 'src/interfaces/jwt.interface';
import { e_status } from 'src/interfaces/e_status.interface';
import { v4 as uuidv4 } from 'uuid';

@Controller('chat')
export class ChatController {
  constructor(
    private db: DatabaseService,
    private dto: createRoomDto,
    private usersConnected: UserConnectedService,
    private gateway: ChatGateway,
  ) {}
  //----------------------------------------------------------------------//
  // @Get(':id')
  // async getAllUsersChatBadOne(@Param('id', ParseIntPipe) id: number) {
  //   if (id <= 0) throw new BadRequestException('invalid user');
  //   const client = await this.db.getClientById42(id);
  //   const json = await this.db.getRoomIdsAndNamesByClientId(client.id);
  //   console.log(json);
  //   return json;
  // }

   //----------------------------------------------------------------------//
  @UseGuards(AuthGuard)
  @Get()
  async getAllUsersChat(
    @Request() req: { user: IJWT },
  ) {
    //  if (id <= 0) throw new BadRequestException('invalid user');
     const client = await this.db.getClientById42(req.user.id);
     let json = await this.db.getRoomIdsAndNamesByClientId(client.id);
	 const banned_list = await this.db.getBannedRelationshipsForId(client.id);
	 json = json.filter((room) => {
		if (room.secu === 3)
		{
			let otherId;
			if (room.ownerid === client.id)
				otherId = room.client2Id;
			else
				otherId = room.ownerid;
			let found = banned_list.find((el) => el.client1.id === otherId || el.client2.id === otherId);
			if (found)
				return false;
			return true;
		}
		return true;
	 })
     return json;
   }

  //----------------------------------------------------------------------//
  @UseGuards(AuthGuard)
  @Get('/messages/:roomid')
  async getAllMessages(@Request() req: { user: IJWT }, @Param('roomid', ParseIntPipe) roomid: number) {
	let client = await this.db.getClientById42(req.user.id);
	let status = await this.db.roomUserCheck(roomid, client.id);
	if (status == null || status.status == 5)
	{
		throw new UnauthorizedException("You are not member");
	}
    const json = await this.db.getRoomMessagesById(roomid, req.user.id);
    const res = [];
    await Promise.all(
      json.map(async (e) => {
        res.push({ sender: e.clientName, message: e.message });
      }),
    );
    return res;
  }

  //----------------------------------------------------------------------//
  @UseGuards(AuthGuard)
  @Get('/blocked')
  async getBlockedUsers(@Request() req: { user: IJWT })
  {
    let client = await this.db.getClientById42(req.user.id);
    let banned_list = await this.db.getBannedRelationshipsForId(client.id);
    return banned_list;
  }
  //----------------------------------------------------------------------//

  @Get('/connected/:id')
  async getConnectedStatus(@Param('id', ParseIntPipe) id: number) {
	let find: e_status = this.usersConnected.checkStatus(id);
	return find;
  }

  @UseGuards(AuthGuard)
  @Get('/room/:id')
  async getRoomsMembers(@Request() req: { user: IJWT }, @Param('id', ParseIntPipe) room_id: number) {
	const client = await this.db.getClientById42(req.user.id);
	let status = await this.db.roomUserCheck(room_id, client.id);
	if (status == null || status.status == 5)// || status.status == 6)
	{
		throw new UnauthorizedException("You are not member");
	}
	
	let json = await this.db.getMembersByRoomId(room_id);
	if (status.status != 0 && status.status != 1) //not owner or admin
		json = json.filter((el) => el.status != 5 && el.status != 6 && el.status != 4);
    return json;
  }

  @UseGuards(AuthGuard)
  @Get('/room/:id/status')
  async getMyStatus(@Request() req: { user: IJWT }, @Param('id', ParseIntPipe) room_id: number) {
	const client = await this.db.getClientById42(req.user.id);
	const room = await this.db.getRoomById(room_id);
	let status = await this.db.roomUserCheck(room_id, client.id);
	if (status && room.secu === 3)
		return {status: 2};
	return status;
  }

  //----------------------------------------------------------------------//
  @Delete()
  quitRoom(): string {
    return 'user quit the room';
  }
  //----------------------------------------------------------------------//
  @UseGuards(AuthGuard)
  @Post()
  async createNewRoom(@Request() req: { user: IJWT }, @Body() data) {
    /**
     * D'abord on verifie que l'id de iddata est bien lid de luser qui cree la room
     */
    if (req.user.id != data.iddata)
      throw new HttpException(
        'User id is not matching data id',
        HttpStatus.BAD_REQUEST,
    );
	if (data.roomName === '')
		throw new HttpException(
        	'room name is empty',
        HttpStatus.BAD_REQUEST,
    );
    const existingRooms = await this.db.getRooms();
    const userinfo = await this.db.getClientById42(parseInt(data.iddata)); //ici check si ok
    const roomNames = existingRooms.map((room) => room.name);
    if (roomNames.includes(data.roomName)) {
      throw new HttpException(
        'Room name already exists',
        HttpStatus.BAD_REQUEST,
      );
    }
    this.dto.name = data.roomName;
    this.dto.ownerid = userinfo.id;

    if (data.roomType == 'public') this.dto.secu = 0;
    if (data.roomType == 'protected') {
      if (!data.password || data.password === '')
        throw new HttpException(
          'no password on protected room',
          HttpStatus.BAD_REQUEST,
        );
      this.dto.secu = 1;
    }
    if (data.roomType == 'private') this.dto.secu = 2;

    if (this.dto.secu === 1) {
      const saltRounds = 10;
      this.dto.password = await bcrypt.hash(data.password, saltRounds);
    }
    const Room = await this.db.createRooom(this.dto);

    this.db.addMemberToRoom(Room.id, this.dto.ownerid, 0);
    //ICI send reloadRoom ou dna add membertoroom service?
    return HttpStatus.NO_CONTENT;
  }

  @Get('/bannedFor/:id')
  async getBannedPeople(@Param('id', ParseIntPipe) clientId: number)
  {
    return this.db.getBannedRelationshipsForId(clientId);
  }

  //----------------------------------------------------------------------//
  /*
	0 - owner
	1 - admin
	2 - member
	3 - muted
	4 - kicked
	5 - banned
	*/
  //----------------------------------------------------------------------//
  // @Get()
  // async getRooms(): Promise<{ id: number; name: string }[]> {
  //   return this.db.getRooms();
  //   //TODO
  //   //return this.db.getRoomsWhereUserIsNotMember(id);
  // }

  @Post('/verify-password')
  async joinProtectedRoom(@Body() data) {
    const room = await this.db.getRoomById(data.roomId);
    const member = await this.db.getRoomByClientIdAndRoomId(
      data.iddata,
      room.id,
    );
    if (!room) {
      throw new Error('Room does not exist');
    }
    if (member) {
      throw new Error('Already member');
    }

    if (room.secu === 1) {
      bcrypt
        .compare(data.password, room.password)
        .then((passwordsMatch) => {
          if (passwordsMatch) {
            this.db.addMemberToRoom(room.id, data.iddata, 2);
            return 'User joined the room';
          } else {
            console.error('Wrong password');
          }
        })
        .catch((error) => {
          console.error('An error occurred during password comparison:', error);
        });
    }
  }


  /**
   * 
   * 0 - Public
   * 1 - Protected
   * 2 - Private
   * 3 - one on one
   * @returns 
   */
  @Post('/invite')
  async inviteToPrivateRoom(@Body() data) {
    const room = await this.db.getRoomById(data.roomId);
    const invited = await this.db.getClientById(data.iddata1);
    const host = await this.db.getClientById(data.iddata2);
    const member1 = await this.db.getRoomByClientIdAndRoomId(host.id, room.id);
    const member2 = await this.db.getRoomByClientIdAndRoomId(
      invited.id,
      room.id,
    );

    if (!room) {
      // room exist ?
      throw new Error('Room does not exist');
    }
    if (member1) {
      // host not member
      throw new Error('Only members can invite into the room');
    }
    if (member2) {
      // invited already member
      throw new Error('Already member');
    }

    await this.db.addMemberToRoom(data.roomId, invited.id, 2);
    return 'User joined the room';
  }

  @UseGuards(AuthGuard)
  @Post('/addFriend')
  async addFriend(@Request() req: { user: IJWT }, @Body() data) {
    const userId = await this.db.getClientById42(req.user.id);
    const newFriend = await this.db.getClientById(data.newFriendId);

    if (!newFriend) {
      throw new Error('User does not exist');
    }

    await this.db.addClientsToClient(userId.id, newFriend.id, 0);
    return 'Users are now friends';
  }

  /**
   * 
   * Creating a one-to-one room here 
   * 
   */
  @UseGuards(AuthGuard)
  @Post('/sendMsg')
  async sendMsg(@Request() req: { user: IJWT }, @Body() data) {
    const client = await this.db.getClientById42(req.user.id);
    const newInterlocutor = await this.db.getClientById(data.newFriendId);
    if (!client)
      throw new Error('You do not exist');

      if (!newInterlocutor) {
        throw new Error('Interlocutor does not exist');
      }
      // TODO check if user or sender is not blocked
      this.dto.name = uuidv4();
      this.dto.ownerid = client.id;
      this.dto.secu = 3;
      this.dto.client2Id = newInterlocutor.id;

    const Room = await this.db.createRooom(this.dto);
    if (!Room) throw new Error('failed to create room');
    this.db.addMemberToRoom(Room.id, client.id, 0);
    this.db.addMemberToRoom(Room.id, newInterlocutor.id, 1); // adding the second as an admin
    // RELOAD ROOMS
    return {roomId: Room.id};
  }

  @UseGuards(AuthGuard)
  @Post('/blockUser')
  async blockUser(@Request() req: { user : IJWT }, @Body() data) {
    const user = await this.db.getClientById42(req.user.id); // actor
    const blockedUser = await this.db.getClientById(data.blockedId); // acted upon

    if (!blockedUser || !user) {
      throw new Error('User does not exist');
    }

    await this.db.createBlockedRelation(user.id, blockedUser.id);
    this.gateway.sendReloadRequest(blockedUser.id); // sending a refresh request to both to refresh data on their session
    this.gateway.sendReloadRequest(user.id);
    return 'Users are now ennemies';
  }

  @UseGuards(AuthGuard)
  @Post('/unblockUser')
  async unblockUser(@Request() req: { user : IJWT }, @Body() data) {
    const user = await this.db.getClientById42(req.user.id); // actor
    const unblockedUser = await this.db.getClientById(data.unblockedId); // acted upon

    if (!unblockedUser || !user) {
      throw new Error('User does not exist');
    }

    await this.db.unblockClient(user.id, unblockedUser.id);
    this.gateway.sendReloadRequest(unblockedUser.id); // sending a refresh request to both to refresh data on their session
    this.gateway.sendReloadRequest(user.id);
    return 'Users are friends again';
  }
}
