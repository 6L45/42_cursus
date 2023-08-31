#!/bin/bash

docker rm $(docker ps -aq) &&\
docker rmi $(docker images -q) &&\
docker volume rm $(docker volume ls | tail -n 3 | awk '{print $2}') &&\
docker volume prune &&\
docker network prune &&\
docker system prune &&\
docker-compose up --build

