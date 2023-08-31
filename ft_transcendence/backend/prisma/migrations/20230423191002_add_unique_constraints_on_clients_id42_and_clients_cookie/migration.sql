/*
  Warnings:

  - A unique constraint covering the columns `[id42]` on the table `Clients` will be added. If there are existing duplicate values, this will fail.
  - A unique constraint covering the columns `[cookie]` on the table `Clients` will be added. If there are existing duplicate values, this will fail.

*/
-- CreateIndex
CREATE UNIQUE INDEX "Clients_id42_key" ON "Clients"("id42");

-- CreateIndex
CREATE UNIQUE INDEX "Clients_cookie_key" ON "Clients"("cookie");
