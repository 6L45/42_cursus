/*
  Warnings:

  - A unique constraint covering the columns `[client1Id,client2Id]` on the table `clients_to_clients` will be added. If there are existing duplicate values, this will fail.

*/
-- CreateIndex
CREATE UNIQUE INDEX "clients_to_clients_client1Id_client2Id_key" ON "clients_to_clients"("client1Id", "client2Id");
