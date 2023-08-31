import {
  BadRequestException,
  ForbiddenException,
  HttpCode,
  Injectable,
  NotFoundException,
  UnauthorizedException,
} from '@nestjs/common';
import { PrismaService } from 'src/prisma/prisma.service';
import { ClientDto, updateRoomDto } from './dtos/dbBaseDto';
import {
  ClientStats,
  ClientToClient,
  Clients,
  MessagesRooms,
  Prisma,
  RoomMembers,
  Rooms,
} from '@prisma/client';
import { UpdateClientDto } from 'src/dashboard/dashboardDtos/updateClientDto';
import {
  createRelationsDto,
  createRoomDto,
  createStatsDto,
  updateStatDto,
} from 'src/dashboard/dashboardDtos/createsTablesDtos';
import { HttpErrorByCode } from '@nestjs/common/utils/http-error-by-code.util';
import { gameHistoricDto } from 'src/game/game.controller';
import { response } from 'express';

@Injectable()
export class DatabaseService {
  constructor(private prisma: PrismaService) {}

  async getClientById42(id42: number): Promise<Clients | null> {
    const client = await this.prisma.clients.findUnique({
      where: {
        id42: id42,
      },
    });

    return client || null;
  }

  async ComTest(ghDto: gameHistoricDto)
  {
    console.log(ghDto);
    return 1;
  }
  
  async getClientById42Dashboard(id42: number) {
    const client = await this.prisma.clients.findUnique({
      where: {
        id42: id42,
      },
      select: {
        id: true,
        name: true,
        img: true,
        Dfa: true,
        clientStats: {
          select: {
            played: true,
            won: true,
            score: true,
            title: true,
            hf: true,
          },
        },
      },
    });

    if (!client) {
      return null;
    }

    return client;
    /*
		const { id, name, img, Dfa, clientStats } = client;

		return {
			id,
			name,
			img,
			Dfa,
			clientStats,
		};*/
  }
  /*
	async getClientByName(name: string) {
		const client = await this.prisma.clients.findUnique({
			where: {
				name,
			},
			select: {
				name: true,
				img: true,
				id: true,
				clientStats: {
					select: {
						played: true,
						won: true,
						score: true,
						title: true,
						hf: true,
					}
				}
			},
		});

		if (!client) {
			throw new HttpErrorByCode[404];
		}

		return client;
	}
  async getIdFromId42(id42: number)
  {
    const id = await this.prisma.clients.findUnique({
      where: {
        id42,
      },
      select: {
        id: true
      }
    });

    return id;
  }
*/

  async getTarget(clientId: number, name: string) {
    const client = await this.prisma.clients.findUnique({
      where: {
        name,
      },
      select: {
        name: true,
        img: true,
        id: true,
        id42: true,
        client1: {
          select: {
            status: true,
          },
          where: {
            client2: {
              id42: clientId,
            },
          },
        },
        client2: {
          select: {
            status: true,
          },
          where: {
            client1: {
              id42: clientId,
            },
          },
        },
      },
    });
    if (!client) throw new NotFoundException('Client does not exist');

    return client;
  }

  async getClientByName(clientId: number, name: string) {
    const client = await this.prisma.clients.findUnique({
      where: {
        name,
      },
      select: {
        name: true,
        img: true,
        id: true,
        clientStats: true,
        client1: {
          select: {
            status: true,
          },
          where: {
            client2Id: clientId,
          },
        },
        client2: {
          select: {
            status: true,
          },
          where: {
            client1Id: clientId,
          },
        },
      },
    });

    if (!client || client.client1.some((c) => c.status === 1)) {
      throw new HttpErrorByCode[404]();
    }
    return client;
  }

  async getClientById(id: number): Promise<Clients | null> {
    const client = await this.prisma.clients.findUnique({
      where: {
        id: id,
      },
    });

    return client || null;
  }

  async getClientImgById(id: number) {
    const client = await this.prisma.clients.findUnique({
      where: {
        id: id,
      },
	  select: {
		img: true,
	  }
    });

    return client || null;
  }

  async getClientImgAndNameById(id: number) {
    const client = await this.prisma.clients.findUnique({
      where: {
        id: id,
      },
	  select: {
		img: true,
		name: true,
	  }
    });

    return client || null;
  }

  // async getClientByCookie(cookie: string): Promise<Clients | null> {
  //   const client = await this.prisma.clients.findUnique({
  //     where: {
  //       cookie: cookie,
  //     },
  //   });

  //   return client || null;
  // }

  async getClientIdFromId42(id42: number): Promise<number | null> {
    const client = await this.prisma.clients.findUnique({
      select: { id: true },
      where: { id42: id42 },
    });

    return client?.id || null;
  }

  async getClientId42FromId(id: number): Promise<number | null> {
    const client = await this.prisma.clients.findUnique({
      select: { id42: true },
      where: { id: id },
    });

    return client?.id42 || null;
  }
  /*
	async findClientsByName(name: string): Promise<Clients[]> {
		return await this.prisma.clients.findMany({
		  where: {
				name: {
				contains: name,
				},
			},
		});
	}
*/

