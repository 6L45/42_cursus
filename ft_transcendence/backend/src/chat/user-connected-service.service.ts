import { Injectable } from '@nestjs/common';
import { disconnect } from 'process';
import { Socket } from 'socket.io';
import { e_status } from 'src/interfaces/e_status.interface';

@Injectable()
export class UserConnectedService {
  hmapconnected = new Map<string, number>();
  hmapingame = new Map<string, number>();

  addUser(socket: Socket, userId: number): void {
    this.hmapconnected.set(socket.id, userId);
  }

  deleteUser(socket: Socket): void {
    try
    {
        this.hmapconnected.delete(socket.id);
    }
    catch
    {
        return;
    }
    this.deleteInGame(socket);
  }

  checkStatus(id: number): number {
    let status: e_status = e_status.Disconnected;
    this.hmapconnected.forEach((value, key, map) => {
      if (value == id) status = e_status.Connected;;
    });
    this.hmapingame.forEach((value, key, map) => {
      if (value == id) status = e_status.InGame;;
    });
    return status;
  }

  addInGame(socket: Socket): void {
    let userId:number = 0;
    this.hmapconnected.forEach((value, key, map) => {
      if (key == socket.id) userId = value;
    });
    if (userId !== 0)
        this.hmapingame.set(socket.id, userId);
  }

  deleteInGame(socket: Socket): void {
    try
    {
        this.hmapingame.delete(socket.id);
    }
    catch
    {
        return;
    }
  }

  findSocketId(id: number): string {
    let res = '';
    this.hmapconnected.forEach((value, key, map) => {
      if (value == id) res = key;
    });
    return res;
  }

  findId(socket_id: string): number {
    let res = null;
    this.hmapconnected.forEach((value, key, map) => {
      if (key == socket_id) res = value;
    });
    return res;
  }
}
