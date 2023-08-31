export function load({ cookies }) {
	const myJwtCookie = cookies.get('jwt_cookie');
	const myid42 = cookies.get('id42');

	return {
		myJwtCookie,
		myid42
	};
}