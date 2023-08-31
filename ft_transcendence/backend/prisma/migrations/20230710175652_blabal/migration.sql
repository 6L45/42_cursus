-- DropIndex
DROP INDEX "Clients_cookie_key";

-- AlterTable
ALTER TABLE "Clients" ALTER COLUMN "cookie" SET DATA TYPE TEXT;
