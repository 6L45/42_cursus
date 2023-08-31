import {
  IsString,
  IsNotEmpty,
  MaxLength,
  IsNumber,
  IsOptional,
} from 'class-validator';

export class MessagesRoomsDto {
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