  async findClientsByName(clientId: number, name: string) {
    const clients = await this.prisma.clients.findMany({
      where: {
        name: {
          contains: name,
        },
        NOT: {
          OR: [
            {
              client2: {
                some: {
                  AND: [{ client1Id: clientId }, { status: 1 }],
                },
              },
            },
            {
              client1: {
                some: {
                  AND: [{ client2Id: clientId }, { status: 1 }],
                },
              },
            },
          ],
        },
      },
    });

    return clients;
  }

  async createClient(dto: ClientDto): Promise<Clients> {
    try {
      const client = await this.prisma.clients.create({
        data: {
          id42: dto.id42,
          name: dto.name,
          cookie: dto.cookie,
          img: dto.img,
          Dfa: false,
          dfaVerified: false,
        },
      });

      return client;
    } catch (error) {
      if (error instanceof Prisma.PrismaClientKnownRequestError) {
        if (error.code === 'P2002') {
          throw new ForbiddenException('Credentials taken');
        }
      }
      throw error;
    }
  }

  async createClientStat(dto: createStatsDto): Promise<ClientStats> {
    try {
      const { clientId, played, won, score, hf } = dto;

      const clientStat = await this.prisma.clientStats.create({
        data: {
          played,
          won,
          score,
          hf,
          clientId,
        },
      });

      return clientStat;
    } catch (error) {
      if (error instanceof Prisma.PrismaClientKnownRequestError) {
        if (error.code === 'P2002') {
          throw new ForbiddenException('Credentials taken');
        }
      }
      throw error;
    }
  }

  async updateStat(
    clientId: number,
    data: updateStatDto,
  ): Promise<ClientStats> {
    try {
      const updateData: Prisma.ClientStatsUpdateInput = {
        played: data.played ? { set: data.played } : undefined,
        won: data.won ? { set: data.won } : undefined,
        title: data.title ? { set: data.title } : undefined,
        score: data.score ? { set: data.score } : undefined,
        hf: data.hf ? { set: data.hf } : undefined,
      };

      const updatedClient = await this.prisma.clientStats.update({
        where: { clientId },
        data: updateData,
      });

      return updatedClient;
    }
    catch (error) {
      if (error instanceof Prisma.PrismaClientKnownRequestError) {
        if (error.code === 'P2025') {
          throw new NotFoundException("User doesn't exist");
        }
        if (error.code === 'P2002') {
          throw new ForbiddenException('Credentials taken');
        }
        throw error;
      }
    }
  }

  async updateClient(id: number, data: UpdateClientDto): Promise<Clients> {
    try {
      const updateData: Prisma.ClientsUpdateInput = {
        img: data.img ? { set: data.img } : undefined,
        name: data.name ? { set: data.name } : undefined,
        Dfa: data.dfa,
        DfaSecret: data.dfaSecret ? { set: data.dfaSecret } : undefined,
        dfaVerified: data.dfaVerified ? { set: data.dfaVerified } : undefined,
      };

      const updatedClient = await this.prisma.clients.update({
        where: { id },
        data: updateData,
      });

      return updatedClient;
    } catch (error) {
      if (error instanceof Prisma.PrismaClientKnownRequestError) {
        if (error.code === 'P2025') {
          throw new NotFoundException("User doesn't exist");
        }
        if (error.code === 'P2002') {
          throw new ForbiddenException('Credentials taken');
        }
        throw error;
      }
    }
  }

  async updateCookie(id: number, data: UpdateClientDto): Promise<Clients> {
    try {
      const updateData: Prisma.ClientsUpdateInput = {
        cookie: data.cookie ? { set: data.cookie } : undefined,
      };

      const updatedClient = await this.prisma.clients.update({
        where: { id42: id },
        data: updateData,
      });

      return updatedClient;
    } catch (error) {
      if (error instanceof Prisma.PrismaClientKnownRequestError) {
        if (error.code === 'P2025') {
          throw new NotFoundException("User doesn't exist");
        }
        if (error.code === 'P2002') {
          throw new ForbiddenException('Credentials taken');
        }
        throw error;
      }
    }
  }

  async getClientStatsById(id: number): Promise<ClientStats> {
    const clientStats = await this.prisma.clientStats.findUnique({
      where: { clientId: id },
      include: { client: true },
    });

    return clientStats;
  }

  async getTop100Scores(): Promise<ClientStats[]> {
    const top100Scores = await this.prisma.clientStats.findMany({
      orderBy: {
        score: 'asc',
      },
      take: 100,
    });

    return top100Scores;
  }

  async getRelationsByClientId1(
    id1: number,
  ): Promise<{ client: Clients | null; status: number }[]> {
    const clientRelations = await this.prisma.clientToClient.findMany({
      where: {
        client1Id: id1,
		status: 0,
      },
      orderBy: [
        {
          status: 'asc',
        },
        {
          client2: {
            name: 'asc',
          },
        },
      ],
      select: {
        client2: {
          select: {
            id: true,
            name: true,
            id42: true,
            img: true,
            cookie: true,
            Dfa: true,
            DfaSecret: true,
            dfaVerified: true,
          },
        },
        status: true,
      },
    });

    const formattedRelations: { client: Clients | null; status: number }[] =
      clientRelations.map((relation) => ({
        client: {
          id: relation.client2?.id,
          name: relation.client2?.name,
          id42: relation.client2?.id42,
          img: relation.client2?.img,
          cookie: relation.client2?.cookie,
          Dfa: relation.client2?.Dfa,
          DfaSecret: relation.client2?.DfaSecret,
          dfaVerified: relation.client2?.dfaVerified,
        },
        status: relation.status,
      }));

    return formattedRelations;
  }

