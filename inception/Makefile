NAME = inception

all:
	@ if [ -d "/home/silas/inception" ]; then docker-compose -f srcs/docker-compose.yml up; else docker-compose -f srcs/docker-compose.yml up --build; fi
	
stop:
	@ docker-compose -f srcs/docker-compose.yml down

clean: stop
	@ docker system prune -a && docker volume prune && sudo rm -rf /home/silas/inception

re: 
	@ docker-compose -f srcs/docker-compose.yml up --build

.PHONY: stop clean re all
