import { HttpException, Injectable } from '@nestjs/common';
import axios from 'axios'; // import default without scopes
import type User42Interface from './user42.interface';

@Injectable()
export class AuthService {
  async get_token(code: any): Promise<any> {
    const data = {
      grant_type: 'authorization_code',
      code,
      client_id: process.env.CLIENT_ID,
      client_secret: process.env.CLIENT_SECRET,
      redirect_uri: 'http://' + process.env.HOSTNAME + ':8080/api/auth',
    };
    const response = axios.post('https://api.intra.42.fr/oauth/token', data);
    const token = await response
      .then((res: any) => {
        return res.data.access_token;
      })
      .catch((err: any) => {
        console.error(err);
        throw new HttpException(err.response.data.error, err.response.status);
      });
    return token;
  }

  async get_user_info(access_token: string): Promise<User42Interface> {
    const headers = { Authorization: `Bearer ${access_token}` };
    const response = await axios.get('https://api.intra.42.fr/v2/me', {
      headers,
    });
    return response.data;
  }
}
