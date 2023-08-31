export class Player {
  idDb: number;
  idSock: string;
  room: string;
}

export class Lobby {
  private plyer: Player[] = [];

  addPlayer(player: Player) {
    this.plyer.push(player);
  }

  deletePlayer(idSock: string): void {
    this.plyer = this.plyer.filter((player) => player.idSock !== idSock);
  }

  findPlayer(idSock: string): Player | undefined {
    return this.plyer.find((player) => player.idSock === idSock);
  }

  findPlayersInList(playerList: Player[]): Player[] {
    return this.plyer.filter((player) =>
      playerList.some((p) => p.idDb === player.idDb),
    );
  }

  getRoomById(idSock: string): string | undefined {
    const player = this.findPlayer(idSock);
    return player ? player.room : undefined;
  }

  getFullAwaitingLobby(): number[] {
    return this.plyer
      .filter((player) => player.room === null)
      .map((player) => player.idDb);
  }

  getFullLPlayingobby(): number[] {
    return this.plyer
      .filter((player) => player.room === null)
      .map((player) => player.idDb);
  }

  getFullLobby(): number[] {
    return this.plyer.map((player) => player.idDb);
  }
}