  async getRoomsByUserId(userId: number): Promise<Rooms[]> {
    return await this.prisma.rooms.findMany({
      where: {
        members: {
          some: {
            id: userId,
          },
        },
      },
    });
  }
/*
  async getLastNMessagesByRoomId(
    roomId: number,
    n: number,
  ): Promise<[string, string][]> {
    const messages = await this.prisma.messagesRooms.findMany({
      where: {
        roomId,
      },
      orderBy: {
        time: 'desc',
      },
      take: n,
      include: {
        client: true,
      },
    });

    return messages.map((message) => [message.client.name, message.msg]);
  }
*/
  async createRelation(dto: createRelationsDto): Promise<ClientToClient> {
    try {
      const relation = await this.prisma.clientToClient.create({
        data: {
          client1Id: dto.idClient1,
          status: dto.status,
          client2Id: dto.idClient2,
        },
      });

      return relation;
    } catch (error) {
      if (error instanceof Prisma.PrismaClientKnownRequestError) {
        if (error.code === 'P2002') {
          throw new ForbiddenException('Credentials taken');
        }
      }
      throw error;
    }
  }
  /*
	async createRooom(dto: createRoomDto): Promise<Rooms>
	{
		try
		{
			const { name, ownerid, secu, password, client2Id } = dto;
			const room = await this.prisma.rooms.create({
				data: {
					name,
					ownerid,
					secu,
					password,
					client2Id,
				},
			});

			return room;
		}
		catch (error)
		{
			if (error instanceof Prisma.PrismaClientKnownRequestError)
			{
				if (error.code === 'P2002') {
					throw new ForbiddenException('Credentials taken');
				}
			}
			throw error;
		}
	}
*/
  async createRooom(dto: createRoomDto): Promise<Rooms> {
    try {
      const { name, ownerid, secu, password, client2Id } = dto;

      if (secu === 3) {
        if (!client2Id) {
          throw new BadRequestException(
            'client2Id est obligatoire lorsque secu est égal à 3',
          );
        }

        const client2 = await this.prisma.clients.findUnique({
          where: { id: client2Id },
          select: { name: true },
        });

        if (!client2) {
          throw new BadRequestException("client2Id spécifié n'existe pas");
        }

        const existingRoom = await this.prisma.rooms.findFirst({
          where: {
            OR: [
              { ownerid, client2Id },
              { ownerid: client2Id, client2Id: ownerid },
            ],
          },
        });

        if (existingRoom) {
          return existingRoom;
        }

        const room = await this.prisma.rooms.create({
          data: {
            name: dto.name,
            ownerid,
            secu,
            password,
            client2Id,
          },
        });

        return room;
      } else {
        const room = await this.prisma.rooms.create({
          data: {
            name,
            ownerid,
            secu,
            password,
            client2Id,
          },
        });

        return room;
      }
    } catch (error) {
      if (error instanceof Prisma.PrismaClientKnownRequestError) {
        if (error.code === 'P2025') {
          throw new NotFoundException("User doesn't exist");
        }
        if (error.code === 'P2002') {
          throw new ForbiddenException('Credentials taken');
        }
        throw error;
      }
    }
  }

  async getRooms(): Promise<{ id: number; name: string; secu: number }[]> {
    const rooms = await this.prisma.rooms.findMany({
      select: {
        id: true,
        name: true,
        secu: true,
      },
    });

    return rooms;
  }

  async getRoomsWhereUserIsNotMember(
    userId: number,
  ): Promise<{ id: number; name: string; secu: number }[]> {
    const rooms = await this.prisma.rooms.findMany({
      where: {
        NOT: {
          members: {
            some: {
              memberId: userId,
            },
          },
        },
      },
      select: {
        id: true,
        name: true,
        secu: true,
      },
    });

    return rooms;
  }

  async getRoomIdsAndNamesByClientId(
    clientId: number,
  ): Promise<{ roomId: number; roomName: string, secu: number, ownerid: number, client2Id: number }[]> {
    const roomMembers = await this.prisma.roomMembers.findMany({
		where: {
			memberId: clientId,
			NOT: {
				OR : [
				{status: 5},
				{status: 6}
				]
			}
			},
      select: {
        room: {
          select: {
            id: true,
            name: true,
			secu: true,
			ownerid: true,
			client2Id: true,
			client2: true,
          },
        },
      },
    });

    const roomIdsAndNames = roomMembers.map((roomMember) => ({
      roomId: roomMember.room.id,
      roomName: roomMember.room.name,
	  secu: roomMember.room.secu,
	  ownerid: roomMember.room.ownerid,
	  client2Id: roomMember.room.client2Id,
	  client2: roomMember.room.client2,
    }));

    return roomIdsAndNames;
  }

