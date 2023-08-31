import {
  IsString,
  IsNotEmpty,
  MaxLength,
  IsNumber,
  IsOptional,
} from 'class-validator';

export class ClientDto {
  @IsNumber()
  @IsNotEmpty()
  id42: number;

  @IsString()
  @MaxLength(100)
  img: string;

  @IsString()
  @MaxLength(50)
  name: string;

  @IsNotEmpty()
  @IsString()
  @MaxLength(250)
  cookie: string;
}

export class updateRoomDto {
  name?:string;

  @IsNumber()
  secu?: number;
  password?: string;
}
