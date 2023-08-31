import {
  BadRequestException,
  Body,
  Controller,
  Get,
  HttpException,
  HttpStatus,
  InternalServerErrorException,
  Param,
  ParseArrayPipe,
  ParseBoolPipe,
  ParseIntPipe,
  Post,
  UseGuards,
  Request,
  UnauthorizedException,
} from '@nestjs/common';
import { DatabaseService } from 'src/database/database.service';
import * as bcrypt from 'bcrypt';
import { AuthGuard } from 'src/auth/auth.guard';
import IJWT from 'src/interfaces/jwt.interface';
import { updateRoomDto } from 'src/database/dtos/dbBaseDto';
import { ChatGateway } from 'src/chat/chat.gateway';
import { error } from 'console';

@Controller('rooms')
export class RoomsController {
  constructor(private db: DatabaseService, 
    private cg: ChatGateway) {}

  @UseGuards(AuthGuard)
  @Get()
  async getOwnedRooms(@Request() req: { user: IJWT }) {
    const client = await this.db.getClientById42(req.user.id);
    return this.db.getRoomsByOwnerId(client.id);
  }

  @UseGuards(AuthGuard)
  @Get('/allMemberwithStatus/:id42/:name')
  async loadAllRoomMember(
    @Param('id42', ParseIntPipe) id42: number,
    @Param('name') roomName: string,
  ) {
    return await this.db.getAllRoomMembers(id42, roomName);
  }
/*
  @Get('/privateRoomMember/:id')
  async getPrivateRoomMembers(@Param('id', ParseIntPipe) id: number) {
    return await this.db.getMembersForPrivateRoom(id);
  }

  @Get('/allRoomMember/:idRoom/:idMember')
  async getAllRoomMember(
    @Param('idRoom', ParseIntPipe) idRoom: number,
    @Param('idMember', ParseIntPipe) idMember: number,
  ) {
    return await this.db.getMembersByRoomIdExcludingClient(idRoom, idMember);
  }

  @Get('/allRoomMemberForAdmins/:idRoom/:idMember')
  async getAllRoomMembeForAdmins(
    @Param('idRoom', ParseIntPipe) idRoom: number,
    @Param('idMember', ParseIntPipe) idMember: number,
  ) {
    return await this.db.getMembersByRoomIdExcludingClientForAdmins(idRoom, idMember);
  }
*/
  @UseGuards(AuthGuard)
  @Get('valideRooms')
  async getAuthorizedRoomsForId(@Request() req: { user: IJWT }) {
    const client = await this.db.getClientById42(req.user.id);
	const rooms_data = await this.db.getRoomsAndMembersExcludingWhereClientIsMember(client.id);
	const response = rooms_data.map((el) => {
		return ({id: el.id, name: el.name, secu: el.secu, quantity: el.members.length});
	});
    return response;
  }
/*
  @Get('getAdmins/:roomId')
  async getRoomAdmins(@Param('roomId', ParseIntPipe) roomId: number) {
    return this.db.getRoomAdmins(roomId);
  }
*/
  @UseGuards(AuthGuard)
  @Get('/replacementList/:id')
  async getReplacements(@Request() req: { user: IJWT }, @Param('id', ParseIntPipe) roomId: number) {
    try {
		const client = await this.db.getClientById42(req.user.id);
		if (!client)
			throw error({message: "not a known user"});
		const status = await this.db.roomUserCheck(roomId, client.id);
		if (status && status.status === 0)
      		return await this.db.getRoomReplacementMembers(roomId);
		else
			throw error({message: "not an owner"});
    } catch (error) {
      throw new HttpException('Unaithorised', HttpStatus.UNAUTHORIZED);
    }
  }

  @UseGuards(AuthGuard)
  @Get('/info/:id')
  async getRoomInfo(@Request() req: { user: IJWT }, @Param('id', ParseIntPipe) roomId: number) {
    try {
		let room = await this.db.getRoomById(roomId);
		if (!room)
			throw error('room not found');
      return {id: room.id, name: room.name, secu: room.secu};
    } catch (error) {
      throw new HttpException(error.message, HttpStatus.NOT_FOUND);
    }
  }