  async getRoomDetailsByClientId(clientId: number): Promise<
    {
      roomId: number;
      roomName: string;
      client2: Clients | null;
      owner: Clients | null;
      secu: number | null;
    }[]
  > {
    const roomMembers = await this.prisma.roomMembers.findMany({
      where: {
        memberId: clientId,
      },
      select: {
        room: {
          select: {
            id: true,
            name: true,
            client2: {
              select: {
                id: true,
                name: true,
                id42: true,
                img: true,
                cookie: true,
                Dfa: true,
                DfaSecret: true,
                dfaVerified: true,
              },
            },
            owner: {
              select: {
                id: true,
                name: true,
                id42: true,
                img: true,
                cookie: true,
                Dfa: true,
                DfaSecret: true,
                dfaVerified: true,
              },
            },
            secu: true,
          },
        },
      },
    });

    const roomDetails = roomMembers.map((roomMember) => ({
      roomId: roomMember.room.id,
      roomName: roomMember.room.name,
      client2: roomMember.room.client2 ?? null,
      owner: roomMember.room.owner ?? null,
      secu: roomMember.room.secu ?? null,
    }));

    return roomDetails;
  }

  /*
	async getRoomIdsAndNamesByClientId(clientId: number): Promise<{ roomId: number; roomName: string }[]> {
		const roomWithOwner = await this.prisma.rooms.findFirst({
			where: {
				ownerid: clientId,
			},
			select: {
				id: true,
				name: true,
			},
		});

		if (roomWithOwner) {
			return [{
				roomId: roomWithOwner.id,
				roomName: roomWithOwner.name,
			}];
		}

		const roomWithClient2 = await this.prisma.rooms.findFirst({
			where: {
				client2Id: clientId,
			},
			select: {
				id: true,
				owner: {
					select: {
						name: true,
					},
				},
			},
		});

		if (roomWithClient2) {
			return [{
				roomId: roomWithClient2.id,
				roomName: roomWithClient2.owner.name,
			}];
		}

		throw new Error("Room not Found");
	}
*/
  async addMemberToRoom(
    roomId: number,
    memberId: number,
    status = 2,
  ): Promise<RoomMembers | null> {
    try {
      const existingMember = await this.prisma.roomMembers.findFirst({
        where: {
          roomId,
          memberId,
        },
      });

      if (existingMember) {
        if (existingMember.status !== status)
          this.changeMemberStatus(roomId, memberId, status);
        return null; // Membre déjà membre de la salle, retourne null
      }

      const roomMember = await this.prisma.roomMembers.create({
        data: {
          roomId,
          memberId,
          status,
        },
      });

      return roomMember;
    } catch (error) {
      if (error instanceof Prisma.PrismaClientKnownRequestError) {
        if (error.code === 'P2025') {
          throw new NotFoundException("L'utilisateur n'existe pas");
        }
        if (error.code === 'P2002') {
          throw new ForbiddenException('Credentials taken');
        }
        throw error;
      }
    }
  }

  async getRoomById(roomId: number): Promise<Rooms | null> {
    try {
      const room = await this.prisma.rooms.findUnique({
        where: {
          id: roomId,
        },
      });

      return room || null;
    } catch (error) {
      throw error;
    }
  }

  async addMessageToRoom(
    roomId: number,
    clientId: number,
    message: string,
  ): Promise<MessagesRooms> {
    try {
      const newMessage = await this.prisma.messagesRooms.create({
        data: {
          msg: message,
          time: new Date(),
          roomId: roomId,
          clientId: clientId,
        },
      });

      return newMessage;
    } catch (error) {
      throw error;
    }
  }

  async getRoomByClientIdAndRoomId(
    clientId: number,
    roomId: number,
  ): Promise<{
    roomId: number;
    clientId: number;
    status: number;
    password: string;
  } | null> {
    const roomMember = await this.prisma.roomMembers.findFirst({
      where: {
        roomId,
        memberId: clientId,
      },
      select: {
        roomId: true,
        memberId: true,
        status: true,
        room: {
          select: {
            password: true,
          },
        },
      },
    });

    if (roomMember) {
      const { roomId, status, room } = roomMember;
      const password = room?.password || ''; // Accès au mot de passe
      return { roomId, clientId, status, password };
    }

    return null;
  }
/*
  async findClientsByName(clientId: number, name: string) {
    const clients = await this.prisma.clients.findMany({
      where: {
        name: {
          contains: name,
        },
        NOT: {
          OR: [
            {
              client2: {
                some: {
                  AND: [{ client1Id: clientId }, { status: 1 }],
                },
              },
            },
            {
              client1: {
                some: {
                  AND: [{ client2Id: clientId }, { status: 1 }],
                },
              },
            },
          ],
        },
      },
    });

    return clients;
  }

  async getRoomMessagesById(roomId: number): Promise<any[]> {
    const messages = await this.prisma.messagesRooms.findMany({
      where: {
        roomId: roomId,
      },
      select: {
        msg: true,
        client: {
          select: {
            name: true,
            id: true,
          },
        },
      },
    });

    return messages.map((message) => ({
      message: message.msg,
      clientId: message.client.id,
      clientName: message.client.name,
    }));
  }
*/

