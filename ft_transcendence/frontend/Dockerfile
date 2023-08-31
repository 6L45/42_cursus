# stage build
FROM node:19.9

ARG HOSTNAME
ARG PUBLIC_HOSTNAME
ARG PUBLIC_API
ARG PUBLIC_DOMAIN_BACK

ENV HOSTNAME ${HOSTNAME}
ENV PUBLIC_HOSTNAME ${PUBLIC_HOSTNAME}
ENV PUBLIC_API_42 ${PUBLIC_API_42}
ENV PUBLIC_DOMAIN_BACK ${PUBLIC_DOMAIN_BACK}

WORKDIR /appli

# copy everything to the container

RUN npm install -g npm@latest

# clean install all dependencies
# RUN npm ci
# RUN npm audit fix

# build SvelteKit app
# RUN npm run build

# CMD ["node", "build/index.js"]

ENTRYPOINT [ "/bin/bash", "entrypoint.sh"]