  @UseGuards(AuthGuard)
  @Get('getRoomId/:roomName')
  async getRoomId(@Param('roomName') roomName: string)
  {
    return this.db.getRoomIdByName(roomName);
  }

  @UseGuards(AuthGuard)
  @Post('/updateRoom/:roomId')
  async updateRoom( @Request() req: { user: IJWT },
  					@Param('roomId', ParseIntPipe) roomId: number,
                  	@Body() data: updateRoomDto)
  {
	let client = await this.db.getClientById42(req.user.id);
	if (!client)
	throw new BadRequestException("Unauthorized to update");
	
	let roomToUpdate = await this.db.getRoomById(roomId);
	if (!roomToUpdate)
	throw new BadRequestException("room doesn't exist");
	
	let status = await this.db.roomUserCheck(roomId, client.id);
	if (! status || status.status !== 0)
	throw new BadRequestException("not an owner");

	let message = '';
	if (roomToUpdate.name !== data.name)
		message += `New room name is ${data.name}. Please consider to refresh the page to see the change.`;
	if (roomToUpdate.secu !== data.secu)
	{
	message += "The room is now ";
	if (data.secu === 0)
		message += 'public.';
	else if (data.secu === 1)
		message += 'protected by a pass.';
	else if (data.secu === 2)
		message += 'private.';
	}
    if (roomToUpdate.secu !== 1 && data.secu === 1 && data.password === '')
	  throw new BadRequestException("missing password to update");
	else if (roomToUpdate.secu !== 1 && data.secu === 1)
	{
		const saltRounds = 10;
		data.password = await bcrypt.hash(data.password, saltRounds);
	}
	else if (roomToUpdate.secu === 1 && data.secu === 1 && data.password !== '')
	{
		const saltRounds = 10;
		data.password = await bcrypt.hash(data.password, saltRounds);
	}
	else if (roomToUpdate.secu === 1 && data.secu === 1)
		data = {name: data.name};
    try {
    	await this.db.updateRoom(roomId, data);
		this.cg.sendServerMsg(roomId, `The room configuration are changed by the owner : ${message}`);
    }
    catch (error) {
      throw new BadRequestException("Update failed");
    }
  }

  @UseGuards(AuthGuard)
  @Post('/join/:roomId')
  async joinRoom(
    @Request() req: { user: IJWT },
    @Param('roomId', ParseIntPipe) roomId: number,
    @Body() data: any,
  ) {
    const room = await this.db.getRoomById(roomId);
    const client = await this.db.getClientById42(req.user.id);

    //Si room n'existe pas ou client n'existe pas bad request
    if (!room || !client) {
      throw new HttpException(
        'room id or client id onvalid',
        HttpStatus.BAD_REQUEST,
      );
    }
    // si clientId déjà memebre de la room
    // on ne fait rien et NO CONTENT return.
    if (await this.db.checkRoomMember(roomId, req.user.id))
      return HttpStatus.ACCEPTED;

    // si room est protected par mot de passe
    if (room.secu === 1) {
      // check password
      const response = await bcrypt
        .compare(data.password, room.password)
        .then((passwordsMatch) => {
          if (passwordsMatch) {
            // valid case
            this.db.addMemberToRoom(room.id, client.id, 2);
			this.cg.sendServerMsg(roomId, `Welcome to a new member : ${client.name}!`);
			this.cg.emitMemberReload(roomId);
            // check password
            return HttpStatus.NO_CONTENT;
          } // error case
          else {
            throw new UnauthorizedException('Access Denied');
          }
        })
        .catch((error) => {
          throw new InternalServerErrorException(error);
        });
		return response;
    }
    // si room est publique
    else if (room.secu === 2) {
      try {
        await this.db.addMemberToRoom(roomId, client.id, 6);
		this.cg.emitMemberReload(roomId);
        return HttpStatus.NO_CONTENT;
      } catch (error) {
        throw new BadRequestException(error);
      }
    }
    // si room est one on one conversation
    else if (room.secu === 3) {
      throw new Error('Cannot join a conversation room');
    }

    // ça y était en théorie on ne passe plus ici,
    // mais la flemme de check l'ensemble des cas de figure donc ça reste
    await this.db.addMemberToRoom(roomId, client.id, 2);
	this.cg.sendServerMsg(roomId, `Welcome to a new member : ${client.name}!`);
	this.cg.emitMemberReload(roomId);
    return HttpStatus.NO_CONTENT;
  }