  async getRoomMessagesById(roomId: number, idClient: number): Promise<any[]> {
	const messages = await this.prisma.messagesRooms.findMany({
		where: {
		  roomId: roomId,
		  NOT: {
			OR: [{
			  client: {
				client1: {
				  some: {
					client1Id: idClient,
					status: 1
				  }
				}
			  }
			},
			{
			  client: {
				client2: {
				  some: {
					client2Id: idClient,
					status: 1
				  }
				}
			  }
			}
		  ]}
		},
		select: {
		  msg: true,
		  client: {
			select: {
			  name: true,
			  id: true,
			},
		  },
		},
		orderBy: {
		  time: 'asc',
		}
	  });

    return messages.map((message) => ({
      message: message.msg,
      clientId: message.client.id,
      clientName: message.client.name,
    }));
  }

  async getBannedRelationshipsForId(clientId: number) {
    const banned = await this.prisma.clientToClient.findMany({
        where: {
          OR: [{
            client1Id: clientId,
            status: 1
          },
          {
            client2Id: clientId,
            status: 1
          }]
        },
        select: {
          client1: {
            select: {
              name: true,
              id: true,
            }
          },
          client2: {
            select: {
              name: true,
              id: true,
            }
          }
        }
      });

      return banned;
  }

  async blockedMemberForClientId(id: number){
	const response = await this.prisma.clientToClient.findMany({
	  where: {
		client1Id: id,
		status: 1
	  },
	  select: {
		client2: {
		  select: {
			id: true,
			name: true,
		  },
		},
	  },
	});
  
	return response || null;
  }

  async addClientsToClient(
    id1: number,
    id2: number,
    status: number,
  ): Promise<void> {
    const existingBlockedRelation = await this.prisma.clientToClient.findFirst({
      where: {
        OR: [
          { client1Id: id1, client2Id: id2, status: 1 },
          { client1Id: id2, client2Id: id1, status: 1 },
        ],
      },
    });

    if (!existingBlockedRelation) {
      try {
        await this.prisma.clientToClient.createMany({
          data: [
            { client1Id: id1, client2Id: id2, status },
            { client1Id: id2, client2Id: id1, status },
          ],
        });
      } catch (error) {
        console.log(error);
        if (error instanceof Prisma.PrismaClientKnownRequestError) {
          if (error.code === 'P2025') {
            throw new NotFoundException("User doesn't exist");
          }
          if (error.code === 'P2002') {
            throw new ForbiddenException('Credentials taken');
          }
          throw error;
        }
      }
    }
  }

  async removeClientsFromClient(id1: number, id2: number): Promise<void> {
    const existingFriendRelation1 = await this.prisma.clientToClient.findFirst({
      where: {
        client1Id: id1,
        client2Id: id2,
        status: 0,
      },
    });

    const existingFriendRelation2 = await this.prisma.clientToClient.findFirst({
      where: {
        client1Id: id2,
        client2Id: id1,
        status: 0,
      },
    });

    if (existingFriendRelation1 && existingFriendRelation2) {
      try {
        await this.prisma.clientToClient.deleteMany({
          where: {
            client1Id: id1,
            client2Id: id2,
          },
        });

        await this.prisma.clientToClient.deleteMany({
          where: {
            client1Id: id2,
            client2Id: id1,
          },
        });
      } catch (error) {
        if (error instanceof Prisma.PrismaClientKnownRequestError) {
          if (error.code === 'P2025') {
            throw new NotFoundException("User doesn't exist");
          }
          if (error.code === 'P2002') {
            throw new ForbiddenException('Credentials taken');
          }
          throw error;
        }
      }
    }
  }

  async createBlockedRelation(
    id1: number,
    id2: number,
  ): Promise<ClientToClient> {
    const existingFriendRelation = await this.prisma.clientToClient.findFirst({
      where: {
        client1Id: id1,
        client2Id: id2,
        status: 0,
      },
    });

    if (existingFriendRelation) {
      // Supprimer les relations existantes
      await this.removeClientsFromClient(id1, id2);
    }
    try {
      const relation = await this.prisma.clientToClient.create({
        data: {
          client1Id: id1,
          client2Id: id2,
          status: 1,
        },
      });

      return relation;
    } catch (error) {
      if (error instanceof Prisma.PrismaClientKnownRequestError) {
        if (error.code === 'P2025') {
          throw new NotFoundException("User doesn't exist");
        }
        if (error.code === 'P2002') {
          throw new ForbiddenException('Credentials taken');
        }
        throw error;
      }
    }
  }

  async unblockClient(id1: number, id2: number): Promise<void> {
    await this.prisma.clientToClient.deleteMany({
      where: {
        client1Id: id1,
        client2Id: id2,
        status: 1,
      },
    });
  }

