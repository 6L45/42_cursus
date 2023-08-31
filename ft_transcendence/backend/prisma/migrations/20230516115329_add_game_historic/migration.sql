-- CreateTable
CREATE TABLE "game_historic" (
    "id" SERIAL NOT NULL,
    "persScore" INTEGER NOT NULL,
    "vsScore" INTEGER NOT NULL,
    "client1Id" INTEGER NOT NULL,
    "client2Id" INTEGER NOT NULL,

    CONSTRAINT "game_historic_pkey" PRIMARY KEY ("id")
);

-- AddForeignKey
ALTER TABLE "game_historic" ADD CONSTRAINT "game_historic_client1Id_fkey" FOREIGN KEY ("client1Id") REFERENCES "Clients"("id") ON DELETE RESTRICT ON UPDATE CASCADE;

-- AddForeignKey
ALTER TABLE "game_historic" ADD CONSTRAINT "game_historic_client2Id_fkey" FOREIGN KEY ("client2Id") REFERENCES "Clients"("id") ON DELETE RESTRICT ON UPDATE CASCADE;