  @UseGuards(AuthGuard)
  @Post('/quit/:roomId')
  async quitRoom(
    @Request() req: { user: IJWT },
    @Param('roomId', ParseIntPipe) roomId: number,
  ) {
	const room = await this.db.getRoomById(roomId);
    const client = await this.db.getClientById42(req.user.id);
	const status = await this.db.roomUserCheck(roomId, client.id);
	if (!room || !client || !status || status.status === 0) {
		throw new HttpException(
		  'room id or client id or client status invalid',
		  HttpStatus.BAD_REQUEST,
		);
	}
	await this.db.removeClientFromRoom(roomId, client.id);
    this.cg.sendServerMsg(roomId, `${client.name} quit the room`);
	this.cg.emitMemberReload(roomId);
    return HttpStatus.NO_CONTENT;
  }

  @UseGuards(AuthGuard)
  @Post('updateStatus/:id/:client/:status')
  async updateClientStatus(
	@Request() req: { user: IJWT },
    @Param('id', ParseIntPipe) roomId: number,
    @Param('client', ParseIntPipe) clientId: number,
    @Param('status', ParseIntPipe) status: number,
  ) {
	const sender = await this.db.getClientById42(req.user.id);
	const sender_status = await this.db.roomUserCheck(roomId, sender.id);
	if (!sender_status || (sender_status.status !== 0 && sender_status.status !== 1))
		throw new UnauthorizedException();
    const ownerCheck = await this.db.checkRoomOwner(roomId, clientId);
    if (ownerCheck) throw new UnauthorizedException();
	const old_status = await this.db.roomUserCheck(roomId, clientId);
    try {
      await this.db.changeMemberStatus(roomId, clientId, status);
      let client = await this.db.getClientById(clientId);
      if (client != null)
      {
        if (status == 3)
          this.cg.sendServerMsg(roomId, `${client.name} is muted`);
        else if (status == 5)
          this.cg.sendServerMsg(roomId, `${client.name} is banned`);
        else if (status == 1)
          this.cg.sendServerMsg(roomId, `${client.name} is now an Admin`);
		else if (status == 2 && old_status.status == 3)
			this.cg.sendServerMsg(roomId, `${client.name} is unmuted`);
		else if (status == 2 && old_status.status == 1)
			this.cg.sendServerMsg(roomId, `${client.name} is no longer an Admin`);
        this.cg.emitMemberReload(roomId);
        return HttpStatus.NO_CONTENT;
      }
      return HttpStatus.NO_CONTENT;
    } catch (error) {
      throw new HttpException(error.message, HttpStatus.BAD_REQUEST);
    }
  }

  @UseGuards(AuthGuard)
  @Post('kick/:roomId/:clientId')
  async kickClient(
	@Request() req: { user: IJWT },
    @Param('roomId', ParseIntPipe) roomId: number,
    @Param('clientId', ParseIntPipe) memberId: number,
  ) {
	const sender = await this.db.getClientById42(req.user.id);
	const sender_status = await this.db.roomUserCheck(roomId, sender.id);
	if (!sender_status || (sender_status.status !== 0 && sender_status.status !== 1))
		throw new UnauthorizedException();
	const ownerCheck = await this.db.checkRoomOwner(roomId, memberId);
	if (ownerCheck)
	throw new HttpException("can't kick room owner", HttpStatus.BAD_REQUEST);
	const status = await this.db.roomUserCheck(roomId, memberId);
	try {
	await this.db.removeClientFromRoom(roomId, memberId);
	let client = await this.db.getClientById(memberId);
	if (client != null)
	{
		if (status.status === 5)
			this.cg.sendServerMsg(roomId, `${client.name} has been unbanned`);
		else if (status.status !== 6)
			this.cg.sendServerMsg(roomId, `${client.name} has been kicked`);
		this.cg.emitMemberReload(roomId);
		return HttpStatus.NO_CONTENT;
	}
	} catch (error) {
	console.error(error);
	throw new HttpException(error.message, HttpStatus.BAD_REQUEST);
	}
  }