  async getClientRelations(id1: number): Promise<ClientToClient[]> {
    const clientRelations = await this.prisma.clientToClient.findMany({
      where: {
        client1Id: id1,
      },
    });

    return clientRelations;
  }
  /*
	async getMembersByRoomId(roomId: number): Promise<Clients[]> {
		const roomMembers = await this.prisma.roomMembers.findMany({
			where: { roomId },
			include: { member: true },
		});

		if (!roomMembers) {
			throw new NotFoundException(`Room with ID ${roomId} not found`);
		}

		const members = roomMembers.map((roomMember) => roomMember.member);

		return members;
	}
*/

  async getMembersByRoomId(roomId: number) {
    const roomMembers = await this.prisma.roomMembers.findMany({
      where: { roomId },
      include: {
        member: true,
      },
    });

    return roomMembers.map((roomMember) => ({
      member: roomMember.member,
      status: roomMember.status,
    }));
  }

  async getClientNamesListByTheirIds(ids: number[] | null): Promise<string[]> {
    if (ids === null) {
      return null;
    }

    const clients = await this.prisma.clients.findMany({
      where: {
        id: {
          in: ids,
        },
      },
      select: {
        name: true,
      },
    });

    const clientNames = clients.map((client) => client.name);

    return clientNames;
  }
  /*
	async getRoomsByOwnerId(ownerId: number): Promise<Rooms[]> {
		const rooms = await this.prisma.rooms.findMany({
			where: {
				ownerid: ownerId,
				secu: {
					not: 3,
				}
			},
		});

		return rooms;
	}
*/

  async getRoomsByOwnerId(
    ownerId: number,
  ): Promise<{ room: Rooms; status: number }[]> {
    const rooms = await this.prisma.rooms.findMany({
      where: {
        OR: [
          {
            ownerid: ownerId,
            secu: {
              not: 3,
            },
          },
          {
            members: {
              some: {
                memberId: ownerId,
                status: 1,
              },
            },
          },
        ],
      },
      include: {
        members: true,
      },
    });

    const result = rooms.map((room) => {
      const member = room.members.find((member) => member.memberId === ownerId);
      const status = member ? member.status : null;
      return { room, status };
    });

    return result;
  }

  async getMembersForPrivateRoom(
    roomId: number,
  ): Promise<{ id: number; name: string }[]> {
    const members = await this.prisma.roomMembers.findMany({
      where: {
        roomId: roomId,
        status: 6,
        room: {
          secu: 2,
        },
      },
      select: {
        member: {
          select: {
            id: true,
            name: true,
          },
        },
      },
    });

    return members.map((roomMember) => ({
      id: roomMember.member.id,
      name: roomMember.member.name,
    }));
  }

  async getMembersByRoomIdExcludingClient(
    roomId: number,
    clientId: number,
  ): Promise<{ id: number; name: string; status: number }[]> {
    const roomMembers = await this.prisma.roomMembers.findMany({
      where: {
        roomId,
        NOT: {
          memberId: clientId,
        },
        status: {
          not: 6,
        },
      },
      include: {
        member: true,
      },
      orderBy: {
        status: 'asc',
      },
    });

    if (!roomMembers) {
      throw new NotFoundException(`Room with ID ${roomId} not found`);
    }

    const members = roomMembers.map((roomMember) => ({
      id: roomMember.member.id,
      name: roomMember.member.name,
      status: roomMember.status,
    }));

    return members;
  }

  async getMembersByRoomIdExcludingClientForAdmins(
    roomId: number,
    clientId: number,
  ): Promise<{ id: number; name: string; status: number }[]> {
    const roomMembers = await this.prisma.roomMembers.findMany({
      where: {
        roomId,
        NOT: {
          memberId: clientId,
        },
        status: {
          notIn: [0, 1],
        },
      },
      include: {
        member: true,
      },
      orderBy: {
        status: 'asc',
      },
    });

    if (!roomMembers) {
      throw new NotFoundException(`Room with ID ${roomId} not found`);
    }

    const members = roomMembers.map((roomMember) => ({
      id: roomMember.member.id,
      name: roomMember.member.name,
      status: roomMember.status,
    }));

    return members;
  }

  async changeMemberStatus(
    roomId: number,
    memberId: number,
    newStatus: number,
  ): Promise<void> {
    try {
      await this.prisma.roomMembers.update({
        where: {
          roomId_memberId: {
            roomId,
            memberId,
          },
        },
        data: {
          status: newStatus,
        },
      });
    } catch (error) {
      if (error instanceof Prisma.PrismaClientKnownRequestError) {
        if (error.code === 'P2025') {
          throw new NotFoundException("User doesn't exist");
        }
        if (error.code === 'P2002') {
          throw new ForbiddenException('Credentials taken');
        }
        throw error;
      }
    }
  }

  async getRoomsExcludingBannedOnes(clientId: number) {
    const rooms = await this.prisma.rooms.findMany({
      where: {
        members: {
          none: {
            memberId: clientId,
            status: 5,
          },
        },
      },
      select: {
        id: true,
        name: true,
      },
    });

    return rooms.map((room) => ({ id: room.id, name: room.name }));
  }

  /*
	async getRoomsExcludingWhereClientIsMember(clientId: number) {
		const rooms = await this.prisma.rooms.findMany({
			where: {
				NOT: {
					members: {
						some: {
							memberId: clientId,
						},
					},
				},
			},
			select: {
				id: true,
				name: true,
			},
		});

		return rooms.map((room) => ({ id: room.id, name: room.name }));
	}
*/

