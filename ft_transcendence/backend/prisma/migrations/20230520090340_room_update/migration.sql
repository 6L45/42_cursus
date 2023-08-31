-- AlterTable
ALTER TABLE "rooms" ADD COLUMN     "client2Id" INTEGER;

-- AddForeignKey
ALTER TABLE "rooms" ADD CONSTRAINT "rooms_client2Id_fkey" FOREIGN KEY ("client2Id") REFERENCES "Clients"("id") ON DELETE SET NULL ON UPDATE CASCADE;
