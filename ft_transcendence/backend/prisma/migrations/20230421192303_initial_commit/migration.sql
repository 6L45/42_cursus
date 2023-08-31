-- CreateTable
CREATE TABLE "Clients" (
    "id" SERIAL NOT NULL,
    "img" BYTEA,
    "name" VARCHAR(50) NOT NULL,
    "pseudo" VARCHAR(50) NOT NULL,
    "email" VARCHAR(100) NOT NULL,
    "cookie" VARCHAR(200) NOT NULL,
    "num" VARCHAR(15) NOT NULL,
    "memberOf" INTEGER[],

    CONSTRAINT "Clients_pkey" PRIMARY KEY ("id")
);

-- CreateTable
CREATE TABLE "clients_to_clients" (
    "id" SERIAL NOT NULL,
    "client1Id" INTEGER NOT NULL,
    "client2Id" INTEGER NOT NULL,
    "status" VARCHAR(10) NOT NULL,

    CONSTRAINT "clients_to_clients_pkey" PRIMARY KEY ("id")
);

-- CreateTable
CREATE TABLE "client_stats" (
    "id" SERIAL NOT NULL,
    "clientId" INTEGER NOT NULL,
    "title" VARCHAR(50) NOT NULL,
    "played" INTEGER NOT NULL,
    "won" INTEGER NOT NULL,
    "score" INTEGER NOT NULL,
    "hf" VARCHAR(100) NOT NULL,

    CONSTRAINT "client_stats_pkey" PRIMARY KEY ("id")
);

-- CreateTable
CREATE TABLE "rooms" (
    "id" SERIAL NOT NULL,
    "name" VARCHAR(50) NOT NULL,
    "ownerid" INTEGER NOT NULL,
    "admins" INTEGER[],
    "members" INTEGER[],

    CONSTRAINT "rooms_pkey" PRIMARY KEY ("id")
);

-- CreateTable
CREATE TABLE "messages_rooms" (
    "id" SERIAL NOT NULL,
    "msg" TEXT NOT NULL,
    "time" TIMESTAMP(3) NOT NULL DEFAULT CURRENT_TIMESTAMP,
    "roomId" INTEGER NOT NULL,
    "clientId" INTEGER NOT NULL,

    CONSTRAINT "messages_rooms_pkey" PRIMARY KEY ("id")
);

-- CreateTable
CREATE TABLE "messages_client_to_client" (
    "id" SERIAL NOT NULL,
    "clientSrcId" INTEGER NOT NULL,
    "clientDestId" INTEGER NOT NULL,
    "message" TEXT NOT NULL,
    "time" TIMESTAMP(3) NOT NULL DEFAULT CURRENT_TIMESTAMP,

    CONSTRAINT "messages_client_to_client_pkey" PRIMARY KEY ("id")
);

-- CreateIndex
CREATE UNIQUE INDEX "Clients_name_key" ON "Clients"("name");

-- CreateIndex
CREATE UNIQUE INDEX "Clients_pseudo_key" ON "Clients"("pseudo");

-- CreateIndex
CREATE UNIQUE INDEX "Clients_email_key" ON "Clients"("email");

-- CreateIndex
CREATE UNIQUE INDEX "Clients_num_key" ON "Clients"("num");

-- CreateIndex
CREATE INDEX "clients_to_clients_status_idx" ON "clients_to_clients"("status");

-- CreateIndex
CREATE UNIQUE INDEX "client_stats_clientId_key" ON "client_stats"("clientId");

-- CreateIndex
CREATE INDEX "owner_idx" ON "rooms"("ownerid");

-- CreateIndex
CREATE UNIQUE INDEX "rooms_name_key" ON "rooms"("name");

-- AddForeignKey
ALTER TABLE "clients_to_clients" ADD CONSTRAINT "clients_to_clients_client1Id_fkey" FOREIGN KEY ("client1Id") REFERENCES "Clients"("id") ON DELETE RESTRICT ON UPDATE CASCADE;

-- AddForeignKey
ALTER TABLE "clients_to_clients" ADD CONSTRAINT "clients_to_clients_client2Id_fkey" FOREIGN KEY ("client2Id") REFERENCES "Clients"("id") ON DELETE RESTRICT ON UPDATE CASCADE;

-- AddForeignKey
ALTER TABLE "client_stats" ADD CONSTRAINT "client_stats_clientId_fkey" FOREIGN KEY ("clientId") REFERENCES "Clients"("id") ON DELETE RESTRICT ON UPDATE CASCADE;

-- AddForeignKey
ALTER TABLE "rooms" ADD CONSTRAINT "rooms_ownerid_fkey" FOREIGN KEY ("ownerid") REFERENCES "Clients"("id") ON DELETE RESTRICT ON UPDATE CASCADE;

-- AddForeignKey
ALTER TABLE "messages_rooms" ADD CONSTRAINT "messages_rooms_clientId_fkey" FOREIGN KEY ("clientId") REFERENCES "Clients"("id") ON DELETE RESTRICT ON UPDATE CASCADE;

-- AddForeignKey
ALTER TABLE "messages_rooms" ADD CONSTRAINT "messages_rooms_roomId_fkey" FOREIGN KEY ("roomId") REFERENCES "rooms"("id") ON DELETE RESTRICT ON UPDATE CASCADE;

-- AddForeignKey
ALTER TABLE "messages_client_to_client" ADD CONSTRAINT "messages_client_to_client_clientSrcId_fkey" FOREIGN KEY ("clientSrcId") REFERENCES "Clients"("id") ON DELETE RESTRICT ON UPDATE CASCADE;

-- AddForeignKey
ALTER TABLE "messages_client_to_client" ADD CONSTRAINT "messages_client_to_client_clientDestId_fkey" FOREIGN KEY ("clientDestId") REFERENCES "Clients"("id") ON DELETE RESTRICT ON UPDATE CASCADE;