  async getRoomsExcludingWhereClientIsMember(clientId: number) {
    const rooms = await this.prisma.rooms.findMany({
      where: {
        NOT: {
          members: {
            some: {
              memberId: clientId,
            },
          },
        },
        owner: {
          NOT: {
            id: clientId,
          },
        },
      },
      select: {
        id: true,
        name: true,
        secu: true,
      },
    });

    return rooms;
  }

  async getRoomsAndMembersExcludingWhereClientIsMember(clientId: number) {
    const rooms = await this.prisma.rooms.findMany({
      where: {
        NOT: {
          members: {
            some: {
              memberId: clientId,
            },
          },
        },
        owner: {
          NOT: {
            id: clientId,
          },
        },
      },
      select: {
        id: true,
        name: true,
        secu: true,
        members: true,
      },
    });

    const filteredRooms = rooms.filter(room => room.secu !== 3);

    return filteredRooms;
  }

  async getRoomAdmins(roomId: number): Promise<{ id: number; name: string }[]> {
    const roomMembers = await this.prisma.roomMembers.findMany({
      where: {
        roomId: roomId,
        status: 1,
      },
      select: {
        member: {
          select: {
            id: true,
            name: true,
          },
        },
      },
    });

    const members = roomMembers.map((roomMember) => ({
      id: roomMember.member.id,
      name: roomMember.member.name,
    }));

    return members;
  }

  async changeRoomOwner(
    roomId: number,
    newOwnerId: number,
  ): Promise<Rooms | null> {
    const room = await this.prisma.rooms.update({
      where: {
        id: roomId,
      },
      data: {
        ownerid: newOwnerId,
      },
    });

    return room;
  }

  async checkRoomOwner(roomId: number, ownerId: number): Promise<Rooms | null> {
    const room = await this.prisma.rooms.findFirst({
      where: {
        id: roomId,
        ownerid: ownerId,
      },
    });

    return room;
  }

  async checkRoomMember(
    roomId: number,
    memberId: number,
  ): Promise<RoomMembers | null> {
    const roomMember = await this.prisma.roomMembers.findFirst({
      where: {
        roomId,
        memberId,
      },
    });

    return roomMember;
  }

  async getRoomReplacementMembers(roomId: number) {
    const roomMembers = await this.prisma.roomMembers.findMany({
      where: {
        roomId: roomId,
      },
      select: {
        member: {
          select: {
            id: true,
            name: true,
          },
        },
        status: true,
      },
    });

    const admins = roomMembers.filter((member) => member.status === 1);
    const members = roomMembers.filter((member) => member.status === 2);

    const adminsList = admins.map((member) => ({
      id: member.member.id,
      name: member.member.name,
    }));

    const membersList = members.map((member) => ({
      id: member.member.id,
      name: member.member.name,
    }));

    return {
      admins: adminsList,
      members: membersList,
    };
  }

  async removeClientFromRoom(roomId: number, memberId: number) {
    try {
      await this.prisma.roomMembers.delete({
        where: {
          roomId_memberId: {
            roomId,
            memberId,
          },
        },
      });
    }
    catch (error) {
      throw new Error('Failed to remove client from room');
    }
  }

  async deleteRoomWithMembers(roomId: number): Promise<void> {
    const room = await this.prisma.rooms.findUnique({
      where: {
        id: roomId,
      },
    });
    if (!room) {
      throw new NotFoundException('Room not found');
    }

    // Supprimer les roomMembers associés à la room
    await this.prisma.roomMembers.deleteMany({
      where: { roomId },
    });

    // Supprimer la room
    await this.prisma.rooms.delete({
      where: { id: roomId },
    });
  }
  /*
	async getAllRoomMembers(clientId42:number, roomName: string)
	{
		const roomId = await this.prisma.rooms.findUnique({
			where:{
				name: roomName
			},
			select:{
				id: true
			}
		});
		if (!roomId)
			throw new NotFoundException("Object Not Found");

		const members = await this.prisma.roomMembers.findMany({
			where:{
				room: {
					name: roomName,
				}
			},
			select: {
				status: true,
				member:{
					select: {
						name: true,
						id: true,
						id42: true,
					}
				},
				room:{
					select:{
						id: true
					}
				}
			}
		})

		const userStatus = members.find(obj => obj.member.id42 === clientId42)?.status;
		if (userStatus !== 1 && userStatus !== 0)
			throw new UnauthorizedException("acces denied");

		const retMembers = members
			.filter(member => member.member.id42 !== clientId42)
			.map(member => ({
				name: member.member.name,
				id: member.member.id,
				status: member.status
			}));
		
		return { retMembers, userStatus, roomId };
	}
*/
  async getAllRoomMembers(clientId42: number, roomName: string) {
    const roomId = await this.prisma.rooms.findUnique({
      where: {
        name: roomName,
      },
      select: {
        id: true,
      },
    });
    if (!roomId) throw new NotFoundException('Object Not Found');

    const userStatus = await this.prisma.roomMembers.findFirst({
      where: {
        room: {
          name: roomName,
        },
        member: {
          id42: clientId42,
        },
      },
      select: {
        status: true,
      },
    });
    if (userStatus.status !== 1 && userStatus.status !== 0)
      throw new UnauthorizedException('acces denied');
    return { status: userStatus.status, roomId: roomId };
  }

