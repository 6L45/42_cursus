import { IsNotEmpty, IsNumber, IsOptional, IsString } from 'class-validator';

export class createRelationsDto {
  @IsNotEmpty()
  @IsNumber()
  idClient1: number;

  @IsNotEmpty()
  status: number;

  @IsNotEmpty()
  @IsNumber()
  idClient2: number;
}

export class createStatsDto {
  @IsNotEmpty()
  @IsNumber()
  played: number;

  @IsNotEmpty()
  @IsNumber()
  won: number;

  @IsNotEmpty()
  @IsNumber()
  score: number;

  @IsNotEmpty()
  @IsString()
  hf: string;

  @IsNotEmpty()
  @IsNumber()
  clientId: number;
}

export class updateStatDto {
  clientId: number;
  played: number;
  won: number;
  title: string;
  score: number;
  hf: string;
}

export class createRoomDto {
  @IsNotEmpty()
  @IsString()
  name: string;

  @IsOptional()
  @IsString()
  name2: string;

  @IsNotEmpty()
  @IsNumber()
  ownerid: number;

  @IsNotEmpty()
  @IsNumber()
  secu: number;

  @IsOptional()
  password?: string;

  @IsOptional()
  client2Id: number;
}