  @UseGuards(AuthGuard)
  @Post('acceptNewMember/:roomId/:clientId')
  async acceptNewMember(
	@Request() req: { user: IJWT },
    @Param('roomId', ParseIntPipe) roomId: number,
    @Param('clientId', ParseIntPipe) memberId: number,
  ) {
	const sender = await this.db.getClientById42(req.user.id);
	const sender_status = await this.db.roomUserCheck(roomId, sender.id);
	if (!sender_status || (sender_status.status !== 0 && sender_status.status !== 1))
		throw new UnauthorizedException();
    try {
		const newMember = await this.db.getClientById(memberId);
      await this.db.addMemberToRoom(roomId, memberId);
	  this.cg.sendServerMsg(roomId, `Welcome to a new member : ${newMember.name}!`);
	  this.cg.emitMemberReload(roomId);
      return HttpStatus.NO_CONTENT;
    } catch (error) {
      throw new HttpException(error.message, HttpStatus.BAD_REQUEST);
    }
  }

  @UseGuards(AuthGuard)
  @Post('/delete/:roomId')
  async deleteRoom(@Request() req: { user: IJWT },
  	@Param('roomId', ParseIntPipe) roomId: number) {
	let client = await this.db.getClientById42(req.user.id);
	if (!client)
		throw new UnauthorizedException();
	let status = await this.db.roomUserCheck(roomId, client.id);
	if (!status || status.status !== 0)
		throw new UnauthorizedException();
    try {
      await this.db.deleteRoomWithMembers(roomId);
      return HttpStatus.NO_CONTENT;
    } catch (error) {
      throw new HttpException(error.message, HttpStatus.BAD_REQUEST);
    }
  }

  @UseGuards(AuthGuard)
  @Post('/resign/:roomId/:adminId/:stay')
  async resign(
	@Request() req: { user: IJWT },
    @Param('roomId', ParseIntPipe) roomId: number,
    @Param('adminId', ParseIntPipe) adminId: number,
    @Param('stay', ParseBoolPipe) stay: boolean,
  ) {
	const client = await this.db.getClientById42(req.user.id);
	const sucessor = await this.db.getClientById(adminId);
	if (!client || !sucessor)
		throw new HttpException(
        'unknown user',
        HttpStatus.BAD_REQUEST,
    );
    const ownerCheck = await this.db.checkRoomOwner(roomId, client.id);
    const roomUserCheck = await this.db.checkRoomMember(roomId, adminId);
    if (!ownerCheck || !roomUserCheck) {
      throw new HttpException(
        'invalid client for specified room',
        HttpStatus.BAD_REQUEST,
      );
    }
    if (client.id === adminId) {
      throw new HttpException('you so funny Larry', HttpStatus.BAD_REQUEST);
    }

    try {
      await this.db.changeMemberStatus(roomId, client.id, 1); // owner becomes admin |__ > table roomMembers
      await this.db.changeMemberStatus(roomId, adminId, 0); // admin becomes owner |
      await this.db.changeRoomOwner(roomId, adminId); // pass admin as owner in table Rooms

      if (!stay)
        // is resign is decided with leaving the room
        await this.db.removeClientFromRoom(roomId, client.id);
		let message = client.name + ' has resign his ownership of the room to ' + sucessor.name + '.';
		this.cg.emitMemberReload(roomId);
	  	this.cg.sendServerMsg(roomId, message);
      return HttpStatus.NO_CONTENT;
    } catch (error) {
      throw new HttpException(error.message, HttpStatus.BAD_REQUEST);
    }
  }
}
