export function createGameState() {
  return {
    ball: {
      x: 600 / 2,
      y: 400 / 2,
      radius: 10,
      velocityX: 4.3,
      velocityY: 4.3,
      speed: 7.3,
      color: 'WHITE',
    },
    user: {
      x: 0, // left side of canvas
      y: (400 - 100) / 2, // -100 the height of paddle
      width: 10,
      height: 100,
      score: 0,
      color: 'WHITE',
    },
    com: {
      x: 600 - 10, // - width of paddle
      y: (400 - 100) / 2, // -100 the height of paddle
      width: 10,
      height: 100,
      score: 0,
      color: 'WHITE',
    },
    net: {
      x: (600 - 2) / 2,
      y: 0,
      height: 10,
      width: 2,
      color: 'RED',
    },
  };
}

export function gameLoop(state: any) {
  if (!state) {
    return;
  }

  let player: any;

  if (state.ball.x - state.ball.radius < 0) {
    state.com.score++;
    if (state.com.score === 20) return 2;
    resetBall(state);
  } else if (state.ball.x + state.ball.radius > 600) {
    state.user.score++;
    if (state.user.score === 20) return 1;
    resetBall(state);
  }

  if (state.ball.y - state.ball.radius < 0)
    state.ball.velocityY = Math.abs(state.ball.velocityY);
  else if (state.ball.y + state.ball.radius > 400)
    state.ball.velocityY = -Math.abs(state.ball.velocityY);

  player = state.ball.x < 600 / 2 ? state.user : state.com;
  if (precolision(state, player)) {
    let collidePoint = state.ball.y - (player.y + player.height / 2);
    collidePoint = collidePoint / (player.height / 2);
    const angleRad = (Math.PI / 4) * collidePoint;
    const direction = state.ball.x + state.ball.radius < 600 / 2 ? 1 : -1;
    state.ball.velocityX = direction * state.ball.speed * Math.cos(angleRad);
    state.ball.velocityY = state.ball.speed * Math.sin(angleRad);
    state.ball.speed += 0.5;
  } else {
    state.ball.x += state.ball.velocityX;
    state.ball.y += state.ball.velocityY;
  }
}

function precolision(state: any, player: any) {
  const test = false;

  const m: number = state.ball.velocityY / state.ball.velocityX;
  const b: number = state.ball.y - m * state.ball.x;
  const newx: number = state.ball.x + state.ball.velocityX;
  const newy: number = state.ball.y + state.ball.velocityY;
  if (state.ball.x < 600 / 2) {
    let dist: number = Math.sqrt(
      Math.pow(newx - (player.x + player.width), 2) +
        Math.pow(newy - player.y, 2),
    );
    if (dist <= state.ball.radius) return 1;
    dist = Math.sqrt(
      Math.pow(newx - (player.x + player.width), 2) +
        Math.pow(newy - (player.y + player.height), 2),
    );
    if (dist <= state.ball.radius) return 1;
    const xcolision: number = /*xmur ?*/ 0 + player.width + state.ball.radius;
    if (newx < xcolision && xcolision < state.ball.x) {
      const ycolision: number = m * xcolision + b;
      if (player.y + player.height >= ycolision && ycolision >= player.y) {
        state.ball.x = xcolision;
        state.ball.y = ycolision;
        return 1;
      }
    }
  } else {
    let dist: number = Math.sqrt(
      Math.pow(newx - player.x, 2) + Math.pow(newy - player.y, 2),
    );
    if (dist <= state.ball.radius) return 1;
    dist = Math.sqrt(
      Math.pow(newx - player.x, 2) +
        Math.pow(state.ball.y - (newy + player.height), 2),
    );
    if (dist <= state.ball.radius) return 1;
    const xcolision: number = /*xmur ?*/ 600 - player.width - state.ball.radius;
    if (state.ball.x < xcolision && xcolision < newx) {
      const ycolision: number = m * xcolision + b;
      if (player.y + player.height >= ycolision && ycolision >= player.y) {
        state.ball.x = xcolision;
        state.ball.y = ycolision;
        return 1;
      }
    }
  }
  return 0;
}

function collision(b: any, p: any) {
  p.top = p.y;
  p.bottom = p.y + p.height;
  p.left = p.x;
  p.right = p.x + p.width;

  b.top = b.y - b.radius;
  b.bottom = b.y + b.radius;
  b.left = b.x - b.radius;
  b.right = b.x + b.radius;

  return (
    p.left < b.right && p.top < b.bottom && p.right > b.left && p.bottom > b.top
  );
}

function resetBall(state: any) {
  state.ball.x = 600 / 2;
  state.ball.y = 400 / 2;
  state.ball.velocityX = -state.ball.velocityX;
  state.ball.speed = 7;
}