  async getRoomIdByName(roomName: string)
  {
    const id = await this.prisma.rooms.findUnique({
      where: {
        name: roomName,
      },
      select: {
        id: true,
      }
    });

    return id;
  }

  async deleteClientById(clientId: number): Promise<void> {
    await this.prisma.$transaction(async (prisma) => {
      // Supprimer le client des membres de salle
      await prisma.roomMembers.deleteMany({
        where: {
          memberId: clientId,
        },
      });

      // Supprimer les enregistrements de l'historique de jeu du client
      await prisma.gameHistoric.deleteMany({
        where: {
          OR: [
            {
              client1Id: clientId,
            },
            {
              client2Id: clientId,
            },
          ],
        },
      });

      // Supprimer les relations ClientToClient du client
      await prisma.clientToClient.deleteMany({
        where: {
          OR: [
            {
              client1Id: clientId,
            },
            {
              client2Id: clientId,
            },
          ],
        },
      });

      // Supprimer les messages du client
      await prisma.messagesRooms.deleteMany({
        where: {
          clientId: clientId,
        },
      });

      // Supprimer les statistiques du client
      await prisma.clientStats.deleteMany({
        where: {
          clientId: clientId,
        },
      });

      // Supprimer le client lui-même
      await prisma.clients.delete({
        where: {
          id: clientId,
        },
      });
    });
  }

  async roomUserCheck(roomId: number, memberId: number)
  {
    const response = await this.prisma.roomMembers.findUnique({
      where: {
          roomId_memberId: {
            roomId,
            memberId,
          },
      },
      select: {
        status: true,
      }
    });

    return response || null;
  }

  async updateRoom(roomid: number, data: updateRoomDto)
  {
    try{
      await this.prisma.rooms.update({
        where: {
          id: roomid,
        },
        data
      });
    }
    catch (error) {
      if (error instanceof Prisma.PrismaClientKnownRequestError) {
        if (error.code === 'P2025') {
          throw new NotFoundException("Room doesn't exist");
        }
        if (error.code === 'P2002') {
          throw new ForbiddenException('name already taken');
        }
        throw error;
      }
    }
  }
  async preDelCheck(clientId: number)
  {
    const response = await this.prisma.rooms.findFirst({
      where: {
        ownerid: clientId
      },
      select: {
        ownerid: true,
      }
    });

    return response || null;
  }

  async clientInStat(clientId: number)
  {
    const client = await this.prisma.clientStats.findUnique({
      where: {
        clientId
      },
      select: {
        clientId: true,
      }
    });

    return client || null;
  }

  async win(clientId: number)
  {
    if (await this.clientInStat(clientId))
    {
      await this.prisma.clientStats.update({
        where: {
          clientId
        },
        data: {
          played: {
            increment: 1,
          },
          won:{
            increment: 1,
          }
        }
      });
    }
    else
    {
      await this.prisma.clientStats.create({
        data: {
          played: 1,
          won: 1,
          score: 10,
          clientId
        }
      });
    }
  }

  async lose(clientId: number)
  {
    if (await this.clientInStat(clientId))
    {
      await this.prisma.clientStats.update({
        where: {
          clientId
        },
        data: {
          played: {
            increment: 1,
          }
        }
      });
    }
    else
    {
      await this.prisma.clientStats.create({
        data: {
          played: 1,
          won: 0,
          score: 0,
          clientId
        }
      });
    }
  }
  
  async historicnewEntry(data: gameHistoricDto){
    try {
      const dataa =  await this.prisma.gameHistoric.create({
        data: {
          persScore: data.persScore,
          vsScore: data.vsScore,
          client1Id: data.client1Id,
          client2Id: data.client2Id,
        }
      })
    }
    catch (error) {
      if (error instanceof Prisma.PrismaClientKnownRequestError) {
        if (error.code === 'P2025') {
          throw new NotFoundException("User doesn't exist");
        }
      }
    }
  }

  async getGameHistoric(clientId: number)
  {
    const response = await this.prisma.gameHistoric.findMany({
      where: {
        OR: [{
          client1Id: clientId,
        },
        {
          client2Id: clientId,
        }]
      },
      select: {
        persScore: true,
        vsScore: true,
        client1: {
          select: {
            name: true,
            id: true
          }
        },
        client2: {
          select: {
            name: true,
            id: true
          }
        }
      }
    });

    return response;
  }

  async dfaSwitch(id: number) {
    const dfaStatus = await this.prisma.clients.findUnique({
      where: {
        id42: id
      },
      select: {
        dfaVerified: true
      }
    });

    if (dfaStatus) {
      const newDfaStatus = !dfaStatus.dfaVerified;

      await this.prisma.clients.update({
        where: {
          id42: id
        },
        data: {
          dfaVerified: newDfaStatus
        }
      });
    }
}
}
